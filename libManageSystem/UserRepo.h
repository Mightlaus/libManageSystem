#pragma once
#include <vector>
#include "User.h"

class UserRepo
{
public:
	UserRepo(BookRepo* p_books) {
		this->p_books = p_books;
		int userNums = 0;
		int adminNums=0;
		int studentNums=0;
		int customerNums=0;
	}

	int userNums;
	int adminNums;
	int studentNums;
	int customerNums;

	//增user
	int addUser(char identity, string user_name, string key);

	//删user
	int delUser(string user_name, string key);

	//改(密码)
	int modifKey(Student* p_stu, string new_key);
	int modifKey(Admin* p_admin, string new_key);
	int modifKey(Customer* p_cust, string new_key);

	//查user
	vector<Student*> findStudent(string user_name);
	vector<Admin*> findAdmin(string user_name);
	vector<Customer*> findCustomer(string user_name);
	
//改为protected
public:
	BookRepo* p_books;
	vector<Admin>* p_admin_repo = new vector<Admin>;
	vector<Student>* p_student_repo = new vector<Student>;
	vector<Customer>* p_customer_repo = new vector<Customer>;
};

