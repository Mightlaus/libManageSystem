#include "UserRepo.h"

int UserRepo::addUser(char identity, string user_name, string key)
{

	if (identity == 'A')
	{
		if (!findAdmin(user_name).empty())
		{
			return -1;
		}
		Admin admin(user_name, key, p_book_repo);
		p_admin_repo->push_back(admin);
		adminNums++;
		return 1;
	}
	else if (identity == 'S')
	{
		if (!findStudent(user_name).empty())
		{
			return -1;
		}
		Student student(user_name, key, p_book_repo);
		p_student_repo->push_back(student);
		studentNums++;
		return 1;
	}
	else if (identity == 'V')
	{
		if (!findVisitor(user_name).empty())
		{
			return -1;
		}
		Visitor visitor(user_name, key, p_book_repo);
		p_visitor_repo->push_back(visitor);
		visitorNums++;
		return 1;
	}

	return 0;
}

int UserRepo::delAdmin(Admin* p_admin)
{
	if (p_admin->exist == 0)
	{
		return 0;
	}
	else
	{
		p_admin->exist = 0;
		adminNums--;
		return 1;
	}
}

int UserRepo::delStudent(Student* p_student)
{
	if (p_student->exist == 0)
	{
		return 0;
	}
	else
	{
		p_student->exist = 0;
		studentNums--;
		return 1;
	}
}

int UserRepo::delVisitor(Visitor* p_visitor)
{
	if (p_visitor->exist == 0)
	{
		return 0;
	}
	else
	{
		p_visitor->exist = 0;
		visitorNums--;
		return 1;
	}
	return 0;
}

int UserRepo::modifKey(Student* p_stu, string new_key)
{
	p_stu->resetKey(new_key);
	return 1;
}

int UserRepo::modifKey(Admin* p_admin, string new_key)
{
	p_admin->resetKey(new_key);
	return 1;
}

int UserRepo::modifKey(Visitor* p_cust, string new_key)
{
	p_cust->resetKey(new_key);
	return 1;
}


vector<Student*> UserRepo::findStudent(string user_name)
{
	vector<Student*> result_vec;

	for (int i = 0; i < p_student_repo->size(); i++)
	{
		if (p_student_repo->at(i).user_name == user_name and p_student_repo->at(i).exist)
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
		if (p_admin_repo->at(i).user_name == user_name and p_admin_repo->at(i).exist)
		{
			result_vec.push_back(&p_admin_repo->at(i));
		}
	}
	return vector<Admin*>(result_vec);
}

vector<Visitor*> UserRepo::findVisitor(string user_name)
{
	vector<Visitor*> result_vec;

	for (int i = 0; i < p_visitor_repo->size(); i++)
	{
		if (p_visitor_repo->at(i).user_name == user_name and p_visitor_repo->at(i).exist)
		{
			result_vec.push_back(&p_visitor_repo->at(i));
		}
	}
	return vector<Visitor*>(result_vec);
}
