#pragma once

#include <vector>
#include <string>
#include "Book.h"
#include "BookRepo.h"


using namespace std;

class Repo
{
private:
	vector<Book>* p_book_repo = new vector<Book>;

public:
	BookRepo books = BookRepo(p_book_repo);// ͼ�����ع���

	// ͼ�����а��ܣ��������а�ͼ��
	vector<Book*> rankBook_newest(int rank_len);

};

