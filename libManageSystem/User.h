#pragma once
#include <string>
#include <vector>
#include "Book.h"


using namespace std;
class User
{
private:
	struct History
	{
		int action; // -1借书， 1还书， 0阅览
		int time;
		Book* p_book;
	};

public:
	User(string user_name, string key, char identity) {
		this->user_name = user_name;
		this->key = key;
		this->identity = identity;
	}

	char identity; // 用户身份 'S' 读者， 'A' 管理员， 'C' 游客
	string user_name;
	vector<History> histories;

	// 密码操作
	bool checkKey(string input_key); 
	void resetKey(string new_key); 

	// 查找图书
	vector<Book*> findBook_isbn(unsigned long long isbn);
	vector<Book*> findBook_caption(string caption);
	vector<Book*> findBook_author(string author);
	vector<Book*> findBook_publish(string publish);

	// 图书变动记录
	void addHistory(int action, int time, Book* p_book); 

protected:
	string key;
};

class Student :public User
{
	Student(string user_name, string key) :User(user_name, key, 'S') {}

	// 借还书操作
	void borrowBook(Book* p_book, int time);
	void returnBook(Book* p_book, int time);
};

class Admin :public User
{
	Admin(string user_name, string key) :User(user_name, key, 'A') {}

	// 管理图书操作
	void addBook(Book* p_book, int time);
	void delBook(Book* p_book, int time);
	void modifBook(Book* p_book, char modif_item);

	// 管理用户操作
};

class Customer :public User
{
	Customer(string user_name, string key) :User(user_name, key, 'C') {}
};