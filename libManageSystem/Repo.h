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

};

