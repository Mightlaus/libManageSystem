﻿#include "read_data.h"
#include "Book.h"
#include "Repo.h"
#include "User.h"


int main()
{
	//测试类 begins
	auto repo = Repo();
	input_output io;
	vector<string*> bookBatch = io.read_csv();
	repo.addBookBatch(bookBatch, 47);
	string a[1] = { "nhjuhbb" };
	
	io.write_csv(1,1,a);
	//string auStr = "Author";
	//////auto vec = repo.findBook_author(auStr);
	//vec[0]->resetAuthor("AHAHA");

	vector<string*> bookBatch = read_csv();
	repo.books.addBatch(bookBatch, 30);

	string str = "出版社";
	auto vec = repo.books.find_publish(str);
	repo.books.delBatch(vec);

	string name = "Lihua";
	string key = "1241";
	repo.users.addUser('A', name, key);
	auto admin = repo.users.p_admin_repo->at(0);
	Book book(name, name, name, name, name, 1, name);
	admin.addBook(book, 0);

	//测试类 ends

	cout << "********************菜单********************" << endl;
	cout << "1.管理员模式" << endl;
	cout << "2.用户模式" << endl;
	cout << "3.退出" << endl;
	while (1)
	{
		cout << "请输入您的选择：";
		string option;
		cin >> option;
		if (option == "1")
		{
			cout << "请输入您的管理员账号和密码（默认账号为学号/教师编号，默认密码为123456）："
				<< endl << "账号：";
			string account;
			cin >> account;
			cout << "密码：";
			string password;
			cin >> password;


			cout << "欢迎您！管理员" << account << endl;
		}
		else if (option == "2")
		{
			cout << "请输入您的用户账号和密码（默认账号为学号/教师编号，默认密码为123456）："
				<< endl << "账号：";
			string account;
			cin >> account;
			cout << "密码：";
			string password;
			cin >> password;


			cout << "欢迎您！用户" << account << endl;
		}
		else if (option == "3")
		{
			return 0;
		}
		else
		{
			cout << "输入格式非法，请重试！" << endl;
		}
	}

	return 0;
}