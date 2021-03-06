#include <iostream>
#include <algorithm>
#if VS_2010
#include "stdafx.h"
#endif
#include "define.h"
class BigInt {
public:
    //Cho so nguyen duong 123456
    //Luu duoi dang chuoi "654321"
    //head =0, tail = 5
#if VS_2010
    int _value;
    bool neg;
    //char number[1024];
    bool bnumber[1024*8] ;
    int head;
    int tail;
    int digits; //number of digits in big int
#else
    int _value = 0;
    bool neg = false;
    //char number[1024];
    bool bnumber[1024*8] = { false };
    int head = 0;
    int tail = 0;
    int digits = 0; //number of digits in big int

#endif
    BigInt() {
    _value = 0;
    neg = false;
    //char number[1024];
    head = 0;
    tail = 0;
    digits = 1; //number of digits in big int
	
	
	};

    BigInt(const BigInt& other);
    BigInt(std::string input);

    BigInt(long long int number);

    ~BigInt()        //destructor to delete the array
    {
        //delete bnumber;
    }
    //BigInt(const char* number);

    void Reset();
    void SetValue(long long int number);
    //void SetValue(const char* number);
    void Update();
    bool isEven();
    void Devision_to_2();
    void Multiply_to_2();
    bool isPositive();
    void RandomPrimeCandidate();
    void Random(int minnumbers, int maxnumbers);

    std::string ToString();
    bool FromString(std::string input);

    friend bool operator == (BigInt first, BigInt second); 

    friend bool operator != (BigInt first, BigInt second);
    friend bool operator != (BigInt first, int second);

    
    friend bool operator < (BigInt first, BigInt second);

    friend bool operator <= (BigInt first, BigInt second);

    friend bool operator > (BigInt first, BigInt second);
    friend bool operator > (BigInt first, int second);

    friend bool operator >= (BigInt first, BigInt second);

    void operator = (long long int number);


    friend void swap(BigInt &first, BigInt &second);

    friend BigInt BigIntAbs(BigInt bigint);

    

    friend BigInt Plus(BigInt first, BigInt second);
  
    
    friend BigInt Minus(BigInt first, BigInt second);

 
    friend BigInt Multiply (BigInt first, BigInt second);
    friend BigInt Divide (BigInt first, BigInt second);


    friend BigInt Modulo(BigInt first, BigInt second);
    friend BigInt Modulo2(BigInt first, BigInt second);


    friend BigInt PowerMod(BigInt first, BigInt second, BigInt mod);
    friend BigInt MulMod(BigInt first, BigInt second, BigInt mod);




};