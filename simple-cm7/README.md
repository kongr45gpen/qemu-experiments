## Execution instructions

```bash
cmake -B build
cmake --build build -j8
~/qemu/build/qemu-system-arm -machine mps2-an500 -display none -kernel build/main.elf -semihosting -semihosting-config enable=on,target=native -s -d cpu_reset
```