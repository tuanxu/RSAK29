#pragma once
#include "BigInt.h"

class CRSA
{
public:
	CRSA(void);
	~CRSA(void);

	
BigInt gcd(BigInt a, BigInt b);





bool fermat_testing(BigInt N, int a);
bool fermat_testing(BigInt x) ;
BigInt PrimeGen();
BigInt rel_prime(BigInt phi);
BigInt encrypt(BigInt N, BigInt e, BigInt M);
BigInt calculate_d(BigInt phi, BigInt  e);
BigInt decrypt(BigInt c,BigInt  d,BigInt  N);

};

