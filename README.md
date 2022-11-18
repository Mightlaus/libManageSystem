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
