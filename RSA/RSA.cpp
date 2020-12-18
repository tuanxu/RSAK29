// RSA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BigInt.h"
#include "BigInterger.h"

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
        

        BigInt t = abs(a - b);
        t.Devision_to_2();
        if (a >= b)
            a = t;
        else
            b = t;
    }
    g = g * b;


    return g;
}

#define PRIME 1
#define COMPOSITE 0

int mod_power(int a, int b, int p) {
    if (b == 1) {
        return a % p;
    }
    else {
        int x = mod_power(a, b / 2, p);
        if (b%2 == 0) { // b is even
            return (x * x) % p;
        }
        else {
            return (((x * x) % p) * a) % p;
        }
    }
}

int fermat_testing(int N, int a) {
    if (gcd(a, N) != 1) {
        return COMPOSITE;
    }
    else {
        if (mod_power(a, N - 1, N) != 1) {
            return COMPOSITE;
        }
        else {
            return PRIME;
        }
    }

}
int fermat_testing(BigInt N, int a) {
    BigInt Ba(a);

    if (gcd(Ba, N) != 1) {
        return COMPOSITE;
    }
    else {
        if (PowerMod(a, N - 1, N) != 1) {
            return COMPOSITE;
        }
        else {
            return PRIME;
        }
    }

}
int main()
{
    /*
    BigInterger x ( 18);
    BigInterger y ( 6);

   BigInterger z = x % y;
    BigInt x1(8);
    BigInt y1(6);

    BigInt z1 = PowerMod(x1,y1,1000000000);
    std::cout << z;
    */





    BigInt x(2649);
    BigInt y(10);
    BigInt z(11);
    BigInt t = PowerMod(x, y, z);
    int t1 = fermat_testing(x,2);
    int t2 = fermat_testing(x,3);
}