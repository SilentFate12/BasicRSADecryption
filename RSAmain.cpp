#include <iostream>
#include <fstream>
#include <string>
//Euclid's extended algorithm, used to find the modular inverse.
int gcdExtended(int a, int b, int* x, int* y)
{
	// Base Case
	if (a == 0)
	{
		*x = 0;
		*y = 1;
		return b;
	}

	int x1 = 0, y1 = 0; // To store results of recursive call
	int gcd = gcdExtended(b % a, a, &x1, &y1);

	// Update x and y using results of
	// recursive call
	*x = y1 - (b / a) * x1;
	*y = x1;
	return gcd;
}
//Driver code for simplifying the large exponents in modular arithmetic. For example, simplifying 32^342 (mod 1643).
int simplification(int c, int d, int n) {
	//Base case
	if (d == 1) {
		return c;
	}
	//Declaring variables
	int oddHolder = 0;
	int temp = 0; //Used to do arithmetic with the base number.
	int result = 0;
	//This determines if the value is odd. If it is, it sets a flag in the form of oddHolder, and multiplies it in later.
	if (d % 2 == 1) {
		oddHolder = c;
		d = d - 1;
	}
	temp = c * c;
	temp = temp % n;
	result = simplification(temp, (d / 2), n);

	if (oddHolder != 0) {
		result = (result * oddHolder) % n;
	}
	else {
		result = result % n;
	}
	return result;
}
int main() {
	int p, q, e, n, phiOfN, d;
	std::cout << "Please enter the first prime of the RSA Encryption: ";
	std::cin >> p;
	std::cout << "\nPlease enter the second prime of the RSA Encryption: ";
	std::cin >> q;
	std::cout << "\nFinally, please enter the public encryptor e to complete the public key: ";
	std::cin >> e;
	//Setting up the basics
	n = p * q;
	phiOfN = (p - 1) * (q - 1);
	//Determining d:
	int x1, x2, g;
	g = gcdExtended(e, phiOfN, &x1, &x2);
	if (g != 1) {
		std::cout << "Error! e and phi(n) are not coprime!";
	}
	//x1 is now the multiplicative inverse of 3^-1 (mod 1540) which is what d is.
	//It's possible for x1 to be negative, and if it is we need to readjust it.
	if (x1 < 0) {
		x1 = phiOfN + x1;
	}
	d = x1;
	std::cout << "The d for this set of primes is: " << d << std::endl;
	//Now, we need to take in a file of numbers, decrypt the numbers, and output a new file with the message. 
	std::ifstream encryptedFile;
	encryptedFile.open("EncryptedFile.txt");
	std::ofstream decryptedMessage;
	decryptedMessage.open("DecryptedMessage.txt");
	std::string currStrHolder;
	int strConverted;
	int numDecrypted;
	char charDecrypted = ' ';
	while (encryptedFile.peek() != EOF) {
		encryptedFile >> currStrHolder;
		strConverted = std::stoi(currStrHolder);
		numDecrypted = simplification(strConverted, d, n); // c^d (mod n) is the decryption process for RSA.
		if (numDecrypted > 2 && numDecrypted < 29) {
			charDecrypted = numDecrypted + 94;
		}
		else if (numDecrypted == 29) {
			charDecrypted = ' ';
		}
		else if (numDecrypted == 30) {
			charDecrypted = '"';
		}
		else if (numDecrypted == 31) {
			charDecrypted = '.';
		}
		else if (numDecrypted == 32) {
			charDecrypted = ',';
		}
		else if (numDecrypted == 33) {
			charDecrypted = '\'';
		}
		std::cout << charDecrypted;
	}
	
	system("pause");
	return 0;
}

