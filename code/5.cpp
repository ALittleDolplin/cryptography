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



void GetKey(long &p, long &aef)
{
	srand((unsigned)time(NULL));
	long min = 100, max = 100;
	long r = 1, q = 1;
	p = 1;
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
	aef = byy(p);
}

void MTIA0()
{
	srand((unsigned)time(NULL));
	long p, aef;
	GetKey(p, aef);
	cout << "生成群，本原元，秘密指数和公开值：" << endl;
	cout << "p=" << p << endl;
	cout << "α=" << aef << endl;
	long av, bv = 1, au, bu = 1;
	av = rand() % (p - 2);
	for (long i = 1; i <= av; i++)
	{
		bv = (bv*aef) % (p - 1);
	}
	getchar();
	au = rand() % (p - 2);
	for (long i = 1; i <= au; i++)
	{
		bu = (bu*aef) % (p - 1);
	}
	cout << "U的秘密指数au为" << au << endl;
	cout << "U的公开指数bu为" << bu << endl;
	cout << "V的秘密指数au为" << av << endl;
	cout << "V的公开指数bu为" << bv << endl;
	getchar();
	long ru, rv, su=1, sv=1;
	cout << "U选取ru,并将ru和U的证书一起发送给V（这里为了方便，直接将vert代替证书发送给V）" << endl;
	ru = rand() % (p - 2);
	for (int i = 1; i <= ru; i++)
	{
		su = (su*aef) % (p - 1);
	}
	getchar();
	cout << "V选取rv,并将rv和V的证书一起发送给U（这里为了方便，直接将vert代替证书发送给U）" << endl;
	getchar();
	rv = rand() % (p - 2);
	for (int i = 1; i <= rv; i++)
	{
		sv = (sv*aef) % (p - 1);
	}

	long k1, k2;
	long x1 = 1, x2 = 1, y1 = 1, y2 = 1;
	for (long i = 1; i <= av; i++)
		x1 = (x1*su) % (p - 1);
	for (long i = 1; i <= rv; i++)
		x2 = (x2*bu) % (p - 1);
	k1 = x1*x2;
	for (long i = 1; i <= au; i++)
		y1 = (y1*sv) % (p - 1);
	for (long i = 1; i <= ru; i++)
		y2 = (y2*bv) % (p - 1);
	k2 = y1*y2;

	cout << "V计算出的密钥K，结果为：" << k1 << endl;
	cout << "U计算出的密钥K，结果为：" << k2 << endl;
	cout << "二者相等，密钥协商完成" << endl;
	
}


int main()
{
		MTIA0();

	return 0;
}