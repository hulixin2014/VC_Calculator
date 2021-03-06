
// CalculatorDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorDlg 对话框



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CALCULATOR_DIALOG, pParent)
	, m_formula(_T(""))
	, m_result(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Text, m_formula);
	DDX_Text(pDX, IDC_RESULT, m_result);
	DDX_Control(pDX, IDC_Text, m_RichEdit);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BUTTON3, &CCalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDOK, &CCalculatorDlg::OnBnClickedOk)
//	ON_BN_CLICKED(IDC_BUTTON5, &CCalculatorDlg::OnBnClickedButton5)
ON_BN_CLICKED(IDC_BUTTON0, &CCalculatorDlg::OnBnClickedButton0)
ON_BN_CLICKED(IDC_BUTTON_DOT, &CCalculatorDlg::OnBnClickedButtonDot)
ON_BN_CLICKED(IDC_BUTTON1, &CCalculatorDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON2, &CCalculatorDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON3, &CCalculatorDlg::OnBnClickedButton3)
ON_BN_CLICKED(IDC_BUTTON4, &CCalculatorDlg::OnBnClickedButton4)
ON_BN_CLICKED(IDC_BUTTON5, &CCalculatorDlg::OnBnClickedButton5)
ON_BN_CLICKED(IDC_BUTTON6, &CCalculatorDlg::OnBnClickedButton6)
ON_BN_CLICKED(IDC_BUTTON7, &CCalculatorDlg::OnBnClickedButton7)
ON_BN_CLICKED(IDC_BUTTON8, &CCalculatorDlg::OnBnClickedButton8)
ON_BN_CLICKED(IDC_BUTTON9, &CCalculatorDlg::OnBnClickedButton9)
ON_BN_CLICKED(IDC_BUTTON_ADD, &CCalculatorDlg::OnBnClickedButtonAdd)
ON_BN_CLICKED(IDC_BUTTON_SUB, &CCalculatorDlg::OnBnClickedButtonSub)
ON_BN_CLICKED(IDC_BUTTON_MUL, &CCalculatorDlg::OnBnClickedButtonMul)
ON_BN_CLICKED(IDC_BUTTON_DIV, &CCalculatorDlg::OnBnClickedButtonDiv)
ON_BN_CLICKED(IDC_BUTTON_MOD, &CCalculatorDlg::OnBnClickedButtonMod)
ON_BN_CLICKED(IDC_BUTTON_POW, &CCalculatorDlg::OnBnClickedButtonPow)
ON_BN_CLICKED(IDC_BUTTON_DEL, &CCalculatorDlg::OnBnClickedButtonDel)
ON_BN_CLICKED(IDC_BUTTON_CLN, &CCalculatorDlg::OnBnClickedButtonCln)
//ON_WM_LBUTTONDBLCLK()
//ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CCalculatorDlg 消息处理程序

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCalculatorDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//传入数据
	UpdateData(TRUE);
	double result = calculator.Compute(m_formula);
	m_result.Format(_T("%f"), result);
	m_result.TrimRight('0');
	UpdateData(FALSE);
	search_index = calculator.GetFormulaNumber();
	is_reinput = true;
}

BOOL CCalculatorDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_UP:
			if (search_index >= 2)
			{
				int pos = calculator.GetInfixExpression(search_index-2).Find(_T("="));
				m_formula = calculator.GetInfixExpression(search_index-2).Left(pos);
				m_result = calculator.GetInfixExpression(search_index-2).Mid(pos + 1);
				m_result.TrimRight('0');
				search_index -= 1;
				UpdateData(FALSE);
			}
			break;
		case VK_DOWN:
			if (search_index <  calculator.GetFormulaNumber())
			{
				int pos = calculator.GetInfixExpression(search_index).Find(_T("="));
				m_formula = calculator.GetInfixExpression(search_index).Left(pos);
				m_result = calculator.GetInfixExpression(search_index).Mid(pos + 1);
				m_result.TrimRight('0');
				search_index += 1;
				UpdateData(FALSE);
			}
			break;
		case VK_LEFT:
			is_reinput = false; break;
		case VK_RIGHT:
			is_reinput = false; break;
		default:
			if (is_reinput)
			{
				m_RichEdit.SetSel(0, -1);
				m_RichEdit.Clear();
				is_reinput = false;
			}
			break;
		}
	}
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		is_reinput = false;
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CCalculatorDlg::OnBnClickedButton0()
{
	// TODO: 在此添加控件通知处理程序代码
    //模拟键盘在输入框输入
	m_RichEdit.SetFocus();
	keybd_event(96, 0, 0, 0);
	keybd_event(96, 0, KEYEVENTF_KEYUP, 0);
}


