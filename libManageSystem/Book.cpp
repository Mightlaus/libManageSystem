#include "Book.h"

void Book::resetCaption(string new_caption)
{
	caption = new_caption;
}

void Book::resetCaption(char* new_caption)
{
	string n_caption(new_caption);
	caption = n_caption;
}

void Book::resetAuthor(string new_author)
{
	author = new_author;
}

void Book::resetAuthor(char* new_author)
{
	string n_author(new_author);
	author = n_author;

}

void Book::resetIsbn(unsigned long long new_isbn)
{
	isbn = new_isbn;
}

void Book::resetPrice(int price)
{
	this->price = price;
}

void Book::addBorrowHistory(int borrow_time, string user_name)
{
	auto borrowHistory = new BorrowHistory(borrow_time, user_name);
	borrow_histories.push_back(borrowHistory);
	borrowed_times++;
}


