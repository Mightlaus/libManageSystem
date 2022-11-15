#include "read_data.h"
#include "Book.h"
#include "Repo.h"


int main()
{
	//测试类 begins
	auto repo = Repo();

	for (int i = 0; i < 20; i++)
	{
		auto mybook = Book("Caption", "Author", i, "Pub", "1989-10", 0, "description");
		repo.addBook(mybook);

	}

	auto vec = repo.findBook(10);
	//测试类 ends

	cout << "********************菜单********************" << endl;
	cout << "1.管理员模式" << endl;
	cout << "2.用户模式" << endl;
	cout << "3.退出" << endl;
	read_csv();
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