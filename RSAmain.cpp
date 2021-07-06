#include <iostream>

int modMultiInverse(int e, int phiOfN) {
	int d = 0;
	int counter = 0;
	int phiHolder = phiOfN;
	int numEGoesIntoPhi = (int)((double)(phiOfN) / (e));
	std::cout << numEGoesIntoPhi;
	//phiOfN = e(counter) + remainder
	return d;
}

int main() {
	int p, q, e, n, phiOfN, d;
	std::cout << "Please enter the first prime of the RSA Encryption.";
	std::cin >> p;
	std::cout << "\nPlease enter the second prime of the RSA Encryption.";
	std::cin >> q;
	std::cout << "\nFinally, please enter the public encryptor e to complete the public key.";
	std::cin >> e;
	//Setting up the basics
	n = p * q;
	phiOfN = (p - 1) * (q - 1);
	d = modMultiInverse(e, phiOfN);

	return 0;
	system("pause");
}

