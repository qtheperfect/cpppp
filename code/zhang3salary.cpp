/* ---------------------------------------
   Description: The demo of the Matrix Game
   Author: Linghuei Guo
   Affiliation: Henu, Kaifeng, China
   MailTo: guolh2013@hotmail.com
   Copyright: All Rights Reserved
--------------------------------------- */

#include <iostream>
#include <iomanip>
using namespace std;

// 注意：一般类名、自定义类型名首字母大写；变量、函数名首字母小写
class MatrixGame { 
public:
  // 关键知识点： static 成员
  const static int rows = 5; // 注意：只有 static const 成员变量可以在类定义时用等号初始化。
  const static int cols = 5;
  int wageMatrix[rows][cols];

  void printMatrix(); // 输出 wageMatrix 各行列
  // 构造函数 (int)
  MatrixGame(int base);  // 利用 base 和 modulus 生成随机数矩阵
  int colMax(int); // auxiliary func
  int rowMin(int); // auxiliary func
  int minMax(); // 主要任务1：各列最大值中最小者
  int maxMin(); // 主要任务2: 各行最小值中最大者
 
  // static 类型的类成员函数可通过 类名::函数名() 调用
  static void test(int base) ; 

private:
  static const int modulus = 9887; // Good Prime Number 9887
};

void MatrixGame::printMatrix(){
  // 输出 wageMatrix 各行列
  for (int i = 0; i < rows; i++){
    cout<<"|";
    for (int j = 0; j < cols; j++){
      cout<<""<<setw(6)<<wageMatrix[i][j]<<" |";
    }
    cout<<"  | {{"<<setw(6)<<rowMin(i)<<" }}"<<endl;
  }
  cout<<endl;
  for (int j = 0; j < cols; j++){
    cout<<"| ("<<setw(4)<<colMax(j)<<")";
  }
  cout<<"| "<<endl<<endl;
}

MatrixGame::MatrixGame(int base){
  int b = base % modulus;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++){
      wageMatrix[i][j] = b;
      b = b * base % modulus;
    }
}

int MatrixGame::rowMin(int i){
  int a = wageMatrix[i][0];
  for (int j = 1; j < cols; j++){
    if (wageMatrix[i][j] < a)
      a = wageMatrix[i][j];
  }
  return a;
}

int MatrixGame::colMax(int j){
  int a = wageMatrix[0][j];
  for (int i = 1; i < rows; i++){
    if (wageMatrix[i][j] > a)
      a = wageMatrix[i][j];
  }
  return a;
}
    
int MatrixGame::maxMin(){
  int a = rowMin(0);
  for (int i = 1; i < rows; i++){
    int a1 = rowMin(i);
    if (a1 > a)
      a = a1;
  }
  return a;
}

int MatrixGame::minMax(){
  int a = colMax(0);
  for (int j = 1; j < cols; j++){
    int a1 = colMax(j);
    if (a1 < a)
      a = a1;
  }
  return a;
}

// class 外部实现 static 函数，无需加 static 关键词。
// 输入数值有默认输入，相当于函数重载。
void MatrixGame::test(int base = 1243) { 
  // static 函数不能访问非 static 成员：
  if (base <= 0)
    return;
  cout<<" * Random seed = "<<base<<endl;
  MatrixGame payGame(base);
  cout<<rows<< " X " <<cols << " Wage Matrix:"<<endl;
  payGame.printMatrix();
  int mm = payGame.maxMin();
  cout<<"The maximum of minimums of rows: "<< mm <<endl;
  mm = payGame.minMax();
  cout<<"The minimum of maximums of cols: "<< mm <<endl;
  cout<<"        --------------------"<<endl<<endl;
  cout<<"Next base: ";
  cin>>base;
  test(base);
}

int main(){
  MatrixGame::test();
  return 0;
}
