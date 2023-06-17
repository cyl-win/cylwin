// 学生成绩管理.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// QQ 523857886
#include<iostream>
#include<string>
#define MAX 200
using namespace std;
struct student
{
    string xingming,  zhuanye, banji;
 
    float xuehao=0;
    float shuxue=0;
    float yingyu=0;
    float yuwen=0;
    float avg = 0;//平均值
};  
 
struct data
{
    int count=0; // 当前学生数组中学生的个数
    struct student stu[MAX]; // 学生数组
}dd;
 
// 显示主菜单
void menu()
{
    
    //略  此部分内容需要的M    Q523857886
}
 
 
// 查看所有学生信息
void view_data()
{
    int i;
    cout << "姓名\t学号\t专业\t班级\t数学\t英语\t语文\t平均分";
    cout<<"\n-------------------------------------------------------------------\n";
    for (i = 0; i < dd.count; i++)
        cout << dd.stu[i].xingming << "\t" << dd.stu[i].xuehao << "\t" << dd.stu[i].zhuanye << "\t" << dd.stu[i].banji << "\t" << dd.stu[i].shuxue << "\t"
        << dd.stu[i].yingyu << "\t" << dd.stu[i].yuwen << "\t" << dd.stu[i].avg << "\n";
    cout<<"\n-------------------------------------------------------------------\n";    
}
 
// 输入学生记录
void add_data()
{
    int b;
    int k = dd.count;
    while (k < MAX)
    {
        float tmp;
 
        cout << "请输入学生姓名："; cin >> dd.stu[k].xingming;
        cout << "请输入学生学号：";
 
        cin >> tmp; 
        while (!cin)
        {
            char ch;
            while ((ch = getchar()) != '\n')
                continue;
            cout << "输入的不是数字,重新输入: ";
            cin.clear();
            cin >> tmp;
        }
        dd.stu[k].xuehao = tmp;
 
        cout << "请输入学生专业："; cin >> dd.stu[k].zhuanye;
        cout << "请输入学生班级："; cin >> dd.stu[k].banji; 
        
 
        cout << "请输入学生数学："; cin >> tmp;
        while (!cin)
        {
            char ch;
            while ((ch = getchar()) != '\n')
                continue;
            cout << "输入的不是数字,重新输入: ";
            cin.clear();
            cin >> tmp;
        }      
        dd.stu[k].shuxue =tmp;
 
        cout << "请输入学生英语："; cin >> tmp;
        while (!cin)
        {
            char ch;
            while ((ch = getchar()) != '\n')
                continue;
            cout << "输入的不是数字,重新输入: ";
            cin.clear();
            cin >> tmp;
        }
        dd.stu[k].yingyu = tmp;
 
        cout << "请输入学生语文："; cin >> tmp; 
        while (!cin)
        {
            char ch;
            while ((ch = getchar()) != '\n')
                continue;
            cout << "输入的不是数字,重新输入: ";
            cin.clear();
            cin >> tmp;
        }
 
        dd.stu[k].yuwen = tmp;
 
 
     
        
 
        dd.count++; //需要提前置0，在主函数中。
        k = dd.count;
        cout<<"\n\n继续添加学生信息[按1回车继续 0回车返回，其他回车退出]:";
        
        
        cin >> b;
        if (b != 1)
        {
            cin.clear();
            break;
        }
        
    }
    
}
 
 
// 修改学生记录
void edit_data()
{
    int i, k=-1;
    float  xuehao;
    cout<<"\n请输入要修改学生的学号:";
    cin >> xuehao;
 
    while (!cin)
    {
        char ch;
        while ((ch = getchar()) != '\n')
            continue;
        cout << "输入的不是数字,重新输入: ";
        cin.clear();
        cin >> xuehao;
    }
    
    for (i = 0; i < dd.count; i++)
    {
        if (dd.stu[i].xuehao== xuehao)
        {
            k = i;
            break;
        }
    }
    if (k == -1)
    {
        cout << "\n\n没有找到该学生(学号-"<< xuehao<<")!";
    }
    else
    {
        cout << "请输入" << xuehao << "学生姓名："; cin >> dd.stu[k].xingming;
        cout << "请输入"<< xuehao <<"学生专业："; cin >> dd.stu[k].zhuanye;
        cout << "请输入" << xuehao << "学生班级："; cin >> dd.stu[k].banji;
        float tmp;
 
        cout << "请输入" << xuehao << "学生数学："; cin >> tmp;
        while (!cin)
        {
            char ch;
            while ((ch = getchar()) != '\n')
                continue;
            cout << "输入的不是数字,重新输入: ";
            cin.clear();
            cin >> tmp;
        }
        dd.stu[k].shuxue = tmp;
 
        cout << "请输入" << xuehao << "学生英语："; cin >> tmp;
        while (!cin)
        {
            char ch;
            while ((ch = getchar()) != '\n')
                continue;
            cout << "输入的不是数字,重新输入: ";
            cin.clear();
            cin >> tmp;
        }
        dd.stu[k].yingyu = tmp;
 
        cout << "请输入" << xuehao << "学生语文："; cin >> tmp;
        while (!cin)
        {
            char ch;
            while ((ch = getchar()) != '\n')
                continue;
            cout << "输入的不是数字,重新输入: ";
            cin.clear();
            cin >> tmp;
        }
 
        dd.stu[k].yuwen = tmp;
        
        cout<<"\n\n修改学生记录(学号-"<< xuehao <<")成功!";
    }
}
 
