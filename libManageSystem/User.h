#pragma once
#include <string>
#include <vector>
#include "Book.h"
#include "BookRepo.h"

using namespace std;


class User
{
public:
	struct UserHistory
	{
		int action; // -1���飬 1���飬 0����
		int time;
		Book* p_book;
		UserHistory(int time, int action, Book* p_book) :action(action), time(time), p_book(p_book) {}
	};
	User(string user_name, string key, char identity, BookRepo* p_book_repo) {
		this->user_name = user_name;
		this->key = key;
		this->identity = identity;
		this->p_book_repo = p_book_repo;
		exist = 1;
	}

	char identity; // �û���� 'S' ���ߣ� 'A' ����Ա�� 'C' �ο�
	int exist;
	string user_name;
	vector<UserHistory> histories;

	// �������
	bool checkKey(string input_key);
	int resetKey(string new_key);

	// ����ͼ�� author��publish�ṩģ�����ҹ��ܣ�isbn��caption��׼����
	vector<Book*> findBook_isbn(string isbn);
	vector<Book*> findBook_caption(string caption);
	vector<Book*> findBook_author(string author);
	vector<Book*> findBook_publish(string publish);

	// ͼ��䶯��¼
	int addHistory(int time, int action, Book* p_book);

protected:
	string key;
	BookRepo* p_book_repo;
};

class Student :public User
{
public:
	Student(string user_name, string key, BookRepo* p_book_repo) :User(user_name, key, 'S', p_book_repo) {}

	// �軹�����
	int borrowBook(Book* p_book, int time);
	int returnBook(Book* p_book, int time);
};

class Admin :public User
{
public:
	Admin(string user_name, string key, BookRepo* p_book_repo) :User(user_name, key, 'A', p_book_repo) {}

	// ����ͼ�����
	int addBook(Book book, int time);
	int delBook(Book* p_book, int time);
	int modifBook(Book* p_book, char modif_item, string new_content); // ��price�����������
	int modifBook(Book* p_book, char modif_tiem, double new_price); // price����

	// �����û�����
};

class Customer :public User
{
public:
	Customer(string user_name, string key, BookRepo* p_book_repo) :User(user_name, key, 'C', p_book_repo) {}
};