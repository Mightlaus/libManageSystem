#pragma once
#include <vector>
#include "User.h"

class UserRepo
{
public:
	UserRepo(BookRepo* p_book_repo) {
		this->p_book_repo = p_book_repo;
		int userNums = 0;
		int adminNums=0;
		int studentNums=0;
		int customerNums=0;
	}

	int userNums;
	int adminNums;
	int studentNums;
	int customerNums;

	//增user identity:'S'->student, 'A'->admin, 'C'->customer; 如果用户已存在，返回-1，identity类型错误返回0，成功返回1
	int addUser(char identity, string user_name, string key);

	//删user 如果用户不存在(exist=0)返回0， 成功返回1；
	int delAdmin(Admin* p_admin);
	int delStudent(Student* p_student);
	int delCustomer(Customer* p_customer);

	//改(密码) 修改成功返回1，暂没考虑不成功情况
	int modifKey(Student* p_stu, string new_key);
	int modifKey(Admin* p_admin, string new_key);
	int modifKey(Customer* p_cust, string new_key);

	//查user 按姓名查找，返回查找到所有结果的vector， 未找到返回空vector
	vector<Student*> findStudent(string user_name);
	vector<Admin*> findAdmin(string user_name);
	vector<Customer*> findCustomer(string user_name);
	
protected:
	BookRepo* p_book_repo;
	vector<Admin>* p_admin_repo = new vector<Admin>;
	vector<Student>* p_student_repo = new vector<Student>;
	vector<Customer>* p_customer_repo = new vector<Customer>;
};

