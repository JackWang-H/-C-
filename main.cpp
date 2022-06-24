#include<iostream>
#include <stdio.h>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<string>
#include <iomanip>
#include<map>
#include<algorithm>
using namespace std;

#define N 9999

int n = 0; //记录个数

class STU{
public:
    STU(){}
    void input(char d[],int X,char n[],char sn[],int sd,int cl){
        strcpy(date,d);
        ClassX = X;
        strcpy(ClassN,n);
        strcpy(stuN,sn);
        stuID = sd;
        ClassL = cl;
    }
    void print(){
        string str;
        if (ClassL == 1) {
            str = "请假";
        }else if(ClassL == 2){
            str = "旷课";
        }else{
            str = "迟到早退";
        }
        cout<<setiosflags(ios_base::left)<<setw(13)<<"缺课日期"<<setiosflags(ios_base::left)<<setw(8)<<"课节"<<setiosflags(ios_base::left)<<setw(16)<<"课程名称"<<setiosflags(ios_base::left)<<setw(14)<<"学生姓名"<<setiosflags(ios_base::left)<<setw(14)<<"学号"<<setiosflags(ios_base::left)<<setw(8)<<"缺课类型"<<endl;
        cout<<setiosflags(ios_base::left)<<setw(12)<<date<<setiosflags(ios_base::left)<<setw(7)<<ClassX<<setiosflags(ios_base::left)<<setw(16)<<ClassN<<setiosflags(ios_base::left)<<setw(14)<<stuN<<setiosflags(ios_base::left)<<setw(14)<<stuID<<setiosflags(ios_base::left)<<setw(8)<<str<<endl;
    }
    friend void Change(STU stu[]);
    friend void Find(STU stu[]);
    friend void show(STU stu[]);
    friend void Find_date(STU stu[]);
    friend void Find_name(STU stu[]);
    friend void Find_id(STU stu[]);
    friend void Find_N(STU stu[]);
    friend void Count_date(STU stu[]);
    friend void Count_id(STU stu[]);
    friend void Count_N(STU stu[]);
    friend void Count_All(STU stu[]);
private:
    char stuN[11]; //学生名称
    int stuID; //学号
    char date[11]; //日期
    int ClassX; //课节
    char ClassN[16]; //课程名称
    int ClassL; //缺课类型
};

STU stu[N]; //存储所有的记录

//主菜单
void meau(){
    cout<<endl;
    cout<<"****************************************"<<endl;
    cout<<"        学生考勤管理系统 "<<endl;
    cout<<"        1.录入学生的缺课记录"<<endl;
    cout<<"        2.修改某个学生的缺课记录"<<endl;
    cout<<"        3.查询缺课记录"<<endl;
    cout<<"        4.统计旷课信息"<<endl;
    cout<<"        5.显示所有学生缺课记录"<<endl;
    cout<<"        6.退出系统"<<endl;
    cout<<"****************************************"<<endl;
    cout<<endl;
}

//-----------------------------------文件存储模块-开始------------------------------
//单条记录文件存入
void File_in(STU stu){
    fstream fout("./binary.dat",ios::app | ios::binary);//app追加的方式
    fout.write((char *)&stu,sizeof (stu));
    fout.close();
}
//清空文件内容，重新写入
void File_rew(){
    fstream fout("./binary.dat",ios::out| ios::binary);//out清空所有的
    for (int i = 0; i < n; ++i) {
        fout.write((char *)&stu[i],sizeof (stu[i]));
    }
    fout.close();
}
//返回文件里记录个数
int GetNumberFromFile()
{
    int count = 0;//对象个数，即学生人数
    fstream infile("./binary.dat",ios::in | ios::binary);//以读方式打开文件
    if (!infile)
    {
        cout<<"open file error!"<<endl;
        getchar();
        exit(0);
    }
    STU stu;
    while (infile.read((char*)&stu,sizeof(stu)))//强制类型转换为(char*),
    {
        count++;
    }
    infile.close();
    return count;
}
//文件读取
void File_out(){
    n = GetNumberFromFile();
    fstream fin("./binary.dat",ios::in| ios::binary);
    for (int i = 0; i < n;i++)
    {
        fin.read((char*)&stu[i], sizeof(stu[i]));
    }
    fin.close();
}
//-----------------------------------文件存储模块-结束------------------------------

