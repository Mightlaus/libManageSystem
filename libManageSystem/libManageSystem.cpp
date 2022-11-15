#include "Book.h"
int main()
{
	string name = "str";
	Book mybook("ap", "au", 998, "5waf", "2002-1", 10);
	mybook.resetAuthor("haha");
	mybook.addBorrowHistory(1, "okk");
}