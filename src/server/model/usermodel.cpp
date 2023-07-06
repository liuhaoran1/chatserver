#include "/home/lhr/Chat/include/server/model/usermodel.hpp"
#include "/home/lhr/Chat/include/server/db/db.h"
#include <iostream>
using namespace std;


//User表的增加方法
bool UserModel::insert(User &user){
    //1、组装sql语句
    char sql[1024] = {0};

    /*
    这段代码使用 sprintf 函数将三个字符串类型的值填充到 SQL 语句中的占位符
    位置，生成一个完整的 SQL 语句。具体来说，这个 SQL 语句会将一个名为 user 的
    用户对象的 name、password 和 state 字段的值插入到 User 表中。其
    中，user.getName().c_str()、user.getPwd().c_str() 和 user.getState().c_str() 分别
    是获取 user 对象的 name、password 和 state 字段的值，并将它们转换为 C 风格的
    字符串类型。这些字符串类型的值会被填充到 SQL 语句中的占位符位置，生成一个
    完整的 SQL 语句。最终，这个 SQL 语句会被传递给数据库执行插入操作。*/
    sprintf(sql,"insert into User(name,password,state) value('%s','%s','%s')",
        user.getName().c_str(),user.getPwd().c_str(),user.getState().c_str());
    MySQL mysql;
    if(mysql.connect()){
        if(mysql.update(sql)){
            //获取插入成功的用户数据生成的主键id
            //这段代码是将 MySQL 数据库中最后插入的一条记录的 ID 值赋值
            //给一个名为 user 的用户对象的 id 属性。具体来说，它调用
            //了 mysql_insert_id 函数来获取最后插入记录的 ID 值，然后
            //将该值赋给 user 对象的 id 属性。这样做的目的是为了确保 user 对
            //象的 id 属性与数据库中的记录 ID 保持一致，以便后续的数据库操作能够正确地进行。
            user.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    return false;
}

User UserModel::query(int id){
    //1.组装sql语句
    char sql[1024] = {0};
    sprintf(sql,"select * from User where id =  %d",id);
    MySQL mysql;
    if(mysql.connect()){
        MYSQL_RES *res = mysql.query(sql);
        if(res != nullptr){
            MYSQL_ROW row = mysql_fetch_row(res);
            if(row != nullptr){
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setPwd(row[2]);
                user.setState(row[3]);
                mysql_free_result(res);//释放资源 内催不断泄露
                return user;
            }
        }
    }
    return User();//如果查询结果为空，则返回一个空的User对象。
}

bool UserModel::updateState(User user){
    //1.组装sql语句
    char sql[1024] = {0};
    sprintf(sql,"update User set state = '%s' where id = %d",user.getState().c_str(),user.getId());
    MySQL mysql;
    if(mysql.connect()){
        if(mysql.update(sql)){
            return true;
        }
    }
    return false;
}

//重置用户的状态信息
void UserModel::resetState(){
    //1.组装sql语句
    char sql[1024] = "update User set state = 'offline' where state = 'online'";

    MySQL mysql;
    if(mysql.connect()){
        mysql.update(sql);
    }
}