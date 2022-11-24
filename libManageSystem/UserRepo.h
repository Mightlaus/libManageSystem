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

	int userNums; // �����û�����
	int adminNums;
	int studentNums;
	int visitorNums;

	//��user identity:'S'->student, 'A'->admin, 'V'->visitor; ����û��Ѵ��ڣ�����-1��identity���ʹ��󷵻�0���ɹ�����1
	int addUser(char identity, string user_name, string key="123456", int exist=1);

	//ɾuser ����û�������(exist=0)����0�� �ɹ�����1��
	int delAdmin(Admin* p_admin);
	int delStudent(Student* p_student);
	int delVisitor(Visitor* p_visitor);

	//��(����) �޸ĳɹ�����1����û���ǲ��ɹ����
	int modifKey(Student* p_stu, string new_key);
	int modifKey(Admin* p_admin, string new_key);
	int modifKey(Visitor* p_cust, string new_key);

	//��user ���������ң����ز��ҵ����н����vector�� δ�ҵ����ؿ�vector
	vector<Student*> findStudent(string user_name, int precise=0);
	vector<Admin*> findAdmin(string user_name, int precise = 0);
	vector<Visitor*> findVisitor(string user_name, int precise = 0);

	vector<Student*> rankUser_borrowest(int rank_len); //��Student�����ҵ�����ͼ���������ѧ��������
	
	BookRepo* p_book_repo;
	vector<Admin>* p_admin_repo;
	vector<Student>* p_student_repo;
	vector<Visitor>* p_visitor_repo;
};

