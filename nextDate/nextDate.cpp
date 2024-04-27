#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
ofstream outputFile("outputNextDate.txt");
class SimpleDate {
    int month;
    int day;
    int year;
    bool check = true;
    bool check_year = true;

public:
    SimpleDate(int m, int d, int y) {
        month = m;
        day = d;
        year = y;
        if (!rangesOK(m, d, y))
        {
                check = false;
        }
        
        
    }

    bool getCheck(){
        return check;
    }
     bool getCheckYear(){
        return check_year;
    }
    int getMonth() const {
        return month;
    }

    void setMonth(int m) {
        month = m;
    }

    void setCheckYear(bool m) {
        check_year = m;
    }
    int getDay() const {
        return day;
    }

    void setDay(int d) {
        day = d;
    }

    int getYear() const {
        return year;
    }

    bool isLeap()  const{
        bool isLeapYear = true;
        
        if(year % 4 != 0)
        isLeapYear = false;
        else if(year % 100 != 0)
        isLeapYear = true;
        else if(year % 400 != 0)
        isLeapYear = false;
        return isLeapYear;
    }

    bool rangesOK(int month, int day, int year) {
        bool dateOK = true;
        dateOK &= (year > 1841) && (year < 2043); // Year OK?
        dateOK &= (month > 0) && (month < 13); // Month OK?
        dateOK &= (day > 0) && (
        ((month == 1 || month == 3 || month == 5 
        || month == 7 || month == 8 || month == 10 || month == 12) && day < 32) ||
        ((month == 4 || month == 6 || month == 9 
        || month == 11) && day < 31) ||
        ((month == 2 && isLeap()) && day < 30) ||
        ((month == 2 && !isLeap()) && day < 29));
        return dateOK;
        }
    
};

class NextDate {
public:
    static SimpleDate nextDate( SimpleDate &date) {
        int tomorrowDay, tomorrowMonth, tomorrowYear;
        tomorrowMonth = date.getMonth();
        tomorrowDay = date.getDay();
        tomorrowYear = date.getYear();

        switch (date.getMonth()) {
            // 31 day months (except Dec.)
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
                if (date.getDay() < 31)
                    tomorrowDay = date.getDay() + 1;
                else {
                    tomorrowDay = 1;
                    tomorrowMonth = date.getMonth() + 1;
                }
                break;
            // 30 day months
            case 4:
            case 6:
            case 9:
            case 11:
                if (date.getDay() < 30)
                    tomorrowDay = date.getDay() + 1;
                else {
                    tomorrowDay = 1;
                    tomorrowMonth = date.getMonth() + 1;
                }
                break;
            // December
            case 12:
                if (date.getDay() < 31)
                    tomorrowDay = date.getDay() + 1;
                else {
                    tomorrowDay = 1;
                    tomorrowMonth = 1;
                    if (date.getYear() == 2042)
                        {
                            cout << "Date beyond 2042 " << endl;
                            outputFile << "Date beyond 2042 " << endl;
                            date.setCheckYear(false);
                        }
                    else
                        tomorrowYear = date.getYear() + 1;
                }
                break;
            // February
            case 2:
                if (date.getDay() < 28)
                    tomorrowDay = date.getDay() + 1;
                else {
                    if (date.getDay() == 28) {
                        if (date.isLeap())
                            tomorrowDay = 29;
                        else {
                            tomorrowDay = 1;
                            tomorrowMonth = 3;
                        }
                    } else if (date.getDay() == 29) {
                        tomorrowDay = 1;
                        tomorrowMonth = 3;
                    }
                }
                break;
        }
        return SimpleDate(tomorrowMonth, tomorrowDay, tomorrowYear);
    }
};
bool isValidNumber(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}
vector<string> split(string s){
    vector<string> arr ;
    string tmp = "";
    for(char i : s)
    {
        
        if(i == '/' || i =='\n'){
            arr.push_back(tmp);
            tmp = "";
        }else{
            tmp+=i;
        }

    }
    arr.push_back(tmp);
    return arr;
}
string delete_space(string str,string result) {
  int pos = 0;
 
  const int len = str.size(); /*Tìm độ dài chuỗi ban đầu*/
  for(int i = 0; i < len; i++) {
      char chr = str[i];

      /*Nếu ký tự lấy ra là ký tự trắng thì bỏ qua*/
      if (chr == '\r' || chr == '\n' || chr == ' ') {
        continue;
      }

      /*Thêm ký tự lấy ra vào kết quả*/
      result[pos++] = chr;
  }
  return result;
}
bool check_stoi(vector<string> s){
    for(string x : s){
        x = delete_space(x,x);
        for(char c : x){
            if(!isdigit(c)){
                return false;
            }
        }
    }
    return true;
}
int main() {
    ifstream inputFile("inputNextDate.txt");
    if (!inputFile) {
        cout << "Không thể mở file inputNextDate.txt" << endl;
        return 0;
    }
    vector<string> list_date ;
    string line;
    while(getline(inputFile, line))
    {
        list_date.push_back(line);
    }
    
    for(string x : list_date){
        vector<string> arr = split(x);
        cout << "Date: " <<  x << " -> ";
        outputFile << "Date: " <<  x << " -> ";
        if(check_stoi(arr)){

            int day = stoi(arr[0]);
            int month = stoi(arr[1]);
            int year = stoi(arr[2]);
            
            SimpleDate tmp_s(month,day,year);
            SimpleDate tmp = NextDate::nextDate(tmp_s);
            if(tmp_s.getCheck() && tmp_s.getCheckYear() ){
                cout << "Next Date: " <<  tmp.getDay() << "/" << tmp.getMonth()  << "/" << tmp.getYear() << endl;  
                outputFile << "Next Date: " <<  tmp.getDay() << "/" << tmp.getMonth()  << "/" << tmp.getYear() << endl;  
            }else if(!tmp_s.getCheck()){
                cout << "Invalid Date" << endl;
                outputFile << "Invalid Date" << endl;
            }
        }else{
            cout << "Invalid Date" << endl;
                outputFile << "Invalid Date" << endl;
        }
    }

    return 0;
}