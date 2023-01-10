#include <iostream>
#include <vector>
#include <string>

class BigInt {
public:
    //~BigInt();
    std::vector<int> a;
    bool negative = false;
    void Read();
    void Print();
    bool operator<(BigInt &right) {
      std::vector<int> &b = right.a;
      // a < b == true
      if (a.size() > b.size()) return false;
      if (a.size() < b.size()) return true;
      for (int i = 0; i < a.size(); i++) {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
      }
      return false;
    }
    BigInt operator+(BigInt &right) {
      BigInt c;
      std::vector<int> &sum = c.a;
      std::vector<int> &b = right.a;
      for (int i = 0; i < std::max(a.size(), b.size()); i++) {
        sum.push_back(0);
        // if (i == a.size()) a.push_back(0);
        if (i < a.size()) sum[i] += a[i];
        if (i < b.size()) sum[i] += b[i];
        if (i != 0 && sum[i - 1] >= 1e9) {
          sum[i - 1] -= 1e9;
          sum[i]++;
        }
      }
      return c;
    }
    BigInt operator-(BigInt &right) {
      // a - b = - (b - a), при b > a
      BigInt c;
      std::vector<int> &raz = c.a;
      std::vector<int> &b = right.a;
      for (int i = 0; i < a.size(); i++) {
        raz.push_back(0);
        raz[i] = a[i];
        if (i < b.size()) raz[i] -= b[i];
        if (i != 0 && raz[i - 1] < 0) {
          raz[i - 1] += 1e9;
          raz[i]--;
        }
      }
      while (raz.size() > 1 && raz.back() == 0) raz.pop_back();
      return c;
    }
    BigInt operator*(BigInt &right) {
      BigInt c;
      std::vector<int> &umn = c.a;
      std::vector<int> &b = right.a;
      umn.resize(a.size() + b.size(), 0);
      for (int i = 0; i < a.size(); i++) {
        for (int j = 0, carry = 0; j < b.size() || carry; j++) {
          long long cur =
                  umn[i + j] + a[i] * 1ll * (j < (int)b.size() ? b[j] : 0) + carry;
          long long base = 1e9;
          umn[i + j] = int(cur % base);
          carry = int(cur / base);
        }
      }
      while (umn.size() > 1 && umn.back() == 0) umn.pop_back();
      return c;
    }
    BigInt operator/(int b) {
      BigInt c;
      std::vector<int> &del = c.a;
      int carry = 0;
      del.resize(a.size(), 0);
      for (int i = (int)a.size() - 1; i >= 0; i--) {
        long long cur = a[i] + 1ll * carry * 1e9;
        del[i] = cur / b;
        carry = cur % b;
      }
      while (del.size() > 1 && del.back() == 0) del.pop_back();
      return c;
    }
};

void BigInt::Read() {
  std::string s;
  std::cin >> s;
  if (s[0] == '-') negative = true;
  for (int i = s.length(); i > 0; i -= 9)
    if (i < 9)
      a.push_back(atoi(s.substr(0, i).c_str()));
    else
      a.push_back(atoi(s.substr(i - 9, 9).c_str()));
}

void BigInt::Print() {
  // printf ("%d", a.empty() ? 0 : a.back());
  if (negative) std::cout <<'-';
  for (int i = (int)a.size() - 1; i >= 0; i--) {
    if (i == (int)a.size() - 1) {
      std::cout << a[i];
    } else {
      for (int j = 0; j < 9 - std::to_string(a[i]).length(); j++)
        std::cout << 0;
      std::cout << a[i];
    }
  }
  std::cout << '\n';
}

signed main() {
  BigInt a, b, c;
  a.Read();
  b.Read();
  ///сложение
  //  c = a + b;

  ///вычитание
  //  if (a < b) {
  //    c = b - a;
  //    c.negative = true;
  //  } else
  //    c = a - b;

  ///умножение
  //  c = a * b;

  ///деление, b2 < 1e9
  //  int b2;
  //  std::cin >> b2;
  //  c = a / b2;

  c.Print();
}
/*
1234567890000
1234567899123
1234567890000

 456731831
*
    374612
----------


48218624
7896521
 */
