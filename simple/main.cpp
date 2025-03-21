// #include <iostream>
#include <cstdio>

using namespace std;

extern void initialise_monitor_handles(void);

extern "C" int main() {
    volatile int i = 99;
    while (true) {
        i += 1;
        // printf("Hello, World!\n");
    }
}


extern "C" void SystemInit() {
    // initialise_monitor_handles();
    // main();
    while (true) {}
}