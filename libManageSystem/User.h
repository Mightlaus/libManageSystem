#pragma once
#include "Book.h"
#include "BookRepo.h"

using namespace std;


class User
{
public:
	struct UserHistory
	{
		int action; // -1借书， 1还书， 0阅览
		long long time;
		Book* p_book;
		UserHistory(long long time, int action, Book* p_book) :action(action), time(time), p_book(p_book) {}
	};
	User(string user_name, string key, char identity, BookRepo* p_book_repo) {
		this->user_name = user_name;
		this->key = key;
		this->identity = identity;
		this->p_book_repo = p_book_repo;
		exist = 1;
	}

	char identity; // 用户身份 'S' 读者， 'A' 管理员， 'V' 游客
	int exist;
	string user_name;
	vector<UserHistory> histories;

	// 密码操作
	bool checkKey(string input_key);
	int resetKey(string new_key);

	// 查找图书 author与publish提供模糊查找功能，isbn与caption精准查找
	vector<Book*> findBook_isbn(string isbn);
	vector<Book*> findBook_caption(string caption);
	vector<Book*> findBook_author(string author);
	vector<Book*> findBook_publish(string publish);

	// 图书变动记录
	int addHistory(long long time, int action, Book* p_book);

	string key;
	BookRepo* p_book_repo;
};

class Student :public User
{
public:
	Student(string user_name, string key, BookRepo* p_book_repo) :User(user_name, key, 'S', p_book_repo) 
	{
		borrowTimes = 0;
	}

	int borrowTimes;

	// 借还书操作
	int borrowBook(Book* p_book, long long time);
	int returnBook(Book* p_book, long long time);
	// 获得所有正在借还未归还的图书
	vector<Book*> getBorrowing();
};

class Admin :public User
{
public:
	Admin(string user_name, string key, BookRepo* p_book_repo) :User(user_name, key, 'A', p_book_repo) {}

	// 管理图书操作
	int addBook(Book book, long long time);
	int delBook(Book* p_book, long long time);
	int modifBook(Book* p_book, char modif_item, string new_content); // 除price、pages外的其他属性
};

class Visitor :public User
{
public:
	Visitor(string user_name, string key, BookRepo* p_book_repo) :User(user_name, key, 'V', p_book_repo) {}
};