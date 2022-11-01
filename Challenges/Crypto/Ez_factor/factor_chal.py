from Crypto.Util.number import isPrime,getPrime,bytes_to_long
import socketserver
import random
import signal
from static_secret import flag,P #static means ... ?

class Task(socketserver.BaseRequestHandler):
    def _recvall(self):
        #These are just the server's transceiver functions and are not important
        BUFF_SIZE = 2048
        data = b''
        while True:
            part = self.request.recv(BUFF_SIZE)
            data += part
            if len(part) < BUFF_SIZE:
                break
        return data.strip()

    def send(self, msg, newline=True):
        #These are just the server's transceiver functions and are not important
        try:
            if newline:
                msg += b'\n'
            self.request.sendall(msg)
        except:
            pass

    def recv(self, prompt=b'[-] '):
        #These are just the server's transceiver functions and are not important
        self.send(prompt, newline=False)
        return self._recvall()

    def Goldbach_proof_of_work(self,BITS):
        bigeven=str(random.randint(1<<BITS,1<<(BITS+1))<<1)
        self.send(f"[+] I have two prime number A,B s.t. A>=B and A+B == {bigeven}".encode())
        p = int(self.recv(prompt=b'[+] Plz tell me A=').decode())
        q = int(self.recv(prompt=b'[+] Plz tell me B=').decode())
        if not (isPrime(p) and isPrime(q) and p+q==int(bigeven) and p>=q):
            return False
        return True

    def handle(self):#main
        signal.alarm(120)
        if not self.Goldbach_proof_of_work(100):
            self.send(b'[!] Wrong! Try again!')
            return
        Q=getPrime(2048)
        N=P*Q
        e=0x10001
        m=pow(bytes_to_long(flag),e,N)
        self.send(b"[+] Good job! Here's the encrypted flag for you:")
        self.send(f"m={hex(m)}".encode())
        self.send(f"N={hex(N)}".encode())
        self.send(b"[+] Have a Nice Day~ Bye!")        

class ThreadedServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    pass

class ForkedServer(socketserver.ForkingMixIn, socketserver.TCPServer):
    pass

if __name__ == "__main__":
    HOST, PORT = '0.0.0.0', 10001
    server = ForkedServer((HOST, PORT), Task)
    server.allow_reuse_address = True
    print(HOST, PORT)
    server.serve_forever()