void CCalculatorDlg::OnBnClickedButtonDot()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEdit.SetFocus();
	keybd_event(110, 0, 0, 0);
	keybd_event(110, 0, KEYEVENTF_KEYUP, 0);
}


void CCalculatorDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEdit.SetFocus();
	keybd_event(97, 0, 0, 0);
	keybd_event(97, 0, KEYEVENTF_KEYUP, 0);
}


void CCalculatorDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEdit.SetFocus();
	keybd_event(98, 0, 0, 0);
	keybd_event(98, 0, KEYEVENTF_KEYUP, 0);
}


void CCalculatorDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEdit.SetFocus();
	keybd_event(99, 0, 0, 0);
	keybd_event(99, 0, KEYEVENTF_KEYUP, 0);
}


void CCalculatorDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEdit.SetFocus();
	keybd_event(100, 0, 0, 0);
	keybd_event(100, 0, KEYEVENTF_KEYUP, 0);
}


void CCalculatorDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEdit.SetFocus();
	keybd_event(101, 0, 0, 0);
	keybd_event(101, 0, KEYEVENTF_KEYUP, 0);
}


void CCalculatorDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEdit.SetFocus();
	keybd_event(102, 0, 0, 0);
	keybd_event(102, 0, KEYEVENTF_KEYUP, 0);
}


void CCalculatorDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEdit.SetFocus();
	keybd_event(103, 0, 0, 0);
	keybd_event(103, 0, KEYEVENTF_KEYUP, 0);
}


void CCalculatorDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEdit.SetFocus();
	keybd_event(104, 0, 0, 0);
	keybd_event(104, 0, KEYEVENTF_KEYUP, 0);
}


void CCalculatorDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEdit.SetFocus();
	keybd_event(105, 0, 0, 0);
	keybd_event(105, 0, KEYEVENTF_KEYUP, 0);
}


void CCalculatorDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEdit.SetFocus();
	keybd_event(107, 0, 0, 0);
	keybd_event(107, 0, KEYEVENTF_KEYUP, 0);
}


void CCalculatorDlg::OnBnClickedButtonSub()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEdit.SetFocus();
	keybd_event(109, 0, 0, 0);
	keybd_event(109, 0, KEYEVENTF_KEYUP, 0);
}


void CCalculatorDlg::OnBnClickedButtonMul()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEdit.SetFocus();
	keybd_event(106, 0, 0, 0);
	keybd_event(106, 0, KEYEVENTF_KEYUP, 0);
}


void CCalculatorDlg::OnBnClickedButtonDiv()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEdit.SetFocus();
	keybd_event(111, 0, 0, 0);
	keybd_event(111, 0, KEYEVENTF_KEYUP, 0);
}


void CCalculatorDlg::OnBnClickedButtonMod()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEdit.SetFocus();
	SendUnicode('%');
	
}


void CCalculatorDlg::OnBnClickedButtonPow()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEdit.SetFocus();
	SendUnicode('^');
}


void CCalculatorDlg::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEdit.SetFocus();
	keybd_event(8, 0, 0, 0);
	keybd_event(8, 0, KEYEVENTF_KEYUP, 0);
}


void CCalculatorDlg::OnBnClickedButtonCln()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RichEdit.SetFocus();
	m_RichEdit.SetSel(0, -1);
	m_RichEdit.Clear();
}

void CCalculatorDlg::SendUnicode(wchar_t data)
{
	INPUT input[2];
	memset(input, 0, 2 * sizeof(INPUT));

	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = 0;
	input[0].ki.wScan = data;
	input[0].ki.dwFlags = 0x4;//KEYEVENTF_UNICODE;  

	input[1].type = INPUT_KEYBOARD;
	input[1].ki.wVk = 0;
	input[1].ki.wScan = data;
	input[1].ki.dwFlags = KEYEVENTF_KEYUP | 0x4;//KEYEVENTF_UNICODE;  

	SendInput(2, input, sizeof(INPUT));
}