/*
 * The basic Boyer-Moore pattern matching algorithm for instructional purpose.
 * The suffix table and the longest suffix matches are printed into the console,
 * to provide a better illustration of the suffix matches in each step.
 * Author: Linghuei Guo. Hnu, Kaifeng, China
 * GPG   : 6819D81B0971C2C4
 * All rights reserved.
 */

#include <iostream>
#include <iomanip>
using namespace std;

namespace boyer_moore {

  template<typename T>
  int suffix_length(int k1, int k2, T* arr1, T* arr2, int patternLen, int* mapSufix) {
    // assert: arr1[k1 - k2 + 1 .. k1 - 1] ~ arr2[0 .. k2 - 1] inclusively
    // @mapSufix: array of max lengths of  matched arr2 suffixes  aligned to each position of arr1.
    // returning: the index - max k' < k s.t. arr1[k1 - k' + 1 .. k1] ~ arr2[0 .. k'] inclusively.
    if (k2 < 0) {
      return k2; // k' < k and may be negative.
    }
    else if (k2 == patternLen || arr1[k1] != arr2[k2]) {
      return suffix_length(k1, mapSufix[k2], arr1, arr2, patternLen, mapSufix);
    }
    else
      return k2;
  }

  template<typename T>
  int selfMatch(int k, T* arr, int arrLen, int *mapSufix) {
    int k2 = mapSufix[k - 1];
    return suffix_length(k - 1, k2, arr, arr, arrLen, mapSufix);
  }

  template<typename T>
  void buildMatcher(T* arr, int arrLen, int* mapSuffix) {
    // build a suffix matching table in mapSuffix containing the length of  each longest matched suffix of arr2[0..end] inside arr2[1..end]
    mapSuffix[0] = -1;
    for (int i = 1; i <= arrLen; i++) {
      mapSuffix[i] = selfMatch(i, arr, arrLen, mapSuffix) + 1;
    }
  }

  template<typename T>
  void printPattern(T* arr, int* mapSuffix, int arrLen) {
    for (int i = 0; i < arrLen; ++i) {
      cout<<setw(4)<<(arr[i])<<",";
    }
    cout<<endl;
    for (int i = 0; i <= arrLen; ++i) {
      cout<<setw(4)<<(mapSuffix[i])<<",";
    }
    cout<<endl;
  }

  template<typename T>
  void matchEverywhere(T* arr1, T* arr2, int textLen, int patternLen, int *result) {
    int suffixTable[patternLen + 1];
    buildMatcher(arr2, patternLen, suffixTable);
    for (int i = 0, j = 0; i < textLen; ++i) {
      j = suffix_length(i, j, arr1, arr2, patternLen, suffixTable);
      result[i] = j++;
    }
  }

  template<typename T>
  void printMatches(T *arr, int* matched, int textLength) {
    for (int i = 0; i < textLength; ++i) {
      cout<<setw(4)<<arr[i]<<",";
    }
    cout<<endl;
    for (int i = 0; i < textLength; ++i) {
      cout<<setw(4)<<matched[i]<<",";
    }
    cout<<endl;
  }

  void test(){
    char arr1[] = "aaaabaabcaaaabaabcaabaabcdaabaabcdaaaaaaaaa";
    char arr2[] = "aabaabcaabaabcdaa";
    
    int patternLen = sizeof(arr2) / sizeof(char) - 1;
    int textLen = sizeof(arr1) / sizeof(char) - 1;

    int mapSuffix[patternLen + 1];
    int matchResult[textLen];


    buildMatcher(arr2, patternLen, mapSuffix);
    printPattern(arr2, mapSuffix, patternLen);

    matchEverywhere(arr1, arr2, textLen, patternLen, matchResult);
    printMatches(arr1, matchResult, textLen);
  }
}

int main(int argnum, char **argarray) {
  using namespace boyer_moore;
  test();
}
