#pragma once
#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <algorithm>      /* std::transform */
#include <string>         /* not needed for Mac OSX */


class TextAnalysis {
public:
	TextAnalysis() = default;
	void add_word(const std::string&, size_t); // IMPLEMENT BELOW
	size_t countWord(const std::string&); // IMPLEMENT BELOW
	size_t countTwoWords(const std::string&, const std::string&); // IMPLEMENT BELOW

	void read_text(std::istream&, const std::string&); 

private:
	std::unordered_map<std::string, std::vector<size_t> > wordtable; // hash table with key=word and value=vector of page numbers
};

//BREAK A LINE INTO A LIST OF WORDS
//Courtesy of Martin Broadhurst -- http://www.martinbroadhurst.com/how-to-split-a-string-in-c.html
template <class Container>
void split(const std::string& str, Container& cont, const std::string& delims = " ") {
	std::size_t curr, prev = 0;
	curr = str.find_first_of(delims);

	while (curr != std::string::npos) {                   // largest possible unsigned number
		cont.push_back(str.substr(prev, curr - prev));
		prev = curr + 1;
		curr = str.find_first_of(delims, prev);
	}

	cont.push_back(str.substr(prev, curr - prev));
}

//READ FROM A TEXT FILE LINE BY LINE
void TextAnalysis::read_text(std::istream& in, const std::string& ignore) {
	std::string line;

	for (size_t i = 1; getline(in, line, '\n'); i++) {
		std::transform(line.begin(), line.end(), line.begin(), ::tolower);

		typedef std::list<std::string> container;
		container words;                          // split into container, dump ignore chars
		split<container>(line, words, ignore);

		typename container::const_iterator cit;
		for (cit = words.cbegin(); cit != words.cend(); ++cit) { add_word(*cit, i); }
	}
}


void TextAnalysis::add_word(const std::string& word, size_t line) {
	//Inserting word and line number using iterator 
	auto itr1 = wordtable.insert(std::make_pair(word, std::vector<size_t>(1, 0)));
	//Adding line number to vector, avoids duplicates
	if (!itr1.second) {
		itr1.first->second.push_back(line);
	}
	
}

size_t TextAnalysis::countWord(const std::string& word) {
//Return the number of occurences of word
	return wordtable[word].size();
}

size_t TextAnalysis::countTwoWords(const std::string& word1, const std::string& word2) {
	//Vector to store words and size
	std::vector<size_t> count;
	//Iterators to iteratre through wordtable and find words
	auto a = wordtable.find(word1);
	auto b = wordtable.find(word2);
	if (a == wordtable.end()) { return 0; }
	//Check too see the word in wordmap using iteraror, if found then add to the vector, ignoring duplicates
	for (auto i : a->second) {
		//Using std::find to find and compare (Using with vector and iterator)
		if (std::find(b->second.begin(), b->second.end(), i) != b->second.end())
			if (std::find(count.begin(), count.end(), i) == count.end()) { count.push_back(i); }
	}
	return count.size();
}
