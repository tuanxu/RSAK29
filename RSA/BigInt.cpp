#include "stdafx.h"
#include "BigInt.h"

void BigInt::Reset(){
    this->neg = false;
    this->head = 0;
    this->tail = 0;
    this->digits = 0;
    Update(); //this is for debug
}

void BigInt::Update() {
    int result = 0;
    while (!this->bnumber[this->tail] && this->tail != this->head)
        this->tail--;
    digits = tail - head + 1;
    for (int i = tail; i >= head; i--)
        result = result * 2 + (bnumber[i]?1:0);
    _value = result;
}
BigInt::BigInt(const BigInt& other) {
    this->neg = other.neg;
    this->head = other.head;
    this->tail = other.tail;
    this->digits = other.digits;
    memset(this->bnumber, false, sizeof(this->bnumber));

    for (int i = other.head; i <= other.tail; i++)
        this->bnumber[i] = other.bnumber[i];
    Update(); //this is for debug
}

void BigInt::SetValue(long long int number) {
    if (number < 0) {
        this->neg = true;
        number *= -1;
    }

    if (number == 0) {
        this->head = 0;
        this->tail = 0;
		this->neg = false;
        this->bnumber[this->tail] = 0;
		this->digits=1;
		this->Update();
        return;
    }
    this->head = 0;
    this->tail = 0;

    this->bnumber[this->tail] = 0;
    int pos = this->tail;
    while (number > 0) {
        this->bnumber[pos] = (number % 2);
        number /= 2;
        pos++;
    }
    this->tail = pos - 1;
    this->digits = pos;
    Update(); //this is for debug
}
BigInt::BigInt(long long int number) {
    this->neg = 0;
    this->head = 0;
    this->tail = 0;
    this->digits = 0;
    //this->bnumber = new bool[1024 * 8]{ false };
    SetValue(number);
}

bool operator == (BigInt first, BigInt second) {
    if ((second.neg != first.neg) || (first.digits != second.digits))
        return false;
    for (int i = 0; i < first.digits; i++)
        if (first.bnumber[first.head + i] != second.bnumber[second.head + i])
            return false;
    return true;
}
bool operator != (BigInt first, BigInt second) {
    return !(first == second);
}
bool operator == (BigInt first, int second) {
    if (first.neg != (second < 0))
        return false;
    for (int i = first.head; i <= first.tail; i++) {
        if (first.bnumber[i] != (second % 2 == 1))
            return false;
        second /= 2;
    }
    return true;
}
bool operator != (BigInt first, int second) {
    return !(first == second);
}
bool operator < (BigInt first, BigInt second) {
    if (first.neg && !second.neg || first.digits < second.digits) return true;
    if (!first.neg && second.neg || first.digits > second.digits) return false;


    for (int i = first.digits - 1; i >= 0; i--)
    {
        if (first.bnumber[first.head + i] && !second.bnumber[second.head + i])
            return false;
        if (!first.bnumber[first.head + i] && second.bnumber[second.head + i])
            return true;
    }
    return false;
}

bool operator <= (BigInt first, BigInt second) {
    return (first == second) || (first < second);
}

bool operator > (BigInt first, BigInt second) {
    if (first.neg && !second.neg || first.digits < second.digits) return false;
    if (!first.neg && second.neg || first.digits > second.digits) return true;

    

    for (int i = first.digits - 1; i >= 0; i--)
    {
        if (first.bnumber[first.head + i] && !second.bnumber[second.head + i])
            return true;
        if (!first.bnumber[first.head + i] && second.bnumber[second.head + i])
            return false;
    }
    return false;
}
bool operator > (BigInt first, int second) {
    if (first.neg && second >=0) return false;
    if (!first.neg && second < 0) return true;

    for (int i = first.digits - 1; i >= 0; i) {
        if (first.bnumber[first.head + i] && (second % 2 == 0))
            return true;
        if (!first.bnumber[first.head + i] && (second % 2 == 1))
            return false;
        second /= 2;
    }
    return true;
}
bool operator >= (BigInt first, BigInt second) {
    return (first == second) || (first > second);
}

bool operator >= (BigInt first, int second) {
    return (first == second) || (first > second);
}

void BigInt::operator = (long long int number) {
    SetValue(number);
}

void swap(BigInt &first, BigInt &second) {
    BigInt temp(first);

    first = second;
    second = temp;
}

BigInt BigIntAbs(BigInt bigint) {
    bigint.neg = false;

    return bigint;
}

BigInt Plus(BigInt first, BigInt second) {
    bool neg = false;

    if (!first.neg && second.neg) {
        second.neg = false; return Minus( first , second);
    }

    if (first.neg && !second.neg) {
        first.neg = false; return Minus(second , first);
    }

    if (first.neg && second.neg) {
        neg = true;
        first.neg = second.neg = false;
    }

    int n = first.digits;
    int m = second.digits;
    int max = std::max(n, m);

    int carry = 0;

    BigInt result(0);

    for (int i = 0; i < max; i++) {
        int add = carry;

        if (i < n) add += first.bnumber[first.head + i];
        if (i < m) add += second.bnumber[second.head + i];

        carry = add / 2;

        result.bnumber[i] = add % 2;

    }

    if (carry != 0) {
        result.bnumber[max] = carry;
        result.tail = max;
        result.digits = max + 1;
    }
    else
    {
        result.tail = max-1;
        result.digits = max;
    }
    result.neg = neg;
    result.Update();
    return result;
}



