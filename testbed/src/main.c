#include <core/logger/logger.h>

// TODO: Remove Later
#include <platform/platform.h>

int main(void) {
    // Test Logging
    KFATAL("A test message: %f", 3.14f);
    KERROR("A test message: %f", 3.14f);
    KWARN("A test message: %f", 3.14f);
    KINFO("A test message: %f", 3.14f);
    KDEBUG("A test message: %f", 3.14f);
    KTRACE("A test message: %f", 3.14f);

    platform_state state;
    if(platform_startup(&state, "Krash Engine Testbed", 100, 100, 780, 480)) {
        while(TRUE) {
            platform_pump_messages(&state);
        }
    }
    platform_shutdown(&state);

    return 0;
}