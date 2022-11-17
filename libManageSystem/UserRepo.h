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

	//��user identity:'S'->student, 'A'->admin, 'C'->customer; ����û��Ѵ��ڣ�����-1��identity���ʹ��󷵻�0���ɹ�����1
	int addUser(char identity, string user_name, string key);

	//ɾuser ����û�������(exist=0)����0�� �ɹ�����1��
	int delAdmin(Admin* p_admin);
	int delStudent(Student* p_student);
	int delCustomer(Customer* p_customer);

	//��(����) �޸ĳɹ�����1����û���ǲ��ɹ����
	int modifKey(Student* p_stu, string new_key);
	int modifKey(Admin* p_admin, string new_key);
	int modifKey(Customer* p_cust, string new_key);

	//��user ���������ң����ز��ҵ����н����vector�� δ�ҵ����ؿ�vector
	vector<Student*> findStudent(string user_name);
	vector<Admin*> findAdmin(string user_name);
	vector<Customer*> findCustomer(string user_name);
	
protected:
	BookRepo* p_book_repo;
	vector<Admin>* p_admin_repo = new vector<Admin>;
	vector<Student>* p_student_repo = new vector<Student>;
	vector<Customer>* p_customer_repo = new vector<Customer>;
};

