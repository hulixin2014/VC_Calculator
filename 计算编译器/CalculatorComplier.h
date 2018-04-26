/*************************************************
Copyright(C), 1988-1999, HuLixin.
Author:胡立新      Version:1.0       Date:2017-11-26 
Description:根据中缀表达式字符串计算出结果，目前只能适用+、-、*、/、%和幂次方"^" 
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
	static MyOperator cs_operator_priority;//操作符优先级
	CArray<CString> m_infix_expression;//保存计算出结果的历史记录，表达式：结果
	
public: 
	CalculatorComplier();
	~CalculatorComplier();

	static CString FindOperatorPos(CString s,int startPos);//在表达式中找到操作符的位置
	static void InfixToPostfix(CString infixExpression, CArray<CString>& postfixExpression);//中缀表达式转为后缀表达式
	double Compute(CString infixExpression);//根据中缀表达式计算出结果
	CString GetInfixExpression(int index);//根据index获取历史记录
	int GetFormulaNumber();//获得历史计算公式的数量大小
};