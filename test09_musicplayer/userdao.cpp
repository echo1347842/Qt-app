#include "userdao.h"
UserDao* UserDao::ud = new UserDao;
UserDao::UserDao()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库文件名
    db.setDatabaseName("test.db");
    //打开数据库
    db.open();
    //绑定数据库
    query = (QSqlQuery)db;
    //创建表
    createTable();

}

UserDao::UserDao(const UserDao &)
{

}

UserDao *UserDao::getUd()
{
    return ud;
}

void UserDao::createTable()
{
    //拼接字符串
    QString sql = "create table if not exists user("
                  "id integer primary key autoincrement,"
                  "username varchar(20),"
                  "password varchar(20));";
    //执行sql
    bool ok = query.exec(sql);
    //判断执行结果
    if(ok)
    {
        qDebug()<<"create success";
    }
    else
    {
        qDebug()<<"create failed";
    }
    //为了保证账号从10001开始，给一条初始数据10000
    query.exec("insert into user values(10000,'admin','123456');");
}

int UserDao::insertTable(QString name, QString pass)
{
    int userId = 0;
    //准备sql
    query.prepare("insert into user(username,password)values(?,?);");
    //绑定参数
    query.bindValue(0,name);
    query.bindValue(1,pass);
    //执行
    bool ok = query.exec();
    if(ok)
    {
        //获取最新插入的id
        query.exec("SELECT LAST_INSERT_ROWID();");
        //查询结果看似存储在链表中，next判断是否有结果数据
        if(query.next())
        {
            //拿到id的值.一行.第一列.转为int
            userId = query.record().value(0).toInt();

            qDebug()<<"insert success"<<userId;
        }


    }
    else
    {
        qDebug()<<"insert failed";
    }
    return  userId;

}

bool UserDao::selectTable(int id, QString pass)
{
    bool flag = false;
    //准备sql
    query.prepare("SELECT count(*) from user where id =? AND password = ?;");
    //绑定参数
    query.bindValue(0,id);
    query.bindValue(1,pass);
    //执行sql
    bool ok = query.exec();
    //判断结果
    if(ok)
    {
        //判断是否查询到数据
        if(query.next())
        {
            flag = query.record().value(0).toInt();
            qDebug()<<"select success";
        }
    }
    else
    {
        qDebug()<<"select failed";
    }
    //返回结果
    return flag;
}

void UserDao::release()
{
    if(ud != nullptr)
    {
        delete ud;
        ud = nullptr;
    }
}

UserDao::~UserDao()
{
    db.close();
}
