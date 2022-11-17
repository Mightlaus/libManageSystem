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

	
	int bookNums; // ����ͼ������

	//��
	void addOne(Book book); //�����������һ����
	void addBatch(vector<string*> book_batch, int batch_size); //ͨ���ļ���д�ķ�ʽ�����������������

	//ɾ
	void delOne(Book* p_book); //ɾ������е�һ���飨����exist��Ϊ0��
	void delBatch(vector<Book*> book_vec); //����ɾ�������б��е�ȫ����

	//��
	void modifCaption(Book* p_book, string caption); //�޸�����
	void modifAuthor(Book* p_book, string author); //�޸�����
	void modifIsbn(Book* p_book, string isbn); //�޸�ISBN
	void modifPrice(Book* p_book, double price); //�޸ļ۸�

	//��
	vector<Book*> find_isbn(string isbn); //����ISBN��׼���ң��ҵ������ָ�����vector�з��أ�û���ҵ����ؿ�vector����ͬ
	vector<Book*> find_caption(string caption);
	vector<Book*> find_author(string author); //��������ģ������
	vector<Book*> find_publish(string publish);//����������ģ������

	vector<Book*> rankBook_newest(int rank_len); //��������ҵ����³����rank_len���鲢����


protected:
	vector<Book>* p_book_repo = new vector<Book>; //���
	
};

