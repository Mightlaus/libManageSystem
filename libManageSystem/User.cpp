#include "User.h"

//借书，不存在返回0，存在但被借走返回-1，成功返回1
int Student::borrowBook(Book* p_book, int time)
{
	if(!p_book->exist) return 0;
	if (p_book->exist and p_book->borrowed) return -1;

	p_book->addHistory(time, -1, this);
	this->addHistory(time, -1, p_book);
	p_book->borrowed = 1;
	return 1;
	// todo 加borrow数量统计
}


// 还书，不存在该书返回0，成功返回1
int Student::returnBook(Book* p_book, int time)
{
	if (!p_book->exist) return 0;

	p_book->addHistory(time, 1, this);
	this->addHistory(time, -1, p_book);
	p_book->borrowed = 0;
	return 1;
}

vector<Book*> User::findBook_isbn(string isbn)
{
	return vector<Book*>(p_books->find_isbn(isbn));
}

vector<Book*> User::findBook_caption(string caption)
{
	return vector<Book*>(p_books->find_caption(caption));
}

vector<Book*> User::findBook_author(string author)
{
	return vector<Book*>(p_books->find_author(author));
}

vector<Book*> User::findBook_publish(string publish)
{
	return vector<Book*>(p_books->find_publish(publish));
}

int User::addHistory(int time, int action, Book* p_book)
{
	UserHistory this_history(time, action, p_book);
	histories.push_back(UserHistory(time, action, p_book));
	return 0;
}
 
int Admin::addBook(Book book, int time)
{
	p_books->addOne(book);
	return 1;
}
