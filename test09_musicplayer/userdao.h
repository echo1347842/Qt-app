#ifndef USERDAO_H
#define USERDAO_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

//��װ���ݿ�  ����ģʽ��������
class UserDao
{
private:
    //1.˽�й���Ϳ�������
    UserDao();
    UserDao(const UserDao &);
    //2.˽�о�̬��ָ��
    static UserDao* ud;
    //�������ݿ������
    QSqlDatabase db;
    //�����������ݿ������
    QSqlQuery query;
public:
    //3.���о�̬��Ա����������ָ��
    static UserDao* getUd();
    //������ �û����˺� �ǳ� ����
    void createTable();
    //�����
    int insertTable(QString name,QString pass);
    //��ѯ��
    bool selectTable(int id,QString pass);
    //��̬���룬��̬�ͷ�
    void release();
    //����
    ~UserDao();


};

#endif // USERDAO_H