//输入学生的缺课记录
void Input(STU stu[]){
    char stuN[11],date[11],ClassN[16]; //学生名称,日期,课程名称
    int stuID,ClassX,ClassL; //学号,课节,缺课类型
    while(1){
        cout<<"请输入缺课记录"<<endl;
        cout<<"请输入缺课日期:";
        cin>>date;
        cout<<"请输入第几节课:";
        cin>>ClassX;
        cout<<"请输入课程名称:";
        cin>>ClassN;
        cout<<"请输入学生姓名:";
        cin>>stuN;
        cout<<"请输入学生学号:";
        cin>>stuID;
        cout<<"请输入缺课类型(1代表请假，2代表旷课, 3代表迟到):";
        cin>>ClassL;
        stu[n].input(date,ClassX,ClassN,stuN,stuID,ClassL);
        File_in(stu[n]); //写入文件
        cout<<"缺课记录信息:"<<endl;
        stu[n].print();
        n++;
        cout<<"输入信息完毕！是否继续输入？y是继续，n是停止:"<<endl;
        char cc;
        getchar();
        cin>>cc;
        if(cc == 'n')
            return ;
    }
}
//修改某个学生的缺课记录
void Change(STU stu[]){
//    只需要知道学号，日期与课节就能找到具体的缺课记录，然后进行修改！
    int stu_id,class_x,flag = 0;
    char date[11];
    cout<<"请输入学号：";
    cin>>stu_id;
    cout<<"请输入日期：";
    cin>>date;
    cout<<"请输入第几节课：";
    cin>>class_x;
    for (int i = 0; i < n; ++i) {
        if (stu[i].stuID == stu_id && !strcmp(stu[i].date,date) && stu[i].ClassX == class_x){
            flag = 1;
            cout<<"缺课记录："<<endl;
            stu[i].print();
            cout<<"是否对该学生缺课记录进行修改?(y/n)"<<endl;
            getchar();
            char cc;
            cin>>cc;
            if(cc == 'n'){
                break;
            }else if(cc == 'y'){
                int t;
                cout<<"请选择修改内容："<<endl;
                cout<<"修改课程名称(1),修改缺课类型(2)：";
                cin>>t;
                if (t == 1){
                    char class_name[16];
                    cout<<"输入课程名称：";
                    cin>>class_name;
                    strcpy(stu[i].ClassN,class_name);
                    cout<<"修改后的记录信息："<<endl;
                    stu[i].print();
                    File_rew();
                    File_out();
                }else if(t == 2){
                    int class_l;
                    cout<<"请输入缺课类型(1代表请假，2代表旷课, 3代表迟到)：";
                    cin>>class_l;
                    stu[i].ClassL = class_l;
                    cout<<"修改后的记录信息："<<endl;
                    stu[i].print();
                    File_rew();
                    File_out();
                }else{
                    cout<<"选项错误！请重新选择！"<<endl;
                }
                break;
            } else{
                cout<<"输入错误！"<<endl;
            }
            break;
        }
    }
    if (flag == 1){
        cout<<"没有查到该缺课记录！"<<endl;
    }
}

