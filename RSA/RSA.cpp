
#if VS_2010
#include "StdAfx.h"
#endif
#include "RSA.h"
#include <iostream>
#include <fstream>

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




bool CRSA::fermat_testing(BigInt n, int a) {
    BigInt Ba(a);

    if (gcd(Ba, n) != 1) {
        return COMPOSITE;
    }
    else {
        BigInt n_1 = Minus(n , 1);
		BigInt power_result = PowerMod(a, n_1, n);
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
    rel.Random(50, 100);
    while (gcd(phi, rel) != 1)
        rel = Plus(rel , 1);
    return rel;
}

BigInt CRSA::encrypt(BigInt m)
{
    BigInt c=PowerMod(m,E,N);
    
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

BigInt CRSA::decrypt(BigInt c)
{
	BigInt m = PowerMod(c,D,N);	
    return m;
}
void CRSA::Init() {
    srand(time(NULL));
    BigInt P = PrimeGen();
    BigInt Q = PrimeGen();

    N = Multiply(P, Q);
    BigInt phi = Multiply(Minus(P, 1), Minus(Q, 1));

    E = rel_prime(phi);
    D = calculate_d(phi, E);
}
void CRSA::Init(BigInt _N, BigInt _E, BigInt _D)
{
    N = _N;
    E = _E;
    D = _D;
}
void CRSA::SaveKeyToFile(const char* filename) {
    std::ofstream fKey(filename);
    fKey << N.ToString() << std::endl;
    fKey << E.ToString() << std::endl;
    fKey << D.ToString() << std::endl;
    fKey.close();

}
void CRSA::LoadKeyFromFile(const char* filename) {

    std::ifstream fKey(filename);

    std::string inputN = "";
    std::string inputE = "";
    std::string inputD = "";
    fKey >> inputN;
    fKey >> inputE;
    fKey >> inputD;
    fKey.close();

    N.FromString(inputN);
    E.FromString(inputE);
    D.FromString(inputD);

}
int main(int argc, char* argv[])
{
    //std::string strN = "10";
    //std::string strE = "20";
    //std::string strD = "30";
    //BigInt N(strN);
    //BigInt E(strE);
    //BigInt D(strD);
    
    //CRSA rsa;
    //rsa.Init();
    //rsa.SaveKeyToFile("key.txt");
    //rsa.LoadKeyFromFile("key.txt");
    
   
    //rsa.Init();

    //BigInt M = 6;

    //BigInt c = rsa.encrypt(M);

    //BigInt M1 = rsa.decrypt(c);
    CRSA rsa;
    rsa.LoadKeyFromFile("key.txt");

    //test
    /*BigInt M("A");
    BigInt C = rsa.encrypt(M);
    std::string strC = C.ToString();
    BigInt C1(strC);
    



    BigInt m1 = rsa.decrypt(C1);
*/
    if (_strcmpi(argv[1], "init") == 0)
    {
        rsa.Init();
        rsa.SaveKeyToFile("key.txt");
        std::cout << "rsa-init";
    }
    else if (_strcmpi(argv[1], "getpublickey") == 0)
    {
        std::cout << rsa.N.ToString();
        std::cout << "-";
        std::cout << rsa.E.ToString();
    }
    else if (_strcmpi(argv[1], "encrypt") == 0)
    {
        //std::cout << "encrypt";
        std::string strM = argv[2];
        for (std::string::iterator it = strM.begin(); it != strM.end(); ++it) {
            BigInt M(*it);
            BigInt c = rsa.encrypt(M);
            std::cout << c.ToString();
            if(it < strM.end() -1)
                std::cout << "-";
            //std::cout << (*it);
        }



    }
    else if (_strcmpi(argv[1], "decrypt") == 0)
    {
        //std::cout << "dencrypt";
        char* strC = argv[2];
        char* next_token1 = NULL;
        char* token = strtok_s(strC, "-", &next_token1);
        while (token != NULL)
        {

            BigInt C(token);
            BigInt M = rsa.decrypt(C);
            char c = M._value;

            std::cout << c;
            
            token = strtok_s(NULL, "-" ,&next_token1);
        }

    }
    return 0;
}
