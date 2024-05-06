#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }

    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

string intToString(int number) {
    stringstream ss;
    ss << number;
    return ss.str();
}

void writeOutputToFile(const string& filename, const string& output) {
    ofstream outFile(filename.c_str(), ios::app);

    if (outFile.is_open()) {
        outFile << output << endl;
        outFile.close(); 
    } else {
        cout << "Khong the mo file " << filename << " de ghi du lieu." << endl;
    }
}

int main() {
    ifstream file("InputSNT.txt");
    ofstream output("outputSNT.txt");

    if (!file.is_open() || !output.is_open()) {
        cout << "Khong the mo file input hoac output." << endl;
        return 1;
    }

    int a, b;

    stringstream primeNumbers; 

    while (file >> a >> b) {
        string outputMsg;

        if (a <= 1 || a > 1000 ) {
            outputMsg = "Giá trị a không hợp lệ";
        } else if (b < 1 || b > 1000 ) {
            outputMsg = "Giá trị b không hợp lệ";
        } else if (a >= b) {
            outputMsg = "Giá trị a phải nhỏ hơn b";
        } else {
            bool hasPrime = false;

            primeNumbers.str(""); 

            for (int i = a; i <= b; ++i) {
                if (isPrime(i)) {
                    hasPrime = true;
                    primeNumbers << i << " "; 
                }
            }

            if (hasPrime) {
                outputMsg = primeNumbers.str();
            } 
        }

        writeOutputToFile("outputSNT.txt", outputMsg);
    }

    file.close();
    output.close();

    cout << "Xuất file outputSNT.txt thành công." << endl;

    return 0;
}
