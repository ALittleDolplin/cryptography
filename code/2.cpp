#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<cmath>
#include<conio.h>
#include< stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string>
#include <vector>
using namespace std;


bool check(long a, long b)
{
	long i;
	for (i = a; 0 != i%b; i += a);
	if (i == a*b)
		return true;
	else
		return false;
}

long phi(long v)
{
	int count = 0;
	for (long i = 1; i <= v; i++)
	{
		if (check(v, i))
		{
			count++;
		}
	}
	return count;
}

long byy(long v)
{
	long benyuanyuan;
	long ph = phi(v);
	for (long i = 1; i<v; i++)
	{
		long a = 1;
		long j;
		for (j = 0; j<ph; j++)
		{
			a = a*i%v;
			if (a == 1)
			{
				j++;
				break;
			}
		}
		if (j == ph && a == 1)
			return i;
	}

	return -1;
}


bool IsPrime(int n)
{
	long i, j;
	for (i = 2, j = int(sqrt(n)); i <= j; i++)
		if (n%i == 0)  return false;
	return true;
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
			if ((x + P / gcd*t) <= 0) 
				return x;
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



void ElGamal(long x)
{
	srand((unsigned)time(NULL));
	long min = 100, max = 100;
	long r=1, q=1, p=1;
	while (1)
	{
		while (q <= min || !IsPrime(q))
		{
			q = min + rand() % max;
		}
		r = 1 + rand() % 10;
		p = r*q + 1;
		if (IsPrime(p))
			break;
	}
	long aef = byy(p);
	long a= min + rand() % max;
	long bt = 1;
	for (long i = 1; i <= a; i++)
		bt = (bt*aef) % p;
	long k = 1 + rand() % (p - 2);
	if (1)
	{
		p = 467; aef = 2; a = 127; bt = 132; k = 213;
	}
	cout << "公钥，私钥生成完毕，其中：" << endl;
	cout << "公钥p=" << p << endl;
	cout << "公钥α=" << aef << endl;
	cout << "公钥β=" << bt << endl;
	cout << "私钥a=" << a << endl;
	cout << "选取随机数k=" << k << endl;
	long _k = niyuan(k, p - 1);
	cout << "k的逆元为：" << _k << endl;
	long gm = 1, dt = 1;
	for (long i = 1; i <= k; i++)
	{
		gm = (gm*aef) % p;
	}
	dt= ((x - a*gm)*_k) % (p - 1);
	while (dt < 0)
		dt += p - 1;
	cout << "加密后的签名为：" << endl;
	cout << "γ=" << gm << endl;
	cout << "δ=" << dt << endl;
	cout << "验证签名：" << endl;
	long s1=1, s2=1, s3=1;
	for (long i = 1; i <= gm; i++)
	{
		s1 = (s1*bt) % p;
		while (s1 <= 0)
			s1 += p;
	}
	for (long i = 1; i <= dt; i++)
	{
		s2 = (s2*gm) % p;
		while (s2 <= 0)
			s2 += p;
	}
	for (long i = 1; i <= x; i++)
	{
		s3 = (s3*aef) % p;
		while (s3 <= 0)
			s3 += p;
	}
	long s4;
	if (1)
	{
		s4 = s1*s2;
		while (s4 < 0)
			s4 += p;
		while (s4 >= p)
			s4 -= p;
	}
	cout << "s3=" << s3 << endl;
	cout << "s4=" << s4 << endl;
	if (s4 == s3)
		cout << "二者相等，验证成功" << endl;
	else
		cout << "二者不等，验证失败" << endl;
	
}

void ElGamalTest()
{
	cout << "请输入签名(数字形式,最大为100000)：";
	long x;
	cin >> x;
	ElGamal(x);
}

int main()
{
		ElGamalTest();

	return 0;
}