#pragma once
#include<iostream>
using namespace std;
#include<worker.h>

//������
class Boss : public Worker
{
public:
	Boss(int id, string name, int dId);
	//��ʾ������Ϣ
	virtual void showInfo();
	//��ȡְ����λ����
	virtual string getDeptName();
};