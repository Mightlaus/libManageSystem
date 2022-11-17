#pragma once
#include <string>
#include <vector>
#include "Book.h"
#include "BookRepo.h"

using namespace std;

class Book;

class User
{
public:
	struct UserHistory
	{
		int action; // -1借书， 1还书， 0阅览
		int time;
		Book* p_book;
		UserHistory(int time, int action, Book* p_book) :action(action), time(time), p_book(p_book) {}
	};

public:
	User(string user_name, string key, char identity, BookRepo* p_books) {
		this->user_name = user_name;
		this->key = key;
		this->identity = identity;
		this->p_books = p_books;
		exist = 1;
	}

	char identity; // 用户身份 'S' 读者， 'A' 管理员， 'C' 游客
	int exist;
	string user_name;
	vector<UserHistory> histories;

	// 密码操作
	bool checkKey(string input_key);
	int resetKey(string new_key);

	// 查找图书
	vector<Book*> findBook_isbn(string isbn);
	vector<Book*> findBook_caption(string caption);
	vector<Book*> findBook_author(string author);
	vector<Book*> findBook_publish(string publish);

	// 图书变动记录
	int addHistory(int time, int action, Book* p_book);

protected:
	string key;
	BookRepo* p_books;
};

class Student :public User
{
public:
	Student(string user_name, string key, BookRepo* p_books) :User(user_name, key, 'S', p_books) {}

	// 借还书操作
	int borrowBook(Book* p_book, int time);
	int returnBook(Book* p_book, int time);
};

class Admin :public User
{
public:
	Admin(string user_name, string key, BookRepo* p_books) :User(user_name, key, 'A', p_books) {}

	// 管理图书操作
	int addBook(Book book, int time);
	int delBook(Book* p_book, int time);
	int modifBook(Book* p_book, char modif_item);

	// 管理用户操作
};

class Customer :public User
{
public:
	Customer(string user_name, string key, BookRepo* p_books) :User(user_name, key, 'C', p_books) {}
};