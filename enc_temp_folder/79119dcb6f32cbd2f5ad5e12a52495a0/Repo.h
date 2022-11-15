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
	void addBookBatch(vector<string*>, int batch_size);

	// ͼ����ҹ��ܣ����ش�����н����***Bookָ��***��vector�����û�ҵ����ؿ��б�
	vector<Book*> findBook_isbn(unsigned long long isbn);
	vector<Book*> findBook_caption(string caption);
	vector<Book*> findBook_author(string author);
	vector<Book*> findBook_publish(string publish);

	// ͼ�����а��ܣ��������а�ͼ��
	vector<Book*> rankBook_newest(int rank_len);
	void testTime(string str);

};

