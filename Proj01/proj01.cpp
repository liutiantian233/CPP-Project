#include <iostream>
using std::cout; using std::cin; using std::endl; using std::fixed;
#include<iomanip>
using std::setprecision;

int main() {
  cout << fixed << setprecision(2);
	float first1, first2, second1, second2, real, imag;
	cin >> first1 >> first2 >> second1 >> second2;
  
  cout << first1 + second1 << " + " << first2 + second2 << "i" << endl;
  cout << first1 - second1 << " + " << first2 - second2 << "i" << endl;
  
  real = first1 * second1 - first2 * second2;
  imag = first1 * second2 + first2 * second1;
  cout << real << " + " << imag << "i" << endl;

  real = (first1 * second1 + first2 * second2) / (second1 * second1 + second2 * second2);
  imag = (first2 * second1 - first1 * second2) / (second1 * second1 + second2 * second2);
  cout << real << " + " << imag << "i" << endl;
}
