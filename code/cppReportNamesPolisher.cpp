/* ---------------------------------------
   Description: Criterion-meeting Cpp Report Filename Generator for the Henu Course
   Author: Linghuei Guo
   Affiliation: Henu, Kaifeng, China
   MailTo: guolh2013@hotmail.com
   Copyright: All Rights Reserved
--------------------------------------- */

#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

// 本科生学号一般为 10 位数字
const int STUNUM_LEN = 10;

class CPPReports {
protected:
  string stuName;
  string stuNo;
  vector<string> assigNames;

  string getPdfName(int i) {
    if (i >= assigNames.size())
      throw "Index " + to_string(i) + " is out of boundary!";
    string expNum = i < 10 ? string("0") + to_string(i + 1) : to_string(i + 1);
    string result = stuNo + "-" + stuName + "-C++程序设计-实验" + expNum + "-" + assigNames[i]  + ".pdf"; 
    return result;
  }

public:
  CPPReports( ) {
    // stuNo=string("1234567890");
    cout<<"请输入学号: ";
    cin>>stuNo;
    if (stuNo.length() != STUNUM_LEN)
      throw string("Student Number with Erroreous Length!");

    // stuName = "张三";
    cout<<"请输入姓名: ";
    cin>>stuName;

    // 向 vector 末端添加数据，要点： push_back()
    assigNames.push_back("C++基本语句及表达式");
    assigNames.push_back("C++数组和字符串");
    assigNames.push_back("C++结构体与枚举");
    assigNames.push_back("C++类初步");
    assigNames.push_back("C++字符串类");
    assigNames.push_back("C++继承、模板与vector");

    cout<<"对象已生成!"<<endl;
  }

  virtual void proper_output(){
    cout<<endl;
    for (int i = 1; i <= assigNames.size(); i++){
      string pdffile = getPdfName(i - 1);
      cout<<pdffile<<endl;
    }
  }
};

template<class T >
class CPPReportsTemp: public CPPReports {
protected:
  T* printer;
public:
  CPPReportsTemp(): CPPReports(){ 
    printer = new T();
  }
  ~CPPReportsTemp(){
    delete printer;
  }
  void proper_output(){
    for (int i = 1; i <= assigNames.size(); i++){
      string pdffile = getPdfName(i - 1);
      printer -> send(pdffile);
    }
  }
};

class StdPrint {
public:
  virtual void send(string s){
    cout<<endl<<s<<endl; // 多输一个换行以示区别
  }
};

class TxtPrint: public StdPrint {
private:
  string txtName; 
  fstream txtout;
public:
  TxtPrint(){
    txtName = "cpp_reports.txt";
    txtout.open(txtName, ios::out);
  }
  ~TxtPrint(){
    txtout.close();
    cout<<endl<<"TxtPrint::txtout safely closed before destruction."<<endl;
  }
  void send(string s){
    cout<<"将写入: \""<<s<<"\" 到: "<<txtName<<endl;
    txtout<<s<<endl;
  }
};



int main(){
  CPPReportsTemp<TxtPrint>* tool = NULL;
  try {
    tool = new CPPReportsTemp<TxtPrint>();
    tool -> proper_output();
  }
  catch(string x){
    cout<<"Error Info:  "<< x <<endl;
  }
  
  if (tool != NULL)
    delete tool;

  cout<<"Terminating with dignity..."<<endl;
  return 0;
}
