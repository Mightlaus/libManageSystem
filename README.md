# libManageSystem

这里是图书馆项目

## 代码命名风格约定

- 普通成员变量：全小写+下划线(name)
- 常量：全大写(DATE)
- 函数名：小驼峰（getName）
- 类、结构体：大驼峰 (MyLibrary)



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
