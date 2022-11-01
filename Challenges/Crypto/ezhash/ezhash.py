from hashlib import md5,sha256
from secret import flag
import socketserver
import random
import signal
import string 

msg = b'c4n_y0u_g1v3_m3_@_string_w1th_th3_same_h4sh_a5_th1s_m3ss4ge?1f_u_g1ve_m3_i_wi11_giv3_y$u_@_flag!'

def pad(m):
    return m + bytes([64-len(m)%64 for _ in range(64-len(m)%64)])

def F(x,y,z):#Don't get confused by magic bit operations! Take it easy!
    return (x * y * z) & 0xffffffffffffffffffffffffffffffff

def R(x,y,z,t):#wow, interesting!
    return (x ^ y ^ z ^ t ^ F(y,z,t) ^ F(z,t,x) ^ F(t,x,y)) & 0xffffffffffffffffffffffffffffffff

def hash(m:bytes) -> str:#Seems too complex? Take it easy!
    m = pad(m)
    H = b""
    for _ in range(len(m)//64):
        round_m = m[_*64:_*64+64]
        a,b,c,d =   int.from_bytes(round_m[:16],byteorder='little'),int.from_bytes(round_m[16:16*2],byteorder='little'),\
                    int.from_bytes(round_m[16*2:16*3],byteorder='little'),int.from_bytes(round_m[16*3:16*4],byteorder='little')
        tmpH = hex(R(a,b,c,d))[2:].rjust(8,'0').encode()
        H = md5(H + tmpH).hexdigest().encode()# Actually, How many iterations?
    return H.decode()

class Task(socketserver.BaseRequestHandler):
    #--------These are just the server's transceiver functions and are not important------
    def _recvall(self):
        BUFF_SIZE = 2048
        data = b''
        while True:
            part = self.request.recv(BUFF_SIZE)
            data += part
            if len(part) < BUFF_SIZE:
                break
        return data.strip()

    def send(self, msg, newline=True):
        try:
            if newline:
                msg += b'\n'
            self.request.sendall(msg)
        except:
            pass

    def recv(self, prompt=b' '):
        self.send(prompt, newline=False)
        return self._recvall()
    #--------Above are just the server's transceiver functions and are not important------

    def proof_of_work(self):
        table = string.ascii_letters+string.digits
        proof = (''.join([random.choice(table)for _ in range(20)])).encode()
        sha = sha256(proof).hexdigest().encode()
        self.send(b"[+] sha256(XXXX+" + proof[4:] + b") == " + sha )
        XXXX = self.recv(prompt = b'[+] Plz Tell Me XXXX :')
        if len(XXXX) != 4 or sha256(XXXX + proof[4:]).hexdigest().encode() != sha:
            return False
        return True

    def handle(self):# main
        signal.alarm(300)#you have 300s to interactive

        self.send(b"Welcome to ezhash! You need to complete the Proof of work first!")
        proof = self.proof_of_work()
        if not proof:
            self.request.close()
        
        #get hash(msg1)
        Hash_nonce = hash(msg)
        self.send(b"Well done! Your challange is to find a collision of given hash.")
        self.send(b"message1 = "+msg)
        self.send(f"Hash(message1) = {Hash_nonce}".encode())

        #get hash(msg2)
        yourmsg=self.recv(b"Tell me message2 = ")
        your_hash=hash(yourmsg)
        self.send(f"Ok, Hash(message2) = {your_hash}".encode())

        if(msg!=yourmsg):#judge
            if(your_hash==Hash_nonce):
                self.send(f"Well done! your flag is {flag}".encode())
            else:
                self.send(b"Not Yet! Try again!")
        else:
            self.send(b"Same message! Try again!")


class ThreadedServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    pass

class ForkedServer(socketserver.ForkingMixIn, socketserver.TCPServer):
    pass

if __name__ == "__main__":
    HOST, PORT = '0.0.0.0', 10002
    server = ForkedServer((HOST, PORT), Task)
    server.allow_reuse_address = True
    print(HOST, PORT)
    server.serve_forever()

