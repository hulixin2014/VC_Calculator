#pragma once
#include<afxcoll.h>
#include<math.h>

#define ZERO_PRIORITY 0
#define ONE_PRIORITY 1
#define TWO_PRIORITY 2
#define THREE_PRIORITY 3
#define FOUR_PRIORITY 4
#define FIVE_PRIORITY 5
#define SIX_PRIORITY 6

class MyOperator
{
public:
	CMapStringToPtr m_operator;
	CArray<CString> m_array_operator;
	MyOperator()
	{
		//the first priority
		m_operator.SetAt(_T("+"), new int(ONE_PRIORITY));
		m_operator.SetAt(_T("-"), new int(ONE_PRIORITY));
		//the second priority
		m_operator.SetAt(_T("*"), new int(TWO_PRIORITY));
		m_operator.SetAt(_T("/"), new int(TWO_PRIORITY));
		m_operator.SetAt(_T("%"), new int(TWO_PRIORITY));
		//the third priority
		m_operator.SetAt(_T("^"), new int(THREE_PRIORITY));
		//the fifth priority
		m_operator.SetAt(_T("("), new int(FIVE_PRIORITY));

		m_array_operator.Add(CString("+"));
		m_array_operator.Add(CString("-"));
		m_array_operator.Add(CString("*"));
		m_array_operator.Add(CString("/"));
		m_array_operator.Add(CString("%"));
		m_array_operator.Add(CString("^"));
		m_array_operator.Add(CString("("));
		m_array_operator.Add(CString(")"));
	}

	//判断是否为操作符，是则返回计算值，不是则返回"value"
	CString JudgeAndCal(CString str, double numberOne, double numberTwo)
	{
		CString value;
		if (str == "+")
		{
			double result = numberOne + numberTwo;
			value.Format(_T("%f_%d"), result, 2);
		}
		else if (str == "-")
		{
			double result = numberOne - numberTwo;
			value.Format(_T("%f_%d"), result, 2);
		}
		else if (str == "*")
		{
			double result = numberOne * numberTwo;
			value.Format(_T("%f_%d"), result, 2);
		}
		else if (str == "/")
		{
			double result = numberOne / numberTwo;
			value.Format(_T("%f_%d"), result, 2);
		}
		else if (str == "%")
		{
			double result = fmod(numberOne, numberTwo);
			value.Format(_T("%f_%d"), result, 2);
		}
		else if (str == "^")
		{
			double result = pow(numberOne,numberTwo);
			value.Format(_T("%f_%d"), result, 2);
		}
		else
		{
			value = "value";
		}
		return value;
	}

	~MyOperator()
	{

	}
};