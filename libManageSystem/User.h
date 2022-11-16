#pragma once
#include <string>
#include <vector>
#include "Book.h"

using namespace std;

class Book;

class User
{
private:
	struct History
	{
		int action; // -1���飬 1���飬 0����
		int time;
		Book* p_book;
		History(int time, int action, Book* p_book) :action(action), time(time), p_book(p_book){}
	};

public:
	User(string user_name, string key, char identity) {
		this->user_name = user_name;
		this->key = key;
		this->identity = identity;
	}

	char identity; // �û���� 'S' ���ߣ� 'A' ����Ա�� 'C' �ο�
	string user_name;
	vector<History> histories;

	// �������
	bool checkKey(string input_key); 
	int resetKey(string new_key); 

	// ����ͼ��
	vector<Book*> findBook_isbn(unsigned long long isbn);
	vector<Book*> findBook_caption(string caption);
	vector<Book*> findBook_author(string author);
	vector<Book*> findBook_publish(string publish);

	// ͼ��䶯��¼
	int addHistory(int time, int action, Book* p_book);

protected:
	string key;
};

class Student :public User
{
public:
	Student(string user_name, string key) :User(user_name, key, 'S') {}

	// �軹�����
	int borrowBook(Book* p_book, int time);
	int returnBook(Book* p_book, int time);
};

class Admin :public User
{
public:
	Admin(string user_name, string key) :User(user_name, key, 'A') {}

	// ����ͼ�����
	int addBook(Book* p_book, int time);
	int delBook(Book* p_book, int time);
	int modifBook(Book* p_book, char modif_item);

	// �����û�����
};

class Customer :public User
{
public:
	Customer(string user_name, string key) :User(user_name, key, 'C') {}
};