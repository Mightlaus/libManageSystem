#pragma once

#include <vector>
#include <string>
#include "Book.h"


using namespace std;

class Repo
{
private:
	vector<Book>* p_book_repo = new vector<Book>;

public:
	void addBook(Book book);

	// ���ش�����н����***Bookָ��***��vector�����û�ҵ����ؿ��б�
	vector<Book*> findBook(unsigned long long isbn);

};

