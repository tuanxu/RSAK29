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
        result = result * 2 + bnumber[i];
    _value = result;
}
BigInt::BigInt(const BigInt& other) {
    this->neg = other.neg;
    this->head = other.head;
    this->tail = other.tail;
    this->digits = other.digits;

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
        this->bnumber[this->tail] = 0;
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
    SetValue(number);
}
/*void BigInt::SetValue(const char* number) {
    int n = strlen(number);
    if (number[0] == '-') {
        this->neg = true;
        n--;
    }
    this->head = 0;
    this->tail = 0;
    int pos = this->head;
    for (int i = n-1; i >=0; i--)
        this->number[pos++] = number[i] - '0';
    this->tail = pos - 1;
    this->digits = pos;
    Update();
}
BigInt::BigInt(const char* number){
    SetValue(number);
    
}
*/
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
    for (int i = 0; i < first.digits; i++) {
        if (first.bnumber[first.tail - i] != (second % 2 == 1))
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
/*
std::istream& operator >> (std::istream& in, BigInt& bigint) {
    std::string number; in >> number;

    bigint.SetValue(number.c_str());

    return in;
}

std::ostream& operator << (std::ostream& out, const BigInt& bigint) {
    std::string number;

    if (bigint.neg)
        number = '-' + number;

    for (int i = bigint.tail; i >= bigint.head; i--)
        number += bigint.bnumber[i] + '0';

    out << number;

    return out;
}
*/
void swap(BigInt& first, BigInt& second) {
    BigInt temp(first);

    first = second;
    second = temp;
}

BigInt abs(BigInt bigint) {
    bigint.neg = false;

    return bigint;
}

BigInt operator + (BigInt first, BigInt second) {
    bool neg = false;

    if (!first.neg && second.neg) {
        second.neg = false; return first - second;
    }

    if (first.neg && !second.neg) {
        first.neg = false; return second - first;
    }

    if (first.neg && second.neg) {
        neg = true;
        first.neg = second.neg = false;
    }

    int n = first.digits;
    int m = second.digits;
    int max = std::max(n, m);

    int carry = 0;

    BigInt result;

    for (int i = 0; i < max; i++) {
        int add = carry;

        if (i < n) add += first.bnumber[first.head + i];
        if (i < m) add += second.bnumber[second.head + i];

        carry = add / 2;

        result.bnumber[i] = add % 2;

    }

    if (carry != 0) {
        result.bnumber[max] = carry;
        result.tail = max+2;
        result.digits = max + 2;
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

BigInt operator + (BigInt bigint) {
    return bigint;
}

BigInt operator - (BigInt first, BigInt second) {
    if (second.neg) {
        second.neg = false;
        return first + second;
    }

    if (first.neg) {
        second.neg = true;
        return first + second;
    }

    bool neg = false;

    if (first < abs(second)) {
        neg = true;

        swap(first, second);
        first = abs(first);
    }

    int n = first.digits;
    int m = second.digits;
    int max = std::max(n, m);
    int carry = 0;

    BigInt result;

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
/*
BigInt operator - (BigInt second) {
    BigInt first("0"); return first - second;
}
*/
BigInt operator * (BigInt first, BigInt second) {
    bool neg = first.neg != second.neg;

    first.neg = false;
    second.neg = false;

    int n = first.digits;
    int m = second.digits;

    BigInt result;

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
            result = (result + first);

    }


    result.neg = neg;

    return result;
}
/*
BigInt operator / (BigInt first, BigInt second) {
    if (second == "0")
        throw "Division with 0";

    bool neg = first.neg != second.neg;

    first.neg = false;
    second.neg = false;

    BigInt quotient;

    int i = first.size() - 1;

    BigInt current(first.bnumber[i] - '0');

    --i;

    while (true) {
        BigInt result = current;

        bool l = false;

        while (result < second && i >= 0) {
            result = result * 2 + (first.bnumber[i--] - '0');

            if (l)
                quotient *= 2;

            l = true;
        }

        int c = 0;

        BigInt result_(result);

        while (result_ >= second) {
            result_ -= second;
            c++;
        }

        quotient = quotient * 2 + c;

        current = result_;

        if (i < 0)
            break;
    }

    quotient.neg = neg;

    return quotient;
}

BigInt operator / (BigInt first, int second) {
    if (second == 0)
        throw "Division with 0";

    bool neg = first.neg != (second < 0);

    first.neg = false;
    

    BigInt quotient;

    int i = first.size() - 1;

    BigInt current(first.number[i] - '0');

    --i;

    while (true) {
        BigInt result = current;

        bool l = false;

        while (result < second && i >= 0) {
            result = result * 2 + (first.number[i--] - '0');

            if (l)
                quotient *= 2;

            l = true;
        }

        int c = 0;

        BigInt result_(result);

        while (result_ >= second) {
            result_ -= second;
            c++;
        }

        quotient = quotient * 2 + c;

        current = result_;

        if (i < 0)
            break;
    }

    quotient.neg = neg;

    return quotient;
}
*/
BigInt operator % (BigInt first, BigInt second) {
    if (second == 0)
        throw "Modulo with 0";

    first.neg = false;
    second.neg = false;

    if (first < second)
        return first;


      while (first > second) 
            first -= second;
        // Initialize result 

    /*int res = 0;

    // One by one process all digits of 'num' 
    for (int i = 0; i < num.length(); i++)
        res = (res * 10 + (int)num[i] - '0') % a;

    return res;

        BigInt res = 0;
        if (first == second)
            return res; //return 0

        for (int i = first.tail; i >= first.head; i--) {
            res.Multiply_to_2();
            res = (res + (int)first.bnumber[i]);
            res = res % second;
        }
        
            */
        
      first.Update();
      return first;
}

BigInt MulMod(BigInt first, BigInt second, BigInt mod) {
    if (mod != 0)
        first %= mod;

    BigInt p = 0;
   
    if (second.bnumber[second.head])
        p = first;

    for (int i = 1; i < second.digits; i++) {
        //A = (A * A)%mod;
        first.Multiply_to_2();
        first = first % mod;
        

        if (second.bnumber[second.head + i])
             p = (p + first) % mod;


    }

    p.Update();
    return p;
}

BigInt PowerMod(BigInt first, BigInt second, BigInt mod) {
    if (mod != 0)
        first %= mod;

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
/*
BigInt operator & (BigInt first_, BigInt second_) {
    std::string first = first_.int_to_base(2);
    std::string second = second_.int_to_base(2);

    unsigned int n = std::min(first.size(), second.size());

    reverse(first.begin(), first.end());
    reverse(second.begin(), second.end());

    std::string result(n, '~');

    for (unsigned int i = 0; i < n; i++) {
        if (first[i] == '1' && second[i] == '1')
            result[i] = '1';
        else
            result[i] = '0';
    }

    reverse(result.begin(), result.end());

    return BigInt().base_to_int(result, 2);
}

BigInt operator | (BigInt first_, BigInt second_) {
    std::string first = first_.int_to_base(2);
    std::string second = second_.int_to_base(2);

    unsigned int n = std::max(first.size(), second.size());

    reverse(first.begin(), first.end());
    reverse(second.begin(), second.end());

    std::string result(n, '~');

    for (unsigned int i = 0; i < n; i++) {
        if (first.size() <= i || second.size() <= i) {
            if (first.size() > i) result[i] = first[i];
            if (second.size() > i) result[i] = second[i];

            continue;
        }

        if (first[i] == '1' || second[i] == '1')
            result[i] = '1';
        else
            result[i] = '0';
    }

    reverse(result.begin(), result.end());

    return BigInt().base_to_int(result, 2);
}

BigInt operator ^ (BigInt first_, BigInt second_) {
    std::string first = first_.int_to_base(2);
    std::string second = second_.int_to_base(2);

    unsigned int n = std::max(first.size(), second.size());

    reverse(first.begin(), first.end());
    reverse(second.begin(), second.end());

    std::string result(n, '~');

    for (unsigned int i = 0; i < n; i++) {
        if (first.size() <= i || second.size() <= i) {
            if (first.size() > i) {
                if (first[i] == '0')
                    result[i] = '0';
                else
                    result[i] = '1';
            }

            if (second.size() > i) {
                if (second[i] == '0')
                    result[i] = '0';
                else
                    result[i] = '1';
            }

            continue;
        }

        if (first[i] == second[i])
            result[i] = '0';
        else
            result[i] = '1';
    }

    reverse(result.begin(), result.end());

    return BigInt().base_to_int(result, 2);
}

BigInt operator << (BigInt first, BigInt second) {
    BigInt x = pow(2, second, BigInt("0"));

    return first * x;
}

BigInt operator >> (BigInt first, BigInt second) {
    BigInt x = pow(2, second, BigInt("0"));

    return first / x;
}

int BigInt::to_int(BigInt bigint) {
    int n = 0;

    for (int i = bigint.digits - 1; i >= 0; i--)
        n = (n * 10) + (bigint.bnumber[i] - '0');

    return n;
}

std::string BigInt::int_to_base(int base) {
    std::string result;
    
    BigInt bigint(*this);

    while (bigint > 0) {
        BigInt r = (bigint % base);

        if (r >= 10)
            result += (char)(to_int(r / 10) + 'A');
        else
            result += (char)(to_int(r) + '0');

        bigint /= base;
    }

    reverse(result.begin(), result.end());
    
    return result;
}

BigInt BigInt::base_to_int(std::string str, int base) {
    BigInt result;

    for (unsigned int i = 0; i < str.size(); i++) {
        BigInt add;

        if ('0' <= str[i] && str[i] <= '9')
            add += str[i] - '0';
        else
            add += (str[i] - 'A') + 10;

        result = result * base + add;
    }

    return result;
}
*/
int BigInt::size() {
    return this->digits;
}

//void BigInt::operator ++ () { *(this) = *(this) + 1; }
//void BigInt::operator -- () { *(this) = *(this) - 1; }

void BigInt::operator += (BigInt bigint) { *(this) = *(this) + bigint; }
void BigInt::operator -= (BigInt bigint) { *(this) = *(this) - bigint; }

void BigInt::operator *= (BigInt bigint) { *(this) = *(this) * bigint; }
//void BigInt::operator /= (BigInt bigint) { *(this) = *(this) / bigint; }
void BigInt::operator %= (BigInt bigint) { *(this) = *(this) % bigint; }

//void BigInt::operator &= (BigInt bigint) { *(this) = *(this) & bigint; }
//void BigInt::operator |= (BigInt bigint) { *(this) = *(this) | bigint; }
//void BigInt::operator ^= (BigInt bigint) { *(this) = *(this) ^ bigint; }
/*
void BigInt::operator <<= (BigInt bigint) { *(this) = *(this) << bigint; }
void BigInt::operator >>= (BigInt bigint) { *(this) = *(this) >> bigint; }
*/
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
        this->bnumber[head] = 0;
        this->tail++;
    }
    Update();

}
bool BigInt::isPositive() {
    return (this->bnumber[this->tail] && !this->neg) ;
}

void BigInt::RandomPrimeCandidate() {
    //this is for test
    int min_n = 500;
    int max_n = 600;

    srand(time(NULL));
    this->head = 1;
    this->tail = rand() % (max_n - min_n) + min_n;
    for (int i = this->head; i <= this->tail; i++)
        this->bnumber[i] = rand() % 2;
    this->bnumber[--this->head] = true;
    Update();
}