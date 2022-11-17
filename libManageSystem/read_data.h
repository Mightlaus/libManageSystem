#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
class input_output
{
public:
	vector<string*> read_csv();
	void write_csv(int n, int m, string* s);
};
