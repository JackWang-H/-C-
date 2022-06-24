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

int n = 0; //��¼����

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
            str = "���";
        }else if(ClassL == 2){
            str = "����";
        }else{
            str = "�ٵ�����";
        }
        cout<<setiosflags(ios_base::left)<<setw(13)<<"ȱ������"<<setiosflags(ios_base::left)<<setw(8)<<"�ν�"<<setiosflags(ios_base::left)<<setw(16)<<"�γ�����"<<setiosflags(ios_base::left)<<setw(14)<<"ѧ������"<<setiosflags(ios_base::left)<<setw(14)<<"ѧ��"<<setiosflags(ios_base::left)<<setw(8)<<"ȱ������"<<endl;
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
    char stuN[11]; //ѧ������
    int stuID; //ѧ��
    char date[11]; //����
    int ClassX; //�ν�
    char ClassN[16]; //�γ�����
    int ClassL; //ȱ������
};

STU stu[N]; //�洢���еļ�¼

//���˵�
void meau(){
    cout<<endl;
    cout<<"****************************************"<<endl;
    cout<<"        ѧ�����ڹ���ϵͳ "<<endl;
    cout<<"        1.¼��ѧ����ȱ�μ�¼"<<endl;
    cout<<"        2.�޸�ĳ��ѧ����ȱ�μ�¼"<<endl;
    cout<<"        3.��ѯȱ�μ�¼"<<endl;
    cout<<"        4.ͳ�ƿ�����Ϣ"<<endl;
    cout<<"        5.��ʾ����ѧ��ȱ�μ�¼"<<endl;
    cout<<"        6.�˳�ϵͳ"<<endl;
    cout<<"****************************************"<<endl;
    cout<<endl;
}

//-----------------------------------�ļ��洢ģ��-��ʼ------------------------------
//������¼�ļ�����
void File_in(STU stu){
    fstream fout("./binary.dat",ios::app | ios::binary);//app׷�ӵķ�ʽ
    fout.write((char *)&stu,sizeof (stu));
    fout.close();
}
//����ļ����ݣ�����д��
void File_rew(){
    fstream fout("./binary.dat",ios::out| ios::binary);//out������е�
    for (int i = 0; i < n; ++i) {
        fout.write((char *)&stu[i],sizeof (stu[i]));
    }
    fout.close();
}
//�����ļ����¼����
int GetNumberFromFile()
{
    int count = 0;//�����������ѧ������
    fstream infile("./binary.dat",ios::in | ios::binary);//�Զ���ʽ���ļ�
    if (!infile)
    {
        cout<<"open file error!"<<endl;
        getchar();
        exit(0);
    }
    STU stu;
    while (infile.read((char*)&stu,sizeof(stu)))//ǿ������ת��Ϊ(char*),
    {
        count++;
    }
    infile.close();
    return count;
}
//�ļ���ȡ
void File_out(){
    n = GetNumberFromFile();
    fstream fin("./binary.dat",ios::in| ios::binary);
    for (int i = 0; i < n;i++)
    {
        fin.read((char*)&stu[i], sizeof(stu[i]));
    }
    fin.close();
}
//-----------------------------------�ļ��洢ģ��-����------------------------------

