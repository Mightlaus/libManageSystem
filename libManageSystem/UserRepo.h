#pragma once
#include <vector>
#include "User.h"

class UserRepo
{
public:
	UserRepo(vector<User>* p_user_repo) {
		this->p_user_repo = p_user_repo;
		int userNums = 0;
	}

	int userNums;

	//��
	

protected:
	vector<User>* p_user_repo;
};

