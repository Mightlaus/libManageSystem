#include "UserRepo.h"
#include <windows.h>

// 按student借阅次数降序排列
void studentSort_borrowest(vector<Student*>& studentRepo, int len)
{
	int size = studentRepo.size();
	for (int i = 0; i < len; i++)
	{
		for (int j = size - 1; j > i; j--)
		{
			if (studentRepo[j]->histories.size() > studentRepo[j - 1]->histories.size())
			{
				swap(studentRepo[j], studentRepo[j - 1]);
			}
		}
	}
}

// string -> wstring
extern wstring str2wstr(string str);
// 模糊匹配字符串
extern bool sparseMatch(string str1, string str2);

int UserRepo::addUser(char identity, string user_name, string key, int exist)
{

	if (identity == 'A')
	{
		if (!findAdmin(user_name).empty())
		{
			return -1;
		}
		Admin admin(user_name, key, p_book_repo);
		admin.exist = exist;
		p_admin_repo->push_back(admin);
		userNums++;
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
		student.exist = exist;
		p_student_repo->push_back(student);
		userNums++;
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
		userNums++;
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
		userNums--;
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
		userNums--;
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
		userNums--;
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
		if (sparseMatch(p_student_repo->at(i).user_name, user_name) and p_student_repo->at(i).exist)
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
		if (sparseMatch(p_admin_repo->at(i).user_name, user_name) and p_admin_repo->at(i).exist)
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
		if (sparseMatch(p_visitor_repo->at(i).user_name, user_name) and p_visitor_repo->at(i).exist)
		{
			result_vec.push_back(&p_visitor_repo->at(i));
		}
	}
	return vector<Visitor*>(result_vec);
}

vector<Student*> UserRepo::rankUser_borrowest(int rank_len)
{
	vector<Student*> rank_vec; //全部student的排序
	vector<Student*> result_vec; // 要取的rank

	for (auto& student : *p_student_repo)
	{
		if (student.exist)
		{
			rank_vec.push_back(&student);
		}

	}

	if (rank_len > rank_vec.size())
	{
		rank_len = rank_vec.size();
	}

	studentSort_borrowest(rank_vec, rank_len);

	for (int i = 0; i < rank_len; i++)
	{
		result_vec.push_back(rank_vec[i]);
	}

	return vector<Student*>(result_vec);
}

