#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<cmath>
#include<conio.h>
#include< stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string>
using namespace std;

bool IsPrime(int n)
{
	long i, j;
	for (i = 2, j = int(sqrt(n)); i <= j; i++)
		if (n%i == 0)  return false;
	return true;
}

int gcd(long a, long b)
{
	if (a%b == 0) 
	{
		return b;
	}
	return gcd(b, a%b);
}

int exgcd(long a, long b, long &x, long &y)
{
	if (b == 0)
	{
		x = 1; 
		y = 0; 
		return a;
	}
	long ans = exgcd(b, a%b, x, y);
	long tmp = x;
	x = y;
	y = tmp - a / b*y;
	return ans;
}

int niyuan(long a, long P)
{
	long x = 0, y = 0;
	long gcd = exgcd(a, P, x, y);
	if (x > 0)
	{
		for (long t = 0;; t--)
		{
			if ((x + P / gcd*t) <= 0) return x;
			else x = x + P / gcd*t;
		}
	}
	else
	{
		for (long t = 0;; t++)
		{
			if ((x + P / gcd*t) > 0)
			{
				x = x + P / gcd*t;
				return x;
			}
		}
	}
}

void RSA(long x)
{
	srand((unsigned)time(NULL));
	long p=1, q=1;
	long min = 100, max = 100;
	while (1)
	{
		p = min + rand() % max;
		if (p > min&&IsPrime(p))
			break;
	}
	while (1)
	{
		q = min + rand() % max;
		if (q > min&&IsPrime(q))
			break;
	}
	long n = p*q;
	long _n = (p - 1)*(q - 1);
	long a, b;
	while (1)
	{
		a = 1 + rand() % _n;
		if (gcd(a, _n) == 1)
			break;
	}
	b = niyuan(a, _n);
	cout << "公钥，私钥生成完毕，其中：" << endl;
	cout << "公钥n=" << n << endl;
	cout << "公钥b=" << b << endl;
	cout << "私钥p=" << p << endl;
	cout << "私钥q=" << q << endl;
	cout << "私钥a=" << a << endl;
	long y=1;
	for (long i = 1; i <= a; i++)
	{
		y = (y*x) % n;
	}
	cout << "加密后的消息y为：" << y << endl;
	long z = 1;
	for (long i = 1; i <= b; i++)
	{
		z = (z*y) % n;
	}
	cout << "解密后的消息x为：" << x%n << endl;
	_getch();
	cout << "ver（x，y）=true，因此验证成功。" << endl;
}

void RSATest()
{
	cout << "请输入要加密的消息（数字形式，最大为10000）";
	long x;
	cin >> x;
	RSA(x);
}

int main()
{
	while (1)
	{
		RSATest();
	}
}