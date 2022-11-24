#include "User.h"

//借书，不存在返回0，存在但被借走返回-1，成功返回1
int Student::borrowBook(Book* p_book, int time)
{
	if(!p_book->exist) return 0;
	if (p_book->exist and p_book->borrowed) return -1;

	p_book->addHistory(time, -1, this);
	this->addHistory(time, -1, p_book);
	this->borrowTimes++;
	p_book->borrowed = 1;
	return 1;
	// todo 加borrow数量统计
}


// 还书，不存在该书返回0，成功返回1
int Student::returnBook(Book* p_book, int time)
{
	if (!p_book->exist) return 0;

	p_book->addHistory(time, 1, this);
	this->addHistory(time, 1, p_book);
	p_book->borrowed = 0;
	return 1;
}

vector<Book*> Student::getBorrowing()
{
	vector<Book*> result;

	for (int i = 0; i < this->histories.size(); i++)
	{	
		int borrowTimes = 0;
		int returnTimes = 0;

		// 已经存在不重复添加
		if (find(result.begin(), result.end(), histories[i].p_book) != result.end())
		{
			continue;
		}

		//统计借阅次数与归还次数
		for (int j = 0; j < this->histories.size(); j++)
		{
			if (this->histories[j].p_book == this->histories[i].p_book)
			{
				if (this->histories[j].action == -1)
				{
					borrowTimes++;
				}
				else if (this->histories[j].action == 1)
				{
					returnTimes++;
				}
			}
		}

		if (borrowTimes > returnTimes)
		{
			result.push_back(this->histories[i].p_book);
		}
	}

	return vector<Book*>(result);
}

bool User::checkKey(string input_key)
{
	if (input_key == this->key)
	{
		return true;
	}
	return false;
}

int User::resetKey(string new_key)
{
	this->key = new_key;
	return 1;
}

vector<Book*> User::findBook_isbn(string isbn)
{
	return vector<Book*>(p_book_repo->find_isbn(isbn));
}

vector<Book*> User::findBook_caption(string caption)
{
	return vector<Book*>(p_book_repo->find_caption(caption));
}

vector<Book*> User::findBook_author(string author)
{
	return vector<Book*>(p_book_repo->find_author(author));
}

vector<Book*> User::findBook_publish(string publish)
{
	return vector<Book*>(p_book_repo->find_publish(publish));
}

int User::addHistory(int time, int action, Book* p_book)
{
	UserHistory this_history(time, action, p_book);
	histories.push_back(UserHistory(time, action, p_book));
	return 0;
}
 
int Admin::addBook(Book book, int time)
{
	p_book_repo->addOne(book);
	return 1;
}

int Admin::delBook(Book* p_book, int time)
{
	p_book_repo->delOne(p_book);
	return 1;
}

int Admin::modifBook(Book* p_book, char modif_item, string new_content)
{
	if (modif_item == 'C')
	{
		p_book->resetCaption(new_content);
		return 1;
	}
	else if (modif_item == 'A')
	{
		p_book->resetAuthor(new_content);
		return 1;
	}
	else if (modif_item=='I')
	{
		p_book->resetIsbn(new_content);
		return 1;
	}
	else if (modif_item == 'D')
	{
		p_book->resetDescription(new_content);
		return 1;
	}

	return 0;
}

int Admin::modifBook(Book* p_book, char modif_item, double new_price)
{
	if (modif_item == 'P')
	{
		p_book->resetPrice(new_price);
		return 1;
	}
	else
	{
		return 0;
	}

}
