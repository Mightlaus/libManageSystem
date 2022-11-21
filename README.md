# libManageSystem

这里是图书馆项目

## 代码命名风格约定

- 普通成员变量：全小写+下划线(name)
- 常量：全大写(DATE)
- 函数名：小驼峰（getName）
- 类、结构体：大驼峰 (MyLibrary)



# 后端接口

后端为前端提供的接口主要分布于三个头文件中

- BookRepo.h
- UserRepo.h
- User.h

你可以通过浏览这三个文件中的public属性和方法来掌握调用方法。

BookRepo与UserRepo都隶属于Repo这个大类(Repo.h)中，而且都是Repo的对象(名为book, users)，所以你需要先实例化Repo这个类(假如名为repo)，然后通过**repo.books.(BookRepo的方法或属性)**来管理图书，或者**repo.users. (UserRepo的方法或属性)**来管理用户。

另外，用户（User）自身的方法包含了对图书的操作，如增删改查等。所以你如果已经拥有一个指向确定用户的指针(UserRepo的查找功能会提供)，那么就使用user里的方法来管理图书，这样的逻辑会更加合理。

下面会按类名详细介绍这些接口。

## User.h

这是一个包含所有用户类（User、Student、Admin、Visitor）的头文件。其中User是其他三个子类的父类，他们之间是继承关系。这里为前端提供了Student、Admin、Visitor的构造函数，我们不建议初始化父类User来使用，因为User类中的功能非常有限。

### class User

要初始化一个User对象，需要提供三个参数

```cpp
	User(string user_name, string key, char identity, BookRepo* p_book_repo) {
		this->user_name = user_name;
		this->key = key;
		this->identity = identity;
		this->p_book_repo = p_book_repo;
		exist = 1;
	}
```

其中，identity可以选择'S','A','V'分别代表了student admin visitor对象。最后一个p_book_repo需要提供一个指向图书库的指针以给予user操作图书的权限。

| 类属性                 | 描述                                     | 变量类型             |
| ---------------------- | ---------------------------------------- | -------------------- |
| identity               | 用户身份'S' 读者， 'A' 管理员， 'V' 游客 | char                 |
| exist                  | 用户是否存在，若已被删除为0              | int                  |
| user_name              | 用户名                                   | string               |
| histories              | 用户的图书借阅历史                       | vector\<UserHistory> |
| key（protected）       | 用户密码                                 | string               |
| p_book_repo(protected) | 指向图书库的指针                         | BookRepo*            |

> UserHistory是一个内置的结构体变量，它包括了借阅时间、借阅操作、借阅图书。值得注意的是借阅图书是一个指向库图书的指针变量，所以前端可以通过这个指针拓展出更多的功能lol。

```cpp
	struct UserHistory
	{
		int action; // -1借书， 1还书， 0阅览
		int time;
		Book* p_book;
		UserHistory(int time, int action, Book* p_book) :action(action), time(time), p_book(p_book) {}
	};
```

| 类方法                                              | 描述                                |
| --------------------------------------------------- | ----------------------------------- |
| bool checkKey(string input_key);                    | 检查输入的密码与自身key属性是否一致 |
| int resetKey(string new_key);                       | 重置用户密码为new_key               |
| vector<Book*> findBook_isbn(string isbn);           | 精准查找与isbn匹配的图书并返回      |
| vector<Book*> findBook_caption(string caption);     | 精准查找与书名匹配的图书并返回      |
| vector<Book*> findBook_author(string author);       | 模糊查找与作者匹配的图书并返回      |
| vector<Book*> findBook_publish(string publish);     | 模糊查找与出版商匹配的图书并返回    |
| int addHistory(int time, int action, Book* p_book); | 向histories属性里添加一条记录       |

> 搜索图书相关的算法实现将在BookRepo部分详细介绍

**虽然我们提供了User类与其子类的构造函数，但是前端并不需要通过这种方式来直接生成用户对象，对应的添加用户方法我们已经放在了用户库（UserRepo）中去实现**

正确的使用方法是已经拿到一个用户对象（或其指针）时，使用其方法去执行操作图书库等操作。

## class Student

**student是user的子类，它继承了所有user的属性与方法**

此外，student加入了独有的借还书操作

| 类方法                                  | 描述                                                  |
| --------------------------------------- | ----------------------------------------------------- |
| int borrowBook(Book* p_book, int time); | 借阅p_book这本书，并自动在histories中添加本次借阅记录 |
| int returnBook(Book* p_book, int time); | 归还p_book这本书，并自动在histories中添加本次归还记录 |

## class Admin

**Admin是user的子类，它继承了所有user的属性与方法**

Admin中

# 类说明

## class Book

- 属性

|       属性       | 描述                                                   | 变量类型                |
| :--------------: | ------------------------------------------------------ | ----------------------- |
|     caption      | 书名                                                   | string                  |
|      author      | 作者                                                   | string                  |
|       isbn       | isbn                                                   | unsigned long long      |
|    publishing    | 出版商                                                 | string                  |
|  published_time  | 出版时间                                               | string                  |
|      price       | 价格                                                   | int                     |
|   description    | 描述                                                   | string                  |
| borrow_histories | 存放该书借书的日志，由vector存储，vector里存放日志指针 | vector\<BorrowHistory\> |

- 方法

  |      方法名      | 描述         | 备注                                        |
  | :--------------: | ------------ | ------------------------------------------- |
  |  void resetxxxx  | 修改xxx属性  | string实参提供了重载函数可以接收char*型形参 |
  | addBorrowHistory | 添加借书日志 |                                             |
  |                  |              |                                             |
