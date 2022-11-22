#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

vector<string*> read_csv(int n);
void write_csv(int n, int m, string* s);