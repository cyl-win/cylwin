// ѧ���ɼ�����.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
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
    float avg = 0;//ƽ��ֵ
};  
 
struct data
{
    int count=0; // ��ǰѧ��������ѧ���ĸ���
    struct student stu[MAX]; // ѧ������
}dd;
 
// ��ʾ���˵�
void menu()
{
    
    //��  �˲���������Ҫ��M    Q523857886
}
 
 
// �鿴����ѧ����Ϣ
void view_data()
{
    int i;
    cout << "����\tѧ��\tרҵ\t�༶\t��ѧ\tӢ��\t����\tƽ����";
    cout<<"\n-------------------------------------------------------------------\n";
    for (i = 0; i < dd.count; i++)
        cout << dd.stu[i].xingming << "\t" << dd.stu[i].xuehao << "\t" << dd.stu[i].zhuanye << "\t" << dd.stu[i].banji << "\t" << dd.stu[i].shuxue << "\t"
        << dd.stu[i].yingyu << "\t" << dd.stu[i].yuwen << "\t" << dd.stu[i].avg << "\n";
    cout<<"\n-------------------------------------------------------------------\n";    
}
 
// ����ѧ����¼
void add_data()
{
    int b;
    int k = dd.count;
    while (k < MAX)
    {
        float tmp;
 
        cout << "������ѧ��������"; cin >> dd.stu[k].xingming;
        cout << "������ѧ��ѧ�ţ�";
 
        cin >> tmp; 
        while (!cin)
        {
            char ch;
            while ((ch = getchar()) != '\n')
                continue;
            cout << "����Ĳ�������,��������: ";
            cin.clear();
            cin >> tmp;
        }
        dd.stu[k].xuehao = tmp;
 
        cout << "������ѧ��רҵ��"; cin >> dd.stu[k].zhuanye;
        cout << "������ѧ���༶��"; cin >> dd.stu[k].banji; 
        
 
        cout << "������ѧ����ѧ��"; cin >> tmp;
        while (!cin)
        {
            char ch;
            while ((ch = getchar()) != '\n')
                continue;
            cout << "����Ĳ�������,��������: ";
            cin.clear();
            cin >> tmp;
        }      
        dd.stu[k].shuxue =tmp;
 
        cout << "������ѧ��Ӣ�"; cin >> tmp;
        while (!cin)
        {
            char ch;
            while ((ch = getchar()) != '\n')
                continue;
            cout << "����Ĳ�������,��������: ";
            cin.clear();
            cin >> tmp;
        }
        dd.stu[k].yingyu = tmp;
 
        cout << "������ѧ�����ģ�"; cin >> tmp; 
        while (!cin)
        {
            char ch;
            while ((ch = getchar()) != '\n')
                continue;
            cout << "����Ĳ�������,��������: ";
            cin.clear();
            cin >> tmp;
        }
 
        dd.stu[k].yuwen = tmp;
 
 
     
        
 
        dd.count++; //��Ҫ��ǰ��0�����������С�
        k = dd.count;
        cout<<"\n\n�������ѧ����Ϣ[��1�س����� 0�س����أ������س��˳�]:";
        
        
        cin >> b;
        if (b != 1)
        {
            cin.clear();
            break;
        }
        
    }
    
}
 
 
// �޸�ѧ����¼
void edit_data()
{
    int i, k=-1;
    float  xuehao;
    cout<<"\n������Ҫ�޸�ѧ����ѧ��:";
    cin >> xuehao;
 
    while (!cin)
    {
        char ch;
        while ((ch = getchar()) != '\n')
            continue;
        cout << "����Ĳ�������,��������: ";
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
        cout << "\n\nû���ҵ���ѧ��(ѧ��-"<< xuehao<<")!";
    }
    else
    {
        cout << "������" << xuehao << "ѧ��������"; cin >> dd.stu[k].xingming;
        cout << "������"<< xuehao <<"ѧ��רҵ��"; cin >> dd.stu[k].zhuanye;
        cout << "������" << xuehao << "ѧ���༶��"; cin >> dd.stu[k].banji;
        float tmp;
 
        cout << "������" << xuehao << "ѧ����ѧ��"; cin >> tmp;
        while (!cin)
        {
            char ch;
            while ((ch = getchar()) != '\n')
                continue;
            cout << "����Ĳ�������,��������: ";
            cin.clear();
            cin >> tmp;
        }
        dd.stu[k].shuxue = tmp;
 
        cout << "������" << xuehao << "ѧ��Ӣ�"; cin >> tmp;
        while (!cin)
        {
            char ch;
            while ((ch = getchar()) != '\n')
                continue;
            cout << "����Ĳ�������,��������: ";
            cin.clear();
            cin >> tmp;
        }
        dd.stu[k].yingyu = tmp;
 
        cout << "������" << xuehao << "ѧ�����ģ�"; cin >> tmp;
        while (!cin)
        {
            char ch;
            while ((ch = getchar()) != '\n')
                continue;
            cout << "����Ĳ�������,��������: ";
            cin.clear();
            cin >> tmp;
        }
 
        dd.stu[k].yuwen = tmp;
        
        cout<<"\n\n�޸�ѧ����¼(ѧ��-"<< xuehao <<")�ɹ�!";
    }
}
 
