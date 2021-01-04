#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<cmath>
#include<conio.h>
#include< stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string>
#include<fstream>
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

void RSAKey(long &p, long &q, long &n, long &a, long &b)
{
	srand((unsigned)time(NULL));
	p = 1, q = 1;
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
	n = p*q;
	long _n = (p - 1)*(q - 1);
	while (1)
	{
		a = 1 + rand() % _n;
		if (gcd(a, _n) == 1)
			break;
	}
	b = niyuan(a, _n);
}

void RASEncrypt(const long x,long &y,long a,long n)
{
	y = 1;
	for (long i = 1; i <= a; i++)
	{
		y = (y*x) % n;
	}
}

bool RSAVerify(long s, long x, long b, long n)
{
	long yy=1;
	for (long i = 1; i <= b; i++)
		yy = (yy*s) % n;
	if (yy = x)
		return true;
	else
		return false;
}

void RSACert()
{
	ofstream fout;
	fout.open("RSACert.txt", ios::out);
	if (!fout.is_open())
	{
		cout << "���ļ�ʧ��" << endl;
		exit(-1);
	}

	cout << "��Aliceͨ��MD5����SHA�㷨���в���,����Ϊ�򵥱仯" << endl;
	getchar();
	long p, q, n, a, b;
	cout << "ȷ��Alice�Ĺ�Կ����Կ" << endl;
	RSAKey(p, q, n, a, b);
	cout << "��Կ��˽Կ������ϣ����У�" << endl;
	cout << "��Կn=" << n << endl;
	cout << "��Կb=" << b << endl;
	cout << "˽Կp=" << p << endl;
	cout << "˽Կq=" << q << endl;
	cout << "˽Կa=" << a << endl;
	getchar();
	long pp, qq, nn, aa, bb;
	cout << "ȷ��TA�Ĺ�Կ����Կ" << endl;
	RSAKey(pp, qq, nn, aa, bb);
	cout << "��Կn=" << nn << endl;
	cout << "��Կb=" << bb << endl;
	cout << "˽Կp=" << pp << endl;
	cout << "˽Կq=" << qq << endl;
	cout << "˽Կa=" << aa << endl;
	long s;
	getchar();
	cout << "TA������Alice��ݱ�ʶ����֤��Կ��ǩ��" << endl;
	long x = 30 + n + b;
	RASEncrypt(x, s, aa, nn);
	cout << "�䷢֤��:" << endl;
	fout << "Alice" << ' ' << n << ' ' << b << ' ' << s << endl;
	getchar();
	cout << "Bob��֤֤�飺" << endl;
	getchar();
	bool t = RSAVerify(s, x, b, n);
	if (t)
		cout << "Bob����" << endl;
	else
		cout << "Bob�ܾ�" << endl;

}

void ElGamalKey(long &r, long &p, long&q, long &aef, long &a, long &bt, long &k, long &_k)
{
	srand((unsigned)time(NULL));
	long min = 100, max = 100;
	r = 1;
	p = 1;
	q = 1;
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
	a = min + rand() % max;
	bt = 1;
	for (long i = 1; i <= a; i++)
		bt = (bt*aef) % p;
	k = 1 + rand() % (p - 2);
	if (0)
	{
		p = 467; aef = 2; a = 127; bt = 132; k = 213;
	}
	_k = niyuan(k, p - 1);
}

void ElGamalEncrypt(const long &x, long &s1, long &s2,long p,long aef, long a, long bt, long k,long _k)
{
	s1 = 1;
	for (long i = 1; i <= k; i++)
	{
		s1 = (s1*aef) % p;
	}

	s2 = ((x - a*s1)*_k) % (p - 1);
	while (s2 < 0)
		s2 += p - 1;
}

bool ElGamalVerify(long x, long p, long aef, long bt,long gm, long dt)
{
	long y1 = 1, y2 = 1, y3 = 1, y4 = 1;
	for (long i = 1; i <= gm; i++)
		y1 = (y1*bt) % p;
	for (long i = 1; i <= dt; i++)
		y2 = (y2*gm) % p;
	for (long i = 1; i <= x; i++)
		y3 = (y3*aef) % p;
	y4 = (y1*y2) % p;
	if (y3 = y4)
		return true;
	else
		return false;
}

void ElGamalCert()
{
	ofstream fout;
	fout.open("ElGamalCert.txt", ios::out);
	if (!fout.is_open())
	{
		cout << "���ļ�ʧ��" << endl;
		exit(-1);
	}

	cout << "��Aliceͨ��MD5����SHA�㷨���в���,����Ϊ�򵥱仯" << endl;
	getchar();
	long r, p, q, aef, a, bt, k, _k;
	ElGamalKey(r, p, q, aef, a, bt, k, _k);
	cout << "ȷ��Alice�Ĺ�Կ����Կ" << endl;
	getchar();
	cout << "��Կ��˽Կ������ϣ����У�" << endl;
	cout << "��Կp=" << p << endl;
	cout << "��Կ��=" << aef << endl;
	cout << "��Կ��=" << bt << endl;
	cout << "˽Կa=" << a << endl;
	cout << "ѡȡ�����k=" << k << endl;
	cout << "k����ԪΪ��" << _k << endl;
	getchar();
	long rr, pp, qq, aaef, aa, bbt, kk, _kk;
	ElGamalKey(rr, pp, qq, aaef, aa, bbt, kk, _kk);
	cout << "ȷ��TA�Ĺ�Կ����Կ" << endl;
	cout << "��Կ��˽Կ������ϣ����У�" << endl;
	cout << "��Կp=" << pp << endl;
	cout << "��Կ��=" << aaef << endl;
	cout << "��Կ��=" << bbt << endl;
	cout << "˽Կa=" << aa << endl;
	cout << "ѡȡ�����k=" << kk << endl;
	cout << "k����ԪΪ��" << _kk << endl;
	getchar();
	long x = 30 + a;
	long s1,s2;
	ElGamalEncrypt(x, s1, s2, pp, aaef, aa, bbt, kk, _kk);
	cout << "�䷢֤��:" << endl;
	fout << "Alice" << ' ' << a << ' ' << s1 << ' ' << s2 << ' ' << endl;
	getchar();
	cout << "Bob��֤֤�飺" << endl;
	getchar();
	bool t = ElGamalVerify(x, pp, aaef, bbt, s1, s2);
	if (t == 1)
		cout << "Bob����" << endl;
	else
		cout << "Bob�ܾ�" << endl;
}


int main()
{
	cout << "1.RSAǩ������" << endl;
	cout << "2.ElGamalǩ������" << endl;
	cout << "������Ҫʹ�õ�ǩ������(1��2)��" << endl;
	int x;
	cin >> x;
	while (x != 1 && x != 2)
	{
		cout << "������������������" << endl;
		cin >> x;
	}
	cout << endl;
	if (x == 1)
		RSACert();
	else
		ElGamalCert();

	return 0;
}