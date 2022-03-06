#include<manager.h>
#include<iostream>
Manager::Manager(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}
void Manager::showInfo()
{
	cout << "职工编号：" << this->m_Id;
	cout << "\t职工姓名：" << this->m_Name;
	cout << "\t岗位：" << this->getDeptName();
	cout << "\t岗位职责：完成老板交给的任务，并下发任务给员工" << endl;
}
string Manager::getDeptName()
{
	return string("经理");
}