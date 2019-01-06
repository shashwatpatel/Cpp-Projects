#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <stdexcept>
#include "Webpage.h"
using namespace std;

class BrowserHistory {
public:
	//Prototypes
	BrowserHistory();

	void visitSite(Webpage newSite);
	string back();
	string forward();

	void readHistory(string fileName);

	string getUrl();
	size_t getNavSize();
	list<Webpage> getSitesVisited();

private:
	list<Webpage> navHistory;
	list<Webpage>::iterator navPos;
	list<Webpage> sitesVisited;
	int numSites;
};
//Default class BrowserHistory
BrowserHistory::BrowserHistory() {}

void BrowserHistory::visitSite(Webpage newSite) {
	//Add new sites and increment sites
	navHistory.push_back(newSite);
	sitesVisited.push_back(newSite);
	++numSites;

	if (navHistory.size() > 1) {
		while(navPos!=next(navHistory.end(),-1))
		{
			navHistory.pop_back();
		}
		navHistory.push_back(newSite);
		navPos = next(navHistory.end(), -1);
	}
	else { (navPos = navHistory.begin()); }
}

string BrowserHistory::back() {
	if (navPos != navHistory.begin()) {
		auto back = (prev(navPos, 1)); //Using auto to skip lines of code (Iterator)
		--navPos; //Going back decrements the navPos
		return back->getUrl(); //Pointing to the previous URL going back
	}
	else { throw new bad_alloc; } //Failed to allocate memory
}



string BrowserHistory::forward() {
	if (navPos != navHistory.end()) {
		auto next = (std::next(navPos, 1)); //Using auto to skip lines of code (Iterator)
		++navPos; //Increase navPos since we going forward
		return next->getUrl(); //Pointing to the next URL going forward
	}
	else { throw new bad_alloc; } //Failed to allocate memory
}

string BrowserHistory::getUrl() {
	if (!navHistory.empty()) { //Check to see if the history is not empty and point to the URL
		return navPos->getUrl();
	}
	else {
		throw logic_error("URL not found...");
	}
}
//Getters getting the size of navigation and the sitesVisited
size_t BrowserHistory::getNavSize() { return navHistory.size(); }

list<Webpage> BrowserHistory::getSitesVisited() { return sitesVisited; }

//Pre implemented
void BrowserHistory::readHistory(string fileName) {
	string temp;
	int newTime;
	Webpage newSite;
	ifstream inFile(fileName.c_str());

	while (inFile >> temp) {
		if (temp == "new") {
			inFile >> temp >> newTime;
			newSite = Webpage(temp, time_t(newTime));
			visitSite(newSite);
		}
		else if (temp == "back") {
			back();
		}
		else if (temp == "forward") {
			forward();
		}
		else {
			throw logic_error("invalid command");
		}
	}
}
