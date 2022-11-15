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
	vector<Book*> findBook_isbn(unsigned long long isbn);
	vector<Book*> findBook_caption(string caption);
	vector<Book*> findBook_author(string author);

};

