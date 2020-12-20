#include "StdAfx.h"
#include "RSA.h"
#define PRIME true
#define COMPOSITE false


CRSA::CRSA(void)
{
}


CRSA::~CRSA(void)
{
}


BigInt CRSA::gcd(BigInt a, BigInt b)
{
    BigInt g = 1;
    while (a.isEven() && b.isEven())
    {
        a.Devision_to_2();
        b.Devision_to_2();
        g.Multiply_to_2();
    }

    while (a.isPositive()) {
        while (a.isEven()) 
            a.Devision_to_2();
        while (b.isEven()) 
            b.Devision_to_2();
        

        BigInt t = BigIntAbs(Minus(a, b));
        t.Devision_to_2();
        if (a >= b)
            a = t;
        else
            b = t;
    }
    g = Multiply (g , b);


    return g;
}

#define PRIME true
#define COMPOSITE false




bool CRSA::fermat_testing(BigInt N, int a) {
    BigInt Ba(a);

    if (gcd(Ba, N) != 1) {
        return COMPOSITE;
    }
    else {
        BigInt n_1 = Minus(N , 1);
		BigInt power_result = PowerMod(a, n_1, N);
		if (power_result != 1) {
        //if (PowerMod(a, Minus(N , 1), N) != 1) {
            return COMPOSITE;
        }
        else {
            return PRIME;
        }
    }

}
bool CRSA::fermat_testing(BigInt x) {

    bool t1 = fermat_testing(x, 2);
    bool t2 = fermat_testing(x, 3);

    return t1 && t2;

}
BigInt CRSA::PrimeGen() {

    BigInt x(0);


    x.RandomPrimeCandidate();
    //BigInt count = 0; //for debug
    while (!fermat_testing(x))
    {
        x = Plus (x , 2);
        //count = count + 1;
    }
    return x;
}

BigInt CRSA::rel_prime(BigInt phi)
{
    BigInt rel = 5;

    while (gcd(phi, rel) != 1)
        rel = Plus(rel , 1);
    return rel;
}

BigInt CRSA::encrypt(BigInt N, BigInt e, BigInt M)
{
    BigInt c=PowerMod(M,e,N);
    
    return c;
}
/*
BigInt CRSA::calculate_d(BigInt phi, BigInt  e)
{
	BigInt rel(5);
	while (MulMod(rel,e,phi) != 1)
        rel = Plus(rel , 1);
    return rel;
}
	*/

BigInt CRSA::calculate_d(BigInt phi, BigInt  e)
{
    BigInt inv, u1, u3, v1, v3, t1, t3, q;
    BigInt iter;
    u1 = 1;
    u3 = e;
    v1 = 0;
    v3 = phi;
    iter = 1;
    while(v3 != 0)
    {
        q = Divide(u3 , v3);
        t3 = Modulo (u3 , v3);
        t1 = Plus(u1 , MulMod(q , v1,phi));
        u1 = v1;
        v1 = t1;
        u3 = v3;
        v3 = t3;
        iter.neg = !iter.neg;
    }
    if(u3 != 1)
        return  0;
    if(iter < 0)
        inv = Minus(phi , u1);
    else
        inv = u1;
    return inv;
}

BigInt CRSA::decrypt(BigInt c,BigInt  d,BigInt  N)
{
	BigInt m = PowerMod(c,d,N);	
    return m;
}