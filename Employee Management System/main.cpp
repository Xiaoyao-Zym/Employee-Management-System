#include<iostream>
#include<Windows.h>
#include<string>
#include<workerManager.h>
#include<worker.h>
#include<employee.h>
using namespace std;

int main()
{
	WorkerManager wm;
	int choice = 0;
	while (true)
	{
		//չʾ�˵�
		wm.Show_Menu();
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:  wm.exitSystem(); // �˻�ϵͳ
			break;
		case 1:  wm.Add_Emp();  //���ְ��
			break;
		case 2:  wm.Show_Emp(); //��ʾְ��
			break;
		case 3:  wm.Del_Emp();   //ɾ��ְ��
			break;
		case 4:  wm.Mod_Emp(); //�޸�ְ��
			break;
		case 5:  wm.Find_Emp();  //����ְ��
			break;
		case 6:  wm.sort_Emp(); //����ְ��
			break;
		case 7:  wm.Clean_File(); //����ļ�
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}