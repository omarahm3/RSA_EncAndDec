#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include "BigInt.h"
using namespace std;


BigInt powerMod(BigInt b, BigInt p, BigInt mod){
	BigInt two("2"), one("1"), zero("0");

	if (b < one || p < zero || mod < one)
		return "-1";

	BigInt res("1");

	while (p>zero){
		if (p % 2 == 1)
			res = (res * b) % mod;
		b = (b * b) % mod;
		p = p / two;
	}

	return res;
}

int main(){
	
	

	BigInt e, d, n, m, res;
	BigInt encrypted, decrypted;

	cout << "m: "; cin >> m;
	cout << "e: "; cin >> e;
	cout << "n: "; cin >> n;
	
	int start = clock();

	encrypted = powerMod(m, e, n);
	cout << "The encrypted msg: " << endl << encrypted << endl;

	cout << "TIME2: " << (double)(clock() - start) / CLOCKS_PER_SEC << endl;

	cout << "------------------------------" << endl;
	

	//decrypted = (encrypted^d) % n;
	//cout << "The decrypted msg: " << endl << decrypted << endl;

//	/*int woo = clock();
//
//	decrypted = powerMod(encrypted, d, n);
//	cout << "The decrypted msg yarb: " << endl << decrypted << endl;
//
//	cout << "TIME FINAL: " << (double)(clock() - woo) / CLOCKS_PER_SEC << endl;
//
//*/


	return 0;
}