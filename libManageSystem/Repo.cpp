#include "Repo.h"
#include <algorithm>
#include <windows.h>
#include <iostream>
#include <regex>


// ����ʱ��ת��
int publishTime(string str_time)
{
	int time = 0;

	if (str_time.empty()) {
		return -1;
	}
	
	if (stoi(str_time.substr(0, 4)) > 2022) {
		return -1;
	}

	regex pattern_year("(\\d+)");
	regex pattern_month("\\d+.+?(\\d+)");
	regex pattern_day("\\d+[-_��]\\d+[-_��](\\d+)");

	smatch result;
	if (regex_search(str_time, result, pattern_year))
	{
		time += stoi(result.str()) * 10000;
	}
	if (regex_search(str_time, result, pattern_month))
	{
		time += stoi(result[1].str()) * 100;
	}
	if (regex_search(str_time, result, pattern_day))
	{
		time += stoi(result[1].str());
	}

	return time;
	
}

//���������ڽ������� 
void bookSort_publish(vector<Book*>& bookRepo, int len=5)
{
	int size = bookRepo.size();
	for (int i = 0; i < len; i++)
	{
		for (int j = size-1; j > i; j--)
		{
			if (publishTime(bookRepo[j]->published_time) > publishTime(bookRepo[j - 1]->published_time))
			{
				swap(bookRepo[j], bookRepo[j - 1]);
			}
		}
	}
}


vector<Book*> Repo::rankBook_newest(int rank_len)
{
	vector<Book*> rank_vec; //ȫ���������
	vector<Book*> result_vec; // Ҫȡ��rank

	for (auto& book : *p_book_repo)
	{
		rank_vec.push_back(&book);
	}

	bookSort_publish(rank_vec);

	for (int i = 0; i < rank_len; i++)
	{
		result_vec.push_back(rank_vec[i]);
	}

	
	return vector<Book*>(result_vec);
}

