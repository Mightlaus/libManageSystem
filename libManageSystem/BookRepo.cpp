#include "BookRepo.h"
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
void bookSort_publish(vector<Book*>& bookRepo, int len = 5)
{
	int size = bookRepo.size();
	for (int i = 0; i < len; i++)
	{
		for (int j = size - 1; j > i; j--)
		{
			if (publishTime(bookRepo[j]->published_time) > publishTime(bookRepo[j - 1]->published_time))
			{
				swap(bookRepo[j], bookRepo[j - 1]);
			}
		}
	}
}

// ��������������
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

// ģ��ƥ���ַ���
bool sparseMatch(string str1, string str2)
{
	// ����Ҫת��Ϊwidestring
	wstring wstr1 = str2wstr(str1);
	wstring wstr2 = str2wstr(str2);
	// ���str1�е�ȫ��char��str2�г��ֹ������෴����������(len1+len2)/(len1-len2)>=2����Ϊƥ��
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
	bookNums++;
}

void BookRepo::addBatch(vector<string*> book_batch, int batch_size)
{
	for (int i = 0; i < batch_size; i++)
	{
		string caption = *(book_batch[i] + 2);
		string author = *(book_batch[i] + 3);
		string isbn = *(book_batch[i] + 1);
		string publishing = *(book_batch[i] + 4);
		string published_time = *(book_batch[i] + 5);
		string description = *(book_batch[i] + 8);;
		double price = stod(*(book_batch[i] + 6));

		Book thisBook(caption, author, isbn, publishing, published_time, price, description);
		addOne(thisBook);
	}
}

void BookRepo::delOne(Book* p_book)
{
	p_book->exist = 0;
	bookNums--;
}

void BookRepo::delBatch(vector<Book*> book_vec)
{
	for (auto p_book : book_vec)
	{
		delOne(p_book);
	}
}

void BookRepo::modifCaption(Book* p_book, string caption)
{
	p_book->resetCaption(caption);
}

void BookRepo::modifAuthor(Book* p_book, string author)
{
	p_book->resetAuthor(author);
}

void BookRepo::modifIsbn(Book* p_book, string isbn)
{
	p_book->resetIsbn(isbn);
}

void BookRepo::modifPrice(Book* p_book, double price)
{
	p_book->resetPrice(price);
}


vector<Book*> BookRepo::find_isbn(string isbn) // ��׼����isbn
{
	vector<Book*> find_result_vec;

	for (int i = 0; i < p_book_repo->size(); i++)
	{
		if (p_book_repo->at(i).isbn == isbn && p_book_repo->at(i).exist)
		{
			find_result_vec.push_back(&(p_book_repo->at(i)));
		}
	}

	bookSort_caption(find_result_vec);
	return vector<Book*>(find_result_vec);
}

vector<Book*> BookRepo::find_caption(string caption) // ��׼����caption
{
	vector<Book*> find_result_vec;

	for (int i = 0; i < p_book_repo->size(); i++)
	{
		if (p_book_repo->at(i).caption == caption && p_book_repo->at(i).exist)
		{
			find_result_vec.push_back(&(p_book_repo->at(i)));
		}
	}

	bookSort_caption(find_result_vec);
	return vector<Book*>(find_result_vec);
}

vector<Book*> BookRepo::find_author(string author) // ģ������author
{
	vector<Book*> find_result_vec;

	for (int i = 0; i < p_book_repo->size(); i++)
	{
		if (sparseMatch(p_book_repo->at(i).author, author) && p_book_repo->at(i).exist)
		{
			find_result_vec.push_back(&(p_book_repo->at(i)));
		}
	}

	bookSort_caption(find_result_vec);
	return vector<Book*>(find_result_vec);
}

vector<Book*> BookRepo::find_publish(string publish) // ģ������publish
{
	vector<Book*> find_result_vec;

	for (int i = 0; i < p_book_repo->size(); i++)
	{
		if (sparseMatch(p_book_repo->at(i).publishing, publish) && p_book_repo->at(i).exist)
		{
			find_result_vec.push_back(&(p_book_repo->at(i)));
		}
	}

	bookSort_caption(find_result_vec);
	return vector<Book*>(find_result_vec);
}


vector<Book*> BookRepo::rankBook_newest(int rank_len)
{
	vector<Book*> rank_vec; //ȫ���������
	vector<Book*> result_vec; // Ҫȡ��rank

	for (auto& book : *p_book_repo)
	{
		if (book.exist)
		{
			rank_vec.push_back(&book);
		}

	}

	bookSort_publish(rank_vec);

	for (int i = 0; i < rank_len; i++)
	{
		result_vec.push_back(rank_vec[i]);
	}


	return vector<Book*>(result_vec);
}