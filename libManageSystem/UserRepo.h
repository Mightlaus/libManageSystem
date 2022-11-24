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
		int visitorNums=0;
		p_admin_repo = new vector<Admin>;
		p_student_repo = new vector<Student>;
		p_visitor_repo = new vector<Visitor>;
	}

	int userNums; // 所有用户总数
	int adminNums;
	int studentNums;
	int visitorNums;

	//增user identity:'S'->student, 'A'->admin, 'V'->visitor; 如果用户已存在，返回-1，identity类型错误返回0，成功返回1
	int addUser(char identity, string user_name, string key="123456", int exist=1);

	//删user 如果用户不存在(exist=0)返回0， 成功返回1；
	int delAdmin(Admin* p_admin);
	int delStudent(Student* p_student);
	int delVisitor(Visitor* p_visitor);

	//改(密码) 修改成功返回1，暂没考虑不成功情况
	int modifKey(Student* p_stu, string new_key);
	int modifKey(Admin* p_admin, string new_key);
	int modifKey(Visitor* p_cust, string new_key);

	//查user 按姓名查找，返回查找到所有结果的vector， 未找到返回空vector
	vector<Student*> findStudent(string user_name, int precise=0);
	vector<Admin*> findAdmin(string user_name, int precise = 0);
	vector<Visitor*> findVisitor(string user_name, int precise = 0);

	vector<Student*> rankUser_borrowest(int rank_len); //在Student库中找到借阅图书次数最多的学生并返回
	
	BookRepo* p_book_repo;
	vector<Admin>* p_admin_repo;
	vector<Student>* p_student_repo;
	vector<Visitor>* p_visitor_repo;
};

