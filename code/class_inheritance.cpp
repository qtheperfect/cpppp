/* ---------------------------------------
   Description: The C++ code using class inheritance for English number conversion 
   Author: Linghuei Guo
   Affiliation: Henu, Kaifeng, China
   MailTo: guolh2013@hotmail.com
   Copyright: All Rights Reserved
--------------------------------------- */

#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
using namespace std;

typedef unsigned long long int u64; 

// class 1
class EngNum2D{
  // num 末两位数转英文：
protected:
  u64 num;
  static const string onesNames[];
  static const string tenAbove[];
  static const string tensName[];
public:
  EngNum2D(u64 num ) : num(num){}
  string toString();
  static void plainTest();
};

const string EngNum2D::onesNames[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
const string EngNum2D::tenAbove[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
const string EngNum2D::tensName[] = {"zero", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};


string EngNum2D::toString() {
  u64 n = num % 100;
  if (n < 10)
    return onesNames[n];
  else if (n < 20)
    return tenAbove[n - 10];
  else if (n % 10 == 0)
    return tensName[n % 100 / 10];
  else
    return tensName[n % 100 / 10] + "-" + onesNames[n % 10];
}

void EngNum2D::plainTest(){
  // 简单 class 测试
  for (u64 n = 0; n < 100; n += 3){
    cout<<setw(5)<<n<<" => \""<< EngNum2D(n).toString()<<"\""<<endl;
  }
}

// class 2
class EngNum3D : public EngNum2D {
  // num 末三位数转英文：
public:
  EngNum3D(u64 num) : EngNum2D( num) {
    //    cout<<"EngNum3D object has been created"<<endl;
  }
  string toString();
  static void plainTest();
};

string EngNum3D::toString(){
  u64 a = num % 1000;
  if (a < 100){
    return EngNum2D::toString();
  }
  else if (a % 100 == 0){
    return onesNames[ a/100 ] + " hundred";
  }
  else {
    return onesNames[a/100] + " hundred and " + EngNum2D::toString(); 
  }
}

void EngNum3D::plainTest(){
  u64 tester[] = {18, 81, 118, 120, 300, 810, 811, 1024 };
  for (u64 n : tester){
    cout<<setw(4)<<n<<" => "<<EngNum3D(n).toString()<<endl; 
  }
}

// class 3
class EngNumRecursive : public EngNum3D {
  // 整个 num 转 English
private:
  string getLargeName();
  int largeIndex;  // 10^3n 数量级单位
public:
  EngNumRecursive(u64 num) : EngNum3D(num), largeIndex(0){}
  EngNumRecursive(u64 num, int largeIndex) : EngNum3D(num), largeIndex(largeIndex){}
  string toStringRecursive();
  string toString() {
    return toStringRecursive();
  }
  static void plainTest(){
    u64 tester[] = {24, 10081, 88010, 8000, 80000, 800000, 800000005, 423511, 1100000003000, 101102103400005600, 9220002000000005807, 18446744073709551615};
    for (u64 n : tester){
      cout<<setw(20)<<n<<" => \""<<EngNumRecursive(n).toString()<<"\"\n"; 
    }
  }
};

string EngNumRecursive::toStringRecursive() {
  if (num == 0)
    return "";
  else if (num % 1000 == 0){
    EngNumRecursive* largerPart = new EngNumRecursive(num / 1000, largeIndex + 1);
    return largerPart -> toStringRecursive();
  }
  else {
    string hundredsNumber = EngNum3D::toString() + getLargeName();
    if (num < 1000)
      return hundredsNumber;
    EngNumRecursive* largerPart = new EngNumRecursive(num / 1000, largeIndex + 1);
    string higherNumber = largerPart -> toStringRecursive();
    return higherNumber + " " + hundredsNumber;
  }
}

string EngNumRecursive::getLargeName(){
  string largeNames[] = {"thousand", "million", "billion", "trillion", "quadrillion", "quintillion", "hextillion", "septillion", "octillion"};
  if (largeIndex <= 0) 
    return "";
  else
    return " " + largeNames[largeIndex - 1];
}




int main(){
  EngNumRecursive::plainTest();
  cout<<"\n   Fix this: \n EngNumRecursive(0).toString() => \""
      << EngNumRecursive(0).toString()
      <<"\" (which should be \"zero\"!)\n";
  return 0;
}


