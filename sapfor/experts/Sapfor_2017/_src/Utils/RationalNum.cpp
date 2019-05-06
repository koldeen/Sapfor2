#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <limits.h>

#include "RationalNum.h"

using std::vector;
using std::ostream;

static inline void getFactors(int num, vector<int64_t>& factorSet) 
{
    if (num != 1) 
        factorSet.push_back(num);
    
    for (int i = 2; i <= sqrt(static_cast<double>(num)); i++) 
    {
        if (num % i == 0) 
        {
            factorSet.push_back(i);
            factorSet.push_back(num / i);
        }
    }
}

static inline void simplifyFun(int64_t& a, int64_t& b)
{
    int64_t tempN = a;
    int64_t tempD = b;
    int64_t small, temp;
    vector<int64_t> factorSet;
    if (tempN == tempD) 
    {
        a = 1;
        b = 1;
        return;
    }
    else if (tempN == -tempD) 
    {
        a = -1;
        b = 1;
        return;
    }
    else if (tempN == 0)
    {
        b = 1;
        return;
    }

    if (abs(tempN) < abs(tempD)) 
        small = abs(tempN);    
    else 
        small = abs(tempD);    

    getFactors(small, factorSet);
    for (int i = 0; i < factorSet.size(); i++) 
    {
        temp = factorSet[i];
        while (tempN % temp == 0 && tempD % temp == 0) 
        {
            tempN /= temp;
            tempD /= temp;
        }
    }
    a = tempN;
    b = tempD;
}


//friend functions definitions
RationalNum operator+(const RationalNum& left, const RationalNum& right) 
{
    RationalNum temp;
    int64_t tempLD = left.getDenominator();
    int64_t tempRD = right.getDenominator();
    simplifyFun(tempLD, tempRD);
    temp.setDenominator(left.getDenominator() * tempRD);
    temp.setNumerator(left.getNumerator() * tempRD + right.getNumerator() * tempLD);
    temp.simplify();
    return temp;
}

RationalNum operator-(const RationalNum& left, const RationalNum& right) { return left + (-right); }

RationalNum operator*(const RationalNum& left, const RationalNum& right) 
{
    RationalNum temp;
    RationalNum temp_2(right.getNumerator(), left.getDenominator());
    RationalNum temp_3(left.getNumerator(), right.getDenominator());
    auto a = temp_2.getDenominator();
    auto b = temp_2.getNumerator();
    auto c = temp_3.getDenominator();
    auto d = temp_3.getNumerator();
    temp.setNumerator(b * d);
    temp.setDenominator(a * c);
    return temp;
}

RationalNum operator/(const RationalNum& left, const RationalNum& right) 
{
    RationalNum temp_1(left.getNumerator(), left.getDenominator());
    RationalNum temp_2(right.getDenominator(), right.getNumerator());
    return temp_1 * temp_2;
}

bool operator==(const RationalNum& left, const RationalNum& right) 
{
    return (left.numerator == right.numerator && left.denominator == right.denominator);
}

bool operator!=(const RationalNum& left, const RationalNum& right) { return !(left == right); }

bool operator<(const RationalNum& left, const RationalNum& right) 
{
    auto lside = left.getNumerator() * right.getDenominator();
    auto rside = left.getDenominator() * right.getNumerator();
    return (lside < rside);
}

bool operator>(const RationalNum& left, const RationalNum& right) 
{
    auto lside = left.getNumerator()*right.getDenominator();
    auto rside = left.getDenominator()*right.getNumerator();
    return (lside > rside);
}

bool operator<=(const RationalNum& left, const RationalNum& right) { return ((left < right) || (left == right)); }

bool operator>=(const RationalNum& left, const RationalNum& right) { return ((left > right) || (left == right)); }

ostream& operator<<(ostream& out, const RationalNum& obj) 
{
    out << obj.numerator;
    if (obj.numerator != 0 && obj.denominator != 1)     
        out << "/" << obj.denominator;    
    return out;
}


//member function definition
RationalNum::RationalNum()
{
    setNumerator(0);
    setDenominator(1);
}

RationalNum::RationalNum(int64_t numerator_, int64_t denominator_)
{
    setNumerator(numerator_);
    setDenominator(denominator_);
    simplify();
}

RationalNum& RationalNum::operator=(const RationalNum& obj) 
{
    setNumerator(obj.getNumerator());
    setDenominator(obj.getDenominator());
    return *this;
}

RationalNum& RationalNum::operator+=(const RationalNum& obj) 
{
    *this = *this + obj;
    return *this;
}

RationalNum& RationalNum::operator-=(const RationalNum& obj) 
{
    *this = *this - obj;
    return *this;
}

RationalNum& RationalNum::operator*=(const RationalNum& obj) 
{
    *this = *this*obj;
    return *this;
}

RationalNum& RationalNum::operator/=(const RationalNum& obj)
{
    *this = *this / obj;
    return *this;
}

RationalNum& RationalNum::operator++() 
{
    *this = *this + 1;
    return *this;
}

RationalNum RationalNum::operator++(int) 
{
    RationalNum before = *this;
    *this = *this + 1;
    return before;
}

RationalNum& RationalNum::operator--()
{
    *this = *this - 1;
    return *this;
}

RationalNum RationalNum::operator--(int) 
{
    RationalNum before = *this;
    *this = *this - 1;
    return before;
}

RationalNum RationalNum::operator+() const { return *this; }

RationalNum RationalNum::operator-() const 
{
    RationalNum temp;
    temp.setNumerator(-getNumerator());
    temp.setDenominator(getDenominator());
    return temp;
}

void RationalNum::setNumerator(int64_t numerator_) { numerator = numerator_; }

int64_t RationalNum::getNumerator() const { return numerator; }

void RationalNum::setDenominator(int64_t denominator_) 
{ 
    if (denominator_ == 0) 
    {
        denominator = 1;
        numerator = 0;
        std::cout << "Denominator is 0! Not good! THe whole is set to 0." << std::endl;
    }
    else 
        denominator = denominator_;    
}

int64_t RationalNum::getDenominator() const { return denominator; }

void RationalNum::simplify() 
{
    int64_t tempN = numerator;
    int64_t tempD = denominator;
    simplifyFun(tempN, tempD);
    setNumerator(tempN);
    setDenominator(tempD);
}
