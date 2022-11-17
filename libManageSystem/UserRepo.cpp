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

vector<Student*> UserRepo::findStudent(string user_name)
{
	vector<Student*> result_vec;

	for (int i = 0; i < p_student_repo->size(); i++)
	{
		if (p_student_repo->at(i).user_name == user_name)
		{
			result_vec.push_back(&p_student_repo->at(i));
		}
	}
	return vector<Student*>(result_vec);
}

vector<Admin*> UserRepo::findAdmin(string user_name)
{
	vector<Admin*> result_vec;

	for (int i = 0; i < p_admin_repo->size(); i++)
	{
		if (p_admin_repo->at(i).user_name == user_name)
		{
			result_vec.push_back(&p_admin_repo->at(i));
		}
	}
	return vector<Admin*>(result_vec);
}

vector<Customer*> UserRepo::findCustomer(string user_name)
{
	vector<Customer*> result_vec;

	for (int i = 0; i < p_customer_repo->size(); i++)
	{
		if (p_customer_repo->at(i).user_name == user_name)
		{
			result_vec.push_back(&p_customer_repo->at(i));
		}
	}
	return vector<Customer*>(result_vec);
}
