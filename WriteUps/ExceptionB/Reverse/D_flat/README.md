# MoeCTF 2022 / D_flat

## 初见

打开压缩包，看到了一些文件

- D_flat.runtimeconfig.json
- D_flat.deps.json
- D_flat.dll
- D_flat.exe
- D_flat.pdb

我就有了十成甚至九成的把握，这应该是个 ~~秒杀题~~ ***C#***写的程序 ~~C#我可熟了，比别的java c/c++什么的熟多了~~

而C#写的程序，放在逆向的话......

话不多说，直接上dnSpy

## 秒杀

但是这里要注意一下，因为这个目录结构，这应该不是.Net Framework的程序，而是.Net Core / .Net 5+的程序

**所以应该对 `D_flat.dll` 进行反编译！**

反编译后，得到`D_flate.Main()`的代码

```C#
using System;
using System.Text;

// Token: 0x02000002 RID: 2
internal class D_flate
{
	// Token: 0x06000001 RID: 1 RVA: 0x00002050 File Offset: 0x00000250
	private static void Main()
	{
		int num = 0;
		int[] array = new int[]
		{
			109,111,101,99,116,102,123,68,95,102,108,97,116,101,95,105,115,95,67,95,115,104,97,114,112,33,125
		};
		Console.WriteLine("In music theory, there is a note that has the same pitch as D flat.");
		Console.WriteLine("Do you know it?\nNow plz input your flag:");
		string text = Console.ReadLine();
		byte[] bytes = Encoding.ASCII.GetBytes(text);
		for (int i = 0; i < text.Length; i++)
		{
			if (array[i] == (int)bytes[i])
			{
				num++;
			}
		}
		if (num == array.Length)
		{
			Console.WriteLine("TTTTTQQQQQQLLLLLLL!!! This is your flag!");
			return;
		}
		Console.WriteLine("QwQ, plz try again.");
	}
}
```

**好的，flag已经甩到你的脸上了**

如果没看出来的话，那稍微进行一下解释

ReadLine读了输入的flag并用ASCII编码成bytes，然后再与array中的数字逐一比较，完全一致则输出tql

所以array就是flag啊，你把他转成bytes然后decode啊（

出题人甚至都没用加密，他真的我哭死