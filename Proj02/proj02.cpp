////////////////////////////////////////////////////////////////////////////////
//
//  Computer Project #02   Juggler sequence
//
//  Define the head File "iostream" and "cmath"
//    use the C++ Standard Library headers
//    the cmath is math tools
//
//  Defining long integer variables
//  use cin to get low and high
//
//    use a if conditional statements to determine low small than high
//    use a while loop to determine how many times to run
//    use a while loop to calculation
//
//      there are one if to determine the num is odd or even
//      there are two if to determine the Max number
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>  // the head File
using std::cout; using std::cin; using std::endl;  // C++ STL

#include <cmath>  // the head File

int main() {

    // use long to determine the variables
    long low, high, num, max_num = 0, max_count = 0, seq_num = 0, seq_count = 0;

    // the input
    cin >> low >> high;

    // To determine low small than high
    if (low > high)
        cout << "Error" << endl;

    // this is right
    else {
        max_num = low;

        // the while loop to determine times
        while (low <= high) {

            num = low;
            int count = 0;

            // the while loop to determine calculation
            while (num != 1) {
                ++count;

                // even result
                if (num % 2 == 0)
                    num = static_cast<long>(floor(pow(num, 0.5)));

                // odd result
                else
                    num = static_cast<long>(floor(pow(num, 1.5)));

                // the max number
                if (num > max_num) {
                    max_num = num;
                    seq_num = low;
                }

                // the max count
                if (count > max_count) {
                    max_count = count;
                    seq_count = low;
                }
            }

            ++low;
        }

        // the output
        cout << seq_count << " " << max_count << endl;
        cout << seq_num << " " << max_num << endl;
    }
}
