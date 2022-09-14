#pragma once
#include <exception>
#include <iostream>
#include <algorithm>

int gcd(int first_number, int second_number) {
    first_number = abs(first_number);
    second_number = abs(second_number);
    while (second_number) {
        first_number %= second_number;
        std::swap(first_number, second_number);
    }
    return first_number;
}

int lcd(int first_number, int second_number) {
    return (first_number * second_number) / gcd(first_number, second_number);
}

class Fraction {
 public:
  Fraction();

  Fraction(int num, int den);
  explicit Fraction(int num);

  Fraction(const Fraction& other);

  ~Fraction() = default;

  int num() const { return num_; }
  int den() const { return den_; }

  /* your code here */
  friend std::ostream& operator<<(std::ostream& out, const Fraction& fract);

  friend Fraction operator+(Fraction lhs, Fraction rhs);
  friend Fraction operator+(Fraction lhs, int rhs);
  friend Fraction operator+(int lhs, Fraction rhs);

  friend Fraction operator-(Fraction lhs, Fraction rhs);
  friend Fraction operator-(Fraction lhs, int rhs);
  friend Fraction operator-(int lhs, Fraction rhs);

  friend Fraction operator*(Fraction lhs, Fraction rhs);
  friend Fraction operator*(Fraction lhs, int rhs);
  friend Fraction operator*(int lhs, Fraction rhs);

  friend Fraction operator/(Fraction lhs, Fraction rhs);
  friend Fraction operator/(Fraction lhs, int rhs);
  friend Fraction operator/(int lhs, Fraction rhs);

  Fraction& operator=(Fraction& other);

  Fraction operator+() { return *this; }
  Fraction operator-() {
    num_ = -num_;
    return *this;
  }

  Fraction& operator++() {
    *this += 1;
    return *this;
  }
  Fraction& operator--() {
    *this -= 1;
    return *this;
  }
  Fraction operator++(int notused) {
    Fraction val = *this;
    ++(*this);
    return val;
  }
  Fraction operator--(int notused) {
    Fraction val = *this;
    --(*this);
    return val;
  }

  Fraction& operator+=(Fraction other);
  Fraction& operator+=(int other);

  Fraction& operator-=(Fraction other);
  Fraction& operator-=(int other);

  Fraction& operator*=(Fraction other);
  Fraction& operator*=(int other);

  Fraction& operator/=(Fraction other);
  Fraction& operator/=(int other);

  friend bool operator<(Fraction lhs, Fraction rhs);
  friend bool operator<(Fraction lhs, int rhs);
  friend bool operator<(int lhs, Fraction rhs);

  friend bool operator>(Fraction lhs, Fraction rhs);
  friend bool operator>(Fraction lhs, int rhs);
  friend bool operator>(int lhs, Fraction rhs);

  friend bool operator<=(int lhs, Fraction rhs);
  friend bool operator<=(Fraction lhs, Fraction rhs);
  friend bool operator<=(Fraction lhs, int rhs);

  friend bool operator>=(int lhs, Fraction rhs);
  friend bool operator>=(Fraction lhs, Fraction rhs);
  friend bool operator>=(Fraction lhs, int rhs);

  friend bool operator==(int lhs, Fraction rhs);
  friend bool operator==(Fraction lhs, Fraction rhs);
  friend bool operator==(Fraction lhs, int rhs);

  friend bool operator!=(int lhs, Fraction rhs);
  friend bool operator!=(Fraction lhs, Fraction rhs);
  friend bool operator!=(Fraction lhs, int rhs);

 private:
  int num_, den_;
};

Fraction::Fraction():  num_(0), den_(1) {}
Fraction::Fraction(int num, int den) {
    if (den == 0) {
        throw std::logic_error("");
    }
    num_ = num / gcd(num, den);
    den_ = den / gcd(num, den);
}

Fraction::Fraction(int num) : num_(num), den_(1) {};
Fraction::Fraction(const Fraction& other) {
    num_ = other.num();
    den_ = other.den();
}


Fraction& Fraction::operator=(Fraction& other) {
    num_ = other.num();
    den_ = other.den();
    return *this;
}

Fraction operator+(Fraction lhs, Fraction rhs) {
    int tmp_lcd = lcd(lhs.den_, rhs.den_);
    lhs.num_ = lhs.num_ * (tmp_lcd / lhs.den_);
    rhs.num_ = rhs.num_ * (tmp_lcd / rhs.den_);
    lhs.num_ += rhs.num_;
    lhs.den_ = tmp_lcd;

    return Fraction(lhs.num_, lhs.den_);   
}

Fraction operator+(int lhs, Fraction rhs) {
    Fraction tmp(lhs, 1);
    return tmp + rhs;
}

