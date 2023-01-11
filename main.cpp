#include <iostream>
#include <vector>
#include <string>

class BigInt {
public:
    ~BigInt()
    {
    }
    BigInt()
    {
      negative = false;
    }
    BigInt(int b) {
      if (b < 0) {
        negative = true;
        b *= -1;
      }
      a.push_back(b);
    }
    bool operator<(BigInt const &right) const{
      std::vector<int> const &b = right.a;
      // a < b == true
      if (a.size() > b.size()) return false;
      if (a.size() < b.size()) return true;
      for (int i = a.size() - 1; i >= 0; i--) {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
      }
      return false;
    }

    friend std::ostream& operator<< (std::ostream &out, const BigInt &b);
    friend std::istream& operator>> (std::istream &in, BigInt &b);
    friend BigInt operator-(BigInt const &left, BigInt const &right);
    friend BigInt operator+(BigInt const &left, BigInt const &right);
    friend BigInt operator*(BigInt const &left, BigInt const &right);
    friend BigInt operator/(BigInt const &left, int b);
private:
    bool negative;
    std::vector<int> a;
};

std::ostream& operator<< (std::ostream &out, const BigInt &b) {
  bool const &negative = b.negative;
  std::vector <int> const &a = b.a;
  if (negative) out <<'-';
  for (int i = (int)a.size() - 1; i >= 0; i--) {
    if (i == (int)a.size() - 1) {
      out << a[i];
    } else {
      for (int j = 0; j < 9 - std::to_string(a[i]).length(); j++)
        out << 0;
      out << a[i];
    }
  }
  out << '\n';
  return out;
}
std::istream& operator>> (std::istream &in, BigInt &b) {
  bool &negative = b.negative;
  std::vector <int> &a = b.a;
  std::string s;
  in >> s;
  if (s[0] == '-') negative = true;
  for (int i = s.length(); i > 0; i -= 9)
    if (i < 9)
      a.push_back(atoi(s.substr(0, i).c_str()));
    else
      a.push_back(atoi(s.substr(i - 9, 9).c_str()));
  return in;
}

BigInt operator-(BigInt const &left, BigInt const &right) {
  // a - b = - (b - a), при b > a
  BigInt c;

  std::vector<int> &raz = c.a;
  std::vector<int> const &b = (left < right ? left.a : right.a);
  std::vector<int> const &a = (left < right ? right.a : left.a);
  if (left < right) {
    c.negative = true;
  }
  raz = a;
  for (int i = 0; i < a.size(); i++) {
    if (i < b.size()) raz[i] -= b[i];
    if (i != 0 && raz[i - 1] < 0) {
      raz[i - 1] += 1e9;
      raz[i]--;
    }
  }
  while (raz.size() > 1 && raz.back() == 0) raz.pop_back();
  return c;
}
BigInt operator+(BigInt const &left, BigInt const &right) {
  BigInt c;
  std::vector<int> &sum = c.a;
  std::vector<int> const &b = right.a;
  std::vector<int> const &a = left.a;
  sum.resize(std::max(a.size(), b.size()), 0);
  for (int i = 0; i < std::max(a.size(), b.size()); i++) {
    if (i < a.size()) sum[i] += a[i];
    if (i < b.size()) sum[i] += b[i];
    if (i != 0 && sum[i - 1] >= 1e9) {
      sum[i - 1] -= 1e9;
      sum[i]++;
    }
  }
  return c;
}
BigInt operator*(BigInt const &left, BigInt const &right) {
  BigInt c;
  std::vector<int> &umn = c.a;
  std::vector<int> const &b = right.a;
  std::vector<int> const &a = left.a;
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
BigInt operator/(BigInt const &left, int b) {
  BigInt c;
  std::vector<int> &del = c.a;
  std::vector<int> const &a = left.a;
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

signed main() {
  BigInt a, b, c;
  std::cin >> a >> b;

  ///сложение
  //  c = a + b;

  ///вычитание
  //  c = a - b;

  ///умножение
  //  c = a * b;

  ///деление, b2 < 1e9
  //  int b2;
  //  std::cin >> b2;
  //  c = a / b2;

  std::cout << c;
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
