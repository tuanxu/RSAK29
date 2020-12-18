// RSA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BigInt.h"


int gcd(int a, int b)
{
    int g = 1;
    while (a % 2 == 0 && b % 2 == 0)
    {
        a = a / 2;
        b = b / 2;
        g = 2 * g;
    }

    while (a > 0) {
        while (a % 2 == 0) a = a / 2;
        while (b % 2 == 0) b = b / 2;

        int t = abs(a - b) / 2;
        if (a >= b)
            a = t;
        else
            b = t;
    }
    g = g * b;
    

    return g;
}

BigInt gcd(BigInt a, BigInt b)
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




bool fermat_testing(BigInt N, int a) {
    BigInt Ba(a);

    if (gcd(Ba, N) != 1) {
        return COMPOSITE;
    }
    else {
        if (PowerMod(a, Minus(N , 1), N) != 1) {
            return COMPOSITE;
        }
        else {
            return PRIME;
        }
    }

}
bool fermat_testing(BigInt x) {

    bool t1 = fermat_testing(x, 2);
    bool t2 = fermat_testing(x, 3);

    return t1 && t2;

}
BigInt PrimeGen() {

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

BigInt rel_prime(BigInt phi)
{
    BigInt rel = 5;

    while (gcd(phi, rel) != 1)
        rel = Plus(rel , 1);
    return rel;
}

BigInt encrypt(BigInt N, BigInt e, BigInt M)
{
    BigInt r(0);
    int i = 0;
    BigInt prod(1);
    BigInt rem_mod (0);
    while (e > 0)
    {
        r = Modulo (e, 2);
        if (i++ == 0)
            rem_mod = Modulo(M , N);
        else
            rem_mod = Modulo (PowerMod(rem_mod, 2) , N);
        if (r == 1)
        {
            prod = Multiply(prod, rem_mod);
            prod = Modulo(prod , N);
        }
        e.Devision_to_2() ;
    }
    return prod;//return c
}

BigInt calculate_d(BigInt phi, BigInt  e)
{
    var x, y, x1, x2, y1, y2, temp, r, orig_phi;
    orig_phi = phi;
    x2 = 1; x1 = 0; y2 = 0; y1 = 1;
    while (e > 0)
    {
        temp = parseInt(phi / e);
        r = phi - temp * e;
        x = x2 - temp * x1;
        y = y2 - temp * y1;
        phi = e; e = r;
        x2 = x1; x1 = x;
        y2 = y1; y1 = y;
        if (phi == 1)
        {
            y2 += orig_phi;
            break;
        }
    }
    return y2;
}

BigInt decrypt(c, d, N)
{
    var r, i = 0, prod = 1, rem_mod = 0;
    while (d > 0)
    {
        r = d % 2;
        if (i++ == 0)
            rem_mod = c % N;
        else
            rem_mod = power(rem_mod, 2) % N;
        if (r == 1)
        {
            prod *= rem_mod;
            prod = prod % N;
        }
        d = parseInt(d / 2);
    }
    return prod;
}
int main()
{
    srand(time(NULL));
    BigInt x ( 100);
    BigInt y(13);
    while (x > y)
    {
        x = Minus (x , y);
    }
    

    
   

    BigInt P = PrimeGen();
    BigInt Q = PrimeGen();

    BigInt N = Multiply(P , Q);
    BigInt phi = Multiply(Minus(P , 1) , Minus(Q , 1));

    BigInt e = rel_prime(Phi);

    BigInt M = 54;
    
    BigInt c = encrypt(N, e, M);
    BigInt d = calculate_d(phi, e);
   
    BigInt M1 = decrypt(c, d, N);
}