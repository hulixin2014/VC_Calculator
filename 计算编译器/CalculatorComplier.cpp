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

#include "stdafx.h"
#include "CalculatorComplier.h"


MyOperator CalculatorComplier::cs_operator_priority;

CalculatorComplier::CalculatorComplier()
{
}


CalculatorComplier::~CalculatorComplier()
{
}

/*************************************************
Description:在字符串s中找到字符串数组任意元素的第一个位置    
Input:
	s:被寻找的字符串
	stringArray:字符串数组
	startPos:寻找的开始位置
Return:
	CString:返回寻找到的第一个元素位置，失败则返回-1
*************************************************/
CString CalculatorComplier::FindOperatorPos(CString s, int startPos)
{
	int length = cs_operator_priority.m_array_operator.GetSize();
	CString a = cs_operator_priority.m_array_operator[0];
	int index = length;
	CString result;
	for (int i = 0; i < length; i++)
	{
		int pos = s.Find(cs_operator_priority.m_array_operator[i], startPos);
		if (pos!=-1 && pos < index)
		{
			index = pos;
			result.Format(_T("%s_%d"), cs_operator_priority.m_array_operator[i],index);
		}
	}
	if (index < length)
	{
		return result;
	}
	else 
	{
		return CString("error");
	}
}

/*************************************************
Description:将中缀表达式转化为后缀表达式
Input:
	infixExpression:中缀表达式
	postfixExpression:中缀表达式转化后的后缀表达式
Return:
*************************************************/
void CalculatorComplier::InfixToPostfix(CString infixExpression, CArray<CString>& postfixExpression)
{
	int pos = 0;
	CArray<CString,CString> operator_stack;
	CString result = FindOperatorPos(infixExpression, pos);
	while (result != "error")
	{
		int split_pos = result.Find(_T("_"));
		CString operator_string = result.Left(split_pos);
		int pos = _ttoi(result.Mid(split_pos + 1));
		//如果有左操作数
		if (pos != 0)
		{
			CString a1 = infixExpression.Left(pos);
			postfixExpression.Add(infixExpression.Left(pos));
		}
		//操作符处理
		if (operator_stack.IsEmpty())
		{
			operator_stack.Add(operator_string);
		}
		else
		{
			//遇到右括号的情况，输出栈的符号直到遇到左括号，但不输出左括号
			if (operator_string == ")")
			{
				while (operator_stack[operator_stack.GetCount() - 1] != "(")
				{
					postfixExpression.Add(operator_stack[operator_stack.GetCount() - 1]);
					operator_stack.RemoveAt(operator_stack.GetCount() - 1);
				}
				operator_stack.RemoveAt(operator_stack.GetCount() - 1);
			}
			//遇到其他操作符
			else 
			{
				while (true)
				{
					int* priority_stack;
					cs_operator_priority.m_operator.Lookup(operator_stack[operator_stack.GetCount() - 1],(void*&)priority_stack);
					int a = *priority_stack;  //查看变量值
					int* priority;
					cs_operator_priority.m_operator.Lookup(operator_string, (void*&)priority);
					//判断是否为左括号
					bool is_left_brackets = operator_stack[operator_stack.GetCount() - 1] == _T("(");
					//如果遇到更高等级的符号或者栈为空或者遇到栈顶第一个符号为左括号
					if (*priority > *priority_stack || operator_stack.IsEmpty() || is_left_brackets)
					{
						operator_stack.Add(operator_string);
						break;
					}
					else
					{
						postfixExpression.Add(operator_stack[operator_stack.GetCount() - 1]);
						operator_stack.RemoveAt(operator_stack.GetCount() - 1);
						if (operator_stack.IsEmpty())
						{
							operator_stack.Add(operator_string);
							break;
						}
					}
				}
			}
		}
		pos += +operator_string.GetLength();
		infixExpression = infixExpression.Mid(pos);
		result = FindOperatorPos(infixExpression, 0);
	}
	//处理完所有操作符之后，处理最后一个操作数和栈中的操作符
	if (pos != infixExpression.GetLength())
	{
		postfixExpression.Add(infixExpression.Mid(pos));
	}
	while (!operator_stack.IsEmpty())
	{
		postfixExpression.Add(operator_stack[operator_stack.GetCount() - 1]);
		operator_stack.RemoveAt(operator_stack.GetCount() - 1);
	}
}

/*************************************************
Description:将中缀表达式转化为后缀表达式
Input:
	infixExpression:中缀表达式
Return:
	(double):计算值
*************************************************/
double CalculatorComplier::Compute(CString infixExpression)
{
	CArray<CString> postfixExpression;
	InfixToPostfix(infixExpression, postfixExpression);
	CArray<double, double> operator_stack;
	int length = postfixExpression.GetCount();
	operator_stack.Add(_ttof(postfixExpression[0]));
	for (int i = 1; i < length; i++)
	{
		int stack_num = operator_stack.GetCount();
		//当栈的元素个数只有一个，只进行单操作数判断
		if (stack_num == 1)
		{
			CString value = cs_operator_priority.JudgeAndCal(postfixExpression[i], operator_stack[stack_num-1], 0);
			if (value == "value")
			{
				operator_stack.Add(_ttof(postfixExpression[i]));
			}
			else
			{
				int index = value.Find('-');
				operator_stack[stack_num-1] = _ttof(value.Left(index));
			}
		}
		//当栈的元素个数大于1，就可能进行双操作数的计算
		else
		{
			CString value = cs_operator_priority.JudgeAndCal(postfixExpression[i], operator_stack[stack_num-2], operator_stack[stack_num - 1]);
			if (value == "value")
			{
				operator_stack.Add(_ttof(postfixExpression[i]));
			}
			else
			{
				int index = value.Find('_');
				operator_stack[stack_num - 2] = _ttof(value.Left(index));
				double a2 = _ttof(value.Left(index));
				operator_stack.RemoveAt(stack_num - 1);
			}
		}
	}
	//将式子和计算结果保存到内存中
	CString formula_result;
	formula_result.Format(_T("%s=%f"), infixExpression, operator_stack[0]);
	m_infix_expression.Add(formula_result);
	return operator_stack[0];
}

/*************************************************
Description:将中缀表达式转化为后缀表达式
Input:
Return:
*************************************************/
CString CalculatorComplier::GetInfixExpression(int index)
{
	if (index < 0 || index >= m_infix_expression.GetSize())
	{
		return CString("error=index is ouf of range");
	}
	return m_infix_expression[index];
}

int CalculatorComplier::GetFormulaNumber()
{
	return m_infix_expression.GetCount();
}
