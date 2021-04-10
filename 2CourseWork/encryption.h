#pragma once
#include <iostream>
#include <vector>

namespace encryption {
	using std::vector;
	std::string encrypt(std::string);
	vector<char> encode(vector<char>, vector<bool>, vector<bool>, vector<bool>, bool);
	vector<bool> gen_via_lfsr(int, vector<bool>, vector<bool>, vector<bool>, vector<bool>, vector<bool>, vector<bool>);
	vector<char> bit2byte(vector<bool>);
	std::string hash(std::string, int);
}