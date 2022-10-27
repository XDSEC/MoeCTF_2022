# MoeCTF 2022 / 维吉尼亚

## 初见

~~看不懂，下一个~~

## 探索

直接用在线的维吉尼亚密码破解工具进行爆破

爆破得到密码`tfdvsjuz`

明文为

```
information security, sometimes shortened to infosec, is the practice of protecting information by mitigating information risks. it is part of information risk management. it typically involves preventing or reducing the probability of unauthorized/inappropriate access to data, or the unlawful use, disclosure, disruption, deletion, corruption, modification, inspection, recording, or devaluation of information. it also involves actions intended to reduce the adverse impacts of such incidents. protected information may take any form, e.g. electronic or physical, tangible (e.g. paperwork) or intangible (e.g. knowledge). information security's primary focus is the balanced protection of the confidentiality, integrity, and availability of data (also known as the cia triad) while maintaining a focus on efficient policy implementation, all without hampering organization productivity. this is largely achieved through a structured risk management process that involves:",
 '1. identifying information and related assets, plus potential threats, vulnerabilities, and impacts;',
 '2. evaluating the risks',
 '3. deciding how to address or treat the risks i.e. to avoid, mitigate, share or accept them',
 '4. where risk mitigation is required, selecting or designing appropriate security controls and implementing them',
 '5. monitoring the activities, making adjustments as necessary to address any issues, changes and improvement opportunities',
 "6. i won't tell you that the flag is moectf attacking the vigenere cipher is interesting",
 "to standardize this discipline, academics and professionals collaborate to offer guidance, policies, and industry standards on password, antivirus software, firewall, encryption software, legal liability, security awareness and training, and so forth. this standardization may be further driven by a wide variety of laws and regulations that affect how data is accessed, processed, stored, transferred and destroyed. however, the implementation of any standards and guidance within an entity may have limited effect if a culture of continual improvement isn't adopted.
```

然后你就看到flag了。什么你没看到？你不会Ctrl+F吗（