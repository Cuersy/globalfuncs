#include<iostream>
#include "../../../../Desktop/C++/globalfuncs.cc"
using namespace std;
int main() {
	string encrypted = encryptnumber("192709126501294609124791286512034612591726349876421012741");
	cout << encrypted;
	cout  <<endl << decryptnumber(encrypted);
	return 0;
}
