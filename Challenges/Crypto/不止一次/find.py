import os

flag = 'moectf{Ma2y_T1m3_9ad_8an_6e_crac7ed}'

while True:
    os.system('python many-time-pad.py')
    with open('key.txt','r') as f:
        key = f.readline()
    if key == flag:
        break
    os.system('python generate.py')