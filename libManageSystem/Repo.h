#pragma once
#include "BookRepo.h"
#include "UserRepo.h"
using namespace std;

class Repo
{
private:

	

public:
	BookRepo books = BookRepo();// ͼ�����ع���
	UserRepo users = UserRepo(&books); //user��ع���
	

};

