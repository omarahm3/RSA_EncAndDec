#include <iostream>
#include <vector> 
#include <string>
#include <algorithm>
#include <sstream>
#include "BigInt.h"
using namespace std;

void err(){
	cout << "ERROR S7SMO: #BIV2. Please check the inputs for this operation." << endl;
}

bool BigInt::operator>=(BigInt a){
	int dif;

	int s1 = digits.size();
	int s2 = a.digits.size();


	if (s1 > s2)
		return true;

	else if (digits.size() < a.digits.size())
		return false;

	BigInt current = *this;

	for (int i = 0; i < digits.size(); i++)
	{
		if (current.digits[i] > a.digits[i])
			return true;
		else if (current.digits[i] < a.digits[i]){
			return false;
		}
	}

	return true;
}

bool BigInt::operator>(BigInt a){
	return a < *this;
}

bool BigInt::operator<(BigInt a)
{
	int dif;

	if (digits.size() > a.digits.size())
		return false;

	else if (digits.size() < a.digits.size())
		return true;

	BigInt current = *this;

	for (int i = 0; i < digits.size(); i++)
	{
		if (current.digits[i] < a.digits[i])
			return true;
		else if (current.digits[i] == a.digits[i]){
			continue;
		}
		else
			return false;
	}

	return false;
}

bool BigInt::operator==(string n){

	BigInt num = n;
	BigInt a = *this;
	int sz = num.digits.size();

	for (int i = 0; i < sz; i++)
	if (a.digits[i] != num.digits[i]) return false;

	return true;
}

BigInt BigInt::mod(BigInt a, BigInt b, BigInt& r){
	
	if (a<b)
	{
		r = a;
		return r;
	}

	

	mod(a, b + b, r);

	if (r >= b)
		r = r - b;

	return r;

}

BigInt BigInt::operator%(BigInt b){
	BigInt a = *this;
	BigInt res;
	BigInt r("0");

	res = mod(a, b, r);
	
	return res;
}

bool BigInt::operator%(int n){
	BigInt bg;
	bg = *this;
	if (bg.digits[bg.digits.size() - 1] % n == 0) return 0;
	return 1;
}

BigInt& BigInt::operator=(BigInt a){
	digits.swap(a.digits);
	return *this;
}

BigInt divsion(BigInt num1, BigInt num2, BigInt & r)
{
	BigInt ret("0");
	BigInt a("1");

	if (num1<num2)
	{
		r = num1;
		return ret;
	}

	BigInt f = num2 + num2;

	BigInt q = divsion(num1, f, r);

	q = q + q;

	if (r >= num2)
	{
		BigInt a("1");
		r = r - num2;
		return q + a;
	}


	return q;

}

void getRemainder(BigInt r){
	cout << "---------------------------" << endl;

	cout << "Remainder : " << r << "\t Result: ";
}

BigInt BigInt::pow(BigInt a, BigInt n){
	if (n == "0") 
		return "1";
	
	BigInt tmp;
	BigInt two("2");
	tmp = pow(a, n / two);

	if (n % 2 == 0)
		return tmp*tmp;

	else
		return a*tmp*tmp;

	/*BigInt result("1"), pow, two("2"), z("0");
	pow = a;
	while (n > z){
		if (n % 2 == 0){
			result = result *  pow;
		}
		pow = pow * pow;
		n = n / two;
	}
	return result;*/
}

BigInt BigInt::operator^(BigInt n){
	BigInt res;
	res = pow(*this, n);
	
	return res;
}

BigInt operator/(BigInt num, BigInt num2)
{
	
	if (num2.digits.size() > 1 && num2.digits[0] == 0){
		int d = num2.digits.size();
		for (int i = 0; i < d; i++)
		{
			if (num2.digits[i] != 0 || num2.digits.size() == 1 || num2.digits.size() == 1)
				break;
			else{
				num2.digits.erase(num2.digits.begin());
				i--;
			}
		}
	}

	if (num.digits.size() > 1 && num.digits[0] == 0){
		int d = num.digits.size();
		for (int i = 0; i < d; i++)
		{
			if (num.digits[i] != 0 || num.digits.size() == 1 || num.digits.size() == 1)
				break;
			else{
				num.digits.erase(num.digits.begin());
				i--;
			}
		}
	}


	if (num2 == "0" && num2.digits.size() < 2)
		err();
	else{
		BigInt copy = num2;
		BigInt reminder;
		BigInt r("0");

		BigInt y = divsion(num, num2, r);

		//getRemainder(r);
		return y;
	}

	return "0";
}


int toInt(char c) { return c - '0'; }; //char -> int

BigInt::BigInt(const BigInt& a) :digits(a.digits){}


BigInt::BigInt(string num){
	transform(num.begin(), num.end(), back_inserter(digits), toInt);
}

BigInt BigInt::operator +(BigInt& a)
{
	int maxSize;
	int num = 0;
	int carry = 0;
	BigInt res;

	//size for output variable
	if (digits.size()<a.digits.size()){
		maxSize = a.digits.size();

		int dif = a.digits.size() - digits.size();
		for (int i = 0; i < dif; i++)
			digits.insert(digits.begin(), 0);
		res.digits.resize(a.digits.size());
	}

	else if (digits.size()>a.digits.size()){
		maxSize = digits.size();

		int dif = digits.size() - a.digits.size();
		for (int i = 0; i < dif; i++)
			a.digits.insert(a.digits.begin(), 0);
		res.digits.resize(digits.size());
	}

	else{
		maxSize = digits.size();
		res.digits.resize(digits.size());
	}
	int i = (maxSize - 1);

	for (i; i >= 0; i--)
	{
		if (i < a.digits.size())
			num = digits[i] + a.digits[i] + carry;
		else
			num = digits[i] + a.digits[i];

		if (num >= 10)
		{
			num = num - 10;
			carry = 1;

		}
		else{
			carry = 0;
		}

		res.digits[i] = num;
	}
	if (carry){
		res.digits.insert(res.digits.begin(), 1);
	}

	if (res.digits.size() > 1)
	{
		int d = res.digits.size();
		for (int i = 0; i < d; i++)
		{
			if (res.digits[i] != 0 || res.digits.size() == 1)
				break;
			else{
				res.digits.erase(res.digits.begin());
				i--;
			}
		}
	}


	return res;

}

