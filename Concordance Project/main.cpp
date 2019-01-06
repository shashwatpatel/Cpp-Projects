//
//  main.cpp
//  concordance
//
//

#include <iostream>
#include <fstream>
#include <string>         /* not needed for Mac OSX */

#include "concordance.h"

#define ARGC_ERROR  1
#define FILE_ERROR  2


template <typename T>
bool testAnswer(const std::string& nameOfTest, const T& received, const T& expected);

size_t testsPassed = 0;
size_t testsFailed = 0;


void make_concordance(concordance& conc, const std::string& inputfile) {
  std::ifstream ifs(inputfile);
  if (!ifs.is_open()) {
    std::cerr << "Could not open input file: " << inputfile << "\n";   exit(FILE_ERROR);
  }

  std::cout << "\n//--------------------------------------------------------------------------\n";
  std::cout << "//--------------------------------------------------------------------------\n";
  std::cout << "// MAKING CONCORDANCE with FILE: " << inputfile << "......";
  conc.read_text(ifs, " ,.;:!?\"()");
  conc.print(std::cout);

  ifs.close();
}

void test_concordance() {
  concordance conc_para(1, 10);
  make_concordance(conc_para, "hp1_paragraph1.txt");

  concordance conc_page(1, 15);
  make_concordance(conc_page, "hp1_page1.txt");

  concordance conc_chapter(1, 20);
  make_concordance(conc_chapter, "hp1_chapter1.txt");

  std::cout << "\nhp1_paragraph words with length..." << "\n";
  testAnswer("...para words with length  1", (int)conc_para.total_words( 1),  0);
  testAnswer("...para words with length  2", (int)conc_para.total_words( 2),  6);
  testAnswer("...para words with length  3", (int)conc_para.total_words( 3),  5);
  testAnswer("...para words with length  4", (int)conc_para.total_words( 4), 11);
  testAnswer("...para words with length  5", (int)conc_para.total_words( 5),  4);
  
  std::cout << "\n";
  testAnswer("...para words with length  6", (int)conc_para.total_words( 6),  6);
  testAnswer("...para words with length  7", (int)conc_para.total_words( 7),  3);
  testAnswer("...para words with length  8", (int)conc_para.total_words( 8),  3);
  testAnswer("...para words with length  9", (int)conc_para.total_words( 9),  1);
  testAnswer("...para words with length 10", (int)conc_para.total_words(10),  1);

  std::cout << "\n";
  testAnswer("hp1_para total words", (int)conc_para.total_words(), 40);

  std::cout << "\n";
  std::cout << "\nhp1_page words with length..." << "\n";
  testAnswer("...page words with length  1", (int)conc_page.total_words( 1),  1);
  testAnswer("...page words with length  2", (int)conc_page.total_words( 2), 15);
  testAnswer("...page words with length  3", (int)conc_page.total_words( 3), 30);
  testAnswer("...page words with length  4", (int)conc_page.total_words( 4), 48);
  testAnswer("...page words with length  5", (int)conc_page.total_words( 5), 30);
  
  std::cout << "\n";
  testAnswer("...page words with length  6", (int)conc_page.total_words( 6), 40);
  testAnswer("...page words with length  7", (int)conc_page.total_words( 7), 20);
  testAnswer("...page words with length  8", (int)conc_page.total_words( 8), 17);
  testAnswer("...page words with length  9", (int)conc_page.total_words( 9),  9);
  testAnswer("...page words with length 10", (int)conc_page.total_words(10),  2);

  std::cout << "\n";
  testAnswer("...page words with length 11", (int)conc_page.total_words(11),  0);
  testAnswer("...page words with length 12", (int)conc_page.total_words(12),  1);
  testAnswer("...page words with length 13", (int)conc_page.total_words(13),  0);
  testAnswer("...page words with length 14", (int)conc_page.total_words(14),  0);
  testAnswer("...page words with length 15", (int)conc_page.total_words(15),  0);

  std::cout << "\n";
  testAnswer("hp1_page1 total words", (int)conc_page.total_words(), 213);

  std::cout << "\n";
  std::cout << "\nhp1_chapter words with length..." << "\n";
  testAnswer("...chapter words with length  1", (int)conc_chapter.total_words( 1),   3);
  testAnswer("...chapter words with length  2", (int)conc_chapter.total_words( 2),  28);
  testAnswer("...chapter words with length  3", (int)conc_chapter.total_words( 3),  96);
  testAnswer("...chapter words with length  4", (int)conc_chapter.total_words( 4), 222);
  testAnswer("...chapter words with length  5", (int)conc_chapter.total_words( 5), 205);
  
  std::cout << "\n";
  testAnswer("...chapter words with length  6", (int)conc_chapter.total_words( 6), 207);
  testAnswer("...chapter words with length  7", (int)conc_chapter.total_words( 7), 184);
  testAnswer("...chapter words with length  8", (int)conc_chapter.total_words( 8), 122);
  testAnswer("...chapter words with length  9", (int)conc_chapter.total_words( 9),  62);
  testAnswer("...chapter words with length 10", (int)conc_chapter.total_words(10),  26);
  
  std::cout << "\n";
  testAnswer("...chapter words with length 11", (int)conc_chapter.total_words(11),  12);
  testAnswer("...chapter words with length 12", (int)conc_chapter.total_words(12),   7);
  testAnswer("...chapter words with length 13", (int)conc_chapter.total_words(13),   3);
  testAnswer("...chapter words with length 14", (int)conc_chapter.total_words(14),   1);
  testAnswer("...chapter words with length 15", (int)conc_chapter.total_words(15),   0);
  std::cout << "\n";
  testAnswer("hp1_chapter1 total words", (int)conc_chapter.total_words(), 1179);

  std::cout << "\n"; 
  testAnswer("Total tests passed", (int)testsPassed, 43);
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


int main(int argc, const char* argv[]) {
  test_concordance();

  std::cout << "\n\n\t\t...done.\n";
  return 0;
}
