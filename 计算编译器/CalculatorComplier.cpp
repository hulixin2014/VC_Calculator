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
Description:���ַ���s���ҵ��ַ�����������Ԫ�صĵ�һ��λ��    
Input:
	s:��Ѱ�ҵ��ַ���
	stringArray:�ַ�������
	startPos:Ѱ�ҵĿ�ʼλ��
Return:
	CString:����Ѱ�ҵ��ĵ�һ��Ԫ��λ�ã�ʧ���򷵻�-1
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
Description:����׺���ʽת��Ϊ��׺���ʽ
Input:
	infixExpression:��׺���ʽ
	postfixExpression:��׺���ʽת����ĺ�׺���ʽ
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
		//������������
		if (pos != 0)
		{
			CString a1 = infixExpression.Left(pos);
			postfixExpression.Add(infixExpression.Left(pos));
		}
		//����������
		if (operator_stack.IsEmpty())
		{
			operator_stack.Add(operator_string);
		}
		else
		{
			//���������ŵ���������ջ�ķ���ֱ�����������ţ��������������
			if (operator_string == ")")
			{
				while (operator_stack[operator_stack.GetCount() - 1] != "(")
				{
					postfixExpression.Add(operator_stack[operator_stack.GetCount() - 1]);
					operator_stack.RemoveAt(operator_stack.GetCount() - 1);
				}
				operator_stack.RemoveAt(operator_stack.GetCount() - 1);
			}
			//��������������
			else 
			{
				while (true)
				{
					int* priority_stack;
					cs_operator_priority.m_operator.Lookup(operator_stack[operator_stack.GetCount() - 1],(void*&)priority_stack);
					int a = *priority_stack;  //�鿴����ֵ
					int* priority;
					cs_operator_priority.m_operator.Lookup(operator_string, (void*&)priority);
					//�ж��Ƿ�Ϊ������
					bool is_left_brackets = operator_stack[operator_stack.GetCount() - 1] == _T("(");
					//����������ߵȼ��ķ��Ż���ջΪ�ջ�������ջ����һ������Ϊ������
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
	//���������в�����֮�󣬴������һ����������ջ�еĲ�����
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
Description:����׺���ʽת��Ϊ��׺���ʽ
Input:
	infixExpression:��׺���ʽ
Return:
	(double):����ֵ
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
		//��ջ��Ԫ�ظ���ֻ��һ����ֻ���е��������ж�
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
		//��ջ��Ԫ�ظ�������1���Ϳ��ܽ���˫�������ļ���
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
	//��ʽ�Ӻͼ��������浽�ڴ���
	CString formula_result;
	formula_result.Format(_T("%s=%f"), infixExpression, operator_stack[0]);
	m_infix_expression.Add(formula_result);
	return operator_stack[0];
}

/*************************************************
Description:����׺���ʽת��Ϊ��׺���ʽ
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
