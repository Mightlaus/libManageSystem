#pragma once
#include <string>
#include <vector>
#include "User.h"
using namespace std;

class User;

class Book
{
private:
	struct History
	{
		int time;
		int action; // -1�裬 0������1��
		User* user;

		History(int time, int action, User* user)
			:time(time), action(action), user(user) {}
	};


public:
	Book(string caption, string author, unsigned long long isbn, string publishing, string published_time, int price, string description)
		:caption(caption),
		author(author),
		isbn(isbn),
		publishing(publishing),
		published_time(published_time),
		price(price),
		description(description),
		borrowed_times(0),
		exist(1),
		borrowed(0) {}

	Book(char* caption, char* author, unsigned long long isbn, char* publishing, char* published_time, int price, char* description)
		:author(author),
		isbn(isbn),
		price(price),
		borrowed_times(0),
		exist(1),
		borrowed(0)
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

	// ����
	int exist; // �Ƿ񻹴��ڣ�û�б�ɾ����
	int borrowed; // �Ƿ񱻽���
	string caption;
	string author;
	unsigned long long isbn;
	string publishing;
	string published_time;
	string description;
	int price;
	int borrowed_times;


	vector<History> histories; // �����ŵ��ǽṹ��ָ��,����Ҳ�൱���ǽ��Ĵ���

	//����
	void resetCaption(string
		_caption);
	void resetCaption(char* new_caption);

	void resetAuthor(string new_author);
	void resetAuthor(char* new_author);

	void resetIsbn(unsigned long long new_isbn);

	void resetPrice(int price);

	void addHistory(int time, int action, User* p_user);

};

