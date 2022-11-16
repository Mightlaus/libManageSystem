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
	BookRepo books = BookRepo();// 图书库相关功能

	// 图书排行榜功能：返回排行榜图书
	vector<Book*> rankBook_newest(int rank_len);

};

