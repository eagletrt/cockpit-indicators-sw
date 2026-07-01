"""
Sends HV_BMS_STATUS, HV_BMS_FEEDBACK_STATUS, HV_BMS_IMD every 100ms on Linux
socketcan. Values are editable live via single-keypress hotkeys (raw terminal
mode).

Setup interfaccia (una volta, richiede privilegi):
    sudo ip link set can0 up type can bitrate 1000000
    # oppure per test senza hardware:
    sudo modprobe vcan
    sudo ip link add dev vcan0 type vcan
    sudo ip link set vcan0 up

Run:
    python3 hv_bms_sender.py --channel can0
    python3 hv_bms_sender.py --channel vcan0   # test senza hardware
    python3 hv_bms_sender.py --dry-run         # nessun bus, solo stampa

Quit: 'x' o Ctrl-C
"""

import sys
import time
import threading
import argparse
import cantools
import can

DBC_PATH = '.pio/libdeps/release/libcan-sw/dbc/primary/primary.dbc'
PERIOD_S = 0.1  # 100ms

# ---------------------------------------------------------------------------
# CLI args (socketcan channel is a Linux interface name, not a USB device)
# ---------------------------------------------------------------------------

parser = argparse.ArgumentParser()
parser.add_argument('--channel', default='can0', help="socketcan interface, e.g. can0, vcan0")
parser.add_argument('--dbc', default=DBC_PATH)
parser.add_argument('--dry-run', action='store_true', help="don't open the bus, just print")
args = parser.parse_args()

# ---------------------------------------------------------------------------
# DBC / bus setup
# ---------------------------------------------------------------------------

db = cantools.database.load_file(args.dbc)

msg_bms = db.get_message_by_name('HV_BMS_STATUS')
msg_fb = db.get_message_by_name('HV_BMS_FEEDBACK_STATUS')
msg_imd = db.get_message_by_name('HV_BMS_IMD')

# enum cycles, derived straight from the DBC so this never drifts out of sync
BMS_STATES = list(msg_bms.get_signal_by_name('name').choices.values())
IMD_STATES = list(msg_imd.get_signal_by_name('status').choices.values())
TRISTATE = ['LOW', 'ERROR', 'HIGH']  # every HV_BMS_FEEDBACK_STATUS signal uses this
FB_SIGNAL_NAMES = [s.name for s in msg_fb.signals]

if args.dry_run:
    print("!! --dry-run: bus not opened, just printing.")
    bus = None
else:
    try:
        # socketcan does not set bitrate here — that's configured once at the OS level:
        #   sudo ip link set can0 up type can bitrate 1000000
        bus = can.Bus(interface='socketcan', channel=args.channel, receive_own_messages=False)
    except OSError as e:
        print(f"!! could not open socketcan interface '{args.channel}' ({e})")
        print(f"   check it's up: ip link show {args.channel} / "
              f"`sudo ip link set {args.channel} up type can bitrate 1000000`")
        print("   falling back to DRY-RUN mode.")
        bus = None

# ---------------------------------------------------------------------------
# Shared mutable state (edited by the key-listener thread, read by the sender)
# ---------------------------------------------------------------------------

state_lock = threading.Lock()

state = {
    'bms_status': BMS_STATES[0],                     # 'INIT'
    'imd': {
        'status': IMD_STATES[1],                      # 'NORMAL'
        'frequency_Hz': 0.0,
        'dutyCycle_pct': 0.0,
        'details': 0,
        'fault_bool': 0,
        'period_ms': 0,
    },
    'feedback': {name: 'LOW' for name in FB_SIGNAL_NAMES},
}

running = True


def cycle(values, current):
    idx = values.index(current)
    return values[(idx + 1) % len(values)]


# ---------------------------------------------------------------------------
# Sender thread — fires all three messages every PERIOD_S regardless of
# what the key-listener thread is doing.
# ---------------------------------------------------------------------------

def sender_loop():
    next_tick = time.monotonic()
    while running:
        with state_lock:
            bms_payload = {'name': state['bms_status']}
            imd_payload = dict(state['imd'])
            fb_payload = dict(state['feedback'])
    try:
        data_bms = msg_bms.encode(bms_payload)
        data_imd = msg_imd.encode(imd_payload)
        data_fb = msg_fb.encode(fb_payload)

        if bus is not None:
            bus.send(can.Message(arbitration_id=msg_bms.frame_id, data=data_bms,
                                  is_extended_id=msg_bms.is_extended_frame))
            bus.send(can.Message(arbitration_id=msg_imd.frame_id, data=data_imd,
                                  is_extended_id=msg_imd.is_extended_frame))
            bus.send(can.Message(arbitration_id=msg_fb.frame_id, data=data_fb,
                                  is_extended_id=msg_fb.is_extended_frame))
    except Exception as e:
        print(f"\n[encode/send error] {e}")

        next_tick += PERIOD_S
        sleep_for = next_tick - time.monotonic()
        if sleep_for > 0:
            time.sleep(sleep_for)
        else:
            next_tick = time.monotonic()  # fell behind, resync


