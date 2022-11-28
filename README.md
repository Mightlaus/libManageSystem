# libManageSystem

这里是图书馆管理项目

![architecture](README.assets/architecture.png)

- [libManageSystem](#libmanagesystem)
  * [开发环境](#开发环境)
  * [代码命名风格约定](#代码命名风格约定)
- [后端开发手册](#后端开发手册)
  * [User.h](#userh)
    + [class User](#class-user)
    + [class Student](#class-student)
    + [class Admin](#class-admin)
    + [class Visitor](#class-visitor)
  * [UserRepo.h](#userrepoh)
  * [BookRepo.h](#bookrepoh)
  * [Book.h](#bookh)
  * [Repo.h](#repoh)
- [前端使用手册](#前端使用手册)
  * [程序特性](#程序特性)
    + [主菜单](#主菜单)
      - [三种用户模式](#三种用户模式)
    + [从csv读写数据](#从csv读写数据)
    + [读取系统时间](#读取系统时间)
    + [健壮性](#健壮性)
    + [用户友好性](#用户友好性)
    + [代码复用率](#代码复用率)
    + [数据静态存储](#数据静态存储)
  * [操作示范](#操作示范)
    + [欢迎界面（自动全屏）](#欢迎界面（自动全屏）)
    + [系统界面（自动调整console大小）](#系统界面（自动调整console大小）)
    + [管理员模式](#管理员模式)
    + [用户模式](#用户模式)
    + [排行榜](#排行榜)
    + [退出](#退出)
    + [一键安装](#一键安装)
## 开发环境

Visual Studio 2022 x64 + 内置Git

Windows10, Windows11 Platform; **Linux不兼容！**

所有含中文字符文件使用GB-2312编码; **UTF-8中文无法正常显示！**

## 代码命名风格约定

- 普通成员变量：全小写+下划线(name)
- 常量：全大写(DATE)
- 函数名：小驼峰（getName）
- 类、结构体：大驼峰 (MyLibrary)

# 后端开发手册

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
## BookRepo.h

说完用户部分，我们接着谈**BookRepo* p_book_repo**这个指针所指向的BookRepo的功能。

与UserRepo一样，这是一个用于管理图书的类，所有的图书都应该保存在其中并且都应该由它来操作。因此，BookRepo针对其内的图书提供了以下方法。

| 类方法                                                     | 描述                                            |
| ---------------------------------------------------------- | ----------------------------------------------- |
| void addOne(Book book);                                    | 向书库中增加一本书                              |
| void addBatch(vector<string*> book_batch, int batch_size); | 通过文件读写的方式向书库中批量增加书            |
| void delOne(Book* p_book);                                 | 删除书库中的一本书（属性exist置为0）            |
| void delBatch(vector<Book*> book_vec);                     | 批量删除传入列表中的全部书                      |
| void modifCaption(Book* p_book, string caption);           | 修改书名                                        |
| void modifAuthor(Book* p_book, string author);             | 修改作者                                        |
| void modifIsbn(Book* p_book, string isbn);                 | 修改ISBN                                        |
| void modifPrice(Book* p_book, double price);               | 修改价格                                        |
| vector<Book*> find_isbn(string isbn);                      | ISBN精准查找                                    |
| vector<Book*> find_caption(string caption);                | 书名模糊查找                                    |
| vector<Book*> find_author(string author);                  | 按作者名模糊查找                                |
| vector<Book*> find_publish(string publish);                | 按出版社名模糊查找                              |
| vector<Book*> rankBook_newest(int rank_len);               | 在书库中找到最新出版的rank_len本书并返回        |
| vector<Book*> rankBook_borrowest(int rank_len);            | 在书库中找到被借阅次数最多的rank_len本书并返回  |
| vector<Book*> recommend(Book* p_book);                     | 推荐,返回借阅传入图书的全部用户借阅的其他所有书 |

增、删、改、查，四种方法字如其名，方法自身声明已经很显式地告知了使用方法，不再赘述。这里重点谈一下最后的三种方法和模糊查找。

- 模糊查找

  模糊查找实际上就是字符串的匹配。当然，为了更高级的查找功能，本程序里设计的模糊查找功能基于综合判断字长、广义子串功能实现。

  假设现在有字符串str1与str2。判断两字符串“成功匹配”（也就是查找到）的条件如下

  1. str1中的全部字符在str2中出现过（不考虑顺序）或者相反
  2. 两字符串长度(len1+len2)/(len1-len2)>=2

  众所周知C++基本没有对汉字的处理能力，一个汉字需要两个字节的位置存放，所以不能通过char的简单ascall编码来查找，否则会发生很严重错误，这就需要我们在查找前首先把汉字做格式转换。必须想办法把单字节的string转换成双字节的wstring，这个函数(str2wst)的在BookRepo.cpp中得到实现。

  这个单字节向双字节的转换函数非常重要，几乎所有处理汉字字符串匹配的都要用到。

  ```cpp
  wstring str2wstr(string str)
  {
  	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
  	if (len == 0)
  		return wstring(L"");
  	wchar_t* wct = new wchar_t[len];
  	if (!wct)
  		return std::wstring(L"");
  
  	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wct, len);
  	wstring wstr(wct);
  	delete[] wct;
  	wct = NULL;
  	return wstr;
  }
  ```

- 最新出版图书排序

  这是个苦功夫，提供的原始图书数据库的时间信息格式非常乱，单单在洗数据上就花费了很多时间。

  此外，由于我们读取存入的是string对象，我们还要想办法对其排序。还是因为格式信息不同，想要简单的使用string比大小肯定漏洞百出，我们最终的解决办法是，用正则表达式匹配来兼容不同格式的数据并提出年月日信息转化为int比较，代码如下。

  ```cpp
  // 出版时间转换
  int publishTime(string str_time)
  {
  	long long time = 0;
  
  	if (str_time.empty()) {
  		return -1;
  	}
  
  	regex pattern_year("(\\d+)");
  	regex pattern_month("\\d+.+?(\\d+)");
  	regex pattern_day("\\d+[-_年]\\d+[-_月](\\d+)");
  
  	smatch result;
  	if (regex_search(str_time, result, pattern_year))
  	{
  		time += stoi(result.str()) * 10000;
  	}
  	if (regex_search(str_time, result, pattern_month))
  	{
  		time += stoi(result[1].str()) * 100;
  	}
  	if (regex_search(str_time, result, pattern_day))
  	{
  		time += stoi(result[1].str());
  	}
  
  	return time;
  
  }
  ```

  它可以识别2022-1-1、2022年1月1日、2022_1_1、2022 1 1等类型的日期表示方法，然后转化为*年\*10000+月\*100+日*的int类型以供比较。

  有了确切的比较对象，那么我们只需要构造一个比较规则然后利用sort函数就可以实现了。可是我们这里并不需要对整个图书库全部排序，只需要找出最新出版的X本就足够了。所以我们的项目里采用冒泡排序即可

  ```cpp
  // 按被借阅次数降序排列
  void bookSort_borrowest(vector<Book*>& bookRepo, int len)
  {
  	int size = bookRepo.size();
  	for (int i = 0; i < len; i++)
  	{
  		for (int j = size - 1; j > i; j--)
  		{
  			if (bookRepo[j]->histories.size() > bookRepo[j - 1]->histories.size())
  			{
  				swap(bookRepo[j], bookRepo[j - 1]);
  			}
  		}
  	}
  }
  ```

- 被借阅次数最多的图书

  方法与最新出版图书类似，略。

- 书->书 推荐

  推荐逻辑在UserRepo里提到过，不再重复。值得注意的是，UserRepo里实现给用户推荐书的方法调用了这个函数的接口，因为在找到用户借的图书后需要根据这些图书找到借他们的用户然后再去找这些用户借的书。(但这是一个递归！难免有些绕)

这个类还包含了一些记录图书库的属性

| 类属性       | 描述         | 数据类型      |
| ------------ | ------------ | ------------- |
| bookNums     | 库内图书总数 | int           |
| *p_book_repo | 书库         | vector\<Book> |

构造函数初始化了这两个属性 

```cpp
BookRepo()
{
    bookNums = 0;
    p_book_repo = new vector<Book>;
}
```

## Book.h

这就是图书库操作的对象——图书。

每一本图书的属性包含了他的基本信息和库状态信息

| 类属性         | 描述                     | 变量类型             |
| -------------- | ------------------------ | -------------------- |
| caption        | 书名                     | string               |
| author         | 作者                     | string               |
| isbn           | ISBN                     | string               |
| publishing     | 出版社                   | string               |
| published_time | 出版时间                 | string               |
| description    | 图书简介                 | string               |
| pages          | 页数                     | int                  |
| price          | 价格                     | double               |
| exist          | 是否还存在（没有被删除） | int                  |
| borrowed       | 是否被借走               | int                  |
| borrowed_times | 被借次数                 | int                  |
| histories      | 借阅记录                 | vector\<BookHistory> |

图书类自己带有修改属性的方法（现在看来没必要，这些方法应该定义在BookRepo中的），下面简单展示

| 类方法                                                     | 描述         |
| ---------------------------------------------------------- | ------------ |
| void resetCaption(string new_caption);                     | 修改书名     |
| void resetAuthor(string new_author);                       | 修改作者     |
| void resetIsbn(string new_isbn);                           | 修改ISBN     |
| void resetDescription(string new_description);             | 修改简介     |
| void resetPrice(double price);                             | 修改价格     |
| void addHistory(long long time, int action, User* p_user); | 新增历史记录 |

> 这里的历史记录与Users里的历史记录一样，是一个结构体，里面包含了操作发生的时间、操作类型、用户指针。这是它的定义

```cpp
	struct BookHistory
	{
		long long time;
		int action; // -1借， 0阅览，1还
		User* user;

		BookHistory(long long time, int action, User* user)
			:time(time), action(action), user(user) {}
	};
```

每一本书被创建时需要提供所有的基础属性，系统自动将borrowed_times置0，exist置1，borrowed置0。

```cpp
	Book(string caption, string author, string isbn, string publishing, string published_time, string description, int pages, double price)
		:caption(caption),
		author(author),
		isbn(isbn),
		publishing(publishing),
		published_time(published_time),
		description(description),
		pages(pages),
		price(price),

		borrowed_times(0),
		exist(1),
		borrowed(0) {}
```

## Repo.h

最后，让我们看一下这些库是如何组织起来的。

Repo.h里的内容少得可怜，因为它就是所有功能库的中央枢纽，在他里面唯一需要做的就是把其他功能库初始化。

```cpp
class Repo
{
private:

	

public:
	BookRepo books = BookRepo();// 图书库相关功能
	UserRepo users = UserRepo(&books); //user相关功能
	

};
```

有了这个枢纽，前端在调用后端的所有功能时唯一需要初始化的就是Repo仓库，没错，这也只要一行即可

```cpp
Repo libRepo;
```

然后，前端就可以通过 . 操作符来使用这里面的各个系统的各个功能。

```cpp
libRepo.books.addBatch(bookBatch, 2560); // 批量添加图书
libRepo.users.findAdmin(account, 1); // 查找管理员
libRepo.books.bookNums; // 图书总数
libRepo.users.addUser();// 添加用户
// ...
```

Repo这个中央枢纽还提供了非常强大的拓展可能。我们现在只设计了图书系统和用户系统的相关功能，未来也许会需要预约系统、存包系统、门禁系统、后勤系统、财务系统等等。那时候需要做的也仅仅就是把这些新系统在中央枢纽里实例化即可。这就像拼积木一样简单，可见我们程序的拓展性与可移植性之强。

# 前端使用手册

## 程序特性



用户交互部分为终端命令行显示，通过输入字符并按下回车以进入下一级或上一级菜单。

前端需要和后端相配合，使用户能够顺畅地体验到后端实现的功能。



- ### 主菜单

​	刚进入系统的菜单分为管理员、学校用户和游客三个模式，用户可以选择其中一个进入。我将三个模式**封装**成了三个函数，这样代码结构更清晰一些。在主界面还可以看到当前时间，图书馆系统当前用户数和图书数量，访问三个排行榜，对图书馆的大致情况进行了解。

- #### 三种用户模式

​	在特定的模式子菜单下，显示当前账号类型所允许的操作列表，并让用户去选择要进行的操作。这里主要就是调用后端的接口，并根据传入的参数和返回的结果，搭配前端用户操作输入输出的逻辑，实现整个系统**“看起来”**的样子。

- ### 从csv读写数据

​	每次打开图书馆系统，系统会先读取当前目录下的图书和用户csv文件到内存，而每次关闭系统会将内存中的数据写入csv文件，以保证图书馆系统的数据实时保持更新。

​	图书的原始数据比较“脏”，所以过程中格式出了很多问题，因此我们先通过excel清洗了数据，再将其读入内存。

- ### 读取系统时间

​	我们在主菜单提供了显示当前时间的功能，此外我们还在读者借还书的操作进行时将当前系统的时间传入后端的接口中，以进行借阅记录的详细显示。



### 健壮性

​	为了系统能在用户的各种**非法输入**下不报错、不崩溃，我在代码中做了很多的if判断分支，以保证一个错误的输入不会影响整个系统的正常运行。最后达到的结果就是，无论用户在哪一步，输入了任何内容，系统都会自动识别非法输入并报错，永远不会出现崩溃的情况。

​	开发过程中出现了cin输入缓存区溢出的问题，用户在int类型输入一个字符串后，系统不能正常运行，一直死循环刷屏。最后采用每次输入非法时对缓存区进行清理的方法，成功解决了问题。



### 用户友好性

​	为了让用户能够在没有操作手册的指导下，流畅地使用系统。我尽量使交互界面所见即所得，尽量简化操作，使界面**清晰易懂**，每一次操作后系统会给出提示，**引导**用户使用系统。

​	比如在每次用户输入时，都告知当前所需读入的量是什么，输入格式非法时，告知用户该输入非法且系统将回到上一级菜单，借书时如果该书已被借走，则会告知用户，还书时如果没有借过书也会相应告知，所以保证每一步都有追溯，不会出现让用户莫名奇妙的情况。

​	每次用户输入操作数，系统都是接着上次的往下输出，如果回到上一级菜单，会重新输出菜单内容，这时候用户可能不太方便找到上次操作的结果，连续输出最后界面会越来越长，也不够美观。所以最后决定在回到上一级菜单时进行清屏操作，从而界面清爽了许多。

​	当图书数量增加到很多，搜索图书的结果可能有七八十个，而这时如果直接输出所有结果，用户需要一点一点往上翻到第一页开始看，这非常不方便，而且有时其实用户仅仅需要前面十条的搜索记录。有鉴于此，我增加了搜索结果分页显示的功能，并让用户自己选择翻页，这样便很好的解决了这个问题。

### 代码复用率

​	为了提高代码复用率，使代码更容易阅读，开发维护成本更低。将搜索图书和输出图书信息的功能封装成了函数，在不同用户模式和操作中去调用它，从而少去了复制粘贴的过程，并且后期修改能够只改一个地方，提高了开发效率

- [x] 提供了在主菜单显示当前图书馆图书数量和读者数量的功能，方便用户更直观地了解图书馆的实时情况
- [x] 管理员模式提供了更改密码，添加用户，删除用户，恢复用户默认密码，增加图书，删除图书，修改图书信息，搜索图书8个功能，覆盖了对图书馆系统用户账号和所有图书的增删改查
- [x] 对用户账号和图书的删、改、查，都采用了相似的一套流程，输入查找类型（可有可无），系统精确搜索（或模糊搜索），按分页的形式列出搜索结果，用户选择继续查看下一页或退出搜索结果查询，并通过序号选择自己要操作的对象。
- [x] 当输入非法格式时，系统自动跳回上一级菜单。但当输入密码错误时，系统会给予重试的机会，这时用户如果放弃输入密码，可以按*退出
- [x] 用户模式提供了更改密码，借阅图书，归还图书，搜索图书，推荐图书，查看借阅记录6个功能
- [x] 用户的推荐图书功能系统会直接列出与当前用户借过相同的书的读者借阅的其他书，而游客模式的推荐图书功能需要用户选择一本书进行相关推荐
- [x] 游客模式提供了搜索图书，推荐图书2个功能，进入此模式系统会自动分配账号，无需通过账号密码登录

### 数据静态存储

系统所有的用户数据都使用了静态存储方法，也即在进入系统前，程序会从文件(users.csv)读取用户信息初始化到系统，退出系统后程序会将变化的用户信息重新写入文件。保证每一次进入系统前用户的状态与上一次退出时一致。

![image-20221128103523414](README.assets/image-20221128103523414.png)

![image-20221128103626573](README.assets/image-20221128103626573.png)

## 操作示范

### 欢迎界面（自动全屏）

![image-20221127220958379](README.assets/image-20221127220958379.png)

### 系统界面（自动调整console大小）

进入欢迎界面后会屏蔽关闭按钮，只有通过内置选项【7】才能正确退出。

![image-20221127221220266](README.assets/image-20221127221220266.png)

### 管理员模式

1. 登录账号

   ![image-20221127202155812](README.assets/image-20221127202155812.png)

![image-20221127202215170](README.assets/image-20221127202215170.png)

2. 删除账号

   ![image-20221127200315462](README.assets/image-20221127200315462.png)

3. 恢复账号

   ![image-20221127200454143](README.assets/image-20221127200438363.png)

![image-20221127200611417](README.assets/image-20221127200611417.png)

4. 搜索图书

   ![image-20221127201929474](README.assets/image-20221127201929474.png)

   ![image-20221127201956869](README.assets/image-20221127201956869.png)



5. 修改图书信息

   ![image-20221127202651222](README.assets/image-20221127202651222.png)



![image-20221127202702408](README.assets/image-20221127202702408.png)

6. 添加图书

   ![image-20221127202956388](README.assets/image-20221127202956388.png)



![image-20221127203011673](README.assets/image-20221127203011673.png)

7. 删除图书

   ![image-20221128100613145](README.assets/image-20221128100613145.png)

   ![image-20221128100627781](README.assets/image-20221128100627781.png)

### 用户模式

![image-20221128100802825](README.assets/image-20221128100802825.png)

![image-20221128100813125](README.assets/image-20221128100813125.png)

1. 更改密码

   ![image-20221128100852964](README.assets/image-20221128100852964.png)

2. 借阅图书

   ![image-20221128100924144](README.assets/image-20221128100924144.png)

   多条选项可以输入n翻页

   ![image-20221128101228751](README.assets/image-20221128101228751.png)

3. 归还图书

   ![image-20221128101253245](README.assets/image-20221128101253245.png)

4. 查看借阅记录

   ![image-20221128101331691](README.assets/image-20221128101331691.png)

5. 推荐图书

   推荐图书会针对该用户的借阅情况来推荐同喜好读者借阅的其他书籍。例如，当前用户student 借阅了三本书分别为《Thining in C++》, 《python黑帽子》，计算机程序设计艺术。

   我们另外登录用户居文涛，让他也借阅同样的《计算机程序设计艺术》，随后让居文涛使用推荐图书功能。

   ![image-20221128101729037](README.assets/image-20221128101729037.png)

   显然，系统找到了借阅同一本书（《计算机程序设计艺术》）的student用户借阅的其他所有书推荐给居文涛。

   如果有多个读者都借阅了《计算机程序设计艺术》，那么系统同样会把这些读者各自借阅的其他书籍推荐给当前用户居文涛。

   如果居文涛借阅了多本书，那推荐结果也可以类推。

   总结就是：**推荐该用户借阅的所有图书的借阅他们的用户借阅的其他所有书**

   这真的是太酷了

### 排行榜

1. 图书借阅次数排行榜

   ![image-20221128102428466](README.assets/image-20221128102428466.png)

2. 读者借阅次数排行榜

   ![image-20221128102504639](README.assets/image-20221128102504639.png)

3.  最新出版图书排行榜

   ![image-20221128102629227](README.assets/image-20221128102629227.png)

   

### 退出

退出界面显示2.5s后彻底中止程序。

![image-20221127221412600](README.assets/image-20221127221412600.png)

### 一键安装

我们的程序还提供了打包好的安装包。在Windows上可以双击.msi文件将程序一键安装至计算机上

![image-20221127221752728](README.assets/image-20221127221752728.png)

安装完成后会在桌面生成快捷方式，双击即可打开使用。

![image-20221127221850630](README.assets/image-20221127221850630.png)

