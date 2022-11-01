from pwn import *
from hashlib import sha256
HOST, PORT = 'polarnova.top', 10002
sh=remote(HOST, PORT)

table = string.ascii_letters+string.digits

def proof_of_work(s,tsha):
    for i in table:
        for j in table:
            for k in table:
                for l in table:
                    proof=i+j+k+l+s
                    if(sha256(proof.encode()).hexdigest()==tsha):
                        sh.sendline((i+j+k+l).encode())
                        return

pres=sh.recvuntil(b'sha256(XXXX+',drop=True)
s=sh.recvuntil(b') == ',drop=True).decode()
tsha=sh.recvuntil(b'\n',drop=True).decode()

proof_of_work(s,tsha)
pres=sh.recvuntil(b'message1 = ',drop=True)
msg=sh.recvuntil(b'\n',drop=True)
forge_msg = msg[32:48] + msg[16:32] + msg[:16] + msg[48:]
sh.sendline(forge_msg)
sh.interactive()