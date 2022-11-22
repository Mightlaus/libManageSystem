#include "io.h"
#include "Book.h"
#include "Repo.h"
#include "User.h"
using namespace std;

void showBooks(vector<Book*> book)
{
	cout << "搜索到" << book.size() << "个结果，以下是搜索到的结果:" << endl;
	for (int i = 0; i < book.size(); i++)
	{
		cout << i + 1 << ". " << book[i]->caption << " " << book[i]->author << " " << book[i]->publishing << " " << endl;
	}
}
vector<Book*> globalSearch(User* curruser, string book_info)
{
	vector<Book*> search_result;
	for (Book* i : curruser->findBook_author(book_info))
	{
		search_result.push_back(i);
	}
	for (Book* i : curruser->findBook_caption(book_info))
	{
		search_result.push_back(i);
	}
	for (Book* i : curruser->findBook_isbn(book_info))
	{
		search_result.push_back(i);
	}
	for (Book* i : curruser->findBook_publish(book_info))
	{
		search_result.push_back(i);
	}
	return search_result;
}
vector<Book*> specificSearch(User* curruser, char type, string book_info)
{
	if (type == 'A') return curruser->findBook_author(book_info);
	if (type == 'C') return curruser->findBook_caption(book_info);
	if (type == 'I') return curruser->findBook_isbn(book_info);
	if (type == 'P') return curruser->findBook_publish(book_info);
}
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
				cout << "账号不存在！返回管理员模式" << endl;
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
			for (int i = 0; i < size; i++)
			{
				string book_info[6];
				for (int j = 0; j < 6; j++)
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
			cout << "请输入搜索类型，1为搜索书名，2为搜索作者，3为ISBN号，4为出版社，5为全局搜索" << endl;
			int search_type;
			cin >> search_type;
			if (search_type != 1 && search_type != 2 && search_type != 3 && search_type != 4 && search_type != 5)
			{
				cout << "输入格式非法！返回管理员模式" << endl;
				continue;
			}
			cout << "请输入要删除的图书信息：";
			string del_bookinfo;
			cin >> del_bookinfo;
			vector<Book*> result;
			if (search_type == 1)
			{
				result = specificSearch(curruser, 'C', del_bookinfo);
			}
			else if (search_type == 2)
			{
				result = specificSearch(curruser, 'A', del_bookinfo);
			}
			else if (search_type == 3)
			{
				result = specificSearch(curruser, 'I', del_bookinfo);
			}
			else if (search_type == 4)
			{
				result = specificSearch(curruser, 'P', del_bookinfo);
			}
			else
			{
				result = globalSearch(curruser, del_bookinfo);
			}

			if (!result.empty())
			{
				showBooks(result);
				cout << "请输入要删除的图书序号：";
				int choice;
				cin >> choice;
				if (choice > 0 && choice <= result.size())
				{
					curruser->delBook(result[choice - 1], 0);
					cout << "删除图书《" << result[choice - 1]->caption << "》成功！" << endl;
				}
				else
				{
					cout << "输入格式非法！返回管理员模式" << endl;
					continue;
				}
			}
			else
			{
				cout << "图书馆还没有这本书哦！返回管理员模式" << endl;
			}
		}

		//更改图书
		else if (option == "7")
		{
			cout << "请输入搜索类型，1为搜索书名，2为搜索作者，3为ISBN号，4为出版社，5为全局搜索" << endl;
			int search_type;
			cin >> search_type;
			if (search_type != 1 && search_type != 2 && search_type != 3 && search_type != 4 && search_type != 5)
			{
				cout << "输入格式非法！返回管理员模式" << endl;
				continue;
			}
			cout << "请输入要更改的图书信息：";
			string change_bookinfo;
			cin >> change_bookinfo;
			vector<Book*> result;
			if (search_type == 1)
			{
				result = specificSearch(curruser, 'C', change_bookinfo);
			}
			else if (search_type == 2)
			{
				result = specificSearch(curruser, 'A', change_bookinfo);
			}
			else if (search_type == 3)
			{
				result = specificSearch(curruser, 'I', change_bookinfo);
			}
			else if (search_type == 4)
			{
				result = specificSearch(curruser, 'P', change_bookinfo);
			}
			else
			{
				result = globalSearch(curruser, change_bookinfo);
			}

			if (!result.empty())
			{
				showBooks(result);
				cout << "请输入要修改的图书序号：";
				int choice;
				cin >> choice;
				if (choice <1 || choice > result.size())
				{
					cout << "输入格式非法！返回管理员模式" << endl;
					continue;
				}
				cout << "请输入要修改的种类和内容，格式：A（作者）/B（ISBN）/C（书名）/D（描述）/P（价格）+新的内容" << endl;
				string change_str;
				cin >> change_str;
				while (curruser->modifBook(result[choice - 1], change_str[0], change_str.substr(1)) == 0)
				{
					cout << "输入格式错误！请重试" << endl;
					cin >> change_str;
				}
				cout << "修改图书《" << result[choice - 1]->caption << "》信息成功！返回管理员模式" << endl;
			}
			else
			{
				cout << "图书馆还没有这本书哦！返回管理员模式" << endl;
			}
		}

		//搜索图书
		else if (option == "8")
		{
			cout << "请输入搜索类型，1为搜索书名，2为搜索作者，3为ISBN号，4为出版社，5为全局搜索" << endl;
			int search_type;
			cin >> search_type;
			if (search_type != 1 && search_type != 2 && search_type != 3 && search_type != 4 && search_type != 5)
			{
				cout << "输入格式非法！返回管理员模式" << endl;
				continue;
			}
			cout << "请输入要搜索的图书信息：";
			string search_bookinfo;
			cin >> search_bookinfo;
			vector<Book*> result;
			if (search_type == 1)
			{
				result = specificSearch(curruser, 'C', search_bookinfo);
			}
			else if (search_type == 2)
			{
				result = specificSearch(curruser, 'A', search_bookinfo);
			}
			else if (search_type == 3)
			{
				result = specificSearch(curruser, 'I', search_bookinfo);
			}
			else if (search_type == 4)
			{
				result = specificSearch(curruser, 'P', search_bookinfo);
			}
			else
			{
				result = globalSearch(curruser, search_bookinfo);
			}

			if (!result.empty())
			{
				showBooks(result);
				cout << "返回管理员模式" << endl;
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
		cout << "6.推荐图书" << endl;
		cout << "7.退出用户模式" << endl;
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
			cout << "请输入搜索类型，1为搜索书名，2为搜索作者，3为ISBN号，4为出版社，5为全局搜索" << endl;
			int search_type;
			cin >> search_type;
			if (search_type != 1 && search_type != 2 && search_type != 3 && search_type != 4 && search_type != 5)
			{
				cout << "输入格式非法！返回用户模式" << endl;
				continue;
			}
			cout << "请输入要借阅的图书信息：";
			string borrow_bookinfo;
			cin >> borrow_bookinfo;
			vector<Book*> result;
			if (search_type == 1)
			{
				result = specificSearch(curruser, 'C', borrow_bookinfo);
			}
			else if (search_type == 2)
			{
				result = specificSearch(curruser, 'A', borrow_bookinfo);
			}
			else if (search_type == 3)
			{
				result = specificSearch(curruser, 'I', borrow_bookinfo);
			}
			else if (search_type == 4)
			{
				result = specificSearch(curruser, 'P', borrow_bookinfo);
			}
			else
			{
				result = globalSearch(curruser, borrow_bookinfo);
			}

			if (!result.empty())
			{
				showBooks(result);
				cout << "请输入要借阅的图书序号：";
				int choice;
				cin >> choice;
				if (choice > 0 && choice <= result.size())
				{
					int borrow_result = curruser->borrowBook(result[choice - 1], 0);
					if (borrow_result == 0)
						cout << "《" << result[choice - 1]->caption << "》已被管理员删除！返回用户模式" << endl;
					else if (borrow_result == -1)
						cout << "《" << result[choice - 1]->caption << "》已经被借走啦！返回用户模式" << endl;
					else
						cout << "借阅《" << result[choice - 1]->caption << "》成功！返回用户模式" << endl;
				}
				else
				{
					cout << "输入格式非法！返回用户模式" << endl;
					continue;
				}
			}
			else
			{
				cout << "图书馆还没有这本书哦！返回用户模式" << endl;
			}
		}

		//归还图书
		else if (option == "3")
		{
			cout << "请输入搜索类型，1为搜索书名，2为搜索作者，3为ISBN号，4为出版社，5为全局搜索" << endl;
			int search_type;
			cin >> search_type;
			if (search_type != 1 && search_type != 2 && search_type != 3 && search_type != 4 && search_type != 5)
			{
				cout << "输入格式非法！返回用户模式" << endl;
				continue;
			}
			cout << "请输入要归还的图书信息：";
			string return_bookinfo;
			cin >> return_bookinfo;
			vector<Book*> result;
			if (search_type == 1)
			{
				result = specificSearch(curruser, 'C', return_bookinfo);
			}
			else if (search_type == 2)
			{
				result = specificSearch(curruser, 'A', return_bookinfo);
			}
			else if (search_type == 3)
			{
				result = specificSearch(curruser, 'I', return_bookinfo);
			}
			else if (search_type == 4)
			{
				result = specificSearch(curruser, 'P', return_bookinfo);
			}
			else
			{
				result = globalSearch(curruser, return_bookinfo);
			}

			if (!result.empty())
			{
				showBooks(result);
				cout << "请输入要借阅的图书序号：";
				int choice;
				cin >> choice;
				if (choice > 0 && choice <= result.size())
				{
					int return_result = curruser->returnBook(result[choice - 1], 0);
					if (return_result == 0)
						cout << "《" << result[choice - 1]->caption << "》已被管理员删除！返回用户模式" << endl;
					else
						cout << "归还《" << result[choice - 1]->caption << "》成功！返回用户模式" << endl;
				}
				else
				{
					cout << "输入格式非法！返回用户模式" << endl;
					continue;
				}


			}
			else
			{
				cout << "图书馆还没有这本书哦！返回用户模式" << endl;
			}
		}

		//搜索图书
		else if (option == "4")
		{
			cout << "请输入搜索类型，1为搜索书名，2为搜索作者，3为ISBN号，4为出版社，5为全局搜索" << endl;
			int search_type;
			cin >> search_type;
			if (search_type != 1 && search_type != 2 && search_type != 3 && search_type != 4 && search_type != 5)
			{
				cout << "输入格式非法！返回用户模式" << endl;
				continue;
			}
			cout << "请输入要搜索的图书信息：";
			string search_bookinfo;
			cin >> search_bookinfo;
			vector<Book*> result;
			if (search_type == 1)
			{
				result = specificSearch(curruser, 'C', search_bookinfo);
			}
			else if (search_type == 2)
			{
				result = specificSearch(curruser, 'A', search_bookinfo);
			}
			else if (search_type == 3)
			{
				result = specificSearch(curruser, 'I', search_bookinfo);
			}
			else if (search_type == 4)
			{
				result = specificSearch(curruser, 'P', search_bookinfo);
			}
			else
			{
				result = globalSearch(curruser, search_bookinfo);
			}

			if (!result.empty())
			{
				showBooks(result);
			}
			else
			{
				cout << "图书馆还没有这本书哦！返回用户模式" << endl;
			}
		}

		//查询借阅记录
		else if (option == "5")
		{
			for (User::UserHistory i : curruser->histories)
			{
				cout << i.time << " ";
				if (i.action == -1)
					cout << "借阅了 《";
				if (i.action == 1)
					cout << "归还了 《";
				if (i.action == 0)
					cout << "阅览了 《";
				cout << i.p_book->caption << "》" << endl;
			}
		}
		//推荐图书
		else if (option == "6")
		{
			cout << "请输入搜索类型，1为搜索书名，2为搜索作者，3为ISBN号，4为出版社，5为全局搜索" << endl;
			int search_type;
			cin >> search_type;
			if (search_type != 1 && search_type != 2 && search_type != 3 && search_type != 4 && search_type != 5)
			{
				cout << "输入格式非法！返回用户模式" << endl;
				continue;
			}
			cout << "请输入推荐基于的图书信息：";
			string reco_bookinfo;
			cin >> reco_bookinfo;
			vector<Book*> result;
			if (search_type == 1)
			{
				result = specificSearch(curruser, 'C', reco_bookinfo);
			}
			else if (search_type == 2)
			{
				result = specificSearch(curruser, 'A', reco_bookinfo);
			}
			else if (search_type == 3)
			{
				result = specificSearch(curruser, 'I', reco_bookinfo);
			}
			else if (search_type == 4)
			{
				result = specificSearch(curruser, 'P', reco_bookinfo);
			}
			else
			{
				result = globalSearch(curruser, reco_bookinfo);
			}

			if (!result.empty())
			{
				showBooks(result);
				cout << "请输入要推荐的图书序号：";
				int choice;
				cin >> choice;
				if (choice > 0 && choice <= result.size())
				{
					vector<Book*> reco_list = libRepo.books.recommend(result[choice - 1]);
					for (int i = 0; i < reco_list.size(); i++)
					{
						cout << i + 1 << ". " << reco_list[i]->caption << " " << reco_list[i]->author << " " << reco_list[i]->publishing << " " << endl;
					}
				}
				else
				{
					cout << "输入格式非法！返回用户模式" << endl;
					continue;
				}
			}
			else
			{
				cout << "图书馆还没有这本书哦！返回用户模式" << endl;
			}
		}
		//退出
		else if (option == "7")
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
		cout << "2.推荐图书" << endl;
		cout << "3.退出游客模式" << endl;
		cout << endl << "请输入您的选择：";
		string option;
		cin >> option;

		libRepo.users.addUser('V', "visitor583");
		Visitor* curruser = libRepo.users.findVisitor("visitor583")[0];
		//搜索图书
		if (option == "1")
		{
			cout << "请输入搜索类型，1为搜索书名，2为搜索作者，3为ISBN号，4为出版社，5为全局搜索" << endl;
			int search_type;
			cin >> search_type;
			if (search_type != 1 && search_type != 2 && search_type != 3 && search_type != 4 && search_type != 5)
			{
				cout << "输入格式非法！返回游客模式" << endl;
				continue;
			}
			cout << "请输入要搜索的图书信息：";
			string search_bookinfo;
			cin >> search_bookinfo;
			vector<Book*> result;
			if (search_type == 1)
			{
				result = specificSearch(curruser, 'C', search_bookinfo);
			}
			else if (search_type == 2)
			{
				result = specificSearch(curruser, 'A', search_bookinfo);
			}
			else if (search_type == 3)
			{
				result = specificSearch(curruser, 'I', search_bookinfo);
			}
			else if (search_type == 4)
			{
				result = specificSearch(curruser, 'P', search_bookinfo);
			}
			else
			{
				result = globalSearch(curruser, search_bookinfo);
			}

			if (!result.empty())
			{
				showBooks(result);
			}
			else
			{
				cout << "图书馆还没有这本书哦！返回游客模式" << endl;
			}
		}

		//推荐图书
		else if (option == "2")
		{
			cout << "请输入搜索类型，1为搜索书名，2为搜索作者，3为ISBN号，4为出版社，5为全局搜索" << endl;
			int search_type;
			cin >> search_type;
			if (search_type != 1 && search_type != 2 && search_type != 3 && search_type != 4 && search_type != 5)
			{
				cout << "输入格式非法！返回游客模式" << endl;
				continue;
			}
			cout << "请输入推荐基于的图书信息：";
			string reco_bookinfo;
			cin >> reco_bookinfo;
			vector<Book*> result;
			if (search_type == 1)
			{
				result = specificSearch(curruser, 'C', reco_bookinfo);
			}
			else if (search_type == 2)
			{
				result = specificSearch(curruser, 'A', reco_bookinfo);
			}
			else if (search_type == 3)
			{
				result = specificSearch(curruser, 'I', reco_bookinfo);
			}
			else if (search_type == 4)
			{
				result = specificSearch(curruser, 'P', reco_bookinfo);
			}
			else
			{
				result = globalSearch(curruser, reco_bookinfo);
			}

			if (!result.empty())
			{
				showBooks(result);
				cout << "请输入要推荐的图书序号：";
				int choice;
				cin >> choice;
				if (choice > 0 && choice <= result.size())
				{
					vector<Book*> reco_list=libRepo.books.recommend(result[choice - 1]);
					for (int i = 0; i < reco_list.size(); i++)
					{
						cout << i + 1 << ". " << reco_list[i]->caption << " " << reco_list[i]->author << " " << reco_list[i]->publishing << " " << endl;
					}
				}
				else
				{
					cout << "输入格式非法！返回游客模式" << endl;
					continue;
				}
			}
			else
			{
				cout << "图书馆还没有这本书哦！返回游客模式" << endl;
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

	string str2("丁若谷");
	string key2 = "123456";
	libRepo.users.addUser('A', str2, key2);


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