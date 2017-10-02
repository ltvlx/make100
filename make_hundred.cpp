#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
#include "rational.h"

template <typename T> void print_Vector(std::vector<T> const &V)
{
  for (auto iter = V.begin(); iter < V.end(); ++iter) {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
}

template<typename T> T pow(T const &x, int deg)
{
//  assert (deg >= 0);
  if (deg < 0) return 0;

  T result = 1;
  for (int i = 0; i < deg; ++i) {
    result *= x;
  }
  return result;
}

int factorial(int x)
{
  int result = 1;
  for (int i = 1; i <= x; ++i) {
    result *= i;
  }
  return result;
}


Rational_Number operation(Rational_Number x, Rational_Number y, int key)
{
  assert((key >= 0) && (key < 5));
  // 0  x + y
  // 1  x - y
  // 2  x * y
  // 3  x / y
  // 4  pow(x,  y)



  switch (key) {
    case 0: {
      return (x + y);
      break;
    }
    case 1: {
      return (x - y);
      break;
    }
    case 2: {
      return (x * y);
      break;
    }
    case 3: {
      return (x / y);
      break;
    }
//    case 4: {
//      y = static_cast<int> (y);
//      return ( pow(x, y));
//      break;
//    }
    default: {
      return 0;
      break;
    }
  }


}

char operation(int key)
{
  assert((key >= 0) && (key < 5));
  // 0  x + y
  // 1  x - y
  // 2  x * y
  // 3  x / y
  // 4  x % y
  // 5  pow(x,  y)

  switch (key) {
    case 0: {
      return '+';
      break;
    }
    case 1: {
      return '-';
      break;
    }
    case 2: {
      return '*';
      break;
    }
    case 3: {
      return '/';
      break;
    }
    case 4: {
      return '^';
      break;
    }
    default: {
      return ' ';
      break;
    }
  }

}

class Split {
  private:
    bool merge_key[5] = {};

  public:
    Split() {
      merge_key[5] = 0;
    }

    Split(int x) {
      assert((x < 32) && (x >= 0));
      merge_key[0] = x / 16;
      x -= merge_key[0] * 16;
      merge_key[1] = x / 8;
      x -= merge_key[1] * 8;
      merge_key[2] = x / 4;
      x -= merge_key[2] * 4;
      merge_key[3] = x / 2;
      x -= merge_key[3] * 2;
      merge_key[4] = x;
    }

    bool & operator[](int ind) {
      assert((ind >= 0) && (ind < 5));
      return (this->merge_key[ind]);
    }
};

class Operations_Order {
  private:
    int const Nf = 4; // Number of functions used
    std::vector<Rational_Number> number;
    std::vector<int> order;
    std::vector<int> function;

    int find_Zero(std::vector<int> &v) {
      for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] == 0) return i;
      }
      return 0;
    }

    void reduce(std::vector<int> &v) {
      for (size_t i = 0; i < v.size(); ++i) {
        --v[i];
      }
    }

    void next_Function(std::vector<int> &current_function) {
      ++current_function[current_function.size() - 1];
      for (int i = (current_function.size() - 1); i > 0; --i) {
        if (current_function[i] > Nf - 1) {
          current_function[i] -= Nf;
          ++current_function[i - 1];
        }
      }
    }

    bool next_Order(std::vector<int> & a) {
      int n = a.size();
      int j = n - 2;
      while (j != -1 && a[j] >= a[j + 1]) {
        j--;
      }

      if (j != -1) {
        int k = n - 1;
        while (a[j] >= a[k]) {
          k--;
        }
        std::swap(a[j], a[k]);

        int l = j + 1, r = n - 1; // sorting the remaining part of sequence

        while (l < r) {
          std::swap(a[l++], a[r--]);
        }

        return true;
      }
      return false;
    }


    void brackets_Sub(std::vector<Rational_Number> number_p, std::vector<int> order_p, std::vector<int> function_p) {
      if (number_p.size() == 1) {
        std::cout << number_p[0];
        return;
      }

      int order_i_max = 0;
      for (size_t i = 0; i < order_p.size(); ++i) {
        if (order_p[i] > order_p[order_i_max]) {
          order_i_max = i;
        }
      }

      std::vector<Rational_Number> l_number(number_p.begin(), number_p.begin() + order_i_max + 1);
      std::vector<Rational_Number> r_number(number_p.begin() + order_i_max + 1, number_p.end());

      std::vector<int> l_order(order_p.begin(), order_p.begin() + order_i_max);
      std::vector<int> r_order(order_p.begin() + order_i_max + 1, order_p.end());

      std::vector<int> l_function(function_p.begin(), function_p.begin() + order_i_max);
      std::vector<int> r_function(function_p.begin() + order_i_max + 1, function_p.end());


      std::cout << "(";
      brackets_Sub(l_number, l_order, l_function);
      std::cout << operation(function_p[order_i_max]);
      brackets_Sub(r_number, r_order, r_function);
      std::cout << ")";
    }

  public:
    Operations_Order(std::vector<Rational_Number> current_number) {
      number.assign(current_number.begin(), current_number.end());
      order.assign(current_number.size() - 1, 0);
      function.assign(current_number.size() - 1, 0);
      for (size_t i = 0; i < order.size(); ++i) {
        order[i] = i;
      }
    }

    void print() {
      if (number.size() == 0) {
        std::cout << number[0];
        return;
      }
      brackets_Sub(this->number, this->order, this->function);
    }

    void search_Function() {
      // there are Nf ^ k variants
      for (int i = 0; i < pow(Nf, function.size()); ++i) {
        std::cout << "Variant #" << i << "   ";
        print_Vector(function);
        next_Function(function);
      }
    }

    void search_Order() {
      print_Vector(order);
      while (next_Order(order)) {
        std::cout << std::endl;
        print_Vector(order);
        this->print();
        std::cout << " = " << this->solve();
      }
    }

    void search() {
      if (order.size() < 2) {
        if (number[0] == 100) {
          this->print();
          std::cout << " = 100" << std::endl;
        }
        return;
      }
      
      for (int i = 0; i < factorial(order.size()); ++i) {
        for (int j = 0; j < pow (Nf, function.size()); ++j) {
          if (this->solve() == 100) {
            this->print();
            std::cout << " = " << this->solve() << std::endl;
          }
          next_Function(function);
        }
        
				function.assign(function.size(), 0);
        next_Order(order);
      }
    }


    Rational_Number solve() {
      std::vector<int> function_s;
      std::vector<int> order_s;
      std::vector<Rational_Number> number_s;
      
      function_s.assign(function.begin(), function.end());
      order_s.assign(order.begin(), order.end());
      number_s.assign(number.begin(), number.end());

      while (order_s.size() > 0) {

        int k = find_Zero(order_s);
        
        // One cannot divide by zero
        if ((function_s[k] == 3) && (number_s[k + 1] == 0)) {
        	return 0;
				}
        // One cannot take power with negative degree
        if ((function_s[k] == 4)  && (number_s[k + 1] <= 0)) {
        	return 0;
				}
				
				number_s[k + 1] = operation(number_s[k], number_s[k + 1], function_s[k]);
        
        number_s.erase(number_s.begin() + k, number_s.begin() + k + 1);
        order_s.erase(order_s.begin() + k, order_s.begin() + k + 1);
        function_s.erase(function_s.begin() + k, function_s.begin() + k + 1);

        reduce(order_s);
      }
      return number_s[0];
    }
};


