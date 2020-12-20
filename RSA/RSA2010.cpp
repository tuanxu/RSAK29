// RSA2010.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RSA.h"
#include <ctime>
int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	CRSA rsa;
	//BigInt x(28657);
	//bool res = rsa.fermat_testing(x);

	
    BigInt P = 3;//rsa.PrimeGen();
    BigInt Q = 11;//rsa.PrimeGen();

    BigInt N = Multiply(P , Q);
    BigInt phi = Multiply(Minus(P , 1) , Minus(Q , 1));

    BigInt e = rsa.rel_prime(phi);
    BigInt d = rsa.calculate_d(phi, e);

    BigInt M = 6;
    
    BigInt c = rsa.encrypt(N, e, M);
   
    BigInt M1 = rsa.decrypt(c, d, N);
	
	return 0;
}

