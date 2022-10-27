# MoeCTF 2022 / 

// TODO

## 初见

鉴定为，汉明码，建议看[3Blue1Brown的视频](https://youtu.be/X8jsijhllIA)

看完就会做

```python
def hamming_correct(bitblock):
    flag_ = 0
    for x in range(16):
        if bitblock[x] == 1:
            flag_ ^=x
    return flag_
```
    