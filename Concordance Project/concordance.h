//
//  concordance
//

#ifndef concordance_solution_h
#define concordance_solution_h

#include <iostream>
#include <map>            /* std::multimap<T> and std::map<T> (not used) */
#include <list>
#include <vector>
#include <algorithm>      /* std::transform */
#include <string>         /* not needed for Mac OSX */


class StringLenCmp {
public:
	StringLenCmp() = default;

	// sort by length first, and then alphabetically
	bool operator()(const std::string& a, const std::string& b) const {
		return (a.size() < b.size()) || (a.size() == b.size() && a < b);
	}

private:
	// no data
};


class concordance {
	typedef std::multimap<std::string, size_t, StringLenCmp> wordDictType;

public:
	concordance(size_t minwordlen = 1, size_t maxwordlen = 50)
		: minwordlen_(minwordlen), maxwordlen_(maxwordlen), words_at_length_() {
		for (size_t i = 0; i < MAXWORDLEN; ++i) {
			words_at_length_.push_back(0);
		}
	}

	void add_word(const std::string&, size_t);
	size_t total_words() const; 
	size_t total_words(size_t length) const; 
	void print(std::ostream&) const; 

	void read_text(std::istream&, const std::string&);

private:
	static const size_t MAXWORDLEN = 40;

	wordDictType word_map_; // multimap with key=word and value=page number
	size_t minwordlen_;
	size_t maxwordlen_;
	std::vector<size_t> words_at_length_; // number of words of each length
};

//BREAK A LINE INTO A LIST OF WORDS
// Courtesy of Martin Broadhurst -- http://www.martinbroadhurst.com/how-to-split-a-string-in-c.html
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
void concordance::read_text(std::istream& in, const std::string& ignore) {
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

//Add a (word, line_number) to the multimap. Do not add if the same (word, line_number) is already present
void concordance::add_word(const std::string& word, size_t line) {
	// First get range of entries using key and iterator
	// Loop through the entires and check if any of them match current line
	for (auto l = word_map_.lower_bound(word); l != word_map_.upper_bound(word); ++l)
		if (l->second == line)
			return;
	// If above condition didnt happen insert word and line number.
	word_map_.insert(make_pair(word, line));

}

//Return the total number of words of length size
size_t concordance::total_words(size_t size) const {
	size_t ctr = 0; //Counter that keeps track of value
	//Goes through all possible lengths using iterator 
	//Checks to see if the length is equal to the size and return the words of that size
	for (auto it = word_map_.begin(); it != word_map_.end(); it = word_map_.upper_bound(it->first)) { if (it->first.length() == size) { ctr++; } }
	return ctr;
}

//Return the total number of words of all lengths
size_t concordance::total_words() const {
	size_t ctr = 0; //Counter that keeps track of value
	//Loop to check the size of the word and return total words (size_t so no conversion warning)
	for (size_t i = minwordlen_; i <= maxwordlen_; ++i) { ctr += total_words(i); }
	return ctr;
}

//Print list of words and line numbers as shown in example_concordances.txt in Project requirements document
void concordance::print(std::ostream& out) const {
	
	std::string lastword("Something random"); //Add something to the string so an empty string is not being passed
	//Loop through word map using iterator
	for (auto ptr = word_map_.begin(); ptr != word_map_.end(); ++ptr) {
		//Prints the line number if the word is same as previous
		if (lastword == (ptr)->first) { out << " " << (ptr)->second; }
		else {
			//Get first entry of the word
			lastword = (ptr)->first;
			out << std::endl << lastword << ": " << (ptr)->second;
		}
	}

}

#endif /* concordance_solution_h */
