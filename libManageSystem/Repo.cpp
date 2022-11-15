#include "Repo.h"

void Repo::addBook(Book book)
{
	p_book_repo->push_back(book);
}

vector<Book*> Repo::findBook_isbn(unsigned long long isbn)
{
	vector<Book*> find_result_vec;

	for (int i = 0; i < p_book_repo->size(); i++)
	{
		if (p_book_repo->at(i).isbn == isbn)
		{
			find_result_vec.push_back(&(p_book_repo->at(i)));
		}
	}

	return vector<Book*>(find_result_vec);
}

vector<Book*> Repo::findBook_caption(string caption)
{
	vector<Book*> find_result_vec;

	for (int i = 0; i < p_book_repo->size(); i++)
	{
		if (p_book_repo->at(i).caption == caption)
		{
			find_result_vec.push_back(&(p_book_repo->at(i)));
		}
	}

	return vector<Book*>(find_result_vec);
}

vector<Book*> Repo::findBook_author(string author)
{
	vector<Book*> find_result_vec;

	for (int i = 0; i < p_book_repo->size(); i++)
	{
		if (p_book_repo->at(i).author == author)
		{
			find_result_vec.push_back(&(p_book_repo->at(i)));
		}
	}

	return vector<Book*>(find_result_vec);
}
