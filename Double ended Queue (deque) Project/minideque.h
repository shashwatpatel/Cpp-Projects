//  minideque.h
//  minidequeproject

#ifndef minideque_h
#define minideque_h

#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <iostream>


template <typename T>
class minideque {
private:
	std::vector<T> fronthalf_;
	std::vector<T> backhalf_;


public:
	minideque() = default;                                   // do not change, C++ defaults are ok
	minideque(const minideque<T>& other) = default;          // rule of three
	minideque& operator=(const minideque<T>& other) = default;
	~minideque() = default;

	size_t size() const { return fronthalf_.size() + backhalf_.size(); } // Function made up of front and back vector sizes
	size_t fronthalfsize() const { return fronthalf_.size(); } // Gets the front vectors size
	size_t backhalfsize() const { return backhalf_.size(); } // Gets the back vectors size
	bool empty()  const { return fronthalf_.size() == 0 && backhalf_.size() == 0; } // Retuns a boolean if front and back vectors are empty

// balance queue across both vectors if pop_front/back is requested on an empty vector
// e.g., minideque has this:                  | ABCDEFG
// after pop_front                        BCD | EFG (A discarded)
// symmetric logic for converse case: ABCDEFG | ===> ABC | DEF (G discarded) after pop_back

	void pop_front() // Pops element from back vector to front vector
	{
		if (!fronthalf_.empty())
			fronthalf_.pop_back();
		else {

			if (size() % 2 != 0) {
				backhalf_.erase(backhalf_.begin());
			}

			while (fronthalfsize() != backhalfsize()) {
				fronthalf_.push_back(backhalf_.front());
				backhalf_.erase(backhalf_.begin());
			}
			reverse(fronthalf_.begin(), fronthalf_.end());
			if (fronthalf_.size() == 1) { fronthalf_.clear(); }
		}

	}

	void pop_back() { // Pops element from front vector to back vector

		if (!backhalf_.empty())
			backhalf_.pop_back();
		else {

			if (size() % 2 != 0) {
				fronthalf_.erase(fronthalf_.begin());
			}

			while (fronthalfsize() != backhalfsize()) {
				backhalf_.push_back(fronthalf_.front());
				fronthalf_.erase(fronthalf_.begin());
			}
			reverse(backhalf_.begin(), backhalf_.end());
			if (backhalf_.size() == 1) { backhalf_.clear(); }
		}
	}

	void push_front(const T& value) { fronthalf_.push_back(value); } // Pushes value to fronthalf vector

	void push_back(const T& value) { backhalf_.push_back(value); } // Pushes value to backhalf vector

	const T& front() const   // If fronthalf vector is empty it will call the front of backhalf vector
	{
		if (fronthalf_.empty()) {
			return backhalf_.front();
		}
		else {
			return fronthalf_.back();
		}

	}
	const T& back() const    // If backhalf vector is empty it will call the front fronthalf vector
	{
		if (backhalf_.empty()) {
			return fronthalf_.front();
		}
		else {
			return backhalf_.back();
		}
	}
	T& front()    // If fronthalf vector is empty it will call the front backhalf vector
	{
		if (fronthalf_.empty()) {
			return backhalf_.front();
		}
		else {
			return fronthalf_.back();
		}
	}
	T& back()   // If backhalf vector is empty it will call the front fronthalf vector
	{
		if (backhalf_.empty()) {
			return fronthalf_.front();
		}
		else {
			return backhalf_.back();
		}
	}

	const T& operator[](size_t index) const  // Finds the i'th element from front or back vector and returns it
	{
		
		if (index<fronthalf_.size())
			return fronthalf_[fronthalf_.size() - (index + 1)];
		else
			return backhalf_[index - fronthalf_.size()];
	}

	T& operator[](size_t index)   // Finds the i'th element from front or back vector and returns it           
	{
		if (index<fronthalf_.size())
			return fronthalf_[fronthalf_.size() - (index + 1)];
		else
			return backhalf_[index - fronthalf_.size()];

	}

	void clear()  // Clears both front and back vectors
	{
		fronthalf_.clear();
		backhalf_.clear();
	}

	friend std::ostream& operator<<(std::ostream& os, const minideque<T>& dq) {    // do not change
		if (dq.empty()) { return os << "minideque is empty"; }

		dq.printFronthalf(os);
		os << "| ";
		dq.printBackhalf(os);
		os << ", front:" << dq.front() << ", back:" << dq.back() << ", size:" << dq.size();
		return os;
	}

	void printFronthalf(std::ostream& os = std::cout) const {                    // do not change
		if (empty()) { std::cout << "fronthalf vector is empty"; }

		for (typename std::vector<T>::const_reverse_iterator crit = fronthalf_.crbegin();
			crit != fronthalf_.crend(); ++crit) {
			os << *crit << " ";
		}
	}

	void printBackhalf(std::ostream& os = std::cout) const {                     // do not change
		if (empty()) { os << "backhalf vector is empty"; }

		for (typename std::vector<T>::const_iterator cit = backhalf_.cbegin();
			cit != backhalf_.cend(); ++cit) {
			os << *cit << " ";
		}
	}
};

#endif /* minideque_h */
