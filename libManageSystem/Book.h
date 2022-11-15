#pragma once
#include <string>
#include <vector>

using namespace std;

class Book
{
	Book(string caption, string author, unsigned long long isbn)
		:caption(caption), author(author), isbn(isbn) {}

private:
	struct BorrowHistory
	{
		int borrow_time;
		string user_name;

		BorrowHistory(int borrow_time = 0, string user_name = "default")
			:borrow_time(borrow_time), user_name(user_name) {}
	};


public:
	string caption;
	string author;
	unsigned long long isbn;
	vector<BorrowHistory*> borrow_histories; // �����ŵ��ǽṹ��ָ��

	void resetCaption(string new_caption);
	void resetAuthor(string new_author);
	void resetIsbn(unsigned long long new_isbn);

	void addBorrowHistory(int borrow_time = 0, string user_name = "default");

};

