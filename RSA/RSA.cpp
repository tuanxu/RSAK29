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

BigInt CRSA::calculate_d(BigInt phi, BigInt  e)
{
	BigInt rel(5);
	while (MulMod(rel,e,phi) != 1)
        rel = Plus(rel , 1);
    return rel;
}
	/*
BigInt CRSA::calculate_d(BigInt phi, BigInt  e)
{
    BigInt d, y, x1, x2, y1, y2, temp, r, orig_phi;
    orig_phi = phi;
    x2 = 1; x1 = 0; y2 = 0; y1 = 1;
    while (e > 0)
    {
        temp = Divide(phi , e);
        r = Minus(phi , MulMod(temp , e,phi));
        x = Minus(x2 , MulMod(temp , x1,phi));
        y = Minus(y2 , MulMod(temp , y1,phi));
        phi = e; e = r;
        x2 = x1; x1 = x;
        y2 = y1; y1 = y;
        if (phi == 1)
        {
            y2 = Plus(y2, orig_phi);
            break;
        }
    }
    return y2;
}
*/
BigInt CRSA::decrypt(BigInt c,BigInt  d,BigInt  N)
{
	BigInt m = PowerMod(c,d,N);	
    return m;
}