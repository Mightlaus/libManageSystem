#include "io.h"
#include "Repo.h"
#include <windows.h>
#include <iomanip>
using namespace std;

SYSTEMTIME sys;
void showBooks(vector<Book*> book)
{
	cout << "搜索到" << book.size() << "个结果，以下是搜索结果第一页:" << endl;
	int index = 1;
	for (auto i : book)
	{
		cout << index << ". " << i->caption << " " << i->author << " " << i->publishing << " " << endl;

		if (index % 10 == 0)
		{
			cout << "输入n查看下一页，或输入b退出搜索结果查看" << endl;
			string show_choice;
			cin >> show_choice;
			if (show_choice == "b")
			{
				break;
			}
		}
		index++;
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
	if (account == "*")
	{
		system("cls");
		return;
	}
	while (libRepo.users.findAdmin(account).empty())
	{
		cout << "账号不存在，请重试！" << endl << "请输入您的管理员账号（默认账号为学号/教师编号，输入*以回到主菜单）" << endl;
		cin.ignore(20, '\n');
		cin >> account;
		if (account == "*")
		{
			system("cls");
			return;
		}
	}

	Admin* curruser = libRepo.users.findAdmin(account)[0];

	cout << "请输入您的密码（默认密码为123456，输入*以回到主菜单）" << endl;
	string password;
	cin >> password;
	if (password == "*")
	{
		system("cls");
		return;
	}
	while (!curruser->checkKey(password))
	{
		cout << "密码错误，请重试！" << endl << "请输入您的密码（默认密码为123456，输入*以回到主菜单）" << endl;
		cin.ignore(20, '\n');
		cin >> password;
		if (password == "*")
		{
			system("cls");
			return;
		}
	}

	system("cls");
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
					system("cls");
					cout << "更改密码成功！返回管理员模式" << endl;
					break;
				}
				else if (verify_password == "*")
				{
					system("cls");
					break;
				}
				else
				{
					cout << "密码错误！请再试一次（输入*以回到管理员模式）" << endl;
					cin.ignore(20, '\n');
				}
			}
		}

		//添加用户
		else if (option == "2")
		{
			cout << "请输入要添加的账号（学号/教师编号）：格式为“A（管理员账号）/S（用户账号）+账号”";
			string insert_account;
			cin >> insert_account;
			int insert_result = libRepo.users.addUser(insert_account[0], insert_account.substr(1));
			if (insert_result == 0)
			{
				system("cls");
				cout << "输入格式错误！返回管理员模式" << endl;
				cin.ignore(20, '\n');
			}
			else if (insert_result == -1)
			{
				system("cls");
				cout << "用户" << insert_account.substr(1) << "已存在！返回管理员模式" << endl;
				continue;
			}
			else if (insert_result == 1)
			{
				system("cls");
				cout << "添加账号" << insert_account.substr(1) << "成功！返回管理员模式" << endl;
			}
		}

		//删除用户
		else if (option == "3")
		{
			cout << "请输入要删除的账号（学号/教师编号）：";
			string del_account;
			cin >> del_account;
			auto result1 = libRepo.users.findAdmin(del_account);
			if (!result1.empty())
			{
				libRepo.users.delAdmin(result1[0]);
				system("cls");
				cout << "删除管理员账号" << del_account << "成功！返回管理员模式" << endl;
				continue;
			}
			auto result2 = libRepo.users.findStudent(del_account);
			if (!result2.empty())
			{
				libRepo.users.delStudent(result2[0]);
				system("cls");
				cout << "删除用户账号" << del_account << "成功！返回管理员模式" << endl;
				continue;
			}
			auto result3 = libRepo.users.findVisitor(del_account);
			if (!result3.empty())
			{
				libRepo.users.delVisitor(result3[0]);
				system("cls");
				cout << "删除游客账号" << del_account << "成功！返回管理员模式" << endl;
				continue;
			}
			system("cls");
			cout << "账号不存在！返回管理员模式" << endl;			
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
				system("cls");
				cout << "恢复管理员账号" << reset_account << "成功！返回管理员模式" << endl;
			}
			else if (!libRepo.users.findStudent(reset_account).empty())
			{
				libRepo.users.modifKey(libRepo.users.findStudent(reset_account)[0], "123456");
				system("cls");
				cout << "恢复学生账号" << reset_account << "成功！返回管理员模式" << endl;
			}
			else if (!libRepo.users.findVisitor(reset_account).empty())
			{
				libRepo.users.modifKey(libRepo.users.findVisitor(reset_account)[0], "123456");
				system("cls");
				cout << "恢复游客账号" << reset_account << "成功！返回管理员模式" << endl;
			}
			else
			{
				system("cls");
				cout << "账号不存在！返回管理员模式" << endl;
			}
		}

		//添加图书
		else if (option == "5")
		{
			cout << "请输入要增加的图书信息，格式：第一行为要增加的本数，之后每一行为一本书的书名，作者，isbn，出版社，出版时间，描述，页数，价格，中间用空格隔开" << endl;
			string str;
			cin >> str;
			int size = stoi(str);
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
			system("cls");
			cout << "添加图书成功！返回管理员模式" << endl;
		}

		//删除图书
		else if (option == "6")
		{
			cout << "请输入搜索类型，1为搜索书名，2为搜索作者，3为ISBN号，4为出版社，5为全局搜索" << endl;
			string search_type;
			cin >> search_type;
			if (search_type != "1" && search_type != "2" && search_type != "3" && search_type != "4" && search_type != "5")
			{
				system("cls");
				cout << "输入格式非法！返回管理员模式" << endl;
				cin.ignore(20, '\n');
				continue;
			}
			cout << "请输入要删除的图书信息：";
			string del_bookinfo;
			cin >> del_bookinfo;
			vector<Book*> result;
			if (search_type == "1")
			{
				result = specificSearch(curruser, 'C', del_bookinfo);
			}
			else if (search_type == "2")
			{
				result = specificSearch(curruser, 'A', del_bookinfo);
			}
			else if (search_type == "3")
			{
				result = specificSearch(curruser, 'I', del_bookinfo);
			}
			else if (search_type == "4")
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
				string str;
				cin >> str;
				if (str[0] > '0' && str[0] <= '9' && stoi(str) <= result.size())
				{
					int choice = stoi(str);
					curruser->delBook(result[choice - 1], 0);
					system("cls");
					cout << "删除图书《" << result[choice - 1]->caption << "》成功！" << endl;
				}
				else
				{
					system("cls");
					cout << "输入格式非法！返回管理员模式" << endl;
					cin.ignore(20, '\n');
					continue;
				}
			}
			else
			{
				system("cls");
				cout << "图书馆还没有这本书哦！返回管理员模式" << endl;
			}
		}

		//更改图书
		else if (option == "7")
		{
			cout << "请输入搜索类型，1为搜索书名，2为搜索作者，3为ISBN号，4为出版社，5为全局搜索" << endl;
			string search_type;
			cin >> search_type;
			if (search_type != "1" && search_type != "2" && search_type != "3" && search_type != "4" && search_type != "5")
			{
				system("cls");
				cout << "输入格式非法！返回管理员模式" << endl;
				cin.ignore(20, '\n');
				continue;
			}
			cout << "请输入要更改的图书信息：";
			string change_bookinfo;
			cin >> change_bookinfo;
			vector<Book*> result;
			if (search_type == "1")
			{
				result = specificSearch(curruser, 'C', change_bookinfo);
			}
			else if (search_type == "2")
			{
				result = specificSearch(curruser, 'A', change_bookinfo);
			}
			else if (search_type == "3")
			{
				result = specificSearch(curruser, 'I', change_bookinfo);
			}
			else if (search_type == "4")
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
				string str;
				cin >> str;
				int choice;
				if (str[0] > '0' && str[0] <= '9' && stoi(str) <= result.size())
				{
					choice = stoi(str);
				}
				else
				{
					system("cls");
					cout << "输入格式非法！返回管理员模式" << endl;
					cin.ignore(20, '\n');
					continue;
				}
				cout << "请输入要修改的种类和内容，格式：A（作者）/B（ISBN）/C（书名）/D（描述）/P（价格）+新的内容" << endl;
				string change_str;
				cin >> change_str;
				while (curruser->modifBook(result[choice - 1], change_str[0], change_str.substr(1)) == 0)
				{
					cout << "输入格式错误！请重试" << endl;
					cin.ignore(20, '\n');
					cin >> change_str;
				}
				system("cls");
				cout << "修改图书《" << result[choice - 1]->caption << "》信息成功！返回管理员模式" << endl;
			}
			else
			{
				system("cls");
				cout << "图书馆还没有这本书哦！返回管理员模式" << endl;
			}
		}

		//搜索图书
		else if (option == "8")
		{
			cout << "请输入搜索类型，1为搜索书名，2为搜索作者，3为ISBN号，4为出版社，5为全局搜索" << endl;
			string search_type;
			cin >> search_type;
			if (search_type != "1" && search_type != "2" && search_type != "3" && search_type != "4" && search_type != "5")
			{
				system("cls");
				cout << "输入格式非法！返回管理员模式" << endl;
				cin.ignore(20, '\n');
				continue;
			}
			cout << "请输入要搜索的图书信息：";
			string search_bookinfo;
			cin >> search_bookinfo;
			vector<Book*> result;
			if (search_type == "1")
			{
				result = specificSearch(curruser, 'C', search_bookinfo);
			}
			else if (search_type == "2")
			{
				result = specificSearch(curruser, 'A', search_bookinfo);
			}
			else if (search_type == "3")
			{
				result = specificSearch(curruser, 'I', search_bookinfo);
			}
			else if (search_type == "4")
			{
				result = specificSearch(curruser, 'P', search_bookinfo);
			}
			else
			{
				result = globalSearch(curruser, search_bookinfo);
			}

			if (!result.empty())
			{
				system("cls");
				showBooks(result);
				cout << "返回管理员模式" << endl;
			}
			else
			{
				system("cls");
				cout << "图书馆还没有这本书哦！返回管理员模式" << endl;
			}
		}

		//退出
		else if (option == "9")
		{
			system("cls");
			break;
		}
		else
		{
			cout << "输入格式非法，请重试！" << endl;
			cin.ignore(20, '\n');
		}
	}
}
void userfunc(Repo& libRepo)
{
	cout << "请输入您的用户账号（默认账号为学号/教师编号，输入*以回到主菜单）" << endl;
	string account;
	cin >> account;
	if (account == "*")
	{
		system("cls");
		return;
	}
	while (libRepo.users.findStudent(account).empty())
	{
		cout << "账号不存在，请重试！" << endl << "请输入您的用户账号（默认账号为学号/教师编号，输入*以回到主菜单）" << endl;
		cin.ignore(20, '\n');
		cin >> account;
		if (account == "*")
		{
			system("cls");
			return;
		}
	}

	Student* curruser = libRepo.users.findStudent(account)[0];

	cout << "请输入您的密码（默认密码为123456，输入*以回到主菜单）" << endl;
	string password;
	cin >> password;
	if (password == "*")
	{
		system("cls");
		return;
	}
	while (!curruser->checkKey(password))
	{
		cout << "密码错误，请重试！" << endl << "请输入您的密码（默认密码为123456，输入*以回到主菜单）" << endl;
		cin.ignore(20, '\n');
		cin >> password;
		if (password == "*")
		{
			system("cls");
			return;
		}
	}

	system("cls");
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
					system("cls");
					cout << "更改密码成功！返回用户模式" << endl;
					break;
				}
				else if (verify_password == "*")
				{
					system("cls");
					break;
				}
				else
				{
					cout << "密码错误！请再试一次（输入*以回到用户模式）" << endl;
					cin.ignore(20, '\n');
				}
			}
		}
		//借阅图书
		else if (option == "2")
		{
			cout << "请输入搜索类型，1为搜索书名，2为搜索作者，3为ISBN号，4为出版社，5为全局搜索" << endl;
			string search_type;
			cin >> search_type;
			if (search_type != "1" && search_type != "2" && search_type != "3" && search_type != "4" && search_type != "5")
			{
				system("cls");
				cout << "输入格式非法！返回用户模式" << endl;
				cin.ignore(20, '\n');
				continue;
			}
			cout << "请输入要借阅的图书信息：";
			string borrow_bookinfo;
			cin >> borrow_bookinfo;
			vector<Book*> result;
			if (search_type == "1")
			{
				result = specificSearch(curruser, 'C', borrow_bookinfo);
			}
			else if (search_type == "2")
			{
				result = specificSearch(curruser, 'A', borrow_bookinfo);
			}
			else if (search_type == "3")
			{
				result = specificSearch(curruser, 'I', borrow_bookinfo);
			}
			else if (search_type == "4")
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
				string str;
				cin >> str;
				if (str[0] > '0' && str[0] <= '9' && stoi(str) <= result.size())
				{
					int choice = stoi(str);
					GetLocalTime(&sys);
					long long time = sys.wYear * 10000000000 + sys.wMonth * 100000000 + sys.wDay * 1000000 + sys.wHour * 10000 + sys.wMinute * 100 + sys.wSecond;
					int borrow_result = curruser->borrowBook(result[choice - 1], time);
					if (borrow_result == 0)
					{
						system("cls");
						cout << "《" << result[choice - 1]->caption << "》已被管理员删除！返回用户模式" << endl;
					}
					else if (borrow_result == -1)
					{
						system("cls");
						cout << "《" << result[choice - 1]->caption << "》已经被借走啦！返回用户模式" << endl;
					}
					else
					{
						system("cls");
						cout << "借阅《" << result[choice - 1]->caption << "》成功！返回用户模式" << endl;
					}
				}
				else
				{
					system("cls");
					cout << "输入格式非法！返回用户模式" << endl;
					cin.ignore(20, '\n');
					continue;
				}
			}
			else
			{
				system("cls");
				cout << "图书馆还没有这本书哦！返回用户模式" << endl;
			}
		}

		//归还图书
		else if (option == "3")
		{
			vector<Book*> result = curruser->getBorrowing();
			if (result.empty())
			{
				cout << "您没有正在借阅的图书！返回用户模式" << endl;
			}
			else
			{
				cout << "您正在借阅的图书有" << result.size() << "本，以下是您已经借阅的图书：" << endl;
				int index = 1;
				for (auto x : result)
				{
					cout << index << '.' << x->caption << " " << x->author << " " << x->publishing << endl;
					if (index % 10 == 0)
					{
						cout << "输入n查看下一页，或输入b退出已借阅图书查看" << endl;
						string show_choice;
						cin >> show_choice;
						if (show_choice == "b")
						{
							break;
						}
					}
					index++;
				}
				cout << "请输入要归还的图书序号：";
				string str;
				cin >> str;
				if (str[0] > '0' && str[0] <= '9' && stoi(str) <= result.size())
				{
					int choice = stoi(str);
					GetLocalTime(&sys);
					long long time = sys.wYear * 10000000000 + sys.wMonth * 100000000 + sys.wDay * 1000000 + sys.wHour * 10000 + sys.wMinute * 100 + sys.wSecond;
					int return_result = curruser->returnBook(result[choice - 1], time);
					if (return_result == 0)
					{
						system("cls");
						cout << "《" << result[choice - 1]->caption << "》已被管理员删除！返回用户模式" << endl;
					}
					else
					{
						system("cls");
						cout << "归还《" << result[choice - 1]->caption << "》成功！返回用户模式" << endl;
					}
				}
				else
				{
					system("cls");
					cout << "输入格式非法！返回用户模式" << endl;
					cin.ignore(20, '\n');
					continue;
				}
			}
		}

		//搜索图书
		else if (option == "4")
		{
			cout << "请输入搜索类型，1为搜索书名，2为搜索作者，3为ISBN号，4为出版社，5为全局搜索" << endl;
			string search_type;
			cin >> search_type;
			if (search_type != "1" && search_type != "2" && search_type != "3" && search_type != "4" && search_type != "5")
			{
				system("cls");
				cout << "输入格式非法！返回用户模式" << endl;
				cin.ignore(20, '\n');
				continue;
			}
			cout << "请输入要搜索的图书信息：";
			string search_bookinfo;
			cin >> search_bookinfo;
			vector<Book*> result;
			if (search_type == "1")
			{
				result = specificSearch(curruser, 'C', search_bookinfo);
			}
			else if (search_type == "2")
			{
				result = specificSearch(curruser, 'A', search_bookinfo);
			}
			else if (search_type == "3")
			{
				result = specificSearch(curruser, 'I', search_bookinfo);
			}
			else if (search_type == "4")
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
				system("cls");
				cout << "图书馆还没有这本书哦！返回用户模式" << endl;
			}
		}

		//查询借阅记录
		else if (option == "5")
		{
			for (User::UserHistory i : curruser->histories)
			{
				string timestr = to_string(i.time);
				cout << timestr.substr(0, 4) << "/" << timestr.substr(4, 2) << "/" << timestr.substr(6, 2) << " " << setfill('0') << setw(2) << timestr.substr(8, 2) << ":" << setw(2) << timestr.substr(10, 2) << ":" << setw(2) << timestr.substr(12, 2);
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
			string search_type;
			cin >> search_type;
			if (search_type != "1" && search_type != "2" && search_type != "3" && search_type != "4" && search_type != "5")
			{
				system("cls");
				cout << "输入格式非法！返回用户模式" << endl;
				cin.ignore(20, '\n');
				continue;
			}
			cout << "请输入推荐基于的图书信息：";
			string reco_bookinfo;
			cin >> reco_bookinfo;
			vector<Book*> result;
			if (search_type == "1")
			{
				result = specificSearch(curruser, 'C', reco_bookinfo);
			}
			else if (search_type == "2")
			{
				result = specificSearch(curruser, 'A', reco_bookinfo);
			}
			else if (search_type == "3")
			{
				result = specificSearch(curruser, 'I', reco_bookinfo);
			}
			else if (search_type == "4")
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
				cout << "请输入要选择的图书序号：";
				string str;
				cin >> str;
				if (str[0] > '0' && str[0] <= '9' && stoi(str) <= result.size())
				{
					int choice = stoi(str);
					vector<Book*> reco_list = libRepo.books.recommend(result[choice - 1]);
					cout << "以下是推荐结果：" << endl;
					for (int i = 0; i < reco_list.size(); i++)
					{
						cout << i + 1 << ". " << reco_list[i]->caption << " " << reco_list[i]->author << " " << reco_list[i]->publishing << " " << endl;
					}
				}
				else
				{
					system("cls");
					cout << "输入格式非法！返回用户模式" << endl;
					cin.ignore(20, '\n');
					continue;
				}
			}
			else
			{
				system("cls");
				cout << "图书馆还没有这本书哦！返回用户模式" << endl;
			}
		}
		//退出
		else if (option == "7")
		{
			system("cls");
			break;
		}
		else
		{
			system("cls");
			cout << "输入格式非法，请重试！" << endl;
			cin.ignore(20, '\n');
		}
	}
}
void visitorfunc(Repo& libRepo)
{
	system("cls");
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
			string search_type;
			cin >> search_type;
			if (search_type != "1" && search_type != "2" && search_type != "3" && search_type != "4" && search_type != "5")
			{
				system("cls");
				cout << "输入格式非法！返回游客模式" << endl;
				cin.ignore(20, '\n');
				continue;
			}
			cout << "请输入要搜索的图书信息：";
			string search_bookinfo;
			cin >> search_bookinfo;
			vector<Book*> result;
			if (search_type == "1")
			{
				result = specificSearch(curruser, 'C', search_bookinfo);
			}
			else if (search_type == "2")
			{
				result = specificSearch(curruser, 'A', search_bookinfo);
			}
			else if (search_type == "3")
			{
				result = specificSearch(curruser, 'I', search_bookinfo);
			}
			else if (search_type == "4")
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
				system("cls");
				cout << "图书馆还没有这本书哦！返回游客模式" << endl;
			}
		}

		//推荐图书
		else if (option == "2")
		{
			cout << "请输入搜索类型，1为搜索书名，2为搜索作者，3为ISBN号，4为出版社，5为全局搜索" << endl;
			string search_type;
			cin >> search_type;
			if (search_type != "1" && search_type != "2" && search_type != "3" && search_type != "4" && search_type != "5")
			{
				system("cls");
				cout << "输入格式非法！返回游客模式" << endl;
				cin.ignore(20, '\n');
				continue;
			}
			cout << "请输入推荐基于的图书信息：";
			string reco_bookinfo;
			cin >> reco_bookinfo;
			vector<Book*> result;
			if (search_type == "1")
			{
				result = specificSearch(curruser, 'C', reco_bookinfo);
			}
			else if (search_type == "2")
			{
				result = specificSearch(curruser, 'A', reco_bookinfo);
			}
			else if (search_type == "3")
			{
				result = specificSearch(curruser, 'I', reco_bookinfo);
			}
			else if (search_type == "4")
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
				cout << "请输入要选择的图书序号：";
				string str;
				cin >> str;
				if (str[0] > '0' && str[0] <= '9' && stoi(str) <= result.size())
				{
					int choice = stoi(str);
					vector<Book*> reco_list = libRepo.books.recommend(result[choice - 1]);
					cout << "以下是为您推荐的图书：" << endl;
					for (int i = 0; i < reco_list.size(); i++)
					{
						cout << i + 1 << ". " << reco_list[i]->caption << " " << reco_list[i]->author << " " << reco_list[i]->publishing << " " << endl;
					}
				}
				else
				{
					system("cls");
					cout << "输入格式非法！返回游客模式" << endl;
					cin.ignore(20, '\n');
					continue;
				}
			}
			else
			{
				system("cls");
				cout << "图书馆还没有这本书哦！返回游客模式" << endl;
			}
		}
		else if (option == "3")
		{
			system("cls");
			break;
		}
		else
		{
			system("cls");
			cout << "输入格式非法，请重试！" << endl;
			cin.ignore(20, '\n');
		}
	}
}


