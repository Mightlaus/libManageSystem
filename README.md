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

- ### class User

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
		long long time;
		Book* p_book;
		UserHistory(long long time, int action, Book* p_book) :action(action), time(time), p_book(p_book) {}
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

- ### class Student

**student是user的子类，它继承了所有user的属性与方法**

此外，student加入了独有的借还书操作

| 类方法                                        | 描述                                                  |
| --------------------------------------------- | ----------------------------------------------------- |
| int borrowBook(Book* p_book, long long time); | 借阅p_book这本书，并自动在histories中添加本次借阅记录 |
| int returnBook(Book* p_book, long long time); | 归还p_book这本书，并自动在histories中添加本次归还记录 |
| vector<Book*> getBorrowing();                 | 返回所有该用户正在借的书                              |

| 类属性      | 描述             | 变量类型 |
| ----------- | ---------------- | -------- |
| borrowTimes | 用户类计借书次数 | int      |

所以，当你要使用借还书操作时，选择Student用户准没错！

- ### class Admin

**Admin是user的子类，它继承了所有user的属性与方法**

Admin负责图书馆的管理，所以对于图书的增删改查的方法都被赋予了Admin类

| 类方法                                                       | 描述                                   |
| ------------------------------------------------------------ | -------------------------------------- |
| int addBook(Book book, long long time);                      | 增加一本图书                           |
| int delBook(Book* p_book, long long time);                   | 删除图书                               |
| int modifBook(Book* p_book, char modif_item, string new_content); | 修改图书信息（书名、isbn、作者、描述） |
| int modifBook(Book* p_book, char modif_tiem, double new_price); | 修改图书信息（价格）                   |

> 添加和删除图书时都需要提供一个记录当前的时间参数time，这便于添加历史记录。
>
> 增删改操作的返回值是int，一般而言如果该功能执行成功返回1，出错返回0，其他情况请看方法声明中的批注信息。
>
> 修改图书信息的函数有两个重载，与string相关的都可以使用上表中的第一个方法，修改价格（int）单独一个重载。不过在使用它时大可不必如此复杂，你只需要添加对应的**modif_item**就修改后的新内容就可以很方便地使用啦。modif_item和图书信息的对应关系如下：
>
> | modif_item | 图书信息         |
> | ---------- | ---------------- |
> | 'C'        | Caption 书名     |
> | 'A'        | Author 作者      |
> | 'I'        | ISBN             |
> | 'D'        | Description 描述 |
> | 'P'        | Price 价格       |

- ### class Visitor

**Visitor是user的子类，它继承了所有user的属性与方法**

这就够了，visitor不需要太多的权限。他只需要能够找找书就够啦！

## UserRepo.h

类如其名，这个类的作用就是**存放所有的用户**和**操作用户**。所以，你可以在这里面找到对用户的增删改查操作。

注意！在实际使用它时，它已经在Repo中被初始化为了一个对象，名为users。所以正确的使用方法是：(repo对象).users.(它的方法)

因为user类一共有三个子类（Student, Admin, Visitor），因此我们需要不同的容器去存放他们，和不同的方法去修改他们。所以你可以看到很多相似的属性和方法，分类调用就可以啦。

| 类方法                                                       | 描述                                                   |
| ------------------------------------------------------------ | ------------------------------------------------------ |
| int addUser(char identity, string user_name, string key="123456"); | 添加用户，需要声明用户类型（identity）默认密码为123456 |
| int delAdmin(Admin* p_admin);                                | 删除管理员用户                                         |
| int delStudent(Student* p_student);                          | 删除读者用户                                           |
| int delVisitor(Visitor* p_visitor);                          | 删除访客用户                                           |
| int modifKey(Student* p_stu, string new_key);                | 改变读者用户密码                                       |
| int modifKey(Admin* p_admin, string new_key);                | 改变管理员用户密码                                     |
| int modifKey(Visitor* p_cust, string new_key);               | 改变访客用户密码                                       |
| vector<Student*> findStudent(string user_name);              | 按用户名查找读者                                       |
| vector<Admin*> findAdmin(string user_name);                  | 按用户名查找管理员                                     |
| vector<Visitor*> findVisitor(string user_name);              | 按用户名查找访客                                       |
| vector<Student*> rankUser_borrowest(int rank_len);           | 在Student库中找到借阅图书次数最多的读者并返回          |

> 用户类型(identity)： 'S':Student	'A':Admain	'V':Visirot
>
> 删改操作的返回值int与之前提到到一样，成功返回1

| 类属性                     | 描述                   | 参数类型          |
| -------------------------- | ---------------------- | ----------------- |
| userNums                   | 当前的用户（三类）总数 | int               |
| adminNums                  | 当前管理员总数         | int               |
| studentNums                | 当前读者总数           | int               |
| visitorNums                | 当前访客总数           | int               |
| p_book_repo (protected)    | 指向图书库的指针       | BookRepo*         |
| p_admin_repo (protected)   | 存放admin用户数据库    | vector\<Admin>*   |
| p_student_repo (protected) | 存放student用户数据库  | vector\<Student>* |
| p_visitor_repo (protected) | 存放visitor用户数据库  | vector\<Visitor>* |

> 使用addXXX的方法添加的用户都会被添加入对应的数据库中

这里有一个很有意思（也很强大）的一个属性: **BookRepo* p_book_repo**。

他是一个指向图书库(BookRepo)的指针，我们就是通过这个指针来建立用户库和图书库的联系，使得users们可以通过自己的方法来对图书增删改查，这个指针就是user与books的单向总线。更加强大的是，你仅仅只用修改这个指针的指向就可以赋予当前的所有用户管理其他图书库的权利！！因此，你需要在实例化UserRepo对象时提供这个参数。

以下是UserRepo的构造函数

```cpp
	UserRepo(BookRepo* p_book_repo) {
		this->p_book_repo = p_book_repo;
		int userNums = 0;
		int adminNums=0;
		int studentNums=0;
		int visitorNums=0;
		p_admin_repo = new vector<Admin>;
		p_student_repo = new vector<Student>;
		p_visitor_repo = new vector<Visitor>;
	}
```

