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

void RSAEncrypt(const long x, long &y, long a, long n)
{
	y = 1;
	for (long i = 1; i <= a; i++)
	{
		y = (y*x) % n;
	}
}

bool RSAVerify(long s, long x, long b, long n)
{
	long yy = 1;
	for (long i = 1; i <= b; i++)
		yy = (yy*s) % n;
	if (yy = x)
		return true;
	else
		return false;
}



void RSAIdentify()
{
	srand((unsigned)time(NULL));
	long pa, qa, na, aa, ba, sa;
	long pb, qb, nb, ab, bb, sb;
	RSAKey(pa, qa, na, aa, ba);
	RSAKey(pb, qb, nb, ab, bb);

	long r1 = 1 + rand() % 1000;
	long r2 = 1 + rand() % 1000;
	long Alice = 22, Bob = 19;
	cout << "生成Bob证书(主要是为了传送自己公开验证的密钥,这里为了简化，直接假设将验证密钥传送过去)，并和随机挑战r1发送给Alice" << endl;
	getchar();
	cout << "生成Alice证书，并和随机挑战r2和y1一起发送给Bob" << endl;
	long y1, y2;
	RSAEncrypt(Bob + r1 + r2, y1, aa, na);
	getchar();
	cout << "Bob获得Alice证书，并获得Alice的验证公钥，然后验证：" << endl;
	getchar();
	bool t1 = (y1, Bob + r1 + r2, ba, na);
	if (t1)
		cout << "Bob接受" << endl;
	else
		cout << "Bob拒绝" << endl;
	getchar();
	cout << "Bob计算y2发送给Alice" << endl;
	RSAEncrypt(Alice + r2, y2, ab, nb);
	getchar();
	cout << "Alice接受Bob的证书，并获得Bob的验证公钥,然后验证" << endl;
	getchar();
	bool t2 = (y2, Alice + r2, bb, nb);
	if (t2)
		cout << "Alice接受" << endl;
	else
		cout << "Alice拒绝" << endl;
	getchar();
	cout << "相互认证结束" << endl;
	
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

void ElGamalEncrypt(const long &x, long &s1, long &s2, long p, long aef, long a, long bt, long k, long _k)
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

bool ElGamalVerify(long x, long p, long aef, long bt, long gm, long dt)
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



void ElGamalIdentify()
{
	srand((unsigned)time(NULL));
	long ra, pa, qa, aefa, aa, bta, ka, _ka;
	long rb, pb, qb, aefb, ab, btb, kb, _kb;
	ElGamalKey(ra, pa, qa, aefa, aa, bta, ka, _ka);
	ElGamalKey(rb, pb, qb, aefb, ab, btb, kb, _kb);
	long r1 = 1 + rand() % 1000;
	long r2 = 1 + rand() % 1000;
	long Alice = 22, Bob = 19;
	cout << "生成Bob证书(主要是为了传送自己公开验证的密钥,这里为了简化，直接假设将验证密钥传送过去)，并和随机挑战r1发送给Alice" << endl;
	getchar();
	cout << "生成Alice证书，并和随机挑战r2和y1一起发送给Bob" << endl;
	long y1_1,y1_2, y2_1,y2_2;
	ElGamalEncrypt(Bob + r1 + r2, y1_1, y1_2, pa, aefa, aa, bta, ka, _ka);
	getchar();
	cout << "Bob获得Alice证书，并获得Alice的验证公钥，然后验证：" << endl;
	getchar();
	bool t1 = ElGamalVerify(Bob + r1 + r2, pa, aefa, bta, y1_1, y1_2);
	if (t1)
		cout << "Bob接受" << endl;
	else
		cout << "Bob拒绝" << endl;
	getchar();
	cout << "Bob计算y2发送给Alice" << endl;
	ElGamalEncrypt(Alice + r2, y2_1, y2_2, pb, aefb, ab, btb, kb, _kb);
	getchar();
	cout << "Alice接受Bob的证书，并获得Bob的验证公钥,然后验证" << endl;
	getchar();
	bool t2 = ElGamalVerify(Alice + r2, pb, aefb, btb, y2_1, y2_2);
	if (t2)
		cout << "Alice接受" << endl;
	else
		cout << "Alice拒绝" << endl;
	getchar();
	cout << "相互认证结束" << endl;


}

int main()
{
	cout << "1.RSA签名方案" << endl;
	cout << "2.ElGamal签名方案" << endl;
	cout << "请输入要使用的签名方案(1或2)：" << endl;
	int x;
	cin >> x;
	while (x != 1 && x != 2)
	{
		cout << "输入有误，请重新输入" << endl;
		cin >> x;
	}
	cout << endl;
	if (x == 1)
		RSAIdentify();
	else
		ElGamalIdentify();

	return 0;
}