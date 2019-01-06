//
//  minideque_project_main.cpp
//  minideque_project
//
//

#include <iostream>
#include "minideque.h"


template <typename T>
bool testAnswer(const std::string& nameOfTest, const T& received, const T& expected);

size_t testsPassed = 0;
size_t testsFailed = 0;

void test_minideque() {
  minideque<int> dq;
  dq.push_back(9);
  testAnswer("dq[0] == dq.front()", dq[0] == dq.front(), true);
  testAnswer("dq[0] == 9", dq[0], 9);
  
  dq.push_front(1);
  testAnswer("dq.front() == 1", dq.front(), 1);
  testAnswer("dq.back() == 9", dq.back(), 9);
  
  std::vector<int> valuesfront = { 2, 3, 4, 5, 6, 7, 8 };
  std::vector<int> valuesback = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
  
  for (auto el : valuesfront) {
    dq.push_front(el);
    testAnswer("dq.front() == dq.push_front(el)", dq.front(), el);
  }
  
  for (auto el : valuesback) {
    dq.push_back(el);
    testAnswer("dq.back() == dq.push_back(el)", dq.back(), el);
  }
  
  int value = 9999;
  dq[0] = value;
  testAnswer("assign to array index", dq[0], value);
  testAnswer("read from array index", dq[0], value);
  
  std::cout << "\nclearing the minideque...\n";
  std::cout << "NOTE: the minideque keeps REBALANCING the front/back to have similar # entries\n";
  while (!dq.empty()) {
    dq.pop_front();
    std::cout << "dq.pop_front() ==> " << dq << "\n";
    if (!dq.empty()) {
      if (dq.front() == 10 || dq.front() == 16) {
        testAnswer("rebalancing fronthalf and backhalf vectors",
                   dq.fronthalfsize(), dq.backhalfsize());
      }
    }
  }
  std::cout << "\n\nPassed: " << testsPassed << " out of: " << testsPassed + testsFailed
  << " total tests.\n";
}

template <typename T>
bool testAnswer(const std::string& nameOfTest, const T& received, const T& expected) {
  if (received == expected) {
    std::cout << "PASSED " << nameOfTest
    << ": expected and received " << received << std::endl;
    ++testsPassed;
    return true;
  }
  std::cout << "FAILED " << nameOfTest
  << ": expected " << expected << " but received " << received << std::endl;
  ++testsFailed;
  return false;
}


int main(int argc, const char * argv[]) {
  test_minideque();
  
  std::cout << "\n\t\t...done.\n";
  return 0;
}
