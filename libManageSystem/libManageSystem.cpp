#include "io.h"
#include "Book.h"
#include "Repo.h"
#include "User.h"


int main()
{
	//测试类 begins
	Repo libRepo;
	vector<string*> bookBatch = read_csv();
	libRepo.books.addBatch(bookBatch, 880);  //181 failed, 140 desctiption goes wrong
	string str("出版社");
	auto cap_vec = libRepo.books.find_publish(str);
	auto rank = libRepo.books.rankBook_newest(20);
	libRepo.users.addUser('A', str, str);
	Admin admin = libRepo.users.p_admin_repo->at(0);
	Book book(str, str, str, str, str, 0.1, str);
	admin.addBook(book, 0);
	auto found = admin.findBook_publish(str);
	
	//测试类 ends


	while (1)
	{
		cout << "********************菜单********************" << endl << endl;
		cout << "1.管理员模式" << endl;
		cout << "2.用户模式" << endl;
		cout << "3.退出图书馆系统" << endl << endl;
		cout << endl << "请输入您的选择：";
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

			//判断密码
			cout << "欢迎您！管理员" << account << endl;
			while (1)
			{
				cout << "**************管理员模式**************" << endl;
				cout << "1.更改密码" << endl;
				cout << "2.添加学校用户" << endl;
				cout << "3.删除学校用户" << endl;
				cout << "4.恢复学校用户默认密码" << endl;
				cout << "5.增加图书" << endl;
				cout << "6.删除图书" << endl;
				cout << "7.修改图书信息" << endl;
				cout << "8.搜索图书" << endl;
				cout << "9.退出管理员模式" << endl;
				cout << endl << "请输入您的选择：";
				string option;
				cin >> option;


				if (option == "1")
				{
					cout << "请再次输入您的密码：";
					string verify_password;
					cin >> verify_password;
					
				}
				else if (option=="2")
				{
					cout << "请输入要添加的账号（学号/教师编号）：";
					string insert_account;
					cin >> insert_account;
				}
				else if(option=="3")
				{
					cout << "请输入要删除的账号（学号/教师编号）：";
					string del_account;
					cin >> del_account;
				}
				else if (option == "4")
				{
					cout << "请输入要恢复的账号（学号/教师编号）：";
					string reset_account;
					cin >> reset_account;
				}
				else if (option == "5")
				{
					cout << "请输入要增加的图书信息：";
					string reset_account;
					cin >> reset_account;
				}
				else if (option == "6")
				{
					cout << "请输入要删除的图书信息：";
					string reset_account;
					cin >> reset_account;
				}
				else if (option == "7")
				{
					cout << "请输入要更改的图书信息：";
					string reset_account;
					cin >> reset_account;
				}
				else if (option == "8")
				{
					cout << "请输入要搜索的图书信息：";
					string reset_account;
					cin >> reset_account;
				}
				else if (option == "9")
				{
					break;
				}
				else
				{
					cout << "输入格式非法，请重试！" << endl;
				}
			}
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

			//判断密码
			cout << "欢迎您！用户" << account << endl;
			while (1)
			{
				cout << "**************用户模式**************" << endl;
				cout << "1.更改密码" << endl;
				cout << "2.借阅图书" << endl;
				cout << "3.归还图书" << endl;
				cout << "4.搜索图书" << endl;
				cout << "5.查看借阅记录" << endl;
				cout << "6.退出用户模式" << endl;
				cout << endl << "请输入您的选择：";
				string option;
				cin >> option;

				if (option == "1")
				{
					cout << "请输入您的密码：";
					string verify_password;
					cin >> verify_password;
					//verify
				}
				else if (option == "2")
				{
					cout << "请输入要借阅的图书信息：";
					string borrow;
					cin >> borrow;
				}
				else if (option == "3")
				{
					cout << "请输入要归还的图书信息：";
					string return_book;
					cin >> return_book;
				}
				else if (option == "4")
				{
					cout << "请输入要搜索的图书信息：";
					string search;
					cin >> search;
				}
				else if (option == "5")
				{
					//直接cout借阅记录
				}
				else if (option == "6")
				{
					break;
				}
				else
				{
					cout << "输入格式非法，请重试！" << endl;
				}
			}
		}


		else if (option == "3")
		{
			break;
		}


		else
		{
			cout << "输入格式非法，请重试！" << endl;
		}
	}

	return 0;
}