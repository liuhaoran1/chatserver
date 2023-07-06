#include  "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;

void fun1(){
    json js;
    js["msg_type"]=2;
    js["from"]="zhang san";
    js["to"]="li si";
    js["message"]="hello,what are you doing now?";
    string sendBuf = js.dump();//json数据对象序列化为json字符串
    cout<<sendBuf.c_str()<<endl;
    // cout<<js<<endl;
}
void fun2(){
    json js;
    // 添加数组
    js["id"] = {1,2,3,4,5};
    // 添加key-value
    js["name"] = "zhang san";
    // 添加对象
    js["msg"]["zhang san"] = "hello world";
    js["msg"]["liu shuo"] = "hello china";
    // 上面等同于下面这句一次性添加数组对象
    js["msg"] = {{"zhang san", "hello world"}, {"liu shuo", "hello china"}};
    cout << js << endl;
}
void fun3(){
    json js;
    // 直接序列化一个vector容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);
    js["list"] = vec;
    // 直接序列化一个map容器
    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});
    js["path"] = m;
    cout<<js<<endl;
}
string fun4(){
    json js;
    js["msg_type"]=2;
    js["from"]="zhang san";
    js["to"]="li si";
    js["message"]="hello,what are you doing now?";
    string sendBuf = js.dump();//json数据对象序列化为json字符串
    return sendBuf;
    // cout<<js<<endl;
}
int main(){
    // fun1();
    // fun2();
    // fun3();
    string jsbuf = fun4();
    json js = json::parse(jsbuf);//json字符串反序列化为json数据对象
    cout<<js["msg_type"]<<endl;
    cout<<js["from"]<<endl;
    cout<<js["to"]<<endl;
    cout<<js["message"]<<endl;
    return  0;
}

