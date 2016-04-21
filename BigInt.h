#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigInt{
	vector<int> digits;
public:
	BigInt divsion(BigInt num1, BigInt num2, BigInt& reminder);
	BigInt(const BigInt& a);
	BigInt(string num = "0");
	BigInt operator+(BigInt& a);
	BigInt operator-(BigInt& a);
	BigInt operator%(BigInt n);
	bool operator%(int n);
	BigInt& operator=(BigInt a);
	BigInt operator*(BigInt a);
	BigInt operator^(BigInt n);

	BigInt pow(BigInt a, BigInt n);


	BigInt mod(BigInt a, BigInt b, BigInt& r);

	BigInt multi(BigInt a, BigInt b);
	BigInt MultUtil(BigInt a, BigInt b);
	int makeEqual(BigInt &a, BigInt &b);

	bool operator <(BigInt a);
	bool operator >(BigInt a);
	bool operator>=(BigInt a);
	bool operator==(string num);


	friend BigInt operator /(BigInt, BigInt);
	friend ostream& operator<<(ostream& out, BigInt a);
	friend istream& operator>>(istream& in, BigInt& a);




};