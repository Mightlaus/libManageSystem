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
		int action; // -1���飬 1���飬 0����
		int time;
		Book* p_book;
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
	void resetKey(string new_key); 

	// ����ͼ��
	vector<Book*> findBook_isbn(unsigned long long isbn);
	vector<Book*> findBook_caption(string caption);
	vector<Book*> findBook_author(string author);
	vector<Book*> findBook_publish(string publish);

	// ͼ��䶯��¼
	void addHistory(int action, int time, Book* p_book); 

protected:
	string key;
};

class Student :public User
{
	Student(string user_name, string key) :User(user_name, key, 'S') {}

	// �軹�����
	void borrowBook(Book* p_book, int time);
	void returnBook(Book* p_book, int time);
};

class Admin :public User
{
	Admin(string user_name, string key) :User(user_name, key, 'A') {}

	// ����ͼ�����
	void addBook(Book* p_book, int time);
	void delBook(Book* p_book, int time);
	void modifBook(Book* p_book, char modif_item);

	// �����û�����
};

class Customer :public User
{
	Customer(string user_name, string key) :User(user_name, key, 'C') {}
};