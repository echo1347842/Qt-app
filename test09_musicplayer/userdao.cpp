#include "userdao.h"
UserDao* UserDao::ud = new UserDao;
UserDao::UserDao()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    //�������ݿ��ļ���
    db.setDatabaseName("test.db");
    //�����ݿ�
    db.open();
    //�����ݿ�
    query = (QSqlQuery)db;
    //������
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
    //ƴ���ַ���
    QString sql = "create table if not exists user("
                  "id integer primary key autoincrement,"
                  "username varchar(20),"
                  "password varchar(20));";
    //ִ��sql
    bool ok = query.exec(sql);
    //�ж�ִ�н��
    if(ok)
    {
        qDebug()<<"create success";
    }
    else
    {
        qDebug()<<"create failed";
    }
    //Ϊ�˱�֤�˺Ŵ�10001��ʼ����һ����ʼ����10000
    query.exec("insert into user values(10000,'admin','123456');");
}

int UserDao::insertTable(QString name, QString pass)
{
    int userId = 0;
    //׼��sql
    query.prepare("insert into user(username,password)values(?,?);");
    //�󶨲���
    query.bindValue(0,name);
    query.bindValue(1,pass);
    //ִ��
    bool ok = query.exec();
    if(ok)
    {
        //��ȡ���²����id
        query.exec("SELECT LAST_INSERT_ROWID();");
        //��ѯ������ƴ洢�������У�next�ж��Ƿ��н������
        if(query.next())
        {
            //�õ�id��ֵ.һ��.��һ��.תΪint
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
    //׼��sql
    query.prepare("SELECT count(*) from user where id =? AND password = ?;");
    //�󶨲���
    query.bindValue(0,id);
    query.bindValue(1,pass);
    //ִ��sql
    bool ok = query.exec();
    //�жϽ��
    if(ok)
    {
        //�ж��Ƿ��ѯ������
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
    //���ؽ��
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