BigInt BigInt::operator -(BigInt& a)
{

	if (*this < a) 
		err();
	else{

		int maxSize;
		int num = 0;
		int carry = 0;
		BigInt res;


		if (digits.size()<a.digits.size()){
			maxSize = a.digits.size();

			int dif = a.digits.size() - digits.size();
			for (int i = 0; i < dif; i++)
				digits.insert(digits.begin(), 0);
			res.digits.resize(maxSize);

			BigInt tmp;
			tmp = a;
			a = *this;
			*this = tmp;

		}

		else if (digits.size()>a.digits.size()){
			maxSize = digits.size();

			int dif = digits.size() - a.digits.size();
			for (int i = 0; i < dif; i++)
				a.digits.insert(a.digits.begin(), 0);
			res.digits.resize(maxSize);
		}
		else if (digits.size() == a.digits.size()){
			if (digits[0] < a.digits[0]){
				BigInt tmp;
				tmp = a;
				a = *this;
				*this = tmp;
			}
			maxSize = digits.size();
			res.digits.resize(maxSize);
		}
		else{
			maxSize = digits.size();
			res.digits.resize(maxSize);
		}


		int i = (maxSize - 1);
		BigInt tmp;
		tmp = *this;
		for (i; i >= 0; i--)
		{

			if (tmp.digits[i] < a.digits[i]){
				tmp.digits[i] += 10;
				num = tmp.digits[i] - a.digits[i];
				tmp.digits[i - 1]--;
			}
			else
				num = tmp.digits[i] - a.digits[i];

			res.digits[i] = num;

		}

		if (res.digits.size() > 1)
		{
			int d = res.digits.size();
			for (int i = 0; i < d; i++)
			{
				if (res.digits[i] != 0 || res.digits.size() == 1)
					break;
				else{
					res.digits.erase(res.digits.begin());
					i--;
				}
			}
		}


		return res;

	}
	return "0";
}


int BigInt::makeEqual(BigInt &a, BigInt &b){
	int Asize, Bsize, dif;
	Asize = a.digits.size();
	Bsize = b.digits.size();

	if (Asize < Bsize){
		dif = b.digits.size() - a.digits.size();
		for (int i = 0; i < dif; i++)
			a.digits.insert(a.digits.begin(), 0);
		return Bsize;
	}
	else if (Bsize < Asize){
		dif = a.digits.size() - b.digits.size();
		for (int i = 0; i < dif; i++)
			b.digits.insert(b.digits.begin(), 0);
	}
	return Asize;
}

string intToString(int a){
	stringstream s;
	s << a;
	string str = s.str();
	return str;
}

BigInt BigInt::MultUtil(BigInt a, BigInt b){
	BigInt res;
	int r = a.digits[0] * b.digits[0];
	return intToString(r);
}

BigInt BigInt::multi(BigInt a, BigInt b){
	BigInt res;
	int len;

	BigInt Xa, Xb, Yc, Yd;

	len = makeEqual(a, b);
	
	if (len == 0) return "0";
	if (len == 1) 
		return MultUtil(a, b);

	int Flen = len / 2;

	//halves of X
	for (int i = 0; i < Flen; i++)
	{
		if (i == 0)
			Xa.digits.erase(Xa.digits.begin());
		Xa.digits.push_back(a.digits[i]);
	}

	for (int i = Flen; i < len; i++){
		if (i == Flen)
			Xb.digits.erase(Xb.digits.begin());
		Xb.digits.push_back(a.digits[i]);

	}

	//halves of Y
	for (int i = 0; i < Flen; i++){
		if (i == 0)
			Yc.digits.erase(Yc.digits.begin());
		Yc.digits.push_back(b.digits[i]);

	}

	for (int i = Flen; i < len; i++){
		if (i == Flen)
			Yd.digits.erase(Yd.digits.begin());
		Yd.digits.push_back(b.digits[i]);

	}

	BigInt res1 = multi(Xa, Yc);
	BigInt res2 = multi(Xb, Yd);
	BigInt res3 = multi((Xa + Xb), (Yc + Yd));

	BigInt z = res3 - (res2 + res1);

	int v1, v2;

	if (len % 2 == 0) { v1 = len, v2 = len / 2; }
	else { v1 = len / 2 + len / 2 + 2, v2 = len / 2 + 1; }



	//Adding zeros to AC
	for (int i = 0; i < v1; i++){
		res1.digits.insert(res1.digits.end(), 0);
	}

	//Adding zeros to Z
	for (int i = 0; i < v2; i++){
		z.digits.insert(z.digits.end(), 0);
	}

	BigInt r = res1 + z + res2;

	return r;

}

BigInt BigInt::operator*(BigInt b){
	BigInt res;
	
	res = multi(*this, b);
	
	return res;
}

ostream& operator <<(ostream& out, BigInt a)
{
	for (int i = 0; i < a.digits.size(); i++){
		out << a.digits[i];
	}
	return out;
}

istream& operator >>(istream& in, BigInt& a)
{
	string s;
	in >> s;
	a = s;
	return in;
}

