
#include "pch.h"
#include "Bignumbers.h"

BigNumber BigNumber::Sum(BigNumber other, bool s) {
	if (s) {
		if (!other.sign && sign) {
			other.sign = true;
			BigNumber res = Raznost(other);
			other.sign = false;
			return res;
		}
		else if (other.sign && !sign) {
			sign = true;
			BigNumber res = other.Raznost(*this);
			sign = false;
			return res;
		}
	}
	vector<int> result;
	vector<int> arrmx;
	vector<int> arrmn;
	if (other.number.size() < number.size()) {
		for (int i : number) {
			arrmx.push_back(i);
		}
		for (int i : other.number) {
			arrmn.push_back(i);
		}
	}
	else {
		for (int i : number) {
			arrmn.push_back(i);
		}
		for (int i : other.number) {
			arrmx.push_back(i);
		}
	}
	//cout << arrmx.size() << " ----- "<< arrmn.size()<<endl;
	int tep;
	reverse(begin(arrmx), end(arrmx));
	reverse(begin(arrmn), end(arrmn));
	int temp = 0;
	for (int i = 0; i < arrmx.size(); i++) {
		if (i < arrmn.size()) {
			if (arrmx[i] + arrmn[i] > 9) {
				result.push_back((arrmx[i] + arrmn[i] + temp) % 10);
				temp = (arrmx[i] + arrmn[i] + temp) / 10;
			}
			else {
				result.push_back((arrmx[i] + arrmn[i] + temp) % 10);
				temp = (arrmx[i] + arrmn[i] + temp) / 10;
			}

		}
		else {
			result.push_back((arrmx[i] + temp) % 10);
			temp = (arrmx[i] + temp) / 10;
		}
		//cout << i << " **  " << result[i] << endl;
	}
	if (temp > 0) result.push_back(temp);
	reverse(begin(result), end(result));
	BigNumber res = BigNumber(result);
	if (!sign && !other.sign) res.sign = false;
	return BigNumber(res);
}

BigNumber BigNumber::Mult(BigNumber other) {
	BigNumber result = BigNumber();
	//arr1 arr2 - мен€ютс€
	//arr1 <->
	vector<int> arr1;
	vector<int> arr2;
	for (int i : number) {
		arr1.push_back(i);
	}
	for (int i : other.number) {
		arr2.push_back(i);
	}
	reverse(begin(arr2), end(arr2));
	int temp = 0;
	// умножаем число на число полностью
	for (int i = 0; i < arr2.size(); i++) {
		//сколько раз мы должны прибавить на число
		for (int j = 0; j < arr2[i]; j++) {
			result = result.Sum(arr1, false);
		}
		arr1.push_back(0);
	}
	result.remove_zeros();
	if ((sign && !other.sign) || (!sign && other.sign)) result.sign = false;
	return result;
}

BigNumber BigNumber::Raznost(BigNumber other) {
	vector<int> arrmx;
	vector<int> arrmn;
	if (sign && !other.sign) {
		other.sign = true;
		BigNumber res = Sum(other, true);
		other.sign = false;
		return res;
	}
	if (!sign && other.sign) {
		BigNumber res = Sum(other, false);
		res.sign = false;
		return res;
	}
	BigNumber result = BigNumber();
	if (this->isGreater(other)) {
		for (int i : number) {
			arrmx.push_back(i);
		}
		for (int i : other.number) {
			arrmn.push_back(i);
		}
	}
	else {
		for (int i : number) {
			arrmn.push_back(i);
		}
		for (int i : other.number) {
			arrmx.push_back(i);
		}
	}
	reverse(begin(arrmx), end(arrmx));
	reverse(begin(arrmn), end(arrmn));
	while (arrmx.size() != 0) {
		if (arrmn.size() > 0) {
			if (arrmx[0] >= arrmn[0]) {
				result.number.push_back(arrmx[0] - arrmn[0]);
				arrmx.erase(begin(arrmx));
				arrmn.erase(begin(arrmn));

			}
			else {
				int i = 1;
				while (arrmx[i] == 0) {
					arrmx[i] += 9;
					i++;
				}
				arrmx[i] -= 1;
				arrmx[0] += 10;
				result.number.push_back(arrmx[0] - arrmn[0]);
				arrmx.erase(begin(arrmx));
				arrmn.erase(begin(arrmn));
			}
		}
		else {
			result.number.push_back(arrmx[0]);
			arrmx.erase(begin(arrmx));
		}
	}
	reverse(begin(result.number), end(result.number));
	result.remove_zeros();
	if (!this->isGreater(other)) {
		result.sign = false;
	}
	if (!sign && !other.sign)
	{
		if (isGreater(other)) {
			result.sign = false;
		}
		else result.sign = true;
	}
	return result;
}



