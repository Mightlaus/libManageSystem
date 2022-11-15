#include "Repo.h"
#include <algorithm>

void bookSort(vector<Book*> &bookRepo)
{
	int size = bookRepo.size();
	for (int i = 0; i < size-1; i++)
	{
		for (int j = 0; j < size-1-i; j++)
		{
			if (bookRepo[j]->caption>bookRepo[j+1]->caption)
			{
				swap(bookRepo[j], bookRepo[j + 1]);
			}
		}
	}
}

void Repo::addBook(Book book)
{
	p_book_repo->push_back(book);
}

void Repo::addBookBatch(vector<string*> book_batch, int batch_size)
{

	for (int i = 0; i < batch_size; i++)
	{
		string caption = *(book_batch[i] + 2);
		string author = * (book_batch[i] + 3);
		unsigned long long isbn = stoll( * (book_batch[i] + 1));
		string publishing = *(book_batch[i] + 4);
		string published_time = *(book_batch[i] + 5);
		string description = *(book_batch[i] + 8);;
		int price = stoi( * (book_batch[i] + 6));

		Book thisBook(caption, author, isbn, publishing, published_time, price, description);
		addBook(thisBook);
	}

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

	bookSort(find_result_vec);
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

	bookSort(find_result_vec);
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

	bookSort(find_result_vec);
	return vector<Book*>(find_result_vec);
}
