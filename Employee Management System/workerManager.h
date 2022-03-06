#pragma once   //��ֹͷ�ļ��ظ�����
#include<iostream>
#include<worker.h>
#include<fstream>
#define FILENAME "emFile.txt"
using namespace std;

class WorkerManager
{
public:
	//���캯��
	WorkerManager();
	//��¼�ļ��е�����
	int m_EmpNum;
	//ְ������ָ��
	Worker** m_EmArray;
	//��־�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;
	//ͳ������
	int get_EmpNum();
	//չʾ�˵�
	void Show_Menu();
	//�����ļ�
	void Save();
	//���ְ��
	void Add_Emp();
	//��ʼ��Ա��
	void init_Emp();
	//��ʾְ��
	void Show_Emp();
	//�ж�ְ������
	int IsExist(int id);
	//ɾ��ְ��
	void Del_Emp();
	//�޸�ְ��
	void Mod_Emp();
	//����ְ��
	void Find_Emp();
	//�˳�ϵͳ
	void exitSystem();
	//����
	void sort_Emp();
	//����ļ�
	void Clean_File();
	//��������
	~WorkerManager();
};