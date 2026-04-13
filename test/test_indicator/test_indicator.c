#include "unity.h"
#include "fff.h"
#include "indicators.h"

DEFINE_FFF_GLOBALS;

void setUp() {
    // RESET_FAKE(...);
    FFF_RESET_HISTORY();
}

int main() {
    UNITY_BEGIN();

    // RUN_TEST(...);

    return UNITY_END();
}
