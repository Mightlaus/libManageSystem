#include "User.h"

//���飬�����ڷ���0�����ڵ������߷���-1���ɹ�����1
int Student::borrowBook(Book* p_book, int time)
{
	if(!p_book->exist) return 0;
	if (p_book->exist and p_book->borrowed) return -1;

	p_book->addHistory(time, -1, this);
	this->addHistory(time, -1, p_book);
	p_book->borrowed = 1;
	return 1;
	// todo ��borrow����ͳ��
}


// ���飬�����ڸ��鷵��0���ɹ�����1
int Student::returnBook(Book* p_book, int time)
{
	if (!p_book->exist) return 0;

	p_book->addHistory(time, 1, this);
	this->addHistory(time, -1, p_book);
	p_book->borrowed = 0;
	return 1;
}

int User::addHistory(int time, int action, Book* p_book)
{
	History this_history(time, action, p_book);
	histories.push_back(History(time, action, p_book));
	return 0;
}
