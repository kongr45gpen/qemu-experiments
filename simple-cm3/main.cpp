// #include <iostream>
#include <cstdio>

extern "C" void initialise_monitor_handles(void);

extern "C" int main() {
    initialise_monitor_handles();

    while (true) {
        printf("Hello, World!\n");
    }
}

extern "C" void SystemInit() {
}