//-----------------------------------查询模块-开始------------------------------
//按日期查询
void Find_date(STU stu[]){
    char date[11];
    string str;
    cout<<"输入日期：";
    cin>>date;
    cout<<setiosflags(ios_base::left)<<setw(13)<<"缺课日期"<<setiosflags(ios_base::left)<<setw(8)<<"课节"<<setiosflags(ios_base::left)<<setw(16)<<"课程名称"<<setiosflags(ios_base::left)<<setw(14)<<"学生姓名"<<setiosflags(ios_base::left)<<setw(14)<<"学号"<<setiosflags(ios_base::left)<<setw(8)<<"缺课类型"<<endl;
    for (int i = 0; i < n; ++i) {
        if (!strcmp(stu[i].date,date)){
            if (stu[i].ClassL == 1) {
                str = "请假";
            }else if(stu[i].ClassL == 2){
                str = "旷课";
            }else{
                str = "迟到早退";
            }
            cout<<setiosflags(ios_base::left)<<setw(12)<<stu[i].date<<setiosflags(ios_base::left)<<setw(7)<<stu[i].ClassX<<setiosflags(ios_base::left)<<setw(16)<<stu[i].ClassN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuID<<setiosflags(ios_base::left)<<setw(8)<<str<<endl;
        }
    }
}
//按姓名查询
void Find_name(STU stu[]){
    string str;
    char name[11];
    cout<<"输入姓名：";
    cin>>name;
    cout<<setiosflags(ios_base::left)<<setw(13)<<"缺课日期"<<setiosflags(ios_base::left)<<setw(8)<<"课节"<<setiosflags(ios_base::left)<<setw(16)<<"课程名称"<<setiosflags(ios_base::left)<<setw(14)<<"学生姓名"<<setiosflags(ios_base::left)<<setw(14)<<"学号"<<setiosflags(ios_base::left)<<setw(8)<<"缺课类型"<<endl;
    for (int i = 0; i < n; ++i) {
        if (!strcmp(stu[i].stuN, name)){
            if (stu[i].ClassL == 1) {
                str = "请假";
            }else if(stu[i].ClassL == 2){
                str = "旷课";
            }else{
                str = "迟到早退";
            }
            cout<<setiosflags(ios_base::left)<<setw(12)<<stu[i].date<<setiosflags(ios_base::left)<<setw(7)<<stu[i].ClassX<<setiosflags(ios_base::left)<<setw(16)<<stu[i].ClassN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuID<<setiosflags(ios_base::left)<<setw(8)<<str<<endl;
        }
    }
}
//按学号查询
void Find_id(STU stu[]){
    string str;
    int id;
    cout<<"输入学号：";
    cin>>id;
    cout<<setiosflags(ios_base::left)<<setw(13)<<"缺课日期"<<setiosflags(ios_base::left)<<setw(8)<<"课节"<<setiosflags(ios_base::left)<<setw(16)<<"课程名称"<<setiosflags(ios_base::left)<<setw(14)<<"学生姓名"<<setiosflags(ios_base::left)<<setw(14)<<"学号"<<setiosflags(ios_base::left)<<setw(8)<<"缺课类型"<<endl;
    for (int i = 0; i < n; ++i) {
        if (stu[i].stuID == id){
            if (stu[i].ClassL == 1) {
                str = "请假";
            }else if(stu[i].ClassL == 2){
                str = "旷课";
            }else{
                str = "迟到早退";
            }
            cout<<setiosflags(ios_base::left)<<setw(12)<<stu[i].date<<setiosflags(ios_base::left)<<setw(7)<<stu[i].ClassX<<setiosflags(ios_base::left)<<setw(16)<<stu[i].ClassN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuID<<setiosflags(ios_base::left)<<setw(8)<<str<<endl;
        }
    }
}
//按课程查询
void Find_N(STU stu[]){
    string str;
    char project[16];
    cout<<"输入课程名称：";
    cin>>project;
    cout<<setiosflags(ios_base::left)<<setw(13)<<"缺课日期"<<setiosflags(ios_base::left)<<setw(8)<<"课节"<<setiosflags(ios_base::left)<<setw(16)<<"课程名称"<<setiosflags(ios_base::left)<<setw(14)<<"学生姓名"<<setiosflags(ios_base::left)<<setw(14)<<"学号"<<setiosflags(ios_base::left)<<setw(8)<<"缺课类型"<<endl;
    for (int i = 0; i < n; ++i) {
        if (!strcmp(stu[i].ClassN,project)){
            if (stu[i].ClassL == 1) {
                str = "请假";
            }else if(stu[i].ClassL == 2){
                str = "旷课";
            }else{
                str = "迟到早退";
            }
            cout<<setiosflags(ios_base::left)<<setw(12)<<stu[i].date<<setiosflags(ios_base::left)<<setw(7)<<stu[i].ClassX<<setiosflags(ios_base::left)<<setw(16)<<stu[i].ClassN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuID<<setiosflags(ios_base::left)<<setw(8)<<str<<endl;
        }
    }
}
//查询界面
void Find(STU stu[]){
    int kind;
    while (1){
        cout<<endl;
        cout<<"****************************************"<<endl;
        cout<<"        查询界面"<<endl;
        cout<<"        1.按日期查询"<<endl;
        cout<<"        2.按姓名查询"<<endl;
        cout<<"        3.按学号查询"<<endl;
        cout<<"        4.按课程查询"<<endl;
        cout<<"        5.退出"<<endl;
        cout<<"****************************************"<<endl;
        cout<<endl;
        cout<<"请选择操作:";
        cin>>kind;
        switch (kind) {
            case 1:
                Find_date(stu);
                system("pause"); //暂停
                break;
            case 2:
                Find_name(stu);
                system("pause");
                break;
            case 3:
                Find_id(stu);
                system("pause");
                break;
            case 4:
                Find_N(stu);
                system("pause");
                break;
            case 5:
                cout<<"退出查询界面。"<<endl;
                return ;
            default:
                cout<<"对不起，该项功能不存在."<<endl;
        }
    }
}
//-----------------------------------查询模块-结束------------------------------