//����ѧ����ȱ�μ�¼
void Input(STU stu[]){
    char stuN[11],date[11],ClassN[16]; //ѧ������,����,�γ�����
    int stuID,ClassX,ClassL; //ѧ��,�ν�,ȱ������
    while(1){
        cout<<"������ȱ�μ�¼"<<endl;
        cout<<"������ȱ������:";
        cin>>date;
        cout<<"������ڼ��ڿ�:";
        cin>>ClassX;
        cout<<"������γ�����:";
        cin>>ClassN;
        cout<<"������ѧ������:";
        cin>>stuN;
        cout<<"������ѧ��ѧ��:";
        cin>>stuID;
        cout<<"������ȱ������(1������٣�2�������, 3����ٵ�):";
        cin>>ClassL;
        stu[n].input(date,ClassX,ClassN,stuN,stuID,ClassL);
        File_in(stu[n]); //д���ļ�
        cout<<"ȱ�μ�¼��Ϣ:"<<endl;
        stu[n].print();
        n++;
        cout<<"������Ϣ��ϣ��Ƿ�������룿y�Ǽ�����n��ֹͣ:"<<endl;
        char cc;
        getchar();
        cin>>cc;
        if(cc == 'n')
            return ;
    }
}
//�޸�ĳ��ѧ����ȱ�μ�¼
void Change(STU stu[]){
//    ֻ��Ҫ֪��ѧ�ţ�������νھ����ҵ������ȱ�μ�¼��Ȼ������޸ģ�
    int stu_id,class_x,flag = 0;
    char date[11];
    cout<<"������ѧ�ţ�";
    cin>>stu_id;
    cout<<"���������ڣ�";
    cin>>date;
    cout<<"������ڼ��ڿΣ�";
    cin>>class_x;
    for (int i = 0; i < n; ++i) {
        if (stu[i].stuID == stu_id && !strcmp(stu[i].date,date) && stu[i].ClassX == class_x){
            flag = 1;
            cout<<"ȱ�μ�¼��"<<endl;
            stu[i].print();
            cout<<"�Ƿ�Ը�ѧ��ȱ�μ�¼�����޸�?(y/n)"<<endl;
            getchar();
            char cc;
            cin>>cc;
            if(cc == 'n'){
                break;
            }else if(cc == 'y'){
                int t;
                cout<<"��ѡ���޸����ݣ�"<<endl;
                cout<<"�޸Ŀγ�����(1),�޸�ȱ������(2)��";
                cin>>t;
                if (t == 1){
                    char class_name[16];
                    cout<<"����γ����ƣ�";
                    cin>>class_name;
                    strcpy(stu[i].ClassN,class_name);
                    cout<<"�޸ĺ�ļ�¼��Ϣ��"<<endl;
                    stu[i].print();
                    File_rew();
                    File_out();
                }else if(t == 2){
                    int class_l;
                    cout<<"������ȱ������(1������٣�2�������, 3����ٵ�)��";
                    cin>>class_l;
                    stu[i].ClassL = class_l;
                    cout<<"�޸ĺ�ļ�¼��Ϣ��"<<endl;
                    stu[i].print();
                    File_rew();
                    File_out();
                }else{
                    cout<<"ѡ�����������ѡ��"<<endl;
                }
                break;
            } else{
                cout<<"�������"<<endl;
            }
            break;
        }
    }
    if (flag == 1){
        cout<<"û�в鵽��ȱ�μ�¼��"<<endl;
    }
}