class Ticket {
  private:
    int initial_number[6] = {};

    std::vector<Rational_Number> make_Current_Number(Split current_split) {
      std::vector<Rational_Number> current_number;
      current_number.push_back(initial_number[0]);
      for (int i = 0; i < 5; ++i) {
        if (current_split[i]) {
          *(current_number.end() - 1) *= 10;
          *(current_number.end() - 1) += initial_number[i + 1];
        } else {
          current_number.push_back(initial_number[i + 1]);
        }
      }
      return current_number;
    }

  public:
    Ticket() {
      initial_number[6] = 0;
    }

    Ticket(int x) {
      initial_number[0] =  x / 100000;
      initial_number[1] = (x / 10000) % 10;
      initial_number[2] = (x / 1000) % 10;
      initial_number[3] = (x / 100) % 10;
      initial_number[4] = (x / 10) % 10;
      initial_number[5] = x % 10;
    }

    void print_Number() {
      for (int i = 0; i < 6; ++i) {
        std::cout << initial_number[i];
      }
      std::cout << std::endl;
    }

    void search() {
      Split current_split;
      std::cout << "Finding a way to make 100 out of ";
      print_Number();

            // Search sequences
            for (int i = 0; i < 32; ++i) {
              current_split = Split(i);
              std::vector<Rational_Number> current_number = make_Current_Number(current_split);
              Operations_Order current_order(current_number);
      				current_order.search();
            }
    }
};


int main()
{
//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);
   
  int n = 100000;
  std::cout << "Enter a ticket number:" << std::endl;
  std::cin >> n;
  if ((n > 999999) || (n < 0)) {
  	std::cout << "Number should be an integer in the range 0-999999." << std::endl;
  	return 0;
	}
  

  Ticket a(n);
  
  a.search();

//  a = Ticket(-n);
//  a.search();



}