int main()
{
	Repo libRepo;
	vector<string*> bookBatch = read_csv(2560);
	libRepo.books.addBatch(bookBatch, 2560);

	string str("居文涛");
	string key = "123456";
	libRepo.users.addUser('S', str, key);

	string str2("丁若谷");
	string key2 = "123456";
	libRepo.users.addUser('A', str2, key2);

	while (1)
	{
		cout << "欢迎来到图书馆管理系统！" << endl;
		GetLocalTime(&sys);
		cout << sys.wYear << "年" << sys.wMonth << "月" << sys.wDay << "日 " << setfill('0') << setw(2) << sys.wHour << ":" << setw(2) << sys.wMinute << ":" << setw(2) << sys.wSecond << " 星期" << sys.wDayOfWeek << endl;
		cout << "当前图书馆共有" << libRepo.books.bookNums << "本书，" << libRepo.users.userNums << "个用户" << endl << endl;
		cout << "********************主菜单********************" << endl << endl;
		cout << "1.管理员模式" << endl;
		cout << "2.用户模式" << endl;
		cout << "3.游客模式" << endl;
		cout << "4.借阅次数排行榜——图书" << endl;
		cout << "5.借阅次数排行榜——读者" << endl;
		cout << "6.最新出版图书" << endl;
		cout << "7.退出图书馆系统" << endl << endl;
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
			auto rank_list = libRepo.books.rankBook_borrowest(10);
			for (int i = 0; i < rank_list.size(); i++)
			{
				cout << i + 1 << ". " << rank_list[i]->caption << " " << rank_list[i]->author << " " << rank_list[i]->publishing << " 被借阅了" << rank_list[i]->borrowed_times << "次" << endl;
			}

			string buffer;
			cout << "\n按任意键返回主菜单...";
			getline(cin, buffer);
			cin.ignore(20, '\n');
			system("cls");
		}
		else if (option == "5")
		{
			auto rank_list = libRepo.users.rankUser_borrowest(10);
			for (int i = 0; i < rank_list.size(); i++)
			{
				cout << i + 1 << ". " << rank_list[i]->user_name << "\t借阅了" << rank_list[i]->borrowTimes << "次" << endl;
			}

			string buffer;
			cout << "\n按任意键返回主菜单...";
			getline(cin, buffer);
			cin.ignore(20, '\n');
			system("cls");
		}
		else if (option == "6")
		{
			auto rank_list = libRepo.books.rankBook_newest(10);
			for (int i = 0; i < rank_list.size(); i++)
			{
				cout << i + 1 << "." << rank_list[i]->published_time << "\t\t" << rank_list[i]->caption << " " << rank_list[i]->author << " " << rank_list[i]->publishing << " " << endl;
			}

			string buffer;
			cout << "\n按任意键返回主菜单...";
			getline(cin, buffer);
			cin.ignore(20, '\n');
			system("cls");
		}
		else if (option == "7")
		{
			break;
		}
		else
		{
			system("cls");
			cout << "输入格式非法，请重试！" << endl;
			cin.ignore(20, '\n');
		}
	}

	return 0;
}