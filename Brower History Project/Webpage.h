#pragma once

#include <string>
using namespace std;

class Webpage {
public:
	Webpage();
	Webpage(const string&, const time_t&);
	string getUrl();
	time_t getTime();

private:
	string url;
	time_t time;
};
//Default Constructor
Webpage::Webpage() {
	url = "";
	time = time_t(NULL);
}
//Overloaded Constructor
Webpage::Webpage(const string& webpageUrl, const time_t& timeVisited) {
	url = webpageUrl;
	time = timeVisited;
}
//Returning data (Getters)
string Webpage::getUrl() { return url; }

time_t Webpage::getTime() { return time; }
