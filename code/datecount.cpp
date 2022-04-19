/* ---------------------------------------
   Description: The demo of date interval calculate 
   Author: Linghuei Guo
   Affiliation: Henu, Kaifeng, China
   MailTo: guolh2013@hotmail.com
   Copyright: All Rights Reserved
--------------------------------------- */

#include <iostream>
using namespace std;

// 重要知识点： static members of a class

class Date{
public:
  int year, month, day;
  // 知识点：构造函数
  Date(int y, int m , int d);
  // 用数组查表，优化时间复杂度。
  // static 的变量全类对象共有，相当于文件的“全局”变量，但类外需用 Date:: 访问。 
  const static int monthDay[12];
  const static int monthDayLeap[12];
  const static int monthOffset[12];
  const static int monthOffsetLeap[12];
  int getOffset();
  bool isLeapYear();
  int allLeapsBefore(); 
  int intervalCount(Date);
  void print();
  // class 测试用函数
  // static 函数禁止访问 non-static 成员
  static void printMinus(Date, Date);
  static void test();
};

// 类外定义 static 成员不需要 static 关键词： 
const int Date::monthDay[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int Date::monthDayLeap[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int Date::monthOffset[12] = { 0, 31, 59, 90, 120,151,181,212,243,273,304,334};
const int Date::monthOffsetLeap[12] = { 0, 31, 60, 91, 121,152,182,213,244,274,305,335}; // no 'static' ahead

Date::Date(int year, int month, int day) {
  this -> year = year;
  const int* mdArray = isLeapYear() ? monthDayLeap : monthDay;
  this -> month = month <= 12 ? month : ((month - 1) % 12) + 1;
  this -> day = day <= mdArray[month - 1] ? day : ((day - 1) % mdArray[month - 1]) + 1;
}

int Date::getOffset(){
  const int* mdArray = isLeapYear() ? monthOffsetLeap: monthOffset;
  return mdArray[month - 1] + day - 1;
}

bool Date::isLeapYear(){
  if (year % 400 == 0 )
    return true;
  else if (year % 100 == 0)
    return false;
  else if (year % 4 == 0)
    return true;
  else
    return false;
}

int Date::allLeapsBefore(){
  int y = year - 1;
  return y / 4 - y / 100 + y / 400;
}

int Date::intervalCount(Date d2) {
  int o1 = getOffset();
  int o2 = d2.getOffset();
  int l1 = allLeapsBefore();
  int l2 = d2.allLeapsBefore();
  return o2 - o1 + l2 - l1 + (d2.year - year) * 365;
}

int intervalBetweenTwo(Date d1, Date d2){
  int o1 = d1.getOffset();
  int o2 = d2.getOffset();
  int l1 = d1.allLeapsBefore();
  int l2 = d2.allLeapsBefore();
  return o2 - o1 + l2 - l1 + (d2.year - d1.year) * 365;
}

void Date::print(){
  printf(" Date(%04d,%02d,%02d) ", year, month, day);
}

void Date::printMinus(Date d1, Date d2) // no 'static' ahead
{
  d1.print();
  cout<<" - ";
  d2.print();
  cout<<"= "<<d1.intervalCount(d2)<<" days "<<endl;
}

void Date::test(){ // no 'static' ahead
  Date d1 =  Date(2020, 4, 1), d2 =  Date(2016,4,1);
  printMinus(d1, d2);
  cout<<"   - Output of intervalBetweenTwo(d2, d1): "<<intervalBetweenTwo(d2, d1)<<endl;
  printMinus(Date(1900, 1, 2), Date(2000,1,2));
  printMinus(Date(2000, 1, 2), Date(2100,1,2));
  printMinus(Date(2016, 4, 1), Date(2020,2,1));
  printMinus(Date(2016, 2, 1), Date(2020,2,1));
}

int main(){
  Date::test();
  return 0;
}
  


