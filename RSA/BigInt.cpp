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
void BigInt::SetValue(const char* number) {
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

bool operator == (BigInt first, BigInt second) {
    if ((second.neg != first.neg) || (first.digits != second.digits))
        return false;
    for (int i = 0; i <= first.digits; i++)
        if (first.number[first.head + i] != second.number[second.head + i])
            return false;
    return true;
}
bool operator != (BigInt first, BigInt second) {
    return !(first == second);
}
bool operator == (BigInt first, int second) {
    if (first.neg != (second < 0))
        return false;
    for (int i = 0; i <= first.digits; i++) {
        if (first.number[first.tail - i] != second % 10)
            return false;
        second /= 10;
    }
    return true;
}
bool operator != (BigInt first, int second) {
    return !(first == second);
}
bool operator < (BigInt first, BigInt second) {
    if (first.neg && !second.neg) return true;
    if (!first.neg && second.neg) return false;



    if (first.digits < second.digits) return true;
    if (first.digits > second.digits) return false;

    std::string temp1 = first.number; reverse(temp1.begin(), temp1.end());
    std::string temp2 = second.number; reverse(temp2.begin(), temp2.end());

    for (int i = 0; i <= first.digits; i++)
        if (first.number[first.head + i] > second.number[second.head + i])
            return false;
    return true;
}

bool operator <= (BigInt first, BigInt second) {
    return (first == second) || (first < second);
}

bool operator > (BigInt first, BigInt second) {
    if (first.neg && !second.neg) return false;
    if (!first.neg && second.neg) return true;



    if (first.digits < second.digits) return true;
    if (first.digits > second.digits) return false;

    std::string temp1 = first.number; reverse(temp1.begin(), temp1.end());
    std::string temp2 = second.number; reverse(temp2.begin(), temp2.end());

    for (int i = 0; i <= first.digits; i++)
        if (first.number[first.head + i] > second.number[second.head + i])
            return false;
    return true;
}
bool operator > (BigInt first, int second) {
    if (first.neg && second >=0) return false;
    if (!first.neg && second < 0) return true;

    for (int i = 0; i <= first.digits; i++) {
        if (first.bnumber[first.tail - i] < second % 2)
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
        number += bigint.number[i] + '0';

    out << number;

    return out;
}

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

    int carry = 0;

    std::string result;

    for (int i = 0; i < std::max(n, m); i++) {
        int add = carry;

        if (i < n) add += first.bnumber[i];
        if (i < m) add += second.bnumber[i];

        carry = add / 2;

        result += add % 2 + '0';
    }

    if (carry != 0)
        result += carry;

    reverse(result.begin(), result.end());

    BigInt result_(result.c_str());
    result_.neg = neg;

    return result_;
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

    int carry = 0;

    BigInt result;


    for (int i = 0; i < std::max(n, m); i++) {
        int add = carry;

        if (i < n) add += first.bnumber[first.head + i];
        if (i < m) add -= second.bnumber[second.head + i];

        if (add < 0) {
            carry = -1;
            result += add + 2;
        }

        else {
            carry = 0;
            result += add;
        }
    }

    reverse(result.begin(), result.end());

    BigInt result_(result.c_str());

    result_.neg = neg;

    return result_;
}

BigInt operator - (BigInt second) {
    BigInt first("0"); return first - second;
}

BigInt operator * (BigInt first, BigInt second) {
    bool neg = first.neg != second.neg;

    first.neg = false;
    second.neg = false;

    int n = first.digits;
    int m = second.digits;

    BigInt result_;

    for (int i = 0; i < n; i++) {
        int carry = 0;

        std::string result;

        for (int j = 0; j < i; j++)
            result += '0';

        for (int j = 0; j < m; j++) {
            int add = carry + (first.number[i] - '0') * (second.number[j] - '0');

            carry = add / 10;

            result += add % 10 + '0';
        }

        if (carry != 0)
            result += carry + '0';

        reverse(result.begin(), result.end());

        BigInt current(result.c_str());

        result_ += current;
    }

    result_.neg = neg;

    return result_;
}

BigInt operator / (BigInt first, BigInt second) {
    if (second == "0")
        throw "Division with 0";

    bool neg = first.neg != second.neg;

    first.neg = false;
    second.neg = false;

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

BigInt operator % (BigInt first, BigInt second) {
    if (second == "0")
        throw "Modulo with 0";

    first.neg = false;
    second.neg = false;

    int i = first.size() - 1;

    BigInt current(first.number[i] - '0');

    --i;

    while (true) {
        BigInt result = current;

        while (result < second && i >= 0)
            result = result * 10 + (first.number[i--] - '0');

        int c = 0;

        BigInt result_(result);

        while (result_ >= second) {
            result_ -= second;
            c++;
        }

        current = result_;

        if (i < 0)
            break;
    }

    current.neg = second.neg;

    return current;
}


BigInt pow(BigInt x, BigInt y, BigInt mod) {
    if (mod != 0)
        x %= mod;

    BigInt res = 1;

    while (y != 0) {
        if (y % 2 == 1) {
            res *= x;

            if (mod != 0)
                res %= mod;
        }

        x *= x;

        if (mod != 0)
            x %= mod;

        y /= 2;
    }

    return res;
}

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
        n = (n * 10) + (bigint.number[i] - '0');

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

int BigInt::size() {
    return this->digits;
}

void BigInt::operator ++ () { *(this) = *(this) + 1; }
void BigInt::operator -- () { *(this) = *(this) - 1; }

void BigInt::operator += (BigInt bigint) { *(this) = *(this) + bigint; }
void BigInt::operator -= (BigInt bigint) { *(this) = *(this) - bigint; }

void BigInt::operator *= (BigInt bigint) { *(this) = *(this) * bigint; }
void BigInt::operator /= (BigInt bigint) { *(this) = *(this) / bigint; }
void BigInt::operator %= (BigInt bigint) { *(this) = *(this) % bigint; }

void BigInt::operator &= (BigInt bigint) { *(this) = *(this) & bigint; }
void BigInt::operator |= (BigInt bigint) { *(this) = *(this) | bigint; }
void BigInt::operator ^= (BigInt bigint) { *(this) = *(this) ^ bigint; }

void BigInt::operator <<= (BigInt bigint) { *(this) = *(this) << bigint; }
void BigInt::operator >>= (BigInt bigint) { *(this) = *(this) >> bigint; }

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