/*************************************************
Copyright(C), 1988-1999, HuLixin.
Author:������      Version:1.0       Date:2017-11-26 
Description:������׺���ʽ�ַ�������������Ŀǰֻ������+��-��*��/��%���ݴη�"^" 
History:
1. Date:
Author:
Modification:
2. ...
*************************************************/

#pragma once
#include "MyOperator.h"

#define ZERO_PRIORITY 0
#define ONE_PRIORITY 1
#define TWO_PRIORITY 2
#define THREE_PRIORITY 3
#define FOUR_PRIORITY 4
#define FIVE_PRIORITY 5

class CalculatorComplier
{
private:
	static MyOperator cs_operator_priority;//���������ȼ�
	CArray<CString> m_infix_expression;//���������������ʷ��¼�����ʽ�����
	
public: 
	CalculatorComplier();
	~CalculatorComplier();

	static CString FindOperatorPos(CString s,int startPos);//�ڱ��ʽ���ҵ���������λ��
	static void InfixToPostfix(CString infixExpression, CArray<CString>& postfixExpression);//��׺���ʽתΪ��׺���ʽ
	double Compute(CString infixExpression);//������׺���ʽ��������
	CString GetInfixExpression(int index);//����index��ȡ��ʷ��¼
	int GetFormulaNumber();//�����ʷ���㹫ʽ��������С
};