#include "io.h"
#include "Book.h"
#include "Repo.h"
#include "User.h"
using namespace std;

void adminfunc(Repo& libRepo)
{
	cout << "请输入您的管理员账号（默认账号为学号/教师编号，输入*以回到主菜单）" << endl;
	string account;
	cin >> account;
	if (account == "*") return;
	while (libRepo.users.findAdmin(account).empty())
	{
		cout << "账号不存在，请重试！" << endl << "请输入您的管理员账号（默认账号为学号/教师编号，输入*以回到主菜单）" << endl;
		cin >> account;
		if (account == "*")	return;
	}

	Admin* curruser = libRepo.users.findAdmin(account)[0];

	cout << "请输入您的密码（默认密码为123456，输入*以回到主菜单）" << endl;
	string password;
	cin >> password;
	if (password == "*") return;
	while (!curruser->checkKey(password))
	{
		cout << "密码错误，请重试！" << endl << "请输入您的密码（默认密码为123456，输入*以回到主菜单）" << endl;
		cin >> password;
		if (password == "*") return;
	}


	cout << "欢迎您，管理员" << account << "！" << endl;
	while (1)
	{
		cout << "**************管理员模式**************" << endl;
		cout << "1.更改密码" << endl;
		cout << "2.添加用户" << endl;
		cout << "3.删除用户" << endl;
		cout << "4.恢复用户默认密码" << endl;
		cout << "5.增加图书" << endl;
		cout << "6.删除图书" << endl;
		cout << "7.修改图书信息" << endl;
		cout << "8.搜索图书" << endl;
		cout << "9.退出管理员模式" << endl;
		cout << endl << "请输入您的选择：";
		string option;
		cin >> option;

		//更改密码
		if (option == "1")
		{
			while (1)
			{
				cout << "请再次输入您的密码(输入*以回到管理员模式)：";
				string verify_password;
				cin >> verify_password;
				if (curruser->checkKey(verify_password))
				{
					cout << "请输入新的密码：";
					string new_key;
					cin >> new_key;
					curruser->resetKey(new_key);
					cout << "更改密码成功！返回管理员模式" << endl;
					break;
				}
				else if (verify_password == "*")
				{
					break;
				}
				else
				{
					cout << "密码错误！请再试一次（输入*以回到管理员模式）" << endl;
				}
			}
		}

		//添加用户
		else if (option == "2")
		{
			cout << "请输入要添加的账号（学号/教师编号）：格式为“A（管理员账号）/S（用户账号）+账号”";
			string insert_account;
			cin >> insert_account;
			if (libRepo.users.addUser(insert_account[0], insert_account.substr(1)) == 0)
			{
				cout << "输入格式错误！返回管理员模式" << endl;
			}
			else if (libRepo.users.addUser(insert_account[0], insert_account.substr(1)) == -1)
			{
				cout << "用户" << insert_account << "已存在！返回管理员模式" << endl;
				continue;
			}
			else if (libRepo.users.addUser(insert_account[0], insert_account.substr(1)) == 1)
			{
				cout << "添加账号" << insert_account << "成功！返回管理员模式" << endl;
			}
		}

		//删除用户
		else if (option == "3")
		{
			cout << "请输入要删除的账号（学号/教师编号）：";
			string del_account;
			cin >> del_account;
			if (libRepo.users.delAdmin(libRepo.users.findAdmin(del_account)[0]) || libRepo.users.delStudent(libRepo.users.findStudent(del_account)[0]) || libRepo.users.delVisitor(libRepo.users.findVisitor(del_account)[0]))
			{
				cout << "删除账号" << del_account << "成功！返回管理员模式" << endl;
			}
			else
			{
				cout << "此用户不存在！返回管理员模式" << endl;
			}
		}

		//恢复账号
		else if (option == "4")
		{
			cout << "请输入要恢复的账号（学号/教师编号）：";
			string reset_account;
			cin >> reset_account;
			if (!libRepo.users.findAdmin(reset_account).empty())
			{
				libRepo.users.modifKey(libRepo.users.findAdmin(reset_account)[0], "123456");
				cout << "恢复管理员账号" << reset_account << "成功！返回管理员模式" << endl;
			}
			else if (!libRepo.users.findStudent(reset_account).empty())
			{
				libRepo.users.modifKey(libRepo.users.findStudent(reset_account)[0], "123456");
				cout << "恢复学生账号" << reset_account << "成功！返回管理员模式" << endl;
			}
			else if (!libRepo.users.findVisitor(reset_account).empty())
			{
				libRepo.users.modifKey(libRepo.users.findVisitor(reset_account)[0], "123456");
				cout << "恢复游客账号" << reset_account << "成功！返回管理员模式" << endl;
			}
			else
			{
				cout << "账号不存在！返回管理员模式" << endl;
			}
		}

		//添加图书
		else if (option == "5")
		{
			cout << "请输入要增加的图书信息，格式：第一行为要增加的本数，之后每一行为一本书的书名，作者，isbn，出版社，出版时间，描述，页数，价格，中间用空格隔开" << endl;
			int size;
			cin >> size;
			for (int i=0;i<size;i++)
			{
				string book_info[6];
				for(int j=0;j<6;j++)
				{
					cin >> book_info[j];
				}
				int pagenum;
				cin >> pagenum;
				double price;
				cin >> price;
				Book book(book_info[0], book_info[1], book_info[2], book_info[3], book_info[4], book_info[5], pagenum, price);
				libRepo.books.addOne(book);
			}
			cout << "添加图书成功！返回管理员模式" << endl;
		}

		//删除图书
		else if (option == "6")
		{
			cout << "请输入要删除的图书信息：（可以为书名，作者，ISBN号，出版社）";
			string del_bookinfo;
			cin >> del_bookinfo;
			if (!curruser->findBook_author(del_bookinfo).empty())
			{
				curruser->delBook(curruser->findBook_author(del_bookinfo)[0], 0);
				cout << "删除图书成功！返回管理员模式" << endl;
			}
			else if (!curruser->findBook_caption(del_bookinfo).empty())
			{
				curruser->delBook(curruser->findBook_caption(del_bookinfo)[0], 0);
				cout << "删除图书成功！返回管理员模式" << endl;
			}
			else if (!curruser->findBook_isbn(del_bookinfo).empty())
			{
				curruser->delBook(curruser->findBook_isbn(del_bookinfo)[0], 0);
				cout << "删除图书成功！返回管理员模式" << endl;
			}
			else if (!curruser->findBook_publish(del_bookinfo).empty())
			{
				curruser->delBook(curruser->findBook_publish(del_bookinfo)[0], 0);
				cout << "删除图书成功！返回管理员模式" << endl;
			}
			else
			{
				cout << "不存在该本图书！返回管理员模式" << endl;
			}
		}

		//更改图书
		else if (option == "7")
		{
			cout << "请输入要更改的图书信息：（可以为书名，作者，ISBN号，出版社）";
			string change_bookinfo;
			cin >> change_bookinfo;
			if (!curruser->findBook_author(change_bookinfo).empty())
			{
				cout << "成功通过作者查找到这本书！请输入要修改的种类和内容，格式：A（作者）/B（ISBN）/C（书名）/D（描述）/P（价格）+新的内容" << endl;
				string change_str;
				cin >> change_str;
				curruser->modifBook(curruser->findBook_author(change_bookinfo)[0], change_str[0], change_str.substr(1));
			}
			else if (!curruser->findBook_caption(change_bookinfo).empty())
			{
				cout << "成功通过书名查找到这本书！请输入要修改的种类和内容，格式：A（作者）/B（ISBN）/C（书名）/D（描述）/P（价格）+新的内容" << endl;
				string change_str;
				cin >> change_str;
				curruser->modifBook(curruser->findBook_caption(change_bookinfo)[0], change_str[0], change_str.substr(1));
			}
			else if (!curruser->findBook_isbn(change_bookinfo).empty())
			{
				cout << "成功通过ISBN号查找到这本书！请输入要修改的种类和内容，格式：A（作者）/B（ISBN）/C（书名）/D（描述）/P（价格）+新的内容" << endl;
				string change_str;
				cin >> change_str;
				curruser->modifBook(curruser->findBook_isbn(change_bookinfo)[0], change_str[0], change_str.substr(1));
			}
			else if (!curruser->findBook_publish(change_bookinfo).empty())
			{
				cout << "成功通过出版社查找到这本书！请输入要修改的种类和内容，格式：A（作者）/B（ISBN）/C（书名）/D（描述）/P（价格）+新的内容" << endl;
				string change_str;
				cin >> change_str;
				curruser->modifBook(curruser->findBook_publish(change_bookinfo)[0], change_str[0], change_str.substr(1));
			}
			else
			{
				cout << "不存在该本图书！返回管理员模式" << endl;
			}
		}

		//搜索图书
		else if (option == "8")
		{
			cout << "请输入要搜索的图书信息：";
			string search_bookinfo;
			cin >> search_bookinfo;
			if (!curruser->findBook_author(search_bookinfo).empty())
			{
				cout << "成功通过作者查找到图书！返回管理员模式" << endl;
			}
			else if (!curruser->findBook_caption(search_bookinfo).empty())
			{
				cout << "成功通过书名查找到图书！返回管理员模式" << endl;
			}
			else if (!curruser->findBook_isbn(search_bookinfo).empty())
			{
				cout << "成功通过ISBN号查找到图书！返回管理员模式" << endl;
			}
			else if (!curruser->findBook_publish(search_bookinfo).empty())
			{
				cout << "成功通过出版社查找到图书！返回管理员模式" << endl;
			}
			else
			{
				cout << "图书馆还没有这本书哦！返回管理员模式" << endl;
			}
		}

		//退出
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
void userfunc(Repo& libRepo)
{
	cout << "请输入您的用户账号（默认账号为学号/教师编号，输入*以回到主菜单）" << endl;
	string account;
	cin >> account;
	if (account == "*") return;
	while (libRepo.users.findStudent(account).empty())
	{
		cout << "账号不存在，请重试！" << endl << "请输入您的用户账号（默认账号为学号/教师编号，输入*以回到主菜单）" << endl;
		cin >> account;
		if (account == "*")	return;
	}

	Student* curruser = libRepo.users.findStudent(account)[0];

	cout << "请输入您的密码（默认密码为123456，输入*以回到主菜单）" << endl;
	string password;
	cin >> password;
	if (password == "*") return;
	while (!curruser->checkKey(password))
	{
		cout << "密码错误，请重试！" << endl << "请输入您的密码（默认密码为123456，输入*以回到主菜单）" << endl;
		cin >> password;
		if (password == "*") return;
	}


	cout << "欢迎您，用户" << account << "！" << endl;
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

		//更改密码
		if (option == "1")
		{
			while (1)
			{
				cout << "请再次输入您的密码(输入*以回到用户模式)：";
				string verify_password;
				cin >> verify_password;
				if (curruser->checkKey(verify_password))
				{
					cout << "请输入新的密码：";
					string new_key;
					cin >> new_key;
					curruser->resetKey(new_key);
					cout << "更改密码成功！返回用户模式" << endl;
					break;
				}
				else if (verify_password == "*")
				{
					break;
				}
				else
				{
					cout << "密码错误！请再试一次（输入*以回到用户模式）" << endl;
				}
			}
		}

		//借阅图书
		else if (option == "2")
		{
			cout << "请输入要借阅的图书信息：";
			string borrow;
			cin >> borrow;
		}

		//归还图书
		else if (option == "3")
		{
			cout << "请输入要归还的图书信息：";
			string return_book;
			cin >> return_book;
		}

		//搜索图书
		else if (option == "4")
		{
			cout << "请输入要搜索的图书信息：";
			string search;
			cin >> search;
		}

		//查询借阅记录
		else if (option == "5")
		{
			//直接cout借阅记录
		}

		//退出
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
void visitorfunc(Repo& libRepo)
{
	cout << "欢迎您，游客！" << endl;
	while (1)
	{
		cout << "**************游客模式**************" << endl;
		cout << "1.搜索图书" << endl;
		cout << "2.退出游客模式" << endl;
		cout << endl << "请输入您的选择：";
		string option;
		cin >> option;

		//搜索图书
		if (option == "1")
		{
			cout << "请输入要搜索的图书信息：";
			string search;
			cin >> search;
		}

		//退出
		else if (option == "2")
		{
			break;
		}


		else
		{
			cout << "输入格式非法，请重试！" << endl;
		}
	}
}
int main()
{
	//测试类 begins
	Repo libRepo;
	vector<string*> bookBatch = read_csv();
	libRepo.books.addBatch(bookBatch, 880);
	string str("居文涛");
	string key = "123456";
	libRepo.users.addUser('S', str, key);


	//测试类 ends

	while (1)
	{
		cout << "********************主菜单********************" << endl << endl;
		cout << "1.管理员模式" << endl;
		cout << "2.用户模式" << endl;
		cout << "3.游客模式" << endl;
		cout << "4.退出图书馆系统" << endl << endl;
		cout << endl << "请输入您的选择：";
		string option;
		cin >> option;
		if (option == "1")
		{
			adminfunc(libRepo);
		}
		else if (option == "2")
		{
			userfunc(libRepo);
		}
		else if (option == "3")
		{
			visitorfunc(libRepo);
		}
		else if (option == "4")
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