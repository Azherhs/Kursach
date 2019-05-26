#ifndef UNTITLED28_BIGNEMBER_H
#define UNTITLED28_BIGNEMBER_H
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
class BigNumber {
public:
	vector<int> number;
	vector<int> fraction;
	bool sign = true;
	BigNumber(string num) {
		string s = "";
		if (num.length() > 0 && num[0] == '-') {
			sign = false;
			for (int i = 0; i < num.length(); i++) {
				if (i != 0) s += num[i];
			}
			num = s;
		}
		for (char c : num) {
			number.push_back(CharToDigit(c));
		}
	}
	BigNumber(string num, string frac) {
		string s = "";
		if (num.length() > 0 && num[0] == '-') {
			sign = false;
			for (int i = 0; i < num.length(); i++) {
				if (i != 0) s += num[i];
			}
			num = s;
		}
		for (char c : num) {
			number.push_back(CharToDigit(c));
		}
		for (char c : frac) {
			fraction.push_back(CharToDigit(c));
		}
	}
	BigNumber() {
		//number.push_back(0);
	}
	BigNumber(vector<int> numb) {
		for (int i : numb) {
			number.push_back(i);
		}
	}
	BigNumber(vector<int> numb, vector<int> frac) {
		for (int i : numb) {
			number.push_back(i);
		}
		for (int i : frac) {
			fraction.push_back(i);
		}
	}
	BigNumber Sum(BigNumber other, bool s);
	BigNumber Mult(BigNumber other);
	BigNumber Raznost(BigNumber other);
	BigNumber Division(BigNumber other);
	BigNumber Ostatok(BigNumber other);
	BigNumber copy();
	bool isGreater(BigNumber other);
	virtual void Display() {

	}
	void print();
	static int CharToDigit(const char &ch) {
		switch (ch) {
		case('1'):
			return 1;
		case('2'):
			return 2;
		case('3'):
			return 3;
		case('4'):
			return 4;
		case('5'):
			return 5;
		case('6'):
			return 6;
		case('7'):
			return 7;
		case('8'):
			return 8;
		case('9'):
			return 9;
		case('0'):
			return 0;
		default:
			return -1;
		}
	}
private:
	void remove_zeros();
};
class vvod:public BigNumber{// ƒолжен быть метод старт цикл из мейна вз€ть код чтобы вводить, 
public:
	string name;
	string s1;
	int len1;
	int len2;
	BigNumber number1;
	BigNumber number2;
	void Start() {
		int k = 1;
		do {
			cout << "Enter numbers or type \"quit\"" << endl;
			getline(std::cin, name);
			
			if (name == "quit") break; 
			len1 = name.length();
			s1 = name;
			number1 = BigNumber(name);
			getline(std::cin, name);
			len2 = name.length();
			number2 = BigNumber(name);
			cout << "====" << endl;
			number1.print();
			cout << endl;
			number2.print();
			cout << endl;
			cout << "====" << endl;
			k++;
		} while (k == 1);
	}
	BigNumber vernut1() {
		return number1;
	}
	BigNumber vernut2() {
		return number2;
	}

		friend class BigNumber;

};
class vivod :public vvod { // Ѕерем мейн вывод, каждый метод выводит операцию.
public:
	void Vivod(BigNumber, BigNumber);
	friend class vvod;
};
#endif //UNTITLED28_BIGNEMBER_H
