#pragma once
#include <vector>
#include <string>
#include "Book.h"

class BookRepo
{
public:
	BookRepo(vector<Book>* p_book_repo)
	{
		this->p_book_repo = p_book_repo;
	}

	void addOne(Book book);
	void addBatch(vector<string*>, int batch_size);

	vector<Book*> find_isbn(unsigned long long isbn);
	vector<Book*> find_caption(string caption);
	vector<Book*> find_author(string author);
	vector<Book*> find_publish(string publish);

private:
	vector<Book>* p_book_repo;
	
};

