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
		//展示菜单
		wm.Show_Menu();
		cout << "请输入您的选择：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:  wm.exitSystem(); // 退回系统
			break;
		case 1:  wm.Add_Emp();  //添加职工
			break;
		case 2:  wm.Show_Emp(); //显示职工
			break;
		case 3:  wm.Del_Emp();   //删除职工
			break;
		case 4:  wm.Mod_Emp(); //修改职工
			break;
		case 5:  wm.Find_Emp();  //查找职工
			break;
		case 6:  wm.sort_Emp(); //排序职工
			break;
		case 7:  wm.Clean_File(); //清空文件
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}