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

	

public:
	BookRepo books = BookRepo();// ͼ�����ع���

	// ͼ�����а��ܣ��������а�ͼ��
	vector<Book*> rankBook_newest(int rank_len);

};