//-----------------------------------��ѯģ��-��ʼ------------------------------
//�����ڲ�ѯ
void Find_date(STU stu[]){
    char date[11];
    string str;
    cout<<"�������ڣ�";
    cin>>date;
    cout<<setiosflags(ios_base::left)<<setw(13)<<"ȱ������"<<setiosflags(ios_base::left)<<setw(8)<<"�ν�"<<setiosflags(ios_base::left)<<setw(16)<<"�γ�����"<<setiosflags(ios_base::left)<<setw(14)<<"ѧ������"<<setiosflags(ios_base::left)<<setw(14)<<"ѧ��"<<setiosflags(ios_base::left)<<setw(8)<<"ȱ������"<<endl;
    for (int i = 0; i < n; ++i) {
        if (!strcmp(stu[i].date,date)){
            if (stu[i].ClassL == 1) {
                str = "���";
            }else if(stu[i].ClassL == 2){
                str = "����";
            }else{
                str = "�ٵ�����";
            }
            cout<<setiosflags(ios_base::left)<<setw(12)<<stu[i].date<<setiosflags(ios_base::left)<<setw(7)<<stu[i].ClassX<<setiosflags(ios_base::left)<<setw(16)<<stu[i].ClassN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuID<<setiosflags(ios_base::left)<<setw(8)<<str<<endl;
        }
    }
}
//��������ѯ
void Find_name(STU stu[]){
    string str;
    char name[11];
    cout<<"����������";
    cin>>name;
    cout<<setiosflags(ios_base::left)<<setw(13)<<"ȱ������"<<setiosflags(ios_base::left)<<setw(8)<<"�ν�"<<setiosflags(ios_base::left)<<setw(16)<<"�γ�����"<<setiosflags(ios_base::left)<<setw(14)<<"ѧ������"<<setiosflags(ios_base::left)<<setw(14)<<"ѧ��"<<setiosflags(ios_base::left)<<setw(8)<<"ȱ������"<<endl;
    for (int i = 0; i < n; ++i) {
        if (!strcmp(stu[i].stuN, name)){
            if (stu[i].ClassL == 1) {
                str = "���";
            }else if(stu[i].ClassL == 2){
                str = "����";
            }else{
                str = "�ٵ�����";
            }
            cout<<setiosflags(ios_base::left)<<setw(12)<<stu[i].date<<setiosflags(ios_base::left)<<setw(7)<<stu[i].ClassX<<setiosflags(ios_base::left)<<setw(16)<<stu[i].ClassN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuID<<setiosflags(ios_base::left)<<setw(8)<<str<<endl;
        }
    }
}
//��ѧ�Ų�ѯ
void Find_id(STU stu[]){
    string str;
    int id;
    cout<<"����ѧ�ţ�";
    cin>>id;
    cout<<setiosflags(ios_base::left)<<setw(13)<<"ȱ������"<<setiosflags(ios_base::left)<<setw(8)<<"�ν�"<<setiosflags(ios_base::left)<<setw(16)<<"�γ�����"<<setiosflags(ios_base::left)<<setw(14)<<"ѧ������"<<setiosflags(ios_base::left)<<setw(14)<<"ѧ��"<<setiosflags(ios_base::left)<<setw(8)<<"ȱ������"<<endl;
    for (int i = 0; i < n; ++i) {
        if (stu[i].stuID == id){
            if (stu[i].ClassL == 1) {
                str = "���";
            }else if(stu[i].ClassL == 2){
                str = "����";
            }else{
                str = "�ٵ�����";
            }
            cout<<setiosflags(ios_base::left)<<setw(12)<<stu[i].date<<setiosflags(ios_base::left)<<setw(7)<<stu[i].ClassX<<setiosflags(ios_base::left)<<setw(16)<<stu[i].ClassN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuID<<setiosflags(ios_base::left)<<setw(8)<<str<<endl;
        }
    }
}
//���γ̲�ѯ
void Find_N(STU stu[]){
    string str;
    char project[16];
    cout<<"����γ����ƣ�";
    cin>>project;
    cout<<setiosflags(ios_base::left)<<setw(13)<<"ȱ������"<<setiosflags(ios_base::left)<<setw(8)<<"�ν�"<<setiosflags(ios_base::left)<<setw(16)<<"�γ�����"<<setiosflags(ios_base::left)<<setw(14)<<"ѧ������"<<setiosflags(ios_base::left)<<setw(14)<<"ѧ��"<<setiosflags(ios_base::left)<<setw(8)<<"ȱ������"<<endl;
    for (int i = 0; i < n; ++i) {
        if (!strcmp(stu[i].ClassN,project)){
            if (stu[i].ClassL == 1) {
                str = "���";
            }else if(stu[i].ClassL == 2){
                str = "����";
            }else{
                str = "�ٵ�����";
            }
            cout<<setiosflags(ios_base::left)<<setw(12)<<stu[i].date<<setiosflags(ios_base::left)<<setw(7)<<stu[i].ClassX<<setiosflags(ios_base::left)<<setw(16)<<stu[i].ClassN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuID<<setiosflags(ios_base::left)<<setw(8)<<str<<endl;
        }
    }
}
//��ѯ����
void Find(STU stu[]){
    int kind;
    while (1){
        cout<<endl;
        cout<<"****************************************"<<endl;
        cout<<"        ��ѯ����"<<endl;
        cout<<"        1.�����ڲ�ѯ"<<endl;
        cout<<"        2.��������ѯ"<<endl;
        cout<<"        3.��ѧ�Ų�ѯ"<<endl;
        cout<<"        4.���γ̲�ѯ"<<endl;
        cout<<"        5.�˳�"<<endl;
        cout<<"****************************************"<<endl;
        cout<<endl;
        cout<<"��ѡ�����:";
        cin>>kind;
        switch (kind) {
            case 1:
                Find_date(stu);
                system("pause"); //��ͣ
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
                cout<<"�˳���ѯ���档"<<endl;
                return ;
            default:
                cout<<"�Բ��𣬸���ܲ�����."<<endl;
        }
    }
}
//-----------------------------------��ѯģ��-����------------------------------

