def rol(x):
    return ((x >> 3) | (x << 5)) & 0xff

enc = [233, 184, 152, 112, 248, 104, 137, 129, 168, 41, 136, 96, 82, 153, 217, 2, 217, 114, 28, 184]
key = 'Python'
flag = ''

for i in range(len(enc)):
    enc[i] = rol(enc[i])
    enc[i] -= i
    enc[i] ^= ord(key[i % len(key)])

for i in enc:
    flag += chr(i)

print(flag)