BigNumber   BigNumber::Division(BigNumber other) {
	BigNumber bn1 = copy();
	BigNumber bn2 = other.copy();
	bn1.sign = true;
	bn2.sign = true;
	BigNumber result = BigNumber();
	BigNumber temp = BigNumber();
	while (bn1.number.size() != 0) {
		while (bn2.isGreater(temp)) {
			if (bn1.number.size() > 0) {
				temp.number.push_back(bn1.number[0]);
				bn1.number.erase(begin(bn1.number));
			}
			else {
				break;
			}
		}
		result.number.push_back(0);
		while (temp.isGreater(bn2)) {
			temp = temp.Raznost(bn2);
			result.number[result.number.size() - 1] += 1;
		}
	}
	if ((sign && !other.sign) || (!sign && other.sign)) {
		result.sign = false;
	}
	return result;
}

BigNumber BigNumber::Ostatok(BigNumber other) {
	BigNumber bn1 = copy();
	BigNumber bn2 = other.copy();
	BigNumber result = BigNumber();
	BigNumber temp = BigNumber();
	while (bn1.number.size() != 0) {
		while (bn2.isGreater(temp)) {
			if (bn1.number.size() > 0) {
				temp.number.push_back(bn1.number[0]);
				bn1.number.erase(begin(bn1.number));
			}
			else {
				break;
			}
		}
		result.number.push_back(0);
		while (temp.isGreater(bn2)) {
			temp = temp.Raznost(bn2);
			result.number[result.number.size() - 1] += 1;
		}
	}
	if ((sign && !other.sign) || (!sign && other.sign)) {
		result.sign = false;
	}
	return temp;
}

BigNumber BigNumber::copy() {
	BigNumber result = BigNumber();
	result.sign = sign;
	for (int i : number) {
		result.number.push_back(i);
	}
	return result;
}

bool BigNumber::isGreater(BigNumber other) {
	remove_zeros();
	other.remove_zeros();
	if (number.size() > other.number.size()) return true;
	if (number.size() < other.number.size()) return false;
	for (int i = 0; i < number.size(); i++) {
		//cout << "here "; print(); cout << endl; other.print(); cout << endl;
		if (number[i] > other.number[i]) return true;
		else if (number[i] < other.number[i]) return false;
	}
	//числа равны
	return true;
}

void BigNumber::print() {
	if (!sign)
		cout << '-';
	for (int i : number) {
		cout << i;
	}
	if (fraction.size() != 0) cout << ".";
	for (int i : fraction) {
		cout << i;
	}
}
void BigNumber::remove_zeros() {
	if (number.size() <= 0) return;
	while (number[0] == 0 && number.size() > 1) {
		number.erase(begin(number));
	}
}


void vivod::Vivod(BigNumber a1, BigNumber a2) {
	int k = 0;
	do {
		BigNumber result;
		string esname;
		cout << "Enter operation * or + or - or / or % or type \"quit\"" << endl;
		getline(std::cin, esname);
		if (esname == "+") { //—умма
			result = a1.Sum(a2, true);
			a1.print(); cout << " + ";
			a2.print(); cout << " = ";
			result.print();
			cout << endl;
		}
		else if (esname == "*") {  //”множение
			result = a1.Mult(a2);
			a1.print(); cout << " * ";
			a2.print(); cout << " = ";
			result.print();
			cout << endl;
		}
		else if (esname == "-") {
			result = a1.Raznost(a2);
			a1.print(); cout << " - ";
			a2.print(); cout << " = ";
			result.print();
			cout << endl;
		}
		else if (esname == "/") {  //ƒеление
			result = a1.Division(a2);
			a1.print(); cout << " / ";
			a2.print(); cout << " = ";
			result.print();
			cout << endl;
		}
		else if (esname == "%") {   //ƒеление с остатком
			result = a1.Ostatok(a2);
			a1.print(); cout << " % ";
			a2.print(); cout << " = ";
			result.print();
			cout << endl;
		}
		else if (esname == "quit") break;
		/*cout << a1.size() << " - " << a2.size() << endl;
		cout << " ------- " << endl;*/
		//print(result);
		k++;
	}

	while (k == 1);
}