Fraction operator+(Fraction lhs, int rhs) {
    return rhs + lhs;
}

Fraction operator-(Fraction lhs, Fraction rhs) {
    rhs.num_ = -rhs.num_;
    return lhs + rhs;
}

Fraction operator-(int lhs, Fraction rhs) {
    Fraction tmp(lhs, 1);
    return tmp - rhs;
}

Fraction operator-(Fraction lhs, int rhs) {
    return -rhs + lhs;
}

Fraction operator*(Fraction lhs, Fraction rhs) {
    lhs.num_ *= rhs.num_;
    lhs.den_ *= rhs.den_;
    return lhs + 0;
}

Fraction operator*(int lhs, Fraction rhs) {
    rhs.num_ *= lhs;
    return rhs + 0;
}

Fraction operator*(Fraction lhs, int rhs) {
    return rhs * lhs;
}

Fraction operator/(Fraction lhs, Fraction rhs) {
    if (rhs.num_ == 0) 
        throw std::logic_error("");
    lhs.num_ *= rhs.den_;
    lhs.den_ *= rhs.num_;
    return lhs + 0;
}

Fraction operator/(int lhs, Fraction rhs) {
    if (rhs.num_ == 0)
        throw std::logic_error("");
    int tmp = rhs.num_;
    rhs.num_ = rhs.den_ * lhs;
    rhs.den_ = tmp;
    return rhs + 0;
}

Fraction operator/(Fraction lhs, int rhs) {
    if (rhs == 0)
        throw std::logic_error("");
    lhs.den_ *= rhs;
    return lhs + 0;
}


Fraction& Fraction::operator+=(Fraction other) {
  Fraction tmp = *this + other;
  *this = tmp;
  return *this;
}

Fraction& Fraction::operator+=(int other) {
    Fraction tmp = *this + other;
    *this = tmp;
    return *this;
}


Fraction& Fraction::operator-=(Fraction other) {
    Fraction tmp = *this - other;
    *this = tmp;
    return *this;
}

Fraction& Fraction::operator-=(int other) {
    Fraction tmp = *this - other;
    *this = tmp;
    return *this;
}


Fraction& Fraction::operator*=(Fraction other) {
    Fraction tmp = *this * other;
    *this = tmp;
    return *this;
}

Fraction& Fraction::operator*=(int other) {
    Fraction tmp = *this * other;
    *this = tmp;
    return *this;
}


Fraction& Fraction::operator/=(Fraction other) {
    Fraction tmp = *this / other;
    *this = tmp;
    return *this;
}

Fraction& Fraction::operator/=(int other) {
    Fraction tmp = *this / other;
    *this = tmp;
    return *this;
}


bool operator<(Fraction lhs, int rhs) {
    return (lhs - rhs).num_ < 0;
}

bool operator<(Fraction lhs, Fraction rhs) {
    return (lhs - rhs).num_ < 0;
}

bool operator<(int lhs, Fraction rhs) {
    return (lhs - rhs).num_ < 0;
}


bool operator>(Fraction lhs, int rhs) {
    return rhs < lhs;
}

bool operator>(Fraction lhs, Fraction rhs) {
    return rhs < lhs;
}

bool operator>(int lhs, Fraction rhs) {
    return rhs < lhs;
}



bool operator<=(Fraction lhs, int rhs) {
    return !(lhs > rhs);
}

bool operator<=(Fraction lhs, Fraction rhs) {
    return !(lhs > rhs);
}

bool operator<=(int lhs, Fraction rhs) {
    return !(lhs > rhs);
}



bool operator>=(Fraction lhs, int rhs) {
    return !(lhs < rhs);
}

bool operator>=(Fraction lhs, Fraction rhs) {
    return !(lhs < rhs);
}

bool operator>=(int lhs, Fraction rhs) {
    return !(lhs < rhs);
}



bool operator==(Fraction lhs, int rhs) {
    return (lhs >= rhs) && (rhs >= lhs);
}

bool operator==(Fraction lhs, Fraction rhs) {
    return (lhs >= rhs) && (rhs >= lhs);
}

bool operator==(int lhs, Fraction rhs) {
    return (lhs >= rhs) && (rhs >= lhs);
}



bool operator!=(Fraction lhs, int rhs) {
    return !(lhs == rhs);
}

bool operator!=(Fraction lhs, Fraction rhs) { return !(lhs == rhs); }

bool operator!=(int lhs, Fraction rhs) { return !(lhs == rhs); }

std::ostream& operator<<(std::ostream& out, const Fraction& fract) {
  return out << fract.num() << "/" << fract.den();
}
