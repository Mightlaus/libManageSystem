#pragma once
#include <vector>
#include <string>
#include "Book.h"

class BookRepo
{
public:
	BookRepo()
	{
		bookNums = 0;
	}

	
	int bookNums; // 库内图书总数

	//增
	void addOne(Book book); //向书库中增加一本书
	void addBatch(vector<string*> book_batch, int batch_size); //通过文件读写的方式向书库中批量增加书

	//删
	void delOne(Book* p_book); //删除书库中的一本书（属性exist置为0）
	void delBatch(vector<Book*> book_vec); //批量删除传入列表中的全部书

	//改
	void modifCaption(Book* p_book, string caption); //修改书名
	void modifAuthor(Book* p_book, string author); //修改作者
	void modifIsbn(Book* p_book, string isbn); //修改ISBN
	void modifPrice(Book* p_book, double price); //修改价格

	//查
	vector<Book*> find_isbn(string isbn); //根据ISBN精准查找，找到的书的指针放在vector中返回，没有找到返回空vector，下同
	vector<Book*> find_caption(string caption);
	vector<Book*> find_author(string author); //按作者名模糊查找
	vector<Book*> find_publish(string publish);//按出版社名模糊查找

	vector<Book*> rankBook_newest(int rank_len); //在书库中找到最新出版的rank_len本书并返回


protected:
	vector<Book>* p_book_repo = new vector<Book>; //书库
	
};

