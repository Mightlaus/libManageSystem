#include "BookRepo.h"
#include <algorithm>
#include <windows.h>
#include <iostream>
#include <regex>

// 按书名升序排列
void bookSort_caption(vector<Book*>& bookRepo)
{
	int size = bookRepo.size();
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (bookRepo[j]->caption > bookRepo[j + 1]->caption)
			{
				swap(bookRepo[j], bookRepo[j + 1]);
			}
		}
	}
}

// string -> wstring
wstring str2wstr(string str)
{
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	if (len == 0)
		return wstring(L"");
	wchar_t* wct = new wchar_t[len];
	if (!wct)
		return std::wstring(L"");

	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wct, len);
	wstring wstr(wct);
	delete[] wct;
	wct = NULL;
	return wstr;
}

// 模糊匹配字符串
bool sparseMatch(string str1, string str2)
{
	// 首先要转换为widestring
	wstring wstr1 = str2wstr(str1);
	wstring wstr2 = str2wstr(str2);
	// 如果str1中的全部char在str2中出现过或者相反，且两长度(len1+len2)/(len1-len2)>=2则认为匹配
	int len1 = wstr1.size();
	int len2 = wstr2.size();
	if ((len1 + len2) / abs(len1 - len2 + 0.0001) < 2)
	{
		return false;
	}

	bool match1 = true, match2 = true;
	for (int i = 0; i < len1; i++)
	{
		if (wstr2.find(wstr1[i]) == string::npos)
		{
			match1 = false;
			break;
		}
	}
	for (int i = 0; i < len2; i++)
	{
		if (wstr1.find(wstr2[i]) == string::npos)
		{
			match2 = false;
			break;
		}
	}

	if (match1 or match2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BookRepo::addOne(Book book)
{
    p_book_repo->push_back(book);
}

void BookRepo::addBatch(vector<string*> book_batch, int batch_size)
{
	for (int i = 0; i < batch_size; i++)
	{
		string caption = *(book_batch[i] + 2);
		string author = *(book_batch[i] + 3);
		unsigned long long isbn = stoll(*(book_batch[i] + 1));
		string publishing = *(book_batch[i] + 4);
		string published_time = *(book_batch[i] + 5);
		string description = *(book_batch[i] + 8);;
		int price = stoi(*(book_batch[i] + 6));

		Book thisBook(caption, author, isbn, publishing, published_time, price, description);
		addOne(thisBook);
	}
}

vector<Book*> BookRepo::find_isbn(unsigned long long isbn) // 精准搜索isbn
{
	vector<Book*> find_result_vec;

	for (int i = 0; i < p_book_repo->size(); i++)
	{
		if (p_book_repo->at(i).isbn == isbn)
		{
			find_result_vec.push_back(&(p_book_repo->at(i)));
		}
	}

	bookSort_caption(find_result_vec);
	return vector<Book*>(find_result_vec);
}

vector<Book*> BookRepo::find_caption(string caption) // 精准搜索caption
{
	vector<Book*> find_result_vec;

	for (int i = 0; i < p_book_repo->size(); i++)
	{
		if (p_book_repo->at(i).caption == caption)
		{
			find_result_vec.push_back(&(p_book_repo->at(i)));
		}
	}

	bookSort_caption(find_result_vec);
	return vector<Book*>(find_result_vec);
}

vector<Book*> BookRepo::find_author(string author) // 模糊搜索author
{
	vector<Book*> find_result_vec;

	for (int i = 0; i < p_book_repo->size(); i++)
	{
		if (sparseMatch(p_book_repo->at(i).author, author))
		{
			find_result_vec.push_back(&(p_book_repo->at(i)));
		}
	}

	bookSort_caption(find_result_vec);
	return vector<Book*>(find_result_vec);
}

vector<Book*> BookRepo::find_publish(string publish) // 模糊搜索publish
{
	vector<Book*> find_result_vec;

	for (int i = 0; i < p_book_repo->size(); i++)
	{
		if (sparseMatch(p_book_repo->at(i).publishing, publish))
		{
			find_result_vec.push_back(&(p_book_repo->at(i)));
		}
	}

	bookSort_caption(find_result_vec);
	return vector<Book*>(find_result_vec);
}
