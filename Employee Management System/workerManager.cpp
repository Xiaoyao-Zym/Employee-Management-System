#include<workerManager.h>
#include<fstream>
#include<string>
#include<iostream>
#include<manager.h>
#include<worker.h>
#include<employee.h>
#include<boss.h>
WorkerManager::WorkerManager()
 {
	ifstream ifs;
	//判断文件存在
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;    //测试输出
		this->m_EmpNum = 0;                //初始化人数
		this->m_FileIsEmpty = true;        //初始化文件为空标志
		this->m_EmArray = NULL;          //初始化数组指针
		ifs.close();                                    //关闭文件
		return;
	}
	//文件存在。并且没有记录
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空！" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmArray = NULL;
		ifs.close();
		return;
	}
	//文件存在，并且记录数据
	int num = this->get_EmpNum();
	cout << "职工个数为：" << num << endl;    //测试代码
	this->m_EmpNum = num;    //更新成员属性
	this->m_EmArray = new Worker * [this->m_EmpNum];
	//将文件数据中的数据，存放在数组中
	this->init_Emp();
	//测试代码
	/*for (int  i = 0; i < this->m_EmpNum; i++)
	{
		cout << "职工编号：" << this->m_EmArray[i]->m_Id
			<< "姓名：" << this->m_EmArray[i]->m_Name
			<< "部门编号" << this->m_EmArray[i]->m_DeptId << endl;
	}*/
 }