//删除记录
void delete_data()
{
    int i, k=-1;
    float  xuehao;
    cout << "\n请输入要修改学生的学号:";
    cin >> xuehao;
 
    while (!cin)
    {
        char ch;
        while ((ch = getchar()) != '\n')
            continue;
        cout << "输入的不是数字,重新输入: ";
        cin.clear();
        cin >> xuehao;
    }
    
    for (i = 0; i < dd.count; i++)
    {
        if (dd.stu[i].xuehao == xuehao)
        {
            k = i;//找到记录所在位置
            break;
        }
    }
    if (k == -1)
    {
        cout << "\n\n没有找到该学生(学号-" << xuehao << ")!";
    }
    else
    {
        for (i = k; i < dd.count - 1; i++)//将k位置的数据被k+1位置的信息覆盖
        {
            dd.stu[i] = dd.stu[i + 1];
        }
        dd.count--;
 
        cout << "\n\n删除学生记录(学号-" << xuehao << ")成功!";
    }
}
 
//学号查询成绩 //需要学号是有序的，不然实现不了折半查询
void qurey_data_xuehao()
{
    
    float  xuehao;
    cout << "\n请输入要修改学生的学号:";
    cin >> xuehao;
    while (!cin)
    {
        char ch;
        while ((ch = getchar()) != '\n')
            continue;
        cout << "输入的不是数字,重新输入: ";
        cin.clear();
        cin >> xuehao;
    }
 
 
    int low = 1;
    int high = dd.count;
    int mid;
 
 
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (dd.stu[mid].xuehao == xuehao)
        {
            cout << "姓名\t学号\t专业\t班级\t数学\t英语\t语文";
            cout << "\n-------------------------------------------------------------------\n";
 
            cout << dd.stu[mid].xingming << "\t" << dd.stu[mid].xuehao << "\t" << dd.stu[mid].zhuanye << "\t" << dd.stu[mid].banji << "\t" << dd.stu[mid].shuxue << "\t"
                << dd.stu[mid].yingyu << "\t" << dd.stu[mid].yuwen << "\n";
            cout << "\n-------------------------------------------------------------------\n";
 
            return ;
        }
        else if (dd.stu[mid].xuehao > xuehao)
        {
            high = mid - 1;
        }        
        else
        {
            low = mid + 1;
        }
    }    
        cout << "\n\n没有找到该学生(学号-" << xuehao << ")!";     
}
 
void qurey_data_average() 
{
    int i;
   
    for (i = 0; i < dd.count; i++)   
        dd.stu[i].avg = (dd.stu[i].shuxue + dd.stu[i].yingyu + dd.stu[i].yuwen) / 3;   
    cout << "\n计算完毕~！\n";   
    
}
 
void sort_data()//排序 根据平均值排序
{
    int i, j, N;
    N = dd.count;
    for (i = 0; i < N - 1; i++) 
    {
        for (j = 0; j < N - 1 - i; j++)
        {
            if (dd.stu[j].avg < dd.stu[j + 1].avg) 
            { 
                student tmp; //临时变量
                tmp = dd.stu[j]; //交换
                dd.stu[j] = dd.stu[j + 1];
                dd.stu[j + 1] = tmp;
            }
        }
 
    }
    qurey_data_average();
    view_data();
}
 
int main() {
    int a;
    dd.count = 0;//开始0条记录
    
    menu();
    cin >> a;
    while (a) {
       //QQ 523857886
        menu();
        cin >> a;
    }
    return 0;
}

