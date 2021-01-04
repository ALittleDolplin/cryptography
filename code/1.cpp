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
	cout << "��Կ��˽Կ������ϣ����У�" << endl;
	cout << "��Կn=" << n << endl;
	cout << "��Կb=" << b << endl;
	cout << "˽Կp=" << p << endl;
	cout << "˽Կq=" << q << endl;
	cout << "˽Կa=" << a << endl;
	long y=1;
	for (long i = 1; i <= a; i++)
	{
		y = (y*x) % n;
	}
	cout << "���ܺ����ϢyΪ��" << y << endl;
	long z = 1;
	for (long i = 1; i <= b; i++)
	{
		z = (z*y) % n;
	}
	cout << "���ܺ����ϢxΪ��" << x%n << endl;
	_getch();
	cout << "ver��x��y��=true�������֤�ɹ���" << endl;
}

void RSATest()
{
	cout << "������Ҫ���ܵ���Ϣ��������ʽ�����Ϊ10000��";
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