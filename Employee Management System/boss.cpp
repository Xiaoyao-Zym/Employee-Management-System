#include<boss.h>
#include<iostream>
Boss::Boss(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}
void Boss::showInfo()
{
	cout << "ְ����ţ�" << this->m_Id;
	cout << "\tְ��������" << this->m_Name;
	cout << "\t��λ��" << this->getDeptName();
	cout << "\t��λְ�𣺹���˾��С����" << endl;
}
string Boss::getDeptName()
{
	return string("�ܲ�");
}