//-----------------------------------ͳ��ģ��-��ʼ------------------------------
//ͳ��ĳ���ȱ�μ�¼
void Count_date(STU stu[]){
    string str;
    char date[11];
    int num = 0;//ȱ������
    int ask_num = 0,truancy_num = 0,late_num = 0;
    cout<<"�������ڣ�";
    cin>>date;
    cout<<setiosflags(ios_base::left)<<setw(13)<<"ȱ������"<<setiosflags(ios_base::left)<<setw(8)<<"�ν�"<<setiosflags(ios_base::left)<<setw(16)<<"�γ�����"<<setiosflags(ios_base::left)<<setw(14)<<"ѧ������"<<setiosflags(ios_base::left)<<setw(14)<<"ѧ��"<<setiosflags(ios_base::left)<<setw(8)<<"ȱ������"<<endl;
    for (int i = 0; i < n; ++i) {
        if (!strcmp(stu[i].date,date)){
            num++;
            if (stu[i].ClassL == 1) {
                ask_num++;
                str = "���";
            }else if(stu[i].ClassL == 2){
                truancy_num++;
                str = "����";
            }else{
                late_num++;
                str = "�ٵ�����";
            }
            cout<<setiosflags(ios_base::left)<<setw(12)<<stu[i].date<<setiosflags(ios_base::left)<<setw(7)<<stu[i].ClassX<<setiosflags(ios_base::left)<<setw(16)<<stu[i].ClassN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuID<<setiosflags(ios_base::left)<<setw(8)<<str<<endl;
        }
    }
    cout<<date<<"--"<<"ȱ��������"<<num<<endl;
    cout<<"\t\t"<<"��٣�"<<ask_num<<endl;
    cout<<"\t\t"<<"���Σ�"<<truancy_num<<endl;
    cout<<"\t\t"<<"�ٵ����ˣ�"<<late_num<<endl;
}
//ͳ��ĳ��ѧ����ȱ����Ϣ
void Count_id(STU stu[]){
    string str;
    char name[11];
    int id;
    int num = 0;//ȱ������
    int ask_num = 0,truancy_num = 0,late_num = 0;
    cout<<"����ѧ�ţ�";
    cin>>id;
    cout<<setiosflags(ios_base::left)<<setw(13)<<"ȱ������"<<setiosflags(ios_base::left)<<setw(8)<<"�ν�"<<setiosflags(ios_base::left)<<setw(16)<<"�γ�����"<<setiosflags(ios_base::left)<<setw(14)<<"ѧ������"<<setiosflags(ios_base::left)<<setw(14)<<"ѧ��"<<setiosflags(ios_base::left)<<setw(8)<<"ȱ������"<<endl;
    for (int i = 0; i < n; ++i) {
        if (stu[i].stuID == id){
            num++;
            strcpy(name,stu[i].stuN);
            if (stu[i].ClassL == 1) {
                ask_num++;
                str = "���";
            }else if(stu[i].ClassL == 2){
                truancy_num++;
                str = "����";
            }else{
                late_num++;
                str = "�ٵ�����";
            }
            cout<<setiosflags(ios_base::left)<<setw(12)<<stu[i].date<<setiosflags(ios_base::left)<<setw(7)<<stu[i].ClassX<<setiosflags(ios_base::left)<<setw(16)<<stu[i].ClassN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuID<<setiosflags(ios_base::left)<<setw(8)<<str<<endl;
        }
    }
    cout<<id<<name<<"--"<<"-ȱ��������"<<num<<endl;
    cout<<"\t\t"<<"��٣�"<<ask_num<<endl;
    cout<<"\t\t"<<"���Σ�"<<truancy_num<<endl;
    cout<<"\t\t"<<"�ٵ����ˣ�"<<late_num<<endl;
}
//ͳ��ĳ���γ̵�ȱ�μ�¼
void Count_N(STU stu[]){
    string str;
    char class_N[16];
    int num = 0;//ȱ������
    int ask_num = 0,truancy_num = 0,late_num = 0;
    cout<<"����γ����ƣ�";
    cin>>class_N;
    cout<<setiosflags(ios_base::left)<<setw(13)<<"ȱ������"<<setiosflags(ios_base::left)<<setw(8)<<"�ν�"<<setiosflags(ios_base::left)<<setw(16)<<"�γ�����"<<setiosflags(ios_base::left)<<setw(14)<<"ѧ������"<<setiosflags(ios_base::left)<<setw(14)<<"ѧ��"<<setiosflags(ios_base::left)<<setw(8)<<"ȱ������"<<endl;
    for (int i = 0; i < n; ++i) {
        if (!strcmp(stu[i].ClassN,class_N)){
            num++;
            if (stu[i].ClassL == 1) {
                ask_num++;
                str = "���";
            }else if(stu[i].ClassL == 2){
                truancy_num++;
                str = "����";
            }else{
                late_num++;
                str = "�ٵ�����";
            }
            cout<<setiosflags(ios_base::left)<<setw(12)<<stu[i].date<<setiosflags(ios_base::left)<<setw(7)<<stu[i].ClassX<<setiosflags(ios_base::left)<<setw(16)<<stu[i].ClassN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuID<<setiosflags(ios_base::left)<<setw(8)<<str<<endl;
        }
    }
    cout<<class_N<<"--"<<"-ȱ��������"<<num<<endl;
    cout<<"\t\t"<<"��٣�"<<ask_num<<endl;
    cout<<"\t\t"<<"���Σ�"<<truancy_num<<endl;
    cout<<"\t\t"<<"�ٵ����ˣ�"<<late_num<<endl;
}
//ͳ������ѧ����ȱ�μ�¼
void Count_All(STU stu[]){
    char name[11];
    string str;
    map<int,int> student;
    student.clear();
    for (int i = 0; i < n; ++i) {
        student[stu[i].stuID]++;
    }
    map<int ,int>::iterator it; //������
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
        cout<<(*it).first<<name<<"--"<<"ȱ��������"<<(*it).second<<endl;
        cout<<"\t\t"<<"��٣�"<<ask_num<<endl;
        cout<<"\t\t"<<"���Σ�"<<truancy_num<<endl;
        cout<<"\t\t"<<"�ٵ����ˣ�"<<late_num<<endl;
    }
}
//ͳ�ƽ���
void Count(STU stu[]){
    int kind;
    while(1){
        cout<<endl;
        cout<<"****************************************"<<endl;
        cout<<"        ͳ�ƽ���"<<endl;
        cout<<"        1.ͳ��ĳ���ȱ�μ�¼"<<endl;
        cout<<"        2.ͳ��ĳ��ѧ����ȱ�μ�¼"<<endl;
        cout<<"        3.ͳ��ĳ���γ̵�ȱ�μ�¼"<<endl;
        cout<<"        4.ͳ������ѧ����ȱ�μ�¼"<<endl;
        cout<<"        5.�˳�����"<<endl;
        cout<<"****************************************"<<endl;
        cout<<endl;
        cout<<"��ѡ�����:";
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
                cout<<"�˳�ͳ�ƽ��档"<<endl;
                return ;
            default:
                cout<<"�Բ��𣬸���ܲ�����."<<endl;
        }
    }
}
//-----------------------------------ͳ��ģ��-����------------------------------

