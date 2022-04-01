/* --------------------------------------- 
   Description: The solution of the extended Euclid decomposition issue from the C++ course of HENU
   Author: Linghuei Guo
   Affiliation: Henu, Kaifeng, China
   MailTo: guolh2013@hotmail.com
   Copyright: All Rights Reserved
--------------------------------------- */

#include <iostream>
#include <iomanip>
using namespace std;

// 使用 64 位长整形（long long int）计算
typedef long long int i64;

typedef void EuclidFunc(i64 a, i64 b, i64 &c, i64 &x, i64 &y);
EuclidFunc euclid, euclidPlain, euclidIterative, euclidLoop;

i64 gcd(i64 a, i64 b){
// Returns the Greatest Common Divider
  if (b == 0)
    return a;
  else
    return gcd(b, a % b);
}


void testEuclid(EuclidFunc * eu, i64 a, i64 b){
  i64 c, x, y;
  (*eu)(a, b, c, x, y);
  printf("  获得 %lld 和 %lld 的 Euclid 分解:\n", a, b);
  printf("  (%lld) * %lld + (%lld) * %lld = %lld\n", x, a, y, b, c);
  printf("       验证: ");
  i64 a1 = a / c;
  i64 b1 = b / c;
  printf("    %lld = %lld * %lld ,    ", a1 * c, a1, c);
  printf(" %lld = %lld * %lld   \n", b1 * c, b1, c);
  printf("       并且:    (%lld) * %lld + (%lld) * %lld = %lld\n", x, a1, y, b1,  x * a1 + y * b1);
  printf("  (上式输出为1方为正确答案！)\n");
}

int main(){
  // Array of pointers of euclid functions:
  EuclidFunc* eus[4] = {euclid, euclidPlain, euclidIterative, euclidLoop}; 
  string eusInfo[4] = {"Recursive", "Plain Searching", "Iterative", "Loop"};
  for (int i = 0; i < 4; i++){
    cout << endl << "------ " << eusInfo[i] << " ------" <<endl;
    testEuclid(eus[i], 5212 * 11, 88158 * 11);
  }
  return 0;
}








// ------------------------ Solution ------------------------










void euclid(i64 a, i64 b, i64 &c, i64 &x, i64 &y ){
  // 使用递归
  if (b == 0){
    c = a;
    x = 1;
    y = 0;
    return;
  }
  else {
    euclid(b, a % b, c, x, y);
    i64 k = a / b;
    i64 y2 = x - k * y;
    x = y;
    y = y2;
    return;
  }
}

/* euclid 函数的另外几种写法：*/



void euclidPlain(i64 a, i64 b, i64 &c, i64 &x, i64 &y ){
  // 暴力搜索法。效率不推荐，但这是一种通用的搜索思路
  c = gcd(a, b);
  // c = x*a + y*b, 其中
  // x, y 不唯一，但如果 a, b > 0 则 |x| < b/c 且 |y| <= a/c 中一定有解 (为啥？)
  for (x = 1; x <= 1 + b/c; x++){
    for (y = 1; y <= 1 + a/c; y++) { 
      i64 c1 = x * a - y * b;
      if (c == c1){
	y = -y;
	return;
      }
      else if (-c == c1){
	x = -x;
	return;
      }
    }
  }
}

void euclidIterative(i64 a, i64 b, i64 &c, i64 &x, i64 &y, i64 saa, i64 sba, i64 sab, i64 sbb ){
  // 使用迭代（尾递归）的 Euclid 分解。
  // 输入参数永远满足：
  // a = saa * a0 + sba * b0
  // b = sab * a0 + sbb * b0
  // Obviously, 若 b = 0, 则 saa, sba 已经是初始问题 (a0, b0) 的答案；否则，辗转相除之。
  if (b == 0){
    c = a;
    x = saa;
    y = sba;
    return;
  }
  else {
    i64 k = a / b;
    // 交换 a b 后对应 S 系数也要交换：
    euclidIterative(b, a % b, c, x, y, sab, sbb, saa - k * sab, sba - k * sbb);
  }
}

void euclidIterative(i64 a, i64 b, i64 &c, i64 &x, i64 &y){
  // Initiator of the iterative process.
  return euclidIterative(a, b, c, x, y, 1, 0, 0, 1);
}

void euclidLoop(i64 a, i64 b, i64 &c, i64 &x, i64 &y ){
  // Euclid decomposition with a while-loop directly deducted from the Iterative version.
  i64 saa = 1, sba = 0;
  i64 sab = 0, sbb = 1;
  i64 a1 = 0, k = 0;
  while (b != 0){
    k = a / b;
    a = a % b;
    saa -= k * sab;
    sba -= k * sbb;
    swap(a, b);
    swap(saa, sab);
    swap(sba, sbb);
  }
  c = a;
  x = saa;
  y = sba;
}


