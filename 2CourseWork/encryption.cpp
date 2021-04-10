#include "Encryption.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define HMOD 1234577

string encryption::hash(string message, int h0) {

	long long ans = h0;

	for (char m : message) {
		ans = (ans + m) * (ans + m) % HMOD;
	}

	return to_string(ans);

}

string encryption::encrypt(string message) {
	vector<char> msg;

	for (char m : message) {
		msg.push_back(m);
	}

	vector<bool> lfsr1_init(26, true);
	vector<bool> lfsr2_init(34, true);
	vector<bool> lfsr3_init(24, true);

	msg = encode(msg, lfsr1_init, lfsr2_init, lfsr3_init, true);

	string ans;

	for (char m : msg) {
		ans += m;
	}

	return hash(ans, 100);

}

vector<char> encryption::encode(vector<char> msg, vector<bool> lfsr_init, vector<bool> lfsr2_init, vector<bool> lfsr3_init, bool gefe) {
	int sz = msg.size();

	int m1 = 26;
	vector<bool> lfsr1 = lfsr_init;
	vector<bool> a1(m1, 0);
	a1[0] = a1[6] = a1[7] = a1[m1 - 1] = 1;
	reverse(a1.begin(), a1.end());

	vector<char> key;

	int m2 = 34;
	vector<bool> lfsr2 = lfsr2_init;
	vector<bool> a2(m2, 0);
	a2[0] = a2[13] = a2[14] = a2[m2 - 1] = 1;
	reverse(a2.begin(), a2.end());

	int m3 = 24;
	vector<bool> lfsr3 = lfsr3_init;
	vector<bool> a3(m3, 0);
	a3[0] = a3[2] = a3[3] = a3[m3 - 1] = 1;
	reverse(a3.begin(), a3.end());

	key = bit2byte(gen_via_lfsr(sz, a1, lfsr1, a2, lfsr2, a3, lfsr3));

	vector<char> cph(msg.size());

	for (int i = 0; i < msg.size(); ++i)
		cph[i] = msg[i] ^ key[i];

	return cph;

}

vector<bool> encryption::gen_via_lfsr(int size, vector<bool> a1, vector<bool> reg1Init,
	vector<bool> a2, vector<bool> reg2Init,
	vector<bool> a3, vector<bool> reg3Init
) {

	size *= 8;

	int m1 = a1.size();
	vector<bool> lfsr1 = reg1Init;
	int m2 = a2.size();
	vector<bool> lfsr2 = reg2Init;
	int m3 = a3.size();
	vector<bool> lfsr3 = reg3Init;

	vector<bool> ans;

	for (int i = 0; i < size; ++i) {

		bool sum = 0;
		for (int j = 0; j < m1; ++j) {
			sum ^= a1[j] * lfsr1[j];
		}

		bool x1 = lfsr1[0];
		for (int j = 0; j < lfsr1.size() - 1; ++j) {
			lfsr1[j] = lfsr1[j + 1];
		}
		lfsr1[m1 - 1] = sum;


		sum = 0;
		for (int j = 0; j < m2; ++j) {
			sum ^= a2[j] * lfsr2[j];
		}

		bool x2 = lfsr2[0];
		for (int j = 0; j < lfsr2.size() - 1; ++j) {
			lfsr2[j] = lfsr2[j + 1];
		}
		lfsr2[m2 - 1] = sum;


		sum = 0;
		for (int j = 0; j < m3; ++j) {
			sum ^= a3[j] * lfsr3[j];
		}

		bool x3 = lfsr1[0];
		for (int j = 0; j < lfsr3.size() - 1; ++j) {
			lfsr3[j] = lfsr3[j + 1];
		}
		lfsr3[m3 - 1] = sum;

		ans.push_back((x1 && x2) || (!x1 && x3));
	}

	return ans;
}

vector<char> encryption::bit2byte(vector<bool> vec) {
	vector<char> ans;

	char chr = vec[0];
	for (int i = 1; i < vec.size(); ++i) {
		if (i % 8 == 0) {
			ans.push_back(chr);
			chr = vec[i];
		}
		else {
			chr = chr * 2 + vec[i];
		}
	}
	ans.push_back(chr);

	return ans;
}
