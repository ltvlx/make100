#include <iostream>
#include <cassert>

int gcd(int a, int b)
{
  int a0 = a, a1 = b, a2 = 0;
  int x0 = 1, x1 = 0, x2 = 0;
  int y0 = 0, y1 = 1, y2 = 0;
  int q = 0;

  while( a1 != 0) {
    q = a0 / a1;
    a2 = a0 - a1 * (a0 / a1);
    a0 = a1;
    a1 = a2;

    x2 = x0 - x1 * q;
    x0 = x1;
    x1 = x2;

    y2 = y0 - y1 * q;
    y0 = y1;
    y1 = y2;
  }

  return a0;
}



class Rational_Number {
  private:
    int num;
    int den;

  public:
    Rational_Number() {
      num = 0;
      den = 1;
    }

    Rational_Number(int p, int q) {
      assert(q != 0);
      int d = gcd(p, q);
//std::cout << "gcd = " << d << std::endl;
      if (d != 1) {
        p /= d;
        q /= d;
      }
      if (q < 0) {
        p *= -1;
        q *= -1;
      }
//std::cout << "p = " << p << "  q = " << q << std::endl;
      num = p;
      den = q;
    }

    Rational_Number(int n) {
      num = n;
      den = 1;
    }

    Rational_Number operator=(int n) {
      int p = n;
      int q = 1;
      Rational_Number result(p, q);
      return result;
    }

    bool operator<=(int n) {
      return (num <= static_cast<long long>(n * den));
    }

    Rational_Number operator+(Rational_Number b) {
      int p = this->num * b.den + b.num * this->den;
      int q = this->den * b.den;
      Rational_Number result(p, q);
      return result;
    }

    Rational_Number operator-(Rational_Number b) {
      b.num *= -1;
      return (*this + b);
    }

    Rational_Number operator*(Rational_Number b) {
      int p = this->num * b.num;
      int q = this->den * b.den;
      Rational_Number result(p, q);
      return result;
    }

    Rational_Number operator/(Rational_Number b) {
      assert(b.num != 0);
      int p = this->num * b.den;
      int q = this->den * b.num;
      Rational_Number result(p, q);
      return result;
    }

    Rational_Number operator*=(int n) {
      int p = this->num * n;
      int q = this->den;
      Rational_Number result(p, q);
      *this = result;
    }

    Rational_Number operator+=(int n) {
      int p = this->num + n * this->den;
      int q = this->den;
      Rational_Number result(p, q);
      *this = result;
    }


    bool operator==(Rational_Number b) {
      if (static_cast<long long> (this->num * b.den) == static_cast<long long> (b.num * this->den)) {
        return true;
      }
      return false;
    }

    bool operator==(int n) {
      if ((this->den == 1) && (this->num == n)) {
        return true;
      }
      return false;
    }

    friend std::ostream& operator<<(std::ostream& stream, Rational_Number a);
};


std::ostream& operator<<(std::ostream& stream, Rational_Number a)
{
  if (a.den == 1) {
    stream << a.num;
  } else {
    stream << a.num << "/" << a.den;
  }

  return stream;
}

