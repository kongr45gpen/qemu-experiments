// #include <iostream>
#include <cstdio>
#include "libs.h"

extern "C" void initialise_monitor_handles(void);

extern "C" int main() {
    initialise_monitor_handles();

    int i = 0;

    volatile char string[] = "Hello, world!";

    while (true) {
        printf("[%05ld] [%08X] %s\n", GetMs(), (unsigned int) string, string);
        Sleepms(500);
    }


}

extern "C" void SystemInit() {
}

extern "C" void SystemCoreClockUpdate () {
}