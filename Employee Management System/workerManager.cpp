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
	//�ж��ļ�����
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;    //�������
		this->m_EmpNum = 0;                //��ʼ������
		this->m_FileIsEmpty = true;        //��ʼ���ļ�Ϊ�ձ�־
		this->m_EmArray = NULL;          //��ʼ������ָ��
		ifs.close();                                    //�ر��ļ�
		return;
	}
	//�ļ����ڡ�����û�м�¼
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ�գ�" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmArray = NULL;
		ifs.close();
		return;
	}
	//�ļ����ڣ����Ҽ�¼����
	int num = this->get_EmpNum();
	cout << "ְ������Ϊ��" << num << endl;    //���Դ���
	this->m_EmpNum = num;    //���³�Ա����
	this->m_EmArray = new Worker * [this->m_EmpNum];
	//���ļ������е����ݣ������������
	this->init_Emp();
	//���Դ���
	/*for (int  i = 0; i < this->m_EmpNum; i++)
	{
		cout << "ְ����ţ�" << this->m_EmArray[i]->m_Id
			<< "������" << this->m_EmArray[i]->m_Name
			<< "���ű��" << this->m_EmArray[i]->m_DeptId << endl;
	}*/
 }
//չʾ�˵�
void WorkerManager::Show_Menu()
{
	cout << "***************************************" << endl;
	cout << "*******��ӭʹ��ְ������ϵͳ��********" << endl;
	cout << "***********0.�˳�������� *************" << endl;
	cout << "***********1.����ְ����Ϣ *************" << endl;
	cout << "***********2.��ʾְ����Ϣ *************" << endl;
	cout << "***********3.ɾ����ְְ�� *************" << endl;
	cout << "***********4.�޸�ְ����Ϣ *************" << endl;
	cout << "***********5.����ְ����Ϣ *************" << endl;
	cout << "***********6.���ձ������ *************" << endl;
	cout << "***********7.��������ĵ� *************" << endl;
	cout << "***************************************" << endl;
	cout << endl;
}
//�˳�ϵͳ
void WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
//���ְԱ
void  WorkerManager::Add_Emp()
{
	cout << "������ְ������" << endl;
	int addNum = 0;     //�����û�����������
	cin >> addNum;
	if (addNum>0)
	{
		//�����¿ռ��С
		int newSize = this->m_EmpNum + addNum;
		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];  //�¿ռ�����=ԭ����¼����+��������
		//��ԭ�ռ������ݴ�ŵ��¿ռ���
		if (this->m_EmArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmArray[i];
			}
		}
		//���������
		for (int i = 0; i < addNum; i++)
		{
			int id;                   //ְ�����
			string name;        //ְ������
			int dSelect;          //����ѡ��
			cout << "�������" << i + 1 << "����ְ����ţ�" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "����ְ��������" << endl;
			cin >> name;
			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
				case 1:    //��ͨԱ��
					worker = new Employee(id, name, 1);
					break;
				case 2:     //����
					worker = new Manager(id, name, 2);
					break;
				case 3:     //�ϰ�
					worker = new Boss(id, name, 3);
					break;
			    default:
				    break; 
			}
			newSpace[this->m_EmpNum + i] = worker;
		}
		//�ͷ�ԭ�пռ�
		delete[]this->m_EmArray;
		//�����¿ռ��ָ��
		this->m_EmArray = newSpace;
		//�����µĸ���
		this->m_EmpNum = newSize;
		//��ʾ��Ϣ
		cout << "�ɹ����" << addNum << "��ְ������" << endl;
		this->Save();      //��������
	}
	else
	{
		cout << "��������" << endl;
	}
	system("pause");
	system("cls");
}
//�����ļ�
void WorkerManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);     //������ķ�ʽ���ļ���д�ļ�
	//����д���ļ�
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
		//��¼����
		num++;
	}
	ifs.close();
	return num; 
}
//��ʼ��ְ������
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
		//���ݲ�ͬ�Ĳ���Id������ͬ����
		if (dId == 1)  //1.��ͨԱ��
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId==2) //2.����
		{
			worker = new Manager(id, name, dId);
		}
		else   //�ܲ�
		{
			worker = new Boss(id, name, dId);
		}
		//�����������
		this->m_EmArray[index] = worker;
		index++;
	}
}
//��ʾְ��
void WorkerManager::Show_Emp()
{
	if (!this->m_FileIsEmpty)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//����
			/*cout << "ְ����ţ�" << this->m_EmArray[i]->m_Id;
			cout << "������" << this->m_EmArray[i]->m_Name;
			cout << "���ű��" << this->m_EmArray[i]->m_DeptId << endl;*/
			//���ö�̬�ӿ�
			this->m_EmArray[i]->showInfo();
		}
	}
	else
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	system("pause");
	system("cls");
}
//�ж�ְ���Ƿ����
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
//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	//�ж�ְ���Ƿ����
	int id=0;
	cout << "��������Ҫɾ����ְ����ţ�" << endl;
	cin>> id;
	int ret = this->IsExist(id);
	if (ret!=-1)
	{
		for (int i = ret; i < this->m_EmpNum-1  ; i++)
		{
			this->m_EmArray[i] = this->m_EmArray[i + 1];
		}
		this->m_EmpNum--;  //���������м�¼��Ա����
		this->Save();   //�����ļ�����
		cout << "��ְ���Գɹ�ɾ��" << endl;
	}
	else
	{
		cout<<"ɾ��ʧ�ܣ�ְ��������"<<endl;
	}
	system("pause");
	system("cls");
}
//�޸�ְ��
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�������" << endl;
	}
	else
	{
		//�ж�ְ���Ƿ����
		int id = 0;
		cout << "��������Ҫ�޸ĵ�ְ����ţ�" << endl;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret!=-1)
		{
			delete this->m_EmArray[ret];
			int new_Id = 0;
			string new_Name="";
			int dSelect = 0;
			cout << "�鵽��" <<id<<"��ְ������������ְ���ţ�"<< endl;
			cin >> new_Id;
			cout << "��������������" << endl;
			cin >> new_Name;
			cout << "�������λ��1����ְͨ����2������3���ϰ�" << endl;
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
			this->m_EmArray[ret] = worker;   //�������ݵ�������
			cout << "�޸ĳɹ�!" << endl;
		}
		else
		{
			cout << "�޸�ʧ�ܣ�δ�ҵ���ְ��!" << endl;
		}
		this->Save(); //�������ݵ��ļ�
	}
	system("pause");
	system("cls");
}
//����ְ��
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�������" << endl;
	}
	else
	{
		//�ж�ְ���Ƿ����
		cout << "��������ҵķ�ʽ��1��������ְ����Ų��ң�2����������������" << endl;
		int slect = 0;
		cin >> slect;
		switch (slect)
		{
		case 1: 
		    {
			    cout << "������Ҫ���ҵ�ְ�����" << endl;
			    int id = 0;
			    cin >> id;
			    int ret = this->IsExist(id);
			    if (ret != -1)
			    {
				    cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				    this->m_EmArray[ret]->showInfo();
			    }
			    else
			    {
				    cout << "���޴��ˣ�" << endl;
			    }
			    break;
		    }
		case 2:
		    {
			    string  name;
			    cout << "��������ҵ�������" << endl;
			    cin >> name;
			    bool flag = false; //���ҵ��ı�־
			    for (int i = 0; i < this->m_EmpNum; i++)
			    {
				    if (m_EmArray[i]->m_Name == name)
				    {
					    cout << "���ҳɹ���ְ�����Ϊ��"
						        << m_EmArray[i]->m_Id
						        << "�ŵ���Ϣ���£�" << endl;
					    flag = true;
					    this->m_EmArray[i]->showInfo();
				    }
				    else
				    {
					cout << "���޴��ˣ�" << endl;
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
		cout << "�ļ�������" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��������ҵķ�ʽ��1������ְ����Ž�������2���������������н���" << endl;
		int slect = 0;
		cin >> slect;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrmax= i;
			for (int  j = i+1; j < this->m_EmpNum; j++)
			{
				switch (slect)
				{
				case 1:  //����
					if (this->m_EmArray[minOrmax]->m_Id > m_EmArray[j]->m_Id)
					{
						minOrmax = j;
					}
					break;
				case 2:  //����
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
		cout << "����ɹ����������Ϊ��" << endl;
		this->Save(); //��������
		this->Show_Emp();  //��ʾ������
	}
	system("pause");
	system("cls");
}
//����ļ�
void WorkerManager::Clean_File()
{
	cout << "ȷ����գ���1��ȷ�ϣ�2������" << endl;
	int select = 0;
	cin >> select;
	if (select==1)
	{
		//��ģʽ  ios::trunc
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
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}
WorkerManager::~WorkerManager()
 {
	if (this->m_EmArray!=NULL)
	{
		//ɾ��������ÿ��ְ������
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmArray[i] != NULL)
			{
				delete this->m_EmArray[i];
			}
		}
		//ɾ����������ָ��
		delete[] this->m_EmArray;
		this->m_EmArray = NULL;
	}
 }