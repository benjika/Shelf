
// ShelfDeBestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShelfDeBest.h"
#include "ShelfDeBestDlg.h"
#include "afxdialogex.h"

#include "Shelf.h"
#include "Book.h"
#include "Basket.h"
#include "Movie.h"
#include "Video.h"
#include "TvShow.h"

#include <iostream>
#include <map>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


map<CString,&Book> basket_book;
//map<CString,&Movie> basket_movie;
//map<CString,&TvShow> basket_tvshow;


//Basket<Book> basket_book;
//Basket<Movie> basket_movie;
//Basket<TvShow> basket_TvShow;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CShelfDeBestDlg dialog




CShelfDeBestDlg::CShelfDeBestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShelfDeBestDlg::IDD, pParent)
	, m_strTextCtrl_Type(_T(""))
	, m_strTextCtrl_Title(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShelfDeBestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_comboBoxCtrl_Type);
	DDX_CBString(pDX, IDC_COMBO_TYPE, m_strTextCtrl_Type);
	DDX_Control(pDX, IDC_EDIT_TITLE, m_editCtrl_Title);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTextCtrl_Title);
}

BEGIN_MESSAGE_MAP(CShelfDeBestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CShelfDeBestDlg::OnCbnSelchangeComboType)
	ON_EN_CHANGE(IDC_EDIT_TITLE, &CShelfDeBestDlg::OnEnChangeEditTitle)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CShelfDeBestDlg::OnBnClickedButtonAdd)
END_MESSAGE_MAP()


// CShelfDeBestDlg message handlers

BOOL CShelfDeBestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CString str;

	str.Format(_T("Book"));
	m_comboBoxCtrl_Type.AddString(str);

	str.Format(_T("Movie"));
	m_comboBoxCtrl_Type.AddString(str);

	str.Format(_T("TvShow"));
	m_comboBoxCtrl_Type.AddString(str);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShelfDeBestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CShelfDeBestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CShelfDeBestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CShelfDeBestDlg::OnCbnSelchangeComboType()
{
	// TODO: Add your control notification handler code here
	m_comboBoxCtrl_Type.GetLBText(m_comboBoxCtrl_Type.GetCurSel(), m_strTextCtrl_Type);
	UpdateData(FALSE);

}


void CShelfDeBestDlg::OnEnChangeEditTitle()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	CString str = _T("");
	m_editCtrl_Title.GetWindowTextW(str);
	if (!str.IsEmpty())
		m_strTextCtrl_Title = str;
	else
		m_strTextCtrl_Title = _T("Write Something");
	UpdateData(FALSE);

}



void CShelfDeBestDlg::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here

	//LPSTR OriginChar=  m_strTextCtrl_Title.GetBuffer(m_strTextCtrl_Title.GetLength());

	CStringA strA(m_strTextCtrl_Type); // a helper string
	LPCSTR ptr = strA;

	if(m_strTextCtrl_Type == "Book")
	{
		//if(!basket_book.exists(m_strTextCtrl_Title))5
		Book *book =new Book(m_strTextCtrl_Title);
		basket_book.insert(std::pair<CString,Book>(m_strTextCtrl_Title,*book));

		//else AfxMessageBox(_T("This book already exists"));
	}

	else if(m_strTextCtrl_Type == "Movie")
	{
		//if(!basket_movie.exists(m_strTextCtrl_Title))
		//basket_movie.insert(m_strTextCtrl_Title);

		//else AfxMessageBox(_T("This movie already exists"));
	}

	else
	{
		//if(!basket_TvShow.exists(m_strTextCtrl_Title))
		//.insert(m_strTextCtrl_Title);

		//else AfxMessageBox(_T("This TvShow already exists"));
	}
}
