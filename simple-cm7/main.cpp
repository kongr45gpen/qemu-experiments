// #include <iostream>
#include <cstdio>
#include "libs.h"

extern "C" void initialise_monitor_handles(void);

extern "C" int main() {
    initialise_monitor_handles();

    int i = 0;

    while (true) {
        printf("[%05ld] Hello, World!\n", GetMs());
        Sleepms(500);
    }


}

extern "C" void SystemInit() {
}

extern "C" void SystemCoreClockUpdate () {
}