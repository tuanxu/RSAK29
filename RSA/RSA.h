#pragma once
#include "BigInt.h"

class CRSA
{
public:
	BigInt N;
	BigInt E;
	BigInt D;

	CRSA(void);
	~CRSA(void);

	
BigInt gcd(BigInt a, BigInt b);

void Init();





bool fermat_testing(BigInt n, int a);
bool fermat_testing(BigInt x) ;
BigInt PrimeGen();
BigInt rel_prime(BigInt phi);
BigInt encrypt(BigInt m);
BigInt calculate_d(BigInt phi, BigInt  e);
BigInt decrypt(BigInt c);

};

