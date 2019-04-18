#pragma once

#include <iostream>

class RationalNum 
{
  friend RationalNum operator+(const RationalNum& left, const RationalNum& right);
  friend RationalNum operator-(const RationalNum& left, const RationalNum& right);
  friend RationalNum operator*(const RationalNum& left, const RationalNum& right);
  friend RationalNum operator/(const RationalNum& left, const RationalNum& right);
  friend bool operator==(const RationalNum& left, const RationalNum& right);
  friend bool operator!=(const RationalNum& left, const RationalNum& right);
  friend bool operator<(const RationalNum& left, const RationalNum& right);
  friend bool operator>(const RationalNum& left, const RationalNum& right);
  friend bool operator<=(const RationalNum& left, const RationalNum& right);
  friend bool operator>=(const RationalNum& left, const RationalNum& right);
  friend std::ostream& operator<<(std::ostream& out, const RationalNum& obj);
  
  public:
    RationalNum();    
    RationalNum(int64_t numerator_, int64_t denominator_ = 1);

    RationalNum& operator=(const RationalNum& obj);
    RationalNum& operator+=(const RationalNum& obj);
    RationalNum& operator-=(const RationalNum& obj);
    RationalNum& operator*=(const RationalNum& obj);
    RationalNum& operator/=(const RationalNum& obj);
    RationalNum& operator++();
    RationalNum operator++(int);
    RationalNum& operator--();
    RationalNum operator--(int);
    RationalNum operator+() const;
    RationalNum operator-() const;
   
    void setNumerator(int64_t numerator_);
    int64_t getNumerator() const;
    void setDenominator(int64_t denominator_);
    int64_t getDenominator() const;

  private:
    int64_t numerator;
    int64_t denominator;
    void simplify();
};
