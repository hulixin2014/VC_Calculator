
// CalculatorDlg.h: 头文件
//

#pragma once
#include "afxcmn.h"
#include "CalculatorComplier.h"


// CCalculatorDlg 对话框
class CCalculatorDlg : public CDialog
{
// 构造
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedOk();
//	afx_msg void OnBnClickedButton5();
	afx_msg void OnLbnSelchangeList1();
	CRichEditCtrl m_RichEdit;
protected:
	CString m_formula;
	CalculatorComplier calculator;
	// 查询索引
	int search_index;
	// 是否重新输入
	bool is_reinput;

	// 发送Unicode编码的字符
	void SendUnicode(wchar_t data);
public:
	// 计算结果
	CString m_result;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButtonDot();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonSub();
	afx_msg void OnBnClickedButtonMul();
	afx_msg void OnBnClickedButtonDiv();
	afx_msg void OnBnClickedButtonMod();
	afx_msg void OnBnClickedButtonPow();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonCln();
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