//ɾ����¼
void delete_data()
{
    int i, k=-1;
    float  xuehao;
    cout << "\n������Ҫ�޸�ѧ����ѧ��:";
    cin >> xuehao;
 
    while (!cin)
    {
        char ch;
        while ((ch = getchar()) != '\n')
            continue;
        cout << "����Ĳ�������,��������: ";
        cin.clear();
        cin >> xuehao;
    }
    
    for (i = 0; i < dd.count; i++)
    {
        if (dd.stu[i].xuehao == xuehao)
        {
            k = i;//�ҵ���¼����λ��
            break;
        }
    }
    if (k == -1)
    {
        cout << "\n\nû���ҵ���ѧ��(ѧ��-" << xuehao << ")!";
    }
    else
    {
        for (i = k; i < dd.count - 1; i++)//��kλ�õ����ݱ�k+1λ�õ���Ϣ����
        {
            dd.stu[i] = dd.stu[i + 1];
        }
        dd.count--;
 
        cout << "\n\nɾ��ѧ����¼(ѧ��-" << xuehao << ")�ɹ�!";
    }
}
 
//ѧ�Ų�ѯ�ɼ� //��Ҫѧ��������ģ���Ȼʵ�ֲ����۰��ѯ
void qurey_data_xuehao()
{
    
    float  xuehao;
    cout << "\n������Ҫ�޸�ѧ����ѧ��:";
    cin >> xuehao;
    while (!cin)
    {
        char ch;
        while ((ch = getchar()) != '\n')
            continue;
        cout << "����Ĳ�������,��������: ";
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
            cout << "����\tѧ��\tרҵ\t�༶\t��ѧ\tӢ��\t����";
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
        cout << "\n\nû���ҵ���ѧ��(ѧ��-" << xuehao << ")!";     
}
 
void qurey_data_average() 
{
    int i;
   
    for (i = 0; i < dd.count; i++)   
        dd.stu[i].avg = (dd.stu[i].shuxue + dd.stu[i].yingyu + dd.stu[i].yuwen) / 3;   
    cout << "\n�������~��\n";   
    
}
 
void sort_data()//���� ����ƽ��ֵ����
{
    int i, j, N;
    N = dd.count;
    for (i = 0; i < N - 1; i++) 
    {
        for (j = 0; j < N - 1 - i; j++)
        {
            if (dd.stu[j].avg < dd.stu[j + 1].avg) 
            { 
                student tmp; //��ʱ����
                tmp = dd.stu[j]; //����
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
    dd.count = 0;//��ʼ0����¼
    
    menu();
    cin >> a;
    while (a) {
       //QQ 523857886
        menu();
        cin >> a;
    }
    return 0;
}

