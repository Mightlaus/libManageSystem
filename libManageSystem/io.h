#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Repo.h"
using namespace std;


namespace io
{
	vector<string*> read_csv(int n);
	void write_csv(int n, int m, string* s);
	void add_user_from_file(Repo* repo);
	void save_user_to_file(Repo* repo);
	void welcome();
	void bye();
}
