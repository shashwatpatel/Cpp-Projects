#include <iostream>
#include <fstream>
#include <string>

#include "TextAnalysis.h"

template <typename T>
bool testAnswer(const std::string& nameOfTest, const T& received, const T& expected);

int main() {
  { 
    std::string inputfile = "hp1_paragraph1.txt";
	TextAnalysis analyze_para;
	std::ifstream ifs(inputfile);
	if (!ifs.is_open()) {
  	  std::cerr << "Could not open input file: " <<inputfile << "\n";
	  return(-1);
	}

	std::cout << "// TESTING with FILE: " << inputfile << "......\n";
	analyze_para.read_text(ifs, " ,.;:!?\"()");
	ifs.close();

	testAnswer("TEST countWord(nonexist)", (int)analyze_para.countWord("nonexist"),  0);
	testAnswer("TEST countWord(nonsense)", (int)analyze_para.countWord("nonsense"),  1);
	testAnswer("TEST countWord(they)", (int)analyze_para.countWord("they"),  3);
	testAnswer("TEST countTwoWords(nonsense,they)", (int)analyze_para.countTwoWords("nonsense", "they"),  1);
	testAnswer("TEST countTwoWords(nonsense,nonexist)", (int)analyze_para.countTwoWords("nonsense", "nonexist"),  0);
  }

  { 
    std::string inputfile = "hp1_page1.txt";
	TextAnalysis analyze_para;
	std::ifstream ifs(inputfile);
	if (!ifs.is_open()) {
  	  std::cerr << "Could not open input file: " <<inputfile << "\n";
	  return(-1);
	}

	std::cout << "// TESTING with FILE: " << inputfile << "......\n";
	analyze_para.read_text(ifs, " ,.;:!?\"()");
	ifs.close();

	testAnswer("TEST countWord(sister)", (int)analyze_para.countWord("sister"),  3);
	testAnswer("TEST countWord(they)", (int)analyze_para.countWord("they"),  10);
	testAnswer("TEST countWord(his)", (int)analyze_para.countWord("his"),  5);
	testAnswer("TEST countTwoWords(sister,they)", (int)analyze_para.countTwoWords("sister", "they"),  1);
	testAnswer("TEST countTwoWords(that,they)", (int)analyze_para.countTwoWords("that", "they"),  3);
  }

  { 
    std::string inputfile = "hp1_chapter1.txt";
	TextAnalysis analyze_para;
	std::ifstream ifs(inputfile);
	if (!ifs.is_open()) {
  	  std::cerr << "Could not open input file: " <<inputfile << "\n";
	  return(-1);
	}

	std::cout << "// TESTING with FILE: " << inputfile << "......\n";
	analyze_para.read_text(ifs, " ,.;:!?\"()");
	ifs.close();

	testAnswer("TEST countWord(sister)", (int)analyze_para.countWord("sister"),  7);
	testAnswer("TEST countWord(they)", (int)analyze_para.countWord("they"),  22);
	testAnswer("TEST countWord(his)", (int)analyze_para.countWord("his"),  70);
	testAnswer("TEST countTwoWords(sister,they)", (int)analyze_para.countTwoWords("sister", "they"),  2);
	testAnswer("TEST countTwoWords(that,they)", (int)analyze_para.countTwoWords("that", "they"),  9);
  }

  std::cout << "All tests completed\n";
  return (0);
}

template <typename T>
bool testAnswer(const std::string& nameOfTest, const T& received, const T& expected) {
  if (received == expected) {
    std::cout << "PASSED " << nameOfTest
                           << ": expected and received " << received << std::endl;
    //++testsPassed;
    return true;
  }
  std::cout << "FAILED " << nameOfTest
            << ": expected " << expected << " but received " << received << std::endl;
  //++testsFailed;
  return false;
}


