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
	cout << "职工编号：" << this->m_Id;
	cout << "\t职工姓名：" << this->m_Name;
	cout << "\t岗位：" << this->getDeptName();
	cout << "\t岗位职责：管理公司大小事务" << endl;
}
string Boss::getDeptName()
{
	return string("总裁");
}