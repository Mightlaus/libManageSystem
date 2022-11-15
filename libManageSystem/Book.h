#pragma once
#include <string>
#include <vector>

using namespace std;

class Book
{
private:
	struct BorrowHistory
	{
		int borrow_time;
		string user_name;

		BorrowHistory(int borrow_time = 0, string user_name = "default")
			:borrow_time(borrow_time), user_name(user_name) {}
	};


public:
	Book(string caption, string author, unsigned long long isbn, string publishing, string published_time, int price)
		:caption(caption), author(author), isbn(isbn), publishing(publishing), published_time(published_time), price(price) {}

	Book(char* caption, char* author, unsigned long long isbn, char* publishing, char* published_time, int price)
		:caption(caption), author(author), isbn(isbn), price(price)
	{
		string cp(caption);
		this->caption = cp;
		string au(author);
		this->author = au;
		string pb(publishing);
		this->publishing = pb;
		string pt(published_time);
		this->published_time = pt;
	}

	// 属性
	string caption;
	string author;
	unsigned long long isbn;
	string publishing;
	string published_time;
	int price;


	vector<BorrowHistory*> borrow_histories; // 里面存放的是结构体指针

	//方法
	void resetCaption(string new_caption);
	void resetCaption(char* new_caption);

	void resetAuthor(string new_author);
	void resetAuthor(char* new_author);

	void resetIsbn(unsigned long long new_isbn);

	void resetPrice(int price);

	void addBorrowHistory(int borrow_time = 0, string user_name = "default");
	void addBorrowHistory(int borrow_time, char* user_name);

};

