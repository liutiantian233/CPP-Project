////////////////////////////////////////////////////////////////////////////////
//
//  Computer Project #01  Real and imaginary operations
//
//  Define the head File "iostream" and "iomanip"
//    use the C++ Standard Library headers
//
//  use the fixed and setprecision(2)
//    the fixed can be elements printed as floating point numbers.
//    the setprecision(2) will always print two decimals after the point.
//
//  use the float to define six variable
//    then can output the operation result
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>  // the head File
using std::cout; using std::cin; using std::endl; using std::fixed;  // C++ STL

#include<iomanip>  // the head File
using std::setprecision;  // C++ STL

int main() {

    cout << fixed << setprecision(2);  // The number after the exact decimal point

    float first1, first2, second1, second2, real, imag;  // define variable

    cin >> first1 >> first2 >> second1 >> second2;  // input

    // output (Addition and subtraction)
    cout << first1 + second1 << " + " << first2 + second2 << "i" << endl;
    cout << first1 - second1 << " + " << first2 - second2 << "i" << endl;

    // operation result and output (Multiplication)
    real = first1 * second1 - first2 * second2;
    imag = first1 * second2 + first2 * second1;
    cout << real << " + " << imag << "i" << endl;

    // operation result and output (division)
    real = (first1 * second1 + first2 * second2) / (second1 * second1 + second2 * second2);
    imag = (first2 * second1 - first1 * second2) / (second1 * second1 + second2 * second2);
    cout << real << " + " << imag << "i" << endl;

}