//展示菜单
void WorkerManager::Show_Menu()
{
	cout << "***************************************" << endl;
	cout << "*******欢迎使用职工管理系统！********" << endl;
	cout << "***********0.退出管理程序 *************" << endl;
	cout << "***********1.增加职工信息 *************" << endl;
	cout << "***********2.显示职工信息 *************" << endl;
	cout << "***********3.删除离职职工 *************" << endl;
	cout << "***********4.修改职工信息 *************" << endl;
	cout << "***********5.查找职工信息 *************" << endl;
	cout << "***********6.按照编号排序 *************" << endl;
	cout << "***********7.清空所有文档 *************" << endl;
	cout << "***************************************" << endl;
	cout << endl;
}
//退出系统
void WorkerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
//添加职员
void  WorkerManager::Add_Emp()
{
	cout << "请输入职工数量" << endl;
	int addNum = 0;     //保存用户的输入数量
	cin >> addNum;
	if (addNum>0)
	{
		//计算新空间大小
		int newSize = this->m_EmpNum + addNum;
		//开辟新空间
		Worker** newSpace = new Worker * [newSize];  //新空间人数=原来记录人数+新增人数
		//将原空间下内容存放到新空间下
		if (this->m_EmArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmArray[i];
			}
		}
		//添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;                   //职工编号
			string name;        //职工姓名
			int dSelect;          //部门选择
			cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工姓名：" << endl;
			cin >> name;
			cout << "请选择该职工的岗位：" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
				case 1:    //普通员工
					worker = new Employee(id, name, 1);
					break;
				case 2:     //经理
					worker = new Manager(id, name, 2);
					break;
				case 3:     //老板
					worker = new Boss(id, name, 3);
					break;
			    default:
				    break; 
			}
			newSpace[this->m_EmpNum + i] = worker;
		}
		//释放原有空间
		delete[]this->m_EmArray;
		//更改新空间的指向
		this->m_EmArray = newSpace;
		//更新新的个数
		this->m_EmpNum = newSize;
		//提示信息
		cout << "成功添加" << addNum << "新职工名！" << endl;
		this->Save();      //保存数据
	}
	else
	{
		cout << "输入有误" << endl;
	}
	system("pause");
	system("cls");
}
//保存文件
void WorkerManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);     //用输出的方式打开文件，写文件
	//数据写入文件
	for (int  i = 0; i < this->m_EmpNum; i++)
	{
		ofs<< this->m_EmArray[i]->m_Id << "  "
			 << this->m_EmArray[i]->m_Name << "  "
			 << this->m_EmArray[i]->m_DeptId << endl;
	}
	ofs.close();
}
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs>>id&&ifs>>name&&ifs>>dId)
	{
		//记录人数
		num++;
	}
	ifs.close();
	return num; 
}
//初始化职工数组
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs>>id&&ifs>>name&&ifs>>dId)
	{
		Worker* worker = NULL;
		//根据不同的部门Id创建不同对象
		if (dId == 1)  //1.普通员工
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId==2) //2.经理
		{
			worker = new Manager(id, name, dId);
		}
		else   //总裁
		{
			worker = new Boss(id, name, dId);
		}
		//存放在数组中
		this->m_EmArray[index] = worker;
		index++;
	}
}
//显示职工
void WorkerManager::Show_Emp()
{
	if (!this->m_FileIsEmpty)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//测试
			/*cout << "职工编号：" << this->m_EmArray[i]->m_Id;
			cout << "姓名：" << this->m_EmArray[i]->m_Name;
			cout << "部门编号" << this->m_EmArray[i]->m_DeptId << endl;*/
			//利用多态接口
			this->m_EmArray[i]->showInfo();
		}
	}
	else
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	system("pause");
	system("cls");
}
//判断职工是否存在
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmArray[i]->m_Id==id)
		{
			index = i;
			break;
		}
	}
	return index;
}
//删除职工
void WorkerManager::Del_Emp()
{
	//判断职工是否存在
	int id=0;
	cout << "请输入需要删除的职工编号：" << endl;
	cin>> id;
	int ret = this->IsExist(id);
	if (ret!=-1)
	{
		for (int i = ret; i < this->m_EmpNum-1  ; i++)
		{
			this->m_EmArray[i] = this->m_EmArray[i + 1];
		}
		this->m_EmpNum--;  //更新数组中记录人员个数
		this->Save();   //更新文件数据
		cout << "该职工以成功删除" << endl;
	}
	else
	{
		cout<<"删除失败，职工不存在"<<endl;
	}
	system("pause");
	system("cls");
}
//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << endl;
	}
	else
	{
		//判断职工是否存在
		int id = 0;
		cout << "请输入需要修改的职工编号：" << endl;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret!=-1)
		{
			delete this->m_EmArray[ret];
			int new_Id = 0;
			string new_Name="";
			int dSelect = 0;
			cout << "查到：" <<id<<"号职工，请输入新职工号："<< endl;
			cin >> new_Id;
			cout << "请输入新姓名：" << endl;
			cin >> new_Name;
			cout << "请输入岗位：1、普通职工，2、经理，3、老板" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(new_Id, new_Name, dSelect);
				break;
			case 2:
				worker = new Manager(new_Id, new_Name, dSelect);
				break;
			case 3:
				worker = new Boss(new_Id, new_Name, dSelect);
				break;
			default:
				break;
			}
			this->m_EmArray[ret] = worker;   //更新数据到数组中
			cout << "修改成功!" << endl;
		}
		else
		{
			cout << "修改失败，未找到该职工!" << endl;
		}
		this->Save(); //更新数据到文件
	}
	system("pause");
	system("cls");
}
//查找职工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << endl;
	}
	else
	{
		//判断职工是否存在
		cout << "请输入查找的方式：1——按照职工编号查找，2——按照姓名查找" << endl;
		int slect = 0;
		cin >> slect;
		switch (slect)
		{
		case 1: 
		    {
			    cout << "请输入要查找的职工编号" << endl;
			    int id = 0;
			    cin >> id;
			    int ret = this->IsExist(id);
			    if (ret != -1)
			    {
				    cout << "查找成功！该职工信息如下：" << endl;
				    this->m_EmArray[ret]->showInfo();
			    }
			    else
			    {
				    cout << "查无此人！" << endl;
			    }
			    break;
		    }
		case 2:
		    {
			    string  name;
			    cout << "请输入查找的姓名：" << endl;
			    cin >> name;
			    bool flag = false; //查找到的标志
			    for (int i = 0; i < this->m_EmpNum; i++)
			    {
				    if (m_EmArray[i]->m_Name == name)
				    {
					    cout << "查找成功，职工编号为："
						        << m_EmArray[i]->m_Id
						        << "号的信息如下：" << endl;
					    flag = true;
					    this->m_EmArray[i]->showInfo();
				    }
				    else
				    {
					cout << "查无此人！" << endl;
				    }
			    }
		    }
		default:
			break;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请输入查找的方式：1、按照职工编号进行升序，2——按照姓名进行降序" << endl;
		int slect = 0;
		cin >> slect;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrmax= i;
			for (int  j = i+1; j < this->m_EmpNum; j++)
			{
				switch (slect)
				{
				case 1:  //升序
					if (this->m_EmArray[minOrmax]->m_Id > m_EmArray[j]->m_Id)
					{
						minOrmax = j;
					}
					break;
				case 2:  //降序
					if (this->m_EmArray[minOrmax]->m_Id < m_EmArray[j]->m_Id)
					{
						minOrmax = j;
					}
				    break;
				default:
					break;
				}
			}
			if (i != minOrmax)
			{
				Worker *temp= m_EmArray[i];
				m_EmArray[i] = m_EmArray[minOrmax];
				m_EmArray[minOrmax] = temp;
			}
		}
		cout << "排序成功，排序后结果为：" << endl;
		this->Save(); //保存数据
		this->Show_Emp();  //显示排序结果
	}
	system("pause");
	system("cls");
}
//清空文件
void WorkerManager::Clean_File()
{
	cout << "确定清空？，1、确认，2、返回" << endl;
	int select = 0;
	cin >> select;
	if (select==1)
	{
		//打开模式  ios::trunc
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmArray!=NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmArray[i]!=NULL)
				{
					delete this->m_EmArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmArray;
			this->m_EmArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}
WorkerManager::~WorkerManager()
 {
	if (this->m_EmArray!=NULL)
	{
		//删除堆区的每个职工对象
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmArray[i] != NULL)
			{
				delete this->m_EmArray[i];
			}
		}
		//删除堆区数组指针
		delete[] this->m_EmArray;
		this->m_EmArray = NULL;
	}
 }