//-----------------------------------统计模块-开始------------------------------
//统计某天的缺课记录
void Count_date(STU stu[]){
    string str;
    char date[11];
    int num = 0;//缺课总数
    int ask_num = 0,truancy_num = 0,late_num = 0;
    cout<<"输入日期：";
    cin>>date;
    cout<<setiosflags(ios_base::left)<<setw(13)<<"缺课日期"<<setiosflags(ios_base::left)<<setw(8)<<"课节"<<setiosflags(ios_base::left)<<setw(16)<<"课程名称"<<setiosflags(ios_base::left)<<setw(14)<<"学生姓名"<<setiosflags(ios_base::left)<<setw(14)<<"学号"<<setiosflags(ios_base::left)<<setw(8)<<"缺课类型"<<endl;
    for (int i = 0; i < n; ++i) {
        if (!strcmp(stu[i].date,date)){
            num++;
            if (stu[i].ClassL == 1) {
                ask_num++;
                str = "请假";
            }else if(stu[i].ClassL == 2){
                truancy_num++;
                str = "旷课";
            }else{
                late_num++;
                str = "迟到早退";
            }
            cout<<setiosflags(ios_base::left)<<setw(12)<<stu[i].date<<setiosflags(ios_base::left)<<setw(7)<<stu[i].ClassX<<setiosflags(ios_base::left)<<setw(16)<<stu[i].ClassN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuID<<setiosflags(ios_base::left)<<setw(8)<<str<<endl;
        }
    }
    cout<<date<<"--"<<"缺课总数："<<num<<endl;
    cout<<"\t\t"<<"请假："<<ask_num<<endl;
    cout<<"\t\t"<<"旷课："<<truancy_num<<endl;
    cout<<"\t\t"<<"迟到早退："<<late_num<<endl;
}
//统计某个学生的缺课信息
void Count_id(STU stu[]){
    string str;
    char name[11];
    int id;
    int num = 0;//缺课总数
    int ask_num = 0,truancy_num = 0,late_num = 0;
    cout<<"输入学号：";
    cin>>id;
    cout<<setiosflags(ios_base::left)<<setw(13)<<"缺课日期"<<setiosflags(ios_base::left)<<setw(8)<<"课节"<<setiosflags(ios_base::left)<<setw(16)<<"课程名称"<<setiosflags(ios_base::left)<<setw(14)<<"学生姓名"<<setiosflags(ios_base::left)<<setw(14)<<"学号"<<setiosflags(ios_base::left)<<setw(8)<<"缺课类型"<<endl;
    for (int i = 0; i < n; ++i) {
        if (stu[i].stuID == id){
            num++;
            strcpy(name,stu[i].stuN);
            if (stu[i].ClassL == 1) {
                ask_num++;
                str = "请假";
            }else if(stu[i].ClassL == 2){
                truancy_num++;
                str = "旷课";
            }else{
                late_num++;
                str = "迟到早退";
            }
            cout<<setiosflags(ios_base::left)<<setw(12)<<stu[i].date<<setiosflags(ios_base::left)<<setw(7)<<stu[i].ClassX<<setiosflags(ios_base::left)<<setw(16)<<stu[i].ClassN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuID<<setiosflags(ios_base::left)<<setw(8)<<str<<endl;
        }
    }
    cout<<id<<name<<"--"<<"-缺课总数："<<num<<endl;
    cout<<"\t\t"<<"请假："<<ask_num<<endl;
    cout<<"\t\t"<<"旷课："<<truancy_num<<endl;
    cout<<"\t\t"<<"迟到早退："<<late_num<<endl;
}
//统计某个课程的缺课记录
void Count_N(STU stu[]){
    string str;
    char class_N[16];
    int num = 0;//缺课总数
    int ask_num = 0,truancy_num = 0,late_num = 0;
    cout<<"输入课程名称：";
    cin>>class_N;
    cout<<setiosflags(ios_base::left)<<setw(13)<<"缺课日期"<<setiosflags(ios_base::left)<<setw(8)<<"课节"<<setiosflags(ios_base::left)<<setw(16)<<"课程名称"<<setiosflags(ios_base::left)<<setw(14)<<"学生姓名"<<setiosflags(ios_base::left)<<setw(14)<<"学号"<<setiosflags(ios_base::left)<<setw(8)<<"缺课类型"<<endl;
    for (int i = 0; i < n; ++i) {
        if (!strcmp(stu[i].ClassN,class_N)){
            num++;
            if (stu[i].ClassL == 1) {
                ask_num++;
                str = "请假";
            }else if(stu[i].ClassL == 2){
                truancy_num++;
                str = "旷课";
            }else{
                late_num++;
                str = "迟到早退";
            }
            cout<<setiosflags(ios_base::left)<<setw(12)<<stu[i].date<<setiosflags(ios_base::left)<<setw(7)<<stu[i].ClassX<<setiosflags(ios_base::left)<<setw(16)<<stu[i].ClassN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuID<<setiosflags(ios_base::left)<<setw(8)<<str<<endl;
        }
    }
    cout<<class_N<<"--"<<"-缺课总数："<<num<<endl;
    cout<<"\t\t"<<"请假："<<ask_num<<endl;
    cout<<"\t\t"<<"旷课："<<truancy_num<<endl;
    cout<<"\t\t"<<"迟到早退："<<late_num<<endl;
}
//统计所有学生的缺课记录
void Count_All(STU stu[]){
    char name[11];
    string str;
    map<int,int> student;
    student.clear();
    for (int i = 0; i < n; ++i) {
        student[stu[i].stuID]++;
    }
    map<int ,int>::iterator it; //迭代器
    for(it = student.begin(); it != student.end(); it++){
        int ask_num = 0,truancy_num = 0,late_num = 0;
        for (int i = 0; i < n; ++i) {
            if (stu[i].stuID == (*it).first){
                strcpy(name,stu[i].stuN);
                if (stu[i].ClassL == 1){
                    ask_num++;
                } else if(stu[i].ClassL == 2){
                    truancy_num++;
                } else if(stu[i].ClassL == 3){
                    late_num++;
                }
            }
        }
        cout<<(*it).first<<name<<"--"<<"缺课总数："<<(*it).second<<endl;
        cout<<"\t\t"<<"请假："<<ask_num<<endl;
        cout<<"\t\t"<<"旷课："<<truancy_num<<endl;
        cout<<"\t\t"<<"迟到早退："<<late_num<<endl;
    }
}
//统计界面
void Count(STU stu[]){
    int kind;
    while(1){
        cout<<endl;
        cout<<"****************************************"<<endl;
        cout<<"        统计界面"<<endl;
        cout<<"        1.统计某天的缺课记录"<<endl;
        cout<<"        2.统计某个学生的缺课记录"<<endl;
        cout<<"        3.统计某个课程的缺课记录"<<endl;
        cout<<"        4.统计所有学生的缺课记录"<<endl;
        cout<<"        5.退出界面"<<endl;
        cout<<"****************************************"<<endl;
        cout<<endl;
        cout<<"请选择操作:";
        cin>>kind;
        switch (kind) {
            case 1:
                Count_date(stu);
                system("pause");
                break;
            case 2:
                Count_id(stu);
                system("pause");
                break;
            case 3:
                Count_N(stu);
                system("pause");
                break;
            case 4:
                Count_All(stu);
                system("pause");
                break;
            case 5:
                cout<<"退出统计界面。"<<endl;
                return ;
            default:
                cout<<"对不起，该项功能不存在."<<endl;
        }
    }
}
//-----------------------------------统计模块-结束------------------------------

