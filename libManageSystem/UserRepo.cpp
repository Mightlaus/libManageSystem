#include "UserRepo.h"

int UserRepo::addUser(char identity, string user_name, string key)
{

	if (identity == 'A')
	{
		Admin admin(user_name, key, p_books);
		p_admin_repo->push_back(admin);
		adminNums++;
		return 1;
	}
	else if (identity == 'S')
	{
		Student student(user_name, key, p_books);
		p_student_repo->push_back(student);
		studentNums++;
		return 1;
	}
	else if (identity == 'C')
	{
		Customer customer(user_name, key, p_books);
		p_customer_repo->push_back(customer);
		customerNums++;
		return 1;
	}

	return 0;
}
