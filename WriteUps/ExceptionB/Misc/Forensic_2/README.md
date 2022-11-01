# MoeCTF 2022 / 好像有一点难的取证

## 初见

~~捏猫猫的，怎么是百度网盘~~ 后续添加了校内的下载通道

## 探索

FTK Image挂载，然后用DiskGenius查看刚刚挂载的虚拟磁盘

发现，有一个分区正常，另外一个被BitLocker加密了，可以看到分区的Identifier，复制备用

附件中还有一个内存镜像，用hex编辑器打开

搜索`BitLocker Drive Encryption recovery key`，对比Identifier，顺利找到Recovery Key

把Recovery Key丢到DiskGenius，成功解密分区，在根目录中找到flag

## 反思

我就不应该想着挂虚拟机，浪费时间！！！