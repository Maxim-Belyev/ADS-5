// Copyright 2021 NNTU-CS
#include <string>
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
template<typename T, int size>
class TStack {
 private:
    T arr[100];
    int m;
 
public:
    TStack(): m(-1) {}
    void push(T value) {
      if (!isFull())
        arr[++m] = value;
      else
        throw std::string("Full");
    }
    T get() const {
      return arr[m];
    }
    T pop() {
      if (isEmpty())
        throw std::string("Empty");
      else
        return arr[m--];
    }
    bool isEmpty() const {
      return m == -1;
    }
    bool isFull() const {
      return m == size - 1;
    }
};
#endif
#include <map>
#include "tstack.h"
int scum(char n) {
  switch (n) {
    case '(':
      return 0;
    case ')':
      return 1;
    case '+': case '-':
      return 2;
    case '*': case '/':
      return 3;
    default:
      return -1;
    }
}
std::string infx2pstfx(std::string inf) {
  std::string res, res1;
  TStack<char, 100>stack1;
  for (auto& n : inf) {
    int a = scum(n);
    if (a == -1) {
      res = res + n + ' ';
    } else {
      char el = stack1.get();
      if (n == 0 || scum(el) < a || stack1.isEmpty()) {
        stack1.push(n);
      } else {
        if (n == ')') {
          while (scum(el) >= n) {
            res = res + el + ' ';
            stack1.pop();
            el = stack1.get();
          }
          stack1.pop();
        } else {
          while (scum(el) >= a) {
            res = res + el + ' ';
            stack1.pop();
            el = stack1.get();
          }
          stack1.push(n);
        }
      }
    }
  }
  while (!stack1.isEmpty()) {
    res = res + stack1.get() + ' ';
    stack1.pop();
  }
  for (int i = 0; i < res.size() - 1; i++)
    res1 += res[i];
  return res1;
}
int scum1(const int& x, const int& y, const int& n) {
  switch (n) {
    case '+':
      return x + y;
    case '-':
      return x - y;
    case '/':
      return x / y;
    case '*':
      return x * y;
    default:
      return 0;
  }
}
int eval(std::string pref) {
  TStack<int, 100> stack1;
  std::string res = "";
  for (int i = 0; i < pref.size(); i++) {
    char el = pref[i];
    if (scum(el) == -1) {
      if (pref[i] == ' ') {
        continue;
      } else if (isdigit(pref[i+1])) {
        res += pref[i];
        continue;
      } else {
        res += pref[i];
        stack1.push(atoi(res.c_str()));
        res = "";
      }
    } else {
      int y = stack1.get();
      stack1.pop();
      int a = stack1.get();
      stack1.pop();
      stack1.push(schet(a, y, el));
    }
  }
  return stack1.get();
}
