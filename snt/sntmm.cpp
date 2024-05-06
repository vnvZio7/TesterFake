#include <bits/stdc++.h>
using namespace std;
bool checkSNT(int n){
    if(n <= 1)   return false;
    for(int i = 2; i <= sqrt(n) ; i++){
        if(n % i == 0)
            return false;
    }
    return true;
}
ofstream outputFile("OutputSNT.txt");
void displaySNT(int a,int b){
    // int cnt = 0;
    for(int i = a; i <= b; i++){
        if(checkSNT(i)){
            outputFile << i << " ";
            // cnt++;
        } 
    }
    // if(cnt == 0)
    //     outputFile << "Không có giá trị nào nằm trong khoảng a, b";
    outputFile << endl;
}
struct number{
    int a;
    int b;
};

void check_number(int a,int b){
    if(a <= 1 || a > 1000){
        outputFile << "Giá trị a không hợp lệ" << endl;
    }else if(b < 1 || b > 1000){
        outputFile << "Giá trị b không hợp lệ" << endl;
    }else{
        if(a < b){
            displaySNT(a,b);
        }else{
            outputFile << "Giá trị a phải nhỏ hơn b" << endl;
        }
    }
}
int main() {
    vector<number> list_number;
    ifstream inputFile("InputSNT.txt");
    while(!inputFile.eof()){
        number temp;
        inputFile >> temp.a >> temp.b;
        list_number.push_back(temp);
    }
    for(number it : list_number)
        check_number(it.a,it.b);

    return 0;
}