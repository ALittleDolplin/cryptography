# cryptography
#**密码学作业**

1. 实现《密码学原理与实践》7.1节RSA签名方案，基于NTL库实现。其中素数p,q要求512比特。
***
2. 实现《密码学原理与实践》7.3节的Elgamal签名方案（密码体制7.2），基于NTL库实现。其中素数p取为1024比特。素数p和本原元α的生成过程：
   （a）产生素数p=rq+1，q为大素数，r是小的整数（以保证能对r有效分解）。使用NTL库的素性测试算法。
   （b）产生模p的本原元α：产生随机数α∈Z，根据费马小定理判断α是否为本原元。如果不是则产生其他随机数继续测试。
***
3. 实现《密码学原理与实践》9.3.1节的基本证书方案，包含证书颁发（协议9.5）和证书验证。  
    ·协议9.5的步骤1中对Alice的身份确定可忽略，ID（Alice）具体内容为Alice的姓名。  
    ·证书中使用的签名方案为RSA签名和Elgamal签名，两种方案都需要支持。  
    ·证书采用txt格式。  
***
4. 实现《密码学原理与实践》9.3.2节的协议9.6，其中签名方案为RSA或者Elgamal签名方案，且两种方案都需支持。注意协议9.6的签名方案和其中证书所用的签名方案是互相独立的。  
***
5. 实现《密码学原理与实践》11.3节的协议11.3.   
  （a）群G取为Z，p为1024位比特的素数，α为本原元，p和α的生成方法见2.  
  （b）用户T的公开值Bt包含在T的证书里作为T的公开验证秘钥，即Bt=Ver（t）  
  
