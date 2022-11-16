#pragma once
#include <string>
#include <vector>
#include "User.h"
using namespace std;

class Book
{
private:
	struct BorrowHistory
	{
		int borrow_time;
		User* user;

		BorrowHistory(int borrow_time, User* user)
			:borrow_time(borrow_time), user(user) {}
	};


public:
	Book(string caption, string author, unsigned long long isbn, string publishing, string published_time, int price, string description)
		:caption(caption), author(author), isbn(isbn), publishing(publishing), published_time(published_time), price(price), description(description), borrowed_times(0) {}

	Book(char* caption, char* author, unsigned long long isbn, char* publishing, char* published_time, int price, char *description)
		:author(author), isbn(isbn), price(price), borrowed_times(0)
	{
		string cp(caption);
		this->caption = cp;
		string au(author);
		this->author = au;
		string pb(publishing);
		this->publishing = pb;
		string pt(published_time);
		this->published_time = pt;
		string dc(description);
		this->description = dc;
	}

	// 属性
	string caption;
	string author;
	unsigned long long isbn;
	string publishing;
	string published_time;
	string description;
	int price;
	int borrowed_times;


	vector<BorrowHistory*> borrow_histories; // 里面存放的是结构体指针,长度也相当于是借阅次数

	//方法
	void resetCaption(string 
		_caption);
	void resetCaption(char* new_caption);

	void resetAuthor(string new_author);
	void resetAuthor(char* new_author);

	void resetIsbn(unsigned long long new_isbn);

	void resetPrice(int price);

	void addBorrowHistory(int borrow_time = 0, string user_name = "default");

};

