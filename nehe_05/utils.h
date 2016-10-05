#ifndef __utils_h
#define __utils_h
#include <string>
#include <regex>
#include <vector>
using namespace std;
vector<string> SplitString(const std::string str, const std::string regExpr)
{
	std::regex rgx(regExpr);
	std::sregex_token_iterator iter(str.begin(), str.end(), rgx, -1);
	std::sregex_token_iterator end;
	std::vector<string> pedacos;
	for (; iter != end; ++iter)
		pedacos.push_back(*iter);
	return pedacos;
}

/*
std::regex rgx("\\s+");
regex_token_iterator<std::string::iterator> sregex_token_iterator;
std::sregex_token_iterator iter(str.begin(),str.end(),rgx,-1);
std::sregex_token_iterator end;
std::vector<string> pedacos;
for (; iter != end; ++iter)
pedacos.push_back(*iter);
*/
#endif __utils_h
