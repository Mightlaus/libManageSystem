#pragma once

#include <vector>
#include <string>
#include "Book.h"
#include "BookRepo.h"
#include "User.h"
#include "UserRepo.h"

using namespace std;

class Repo
{
private:

	

public:
	BookRepo books = BookRepo();// ͼ�����ع���
	UserRepo users = UserRepo(&books); //user��ع���
	

	// ͼ�����а��ܣ��������а�ͼ��
	vector<Book*> rankBook_newest(int rank_len);

};

