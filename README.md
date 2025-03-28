## Execution

```bash
qemu-system-arm -machine stm32vldiscovery -display none -kernel main.elf -semihosting -semihosting-config enable=on,target=native -s -d cpu_reset
```

You can then connect to qemu with gdb:
```bash
gdb-multiarch main.elf -ex 'target extended-remote localhost:1234'
```