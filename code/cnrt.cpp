/**
 * An instructional program showing how to resolve the Chinese Remainder Theorem using the ExEuclidean method:
 *    forAll r: r = r1 (mod m1) and r = r2 (mod m2), s.t. u * m1 + v * m2 = 1 ->
 *       r = r2 * u * m1 + r1 * v * m2 + k * (m1 * m2)
 * Author: Linghuei Guo
 * Address: Henu, Kaifeng, China
 * Contact(GPG): 6819D81B0971C2C4
 * All Rights Reserved. */

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

namespace cnrt {
  typedef long long int i64;

  struct BezoutResult {
    i64 u, v, c;
    BezoutResult(): u(1), v(0), c(1) {}

    BezoutResult(i64 x, i64 y) {
      update(x, y);
    }

    void __looper__(i64 x, i64 y, i64& u, i64& v) {
      if (y == 0) {
	c = x;
	u = 1;
      }
      else {
	i64 k = x / y;
	__looper__(y, x % y, v, u);
	v -= k * u;
      }
    }

    // Update values s.t. u > 0, v < 0, ux + vy = c
    BezoutResult& update(i64 x, i64 y) {
      u = 1;
      v = 0;
      __looper__(x, y, u, v);
      return *this;
    }

    void test(i64 x, i64 y) {
      printf("            c =\t %-4lld\n", c);
      printf("%4lld * %-4lld + %4lld * %-4lld =\t %-4lld\n", u, x, v, y, u * x + v * y);
    }
  } bzObj;

  void test() {
    i64 x = 2222, y = 121;
    bzObj.update(x, y).test(x, y);
  }

  struct ChineseRemainder {
    i64 mod1, mod2;
    i64 r1, r2;
    i64 result;
    ChineseRemainder(): mod1(1), mod2(1), r1(0), r2(0), result(0) {}; 
    ChineseRemainder& resolve() {
      // update value: this -> result s.t. result == r1 (mod mod1) AND result == r2 (mod mod2)
      return resolve(r1, r2);
    }
    ChineseRemainder& resolve(i64 _r1, i64 _r2) {
      BezoutResult bzObj(mod1, mod2);

      // Shalt mod1 et mod2 be coprime:
      mod1 = mod1 / bzObj.c;
      mod2 = mod2 / bzObj.c;
      r1 = _r1 % mod1;
      r2 = _r2 % mod2;

      result = r2 * bzObj.u * mod1 + r1 * bzObj.v * mod2; 

      i64 m12 = mod1 * mod2;
      result = (result % m12 + m12) % m12;

      // Shalt the gcd information be verified and absorbed into.
      if (bzObj.c > 1) {
	assert(_r1 % bzObj.c == _r2 % bzObj.c);
	// Here guaranteed: mod1, mod2 and bzObj.c are multually coprime numbers, so no further recursions occur:
	return this -> extend(bzObj.c, _r1 % bzObj.c); 
      }
      return *this;
    }
    
    ChineseRemainder& extend(i64 mod3, i64 r3) {
      // update value: result <- _result s.t. _result == result (mod mod1 * mod2) AND _result == r3 (mod mod3)
      mod1 = mod1 * mod2;
      mod2 = mod3;
      return resolve(result, r3);
    }

    void printVerifier(i64 r) {
      i64 m12 = mod1 * mod2;
      printf("Verify: %8lld mod %-8lld =\t %-6lld == (result: %-4lld)\n", r, m12, r % m12, result);
    }

    void static test() {
      i64 r = 1234;
      ChineseRemainder obj;
      vector<i64> mods = {11, 22, 25, 35, 81};
      for (i64 m : mods) {
	obj.extend(m, r % m);
	obj.printVerifier(r);
      }
    }
  };
}

int main() {
  using cnrt::test;
  cnrt::ChineseRemainder::test();
}
