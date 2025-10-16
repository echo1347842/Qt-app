#ifndef USERDAO_H
#define USERDAO_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

//封装数据库  单例模式（饿汉）
class UserDao
{
private:
    //1.私有构造和拷贝构造
    UserDao();
    UserDao(const UserDao &);
    //2.私有静态类指针
    static UserDao* ud;
    //创建数据库类对象
    QSqlDatabase db;
    //创建操作数据库类对象
    QSqlQuery query;
public:
    //3.公有静态成员函数返回类指针
    static UserDao* getUd();
    //创建表 用户表：账号 昵称 密码
    void createTable();
    //插入表
    int insertTable(QString name,QString pass);
    //查询表
    bool selectTable(int id,QString pass);
    //静态申请，静态释放
    void release();
    //析构
    ~UserDao();


};

#endif // USERDAO_H
