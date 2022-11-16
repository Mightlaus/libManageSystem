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
		bookNums = 0;
	}

	
	int bookNums; // ����ͼ������

	//��
	void addOne(Book book);
	void addBatch(vector<string*> book_batch, int batch_size);

	//ɾ
	void delOne(Book* p_book);
	void delBatch(vector<Book*> book_vec);

	//��
	void modifCaption(Book* p_book, string caption);
	void modifAuthor(Book* p_book, string author);
	void modifIsbn(Book* p_book, unsigned long long isbn);
	void modifPrice(Book* p_book, int price);

	//��
	vector<Book*> find_isbn(unsigned long long isbn);
	vector<Book*> find_caption(string caption);
	vector<Book*> find_author(string author);
	vector<Book*> find_publish(string publish);

protected:
	vector<Book>* p_book_repo;
	
};