//��ʾ����ȱ�μ�¼
void show(STU stu[]){
    string str;
    cout<<setiosflags(ios_base::left)<<setw(13)<<"ȱ������"<<setiosflags(ios_base::left)<<setw(8)<<"�ν�"<<setiosflags(ios_base::left)<<setw(16)<<"�γ�����"<<setiosflags(ios_base::left)<<setw(14)<<"ѧ������"<<setiosflags(ios_base::left)<<setw(14)<<"ѧ��"<<setiosflags(ios_base::left)<<setw(8)<<"ȱ������"<<endl;
    for (int i = 0; i < N; ++i) {
        if (stu[i].ClassX != 0){
            if (stu[i].ClassL == 1) {
                str = "���";
            }else if(stu[i].ClassL == 2){
                str = "����";
            }else{
                str = "�ٵ�����";
            }
            cout<<setiosflags(ios_base::left)<<setw(12)<<stu[i].date<<setiosflags(ios_base::left)<<setw(7)<<stu[i].ClassX<<setiosflags(ios_base::left)<<setw(16)<<stu[i].ClassN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuN<<setiosflags(ios_base::left)<<setw(14)<<stu[i].stuID<<setiosflags(ios_base::left)<<setw(8)<<str<<endl;
        }else{
            break;
        }
    }
}


int main(){
    File_out();//���ļ����������еļ�¼
    while(1){
        meau();
        cout<<"�������Ӧ�������"<<endl;
        int x;
        cin>>x;
        switch(x){
            case 1:
                Input(stu);
                system("pause");
                break;
            case 2:
                if(n==0){
                    cout<<"��������Ϣ��\n";
                }
                else{
                    Change(stu);
                }
                system("pause");
                break;
            case 3:
                if(n==0){
                    cout<<"��������Ϣ��\n";
                }
                else{
                    Find(stu);
                }
                system("pause");
                break;
            case 4:
                if(n==0){
                    cout<<"��������Ϣ��\n";
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
                cout<<"�˳���ϵͳ��"<<endl;
                return 0;
            }
            default:
                cout<<"�Բ��𣬸���ܲ�����."<<endl;
        }
    }
    return 0;
}
