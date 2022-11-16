#pragma once

#include <vector>
#include <string>
#include "Book.h"
#include "BookRepo.h"
#include "User.h"

using namespace std;

class Repo
{
private:
	//vector<Book>* p_book_repo = new vector<Book>;
	vector<User>* p_user_repo = new vector<User>;

public:
	BookRepo books = BookRepo();// ͼ�����ع���

	// ͼ�����а��ܣ��������а�ͼ��
	vector<Book*> rankBook_newest(int rank_len);

};