BigInt Minus (BigInt first, BigInt second) {
    if (second.neg) {
        second.neg = false;
        return Plus(first , second);
    }

    if (first.neg) {
        second.neg = true;
        return Plus(first, second);
    }

    bool neg = false;

    if (first < BigIntAbs(second)) {
        neg = true;

        swap(first, second);
        first = BigIntAbs(first);
    }

    int n = first.digits;
    int m = second.digits;
    int max = std::max(n, m);
    int carry = 0;

    BigInt result(0);

    for (int i = 0; i < max; i++) {
        int add = carry;

        if (i < n) add += first.bnumber[first.head + i];
        if (i < m) add -= second.bnumber[second.head + i];

        carry = add < 0 ? (-1) : 0;

        result.bnumber[i] = add % 2;

    }

    
    result.tail = max-1;
    result.digits = max - 1;
    result.neg = neg;

    result.Update();
    return result;
}

BigInt Multiply (BigInt first, BigInt second) {
    bool neg = first.neg != second.neg;

    first.neg = false;
    second.neg = false;

    int n = first.digits;
    int m = second.digits;

    BigInt result (0);

    if ((first.tail - first.head == 0 && !first.bnumber[first.head])
        || second.tail - second.head == 0 && !second.bnumber[second.head])
        return result; //return 0

    if (first.tail - first.head == 0 && first.bnumber[first.head]) // = 1
        return second; 

    if (second.tail - second.head == 0 && second.bnumber[second.head]) // = 1
        return first;

    if (second.bnumber[second.head])
        result = first;

    for (int i = 1; i < second.digits; i++) {
        int carry = 0;
        first.Multiply_to_2();

        if (second.bnumber[second.head + i])
            result = Plus(result , first);

    }


    result.neg = neg;

    return result;
}

BigInt Modulo (BigInt first, BigInt second) {
    if (second == 0)
        throw "Modulo with 0";

    first.neg = false;
    second.neg = false;

    if (first < second)
        return first;


    while (first >= second) {
        first = Minus(first , second);
    }

        
      first.Update();
      return first;
}
BigInt Divide (BigInt first, BigInt second) {
    if (second == 0)
        throw "Divide with 0";

    first.neg = false;
    second.neg = false;

    if (first < second)
        return 0;

	BigInt result = 0;
    while (first > second) {
        first = Minus(first , second);
		result = Plus(result,1);
    }

        
      result.Update();
      return result;
}
BigInt MulMod(BigInt first, BigInt second, BigInt mod) {
    if (mod != 0)
        first = Modulo( first , mod);

    BigInt p = 0;
   
    if (second.bnumber[second.head])
        p = first;

    for (int i = 1; i < second.digits; i++) {
        //A = (A * A)%mod;
        first.Multiply_to_2();
        first = Modulo(first, mod);
        

        if (second.bnumber[second.head + i])
             p = Modulo(Plus(p , first) , mod);


    }

    p.Update();
    return p;
}

BigInt PowerMod(BigInt first, BigInt second, BigInt mod) {
    if (mod != 0)
        first = Modulo (first,mod);

    BigInt y = 1;
    if (second == 0) {
        y.Update();
        return y;
    }
    BigInt A = first;
    if (second.bnumber[second.head] == 1)
        y = first;
    for (int i = 1; i < second.digits; i++) {
        //A = (A * A)%mod;
        A = MulMod(A, A, mod);

        if (second.bnumber[second.head + i] == 1)
            //y = (A * y) % mod;
            y = MulMod(A, y, mod);


    }
    
    y.Update();
    return y;
}



bool BigInt::isEven() {
    return this->bnumber[this->head] == 0;
}

void BigInt::Devision_to_2() {
    if(this->head < this->tail)
        this->head++;
    Update();
}
void BigInt::Multiply_to_2() {
    if (this->tail < 1024 * 8) {
        for (int i = this->tail; i >= this->head; i--)
            this->bnumber[i + 1] = this->bnumber[i];
        this->bnumber[head] = false;
        this->tail++;
    }
    Update();

}
bool BigInt::isPositive() {
    return (this->bnumber[this->tail] && !this->neg) ;
}

void BigInt::RandomPrimeCandidate() {
    //this is for test
    int min_n = 50;
    int max_n = 100;

    
    this->head = 1;
    this->tail = rand() % (max_n - min_n) + min_n;
    for (int i = this->head; i <= this->tail; i++)
        this->bnumber[i] = rand() % 2;
    this->bnumber[--this->head] = true;
    Update();
}