#pragma once
#include "Book.h"
#include "BookRepo.h"

using namespace std;


class User
{
public:
	struct UserHistory
	{
		int action; // -1���飬 1���飬 0����
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

	char identity; // �û���� 'S' ���ߣ� 'A' ����Ա�� 'V' �ο�
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

	// �軹�����
	int borrowBook(Book* p_book, long long time);
	int returnBook(Book* p_book, long long time);
	// ����������ڽ軹δ�黹��ͼ��
	vector<Book*> getBorrowing();
};

class Admin :public User
{
public:
	Admin(string user_name, string key, BookRepo* p_book_repo) :User(user_name, key, 'A', p_book_repo) {}

	// ����ͼ�����
	int addBook(Book book, long long time);
	int delBook(Book* p_book, long long time);
	int modifBook(Book* p_book, char modif_item, string new_content); // ��price��pages�����������
};

class Visitor :public User
{
public:
	Visitor(string user_name, string key, BookRepo* p_book_repo) :User(user_name, key, 'V', p_book_repo) {}
};