#pragma once
#include "BookRepo.h"
#include "UserRepo.h"
using namespace std;

class Repo
{
private:

	

public:
	BookRepo books = BookRepo();// 图书库相关功能
	UserRepo users = UserRepo(&books); //user相关功能
	

};

