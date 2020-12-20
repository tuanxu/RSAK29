// RSA2010.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RSA.h"
#include <ctime>

int calculate_d(int phi, int e)
{
    int inv, u1, u3, v1, v3, t1, t3, q;
    int iter;
    u1 = 1;
    u3 = e;
    v1 = 0;
    v3 = phi;
    iter = 1;
    while(v3 != 0)
    {
        q = u3 / v3;
        t3 = u3 % v3;
        t1 = u1 + q * v1;
        u1 = v1;
        v1 = t1;
        u3 = v3;
        v3 = t3;
        iter = -iter;
    }
    if(u3 != 1)
        return  0;
    if(iter < 0)
        inv = phi - u1;
    else
        inv = u1;
    return inv;
}
int gcd(int a, int b){
    while (b != 0){
        int t= b;
        b= a % b;
		a= t;
	}
    return a;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int rs = gcd(91,10);
	srand(time(NULL));
	CRSA rsa;
	//BigInt x(28657);
	//bool res = rsa.fermat_testing(x);
	//int d1 = calculate_d(20,7);
	
    BigInt P = rsa.PrimeGen();
    BigInt Q = rsa.PrimeGen();

    BigInt N = Multiply(P , Q);
    BigInt phi = Multiply(Minus(P , 1) , Minus(Q , 1));

    BigInt e = rsa.rel_prime(phi);
    BigInt d = rsa.calculate_d(phi, e);

    BigInt M = 6;
    
    BigInt c = rsa.encrypt(N, e, M);
   
    BigInt M1 = rsa.decrypt(c, d, N);
	
	return 0;
}

