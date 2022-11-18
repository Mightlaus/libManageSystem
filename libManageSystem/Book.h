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
		int action; // -1�裬 0������1��
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

	// ����
	int exist; // �Ƿ񻹴��ڣ�û�б�ɾ����
	int borrowed; // �Ƿ񱻽���
	string caption;
	string author;
	string isbn;
	string publishing;
	string published_time;
	string description;
	int pages;
	double price;
	int borrowed_times;


	vector<BookHistory> histories; // �����ŵ��ǽṹ��ָ��,����Ҳ�൱���ǽ��Ĵ���

	//����
	void resetCaption(string new_caption);
	void resetCaption(char* new_caption);

	void resetAuthor(string new_author);
	void resetAuthor(char* new_author);

	void resetIsbn(string new_isbn);

	void resetDescription(string new_description);

	void resetPrice(double price);

	void addHistory(int time, int action, User* p_user);

};