//显示所有缺课记录
void show(STU stu[]){
    string str;
    cout<<setiosflags(ios_base::left)<<setw(13)<<"缺课日期"<<setiosflags(ios_base::left)<<setw(8)<<"课节"<<setiosflags(ios_base::left)<<setw(16)<<"课程名称"<<setiosflags(ios_base::left)<<setw(14)<<"学生姓名"<<setiosflags(ios_base::left)<<setw(14)<<"学号"<<setiosflags(ios_base::left)<<setw(8)<<"缺课类型"<<endl;
    for (int i = 0; i < N; ++i) {
        if (stu[i].ClassX != 0){
            if (stu[i].ClassL == 1) {
                str = "请假";
            }else if(stu[i].ClassL == 2){
                str = "旷课";
            }else{
                str = "迟到早退";
            }
            cout<<setiosflags(ios_base::left)<<setw(12)<<stu[i].date<<setiosflags(ios_base::left)<<setw(7)<<stu[i].ClassX<<setiosflags(ios_base::left)<<setw(16)<<stu[i].ClassN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuID<<setiosflags(ios_base::left)<<setw(8)<<str<<endl;
        }else{
            break;
        }
    }
}


int main(){
    File_out();//读文件，读出所有的记录
    while(1){
        meau();
        cout<<"请输入对应功能序号"<<endl;
        int x;
        cin>>x;
        switch(x){
            case 1:
                Input(stu);
                system("pause");
                break;
            case 2:
                if(n==0){
                    cout<<"错误，无信息！\n";
                }
                else{
                    Change(stu);
                }
                system("pause");
                break;
            case 3:
                if(n==0){
                    cout<<"错误，无信息！\n";
                }
                else{
                    Find(stu);
                }
                system("pause");
                break;
            case 4:
                if(n==0){
                    cout<<"错误，无信息！\n";
                }
                else{
                    Count(stu);
                }
                system("pause");
                break;
            case 5:
                show(stu);
                system("pause");
                break;
            case 6:{
                cout<<"退出该系统。"<<endl;
                return 0;
            }
            default:
                cout<<"对不起，该项功能不存在."<<endl;
        }
    }
    return 0;
}
