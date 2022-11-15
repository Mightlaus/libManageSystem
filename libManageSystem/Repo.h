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

	// 返回存放所有结果的***Book指针***的vector，如果没找到返回空列表
	vector<Book*> findBook_isbn(unsigned long long isbn);
	vector<Book*> findBook_caption(string caption);
	vector<Book*> findBook_author(string author);

};