# ---------------------------------------------------------------------------
# Status line
# ---------------------------------------------------------------------------

def print_status():
    with state_lock:
        b = state['bms_status']
        i = state['imd']
        n_hot = sum(1 for v in state['feedback'].values() if v != 'LOW')
    sys.stdout.write(
        f"\rBMS={str(b):<16} IMD={str(i['status']):<14} freq={i['frequency_Hz']:>5.1f}Hz "
        f"duty={i['dutyCycle_pct']:.2f} fault={i['fault_bool']} period={i['period_ms']}ms  "
        f"FEEDBACK[non-LOW]={n_hot:2d}/20     "
    )
    sys.stdout.flush()


# ---------------------------------------------------------------------------
# Key listener — raw single-char mode on Unix. Falls back to line-buffered
# input() on platforms without termios (Windows).
# ---------------------------------------------------------------------------

HELP = """
Hotkeys:
  1        cycle HV_BMS_STATUS.name          (INIT -> IDLE -> ... -> TS_ON)
  2        cycle HV_BMS_IMD.status           (SHORT_CIRCUIT -> NORMAL -> ...)
  3 / 4    IMD frequency_Hz  -5 / +5   (clamped 0-60)
  5 / 6    IMD dutyCycle_pct -0.1 / +0.1 (clamped 0-1)
  7        toggle IMD fault_bool
  8 / 9    IMD period_ms  -10 / +10 (clamped 0-255)
  f        cycle a named HV_BMS_FEEDBACK_STATUS signal (prompts for name)
  l        list all HV_BMS_FEEDBACK_STATUS signal names
  0        reset all feedback signals to LOW
  h        show this help
  p        print full state dump
  x        quit
"""


def get_key_unix():
    import termios
    import tty
    fd = sys.stdin.fileno()
    old = termios.tcgetattr(fd)
    try:
        tty.setraw(fd)
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old)
    return ch


def handle_key(k):
    global running
    with state_lock:
        if k == '1':
            state['bms_status'] = cycle(BMS_STATES, state['bms_status'])
        elif k == '2':
            state['imd']['status'] = cycle(IMD_STATES, state['imd']['status'])
        elif k == '3':
            state['imd']['frequency_Hz'] = max(0.0, state['imd']['frequency_Hz'] - 5)
        elif k == '4':
            state['imd']['frequency_Hz'] = min(60.0, state['imd']['frequency_Hz'] + 5)
        elif k == '5':
            state['imd']['dutyCycle_pct'] = round(max(0.0, state['imd']['dutyCycle_pct'] - 0.1), 2)
        elif k == '6':
            state['imd']['dutyCycle_pct'] = round(min(1.0, state['imd']['dutyCycle_pct'] + 0.1), 2)
        elif k == '7':
            state['imd']['fault_bool'] = 0 if state['imd']['fault_bool'] else 1
        elif k == '8':
            state['imd']['period_ms'] = max(0, state['imd']['period_ms'] - 10)
        elif k == '9':
            state['imd']['period_ms'] = min(255, state['imd']['period_ms'] + 10)
        elif k == '0':
            for name in FB_SIGNAL_NAMES:
                state['feedback'][name] = 'LOW'
    if k == 'f':
        sig = input("\nfeedback signal name to cycle: ").strip()
        with state_lock:
            if sig in state['feedback']:
                state['feedback'][sig] = cycle(TRISTATE, state['feedback'][sig])
            else:
                print(f"unknown signal '{sig}' — press 'l' to list valid names")
    elif k == 'l':
        print("\n" + ", ".join(FB_SIGNAL_NAMES))
    elif k == 'h':
        print(HELP)
    elif k == 'p':
        with state_lock:
            print(f"\n{state}")
    elif k in ('x', '\x03'):  # x or Ctrl-C
        running = False


def key_loop():
    use_raw = sys.stdin.isatty() and hasattr(sys, 'ps1') is False
    try:
        import termios  # noqa: F401
        raw_available = True
    except ImportError:
        raw_available = False

    print(HELP)
    while running:
        if raw_available and use_raw:
            k = get_key_unix()
        else:
            k = input("key> ").strip()[:1]
            if not k:
                continue
        handle_key(k)
        print_status()


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

if __name__ == '__main__':
    t = threading.Thread(target=sender_loop, daemon=True)
    t.start()
    try:
        key_loop()
    except KeyboardInterrupt:
        pass
    finally:
        running = False
        time.sleep(PERIOD_S * 2)
        if bus is not None:
            bus.shutdown()
        print("\nStopped.")
