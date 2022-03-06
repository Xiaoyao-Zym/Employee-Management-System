#pragma once   //防止头文件重复包含
#include<iostream>
#include<worker.h>
#include<fstream>
#define FILENAME "emFile.txt"
using namespace std;

class WorkerManager
{
public:
	//构造函数
	WorkerManager();
	//记录文件中的人数
	int m_EmpNum;
	//职工数组指针
	Worker** m_EmArray;
	//标志文件是否为空
	bool m_FileIsEmpty;
	//统计人数
	int get_EmpNum();
	//展示菜单
	void Show_Menu();
	//保存文件
	void Save();
	//添加职工
	void Add_Emp();
	//初始化员工
	void init_Emp();
	//显示职工
	void Show_Emp();
	//判断职工存在
	int IsExist(int id);
	//删除职工
	void Del_Emp();
	//修改职工
	void Mod_Emp();
	//查找职工
	void Find_Emp();
	//退出系统
	void exitSystem();
	//排序
	void sort_Emp();
	//清空文件
	void Clean_File();
	//析构函数
	~WorkerManager();
};