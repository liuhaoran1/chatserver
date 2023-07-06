#ifndef USERMODEL_H
#define USERMODEL_H
#include <string>
#include "user.hpp"
using namespace std;
//User表的数据操作类
class UserModel{
public:
    //User表的增加方法
    bool insert(User &user);
    //根据用户号码查询用户信息
    User query(int id);
    //跟星用户状态信息
    bool updateState(User user);
    //重置用户的状态信息
    void resetState();

private:



};

#endif