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

#define PRIME true
#define COMPOSITE false

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


bool fermat_testing(BigInt N, int a) {
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
bool fermat_testing(BigInt x) {

    bool t1 = fermat_testing(x, 2);
    bool t2 = fermat_testing(x, 3);

    return t1 && t2;

}
BigInt PrimeGen() {

    BigInt x;

    x.RandomPrimeCandidate();
    int count = 0; //for debug
    while (!fermat_testing(x))
    {
        x = x + 2;
        count++;
    }
    return x;
}

int main()
{
    /*
    BigInt x ( 10);
    BigInt y(10);
    BigInt z(91);

    BigInt t = MulMod(x, y, z);
   
    //std::string num = "18";
    //std::cout << mod(num, 5);

*/
    BigInt x = PrimeGen();
   
    bool t1 = fermat_testing(x, 2);
    bool t2 = fermat_testing(x, 3);
    bool t3 = fermat_testing(x, 5);

   

}