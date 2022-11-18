#pragma once
#include <string>
#include <vector>
using namespace std;

class User;

class Book
{
public:
	struct BookHistory
	{
		int time;
		int action; // -1借， 0阅览，1还
		User* user;

		BookHistory(int time, int action, User* user)
			:time(time), action(action), user(user) {}
	};


public:
	Book(string caption, string author, string isbn, string publishing, string published_time, string description, int pages, double price)
		:caption(caption),
		author(author),
		isbn(isbn),
		publishing(publishing),
		published_time(published_time),
		description(description),
		pages(pages),
		price(price),

		borrowed_times(0),
		exist(1),
		borrowed(0) {}

	// 属性
	int exist; // 是否还存在（没有被删除）
	int borrowed; // 是否被借走
	string caption;
	string author;
	string isbn;
	string publishing;
	string published_time;
	string description;
	int pages;
	double price;
	int borrowed_times;


	vector<BookHistory> histories; // 里面存放的是结构体指针,长度也相当于是借阅次数

	//方法
	void resetCaption(string new_caption);
	void resetCaption(char* new_caption);

	void resetAuthor(string new_author);
	void resetAuthor(char* new_author);

	void resetIsbn(string new_isbn);

	void resetDescription(string new_description);

	void resetPrice(double price);

	void addHistory(int time, int action, User* p_user);

};

