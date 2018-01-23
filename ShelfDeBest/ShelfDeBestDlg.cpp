
// ShelfDeBestDlg.cpp : implementation file
//

#include "StdAfx.h"
#include "afxtempl.h"
#include "ShelfDeBest.h"
#include "ShelfDeBestDlg.h"
#include "afxdialogex.h"
#include <sstream>
#include  <iostream>
#include "Shelf.h"
#include "Book.h"

#include "Movie.h"
#include "Video.h"
#include "TvShow.h"
#include <map>
#include <stack>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


std::stack<CString> undone_actions;      //actions to redo
std::stack<CString> undone_titles_main; 
std::stack<CString> undone_types_main;
std::stack<CString> undone_titles_edit;
std::stack<CString> undone_types_edit;

std::stack<CString> done_actions;        //actions to undo
std::stack<CString> done_titles_main;
std::stack<CString> done_types_main;
std::stack<CString> done_titles_edit;
std::stack<CString> done_types_edit;

std::map<CString,Shelf*> basket;
std::map<CString,Shelf*> trash;

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
	, input_main_type(_T(""))
	, input_main_title(_T(""))
	, input_edit_title(_T(""))
	, input_edit_type(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShelfDeBestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_comboBoxCtrl_Type);
	DDX_CBString(pDX, IDC_COMBO_TYPE, input_main_type);
	DDX_Control(pDX, IDC_EDIT_TITLE, m_editCtrl_Title);
	DDX_Text(pDX, IDC_EDIT_TITLE, input_main_title);
	DDX_Control(pDX, IDC_EDIT_NEW_TITLE, m_editCtrl_Edit);
	DDX_Text(pDX, IDC_EDIT_NEW_TITLE, input_edit_title);
	DDX_Control(pDX, IDC_COMBO_TYPE_EDIT, m_comboBoxCtrl_edit);
	DDX_CBString(pDX, IDC_COMBO_TYPE_EDIT, input_edit_type);
}

BEGIN_MESSAGE_MAP(CShelfDeBestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CShelfDeBestDlg::OnCbnSelchangeComboType)
	ON_EN_CHANGE(IDC_EDIT_TITLE, &CShelfDeBestDlg::OnEnChangeEditTitle)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CShelfDeBestDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CShelfDeBestDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CShelfDeBestDlg::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_UNDO, &CShelfDeBestDlg::OnBnClickedButtonUndo)
	ON_BN_CLICKED(IDC_BUTTON_USE, &CShelfDeBestDlg::OnBnClickedButtonUse)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CShelfDeBestDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN_ALL, &CShelfDeBestDlg::OnBnClickedButtonCleanAll)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CShelfDeBestDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_REDO, &CShelfDeBestDlg::OnBnClickedButtonRedo)
	ON_BN_CLICKED(IDC_BUTTON_EXISTS, &CShelfDeBestDlg::OnBnClickedButtonExists)
	ON_BN_CLICKED(IDC_BUTTON_PRINT_ALL_BASKET, &CShelfDeBestDlg::OnBnClickedButtonPrintAllBasket)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE_EDIT, &CShelfDeBestDlg::OnCbnSelchangeComboTypeEdit)
	ON_EN_CHANGE(IDC_EDIT_NEW_TITLE, &CShelfDeBestDlg::OnEnChangeEditNewTitle)
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
	m_comboBoxCtrl_edit.AddString(str);
	m_comboBoxCtrl_Type.AddString(str);

	str.Format(_T("Movie"));
	m_comboBoxCtrl_edit.AddString(str);
	m_comboBoxCtrl_Type.AddString(str);

	str.Format(_T("TvShow"));
	m_comboBoxCtrl_edit.AddString(str);
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

void CShelfDeBestDlg::OnEnChangeEditNewTitle()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString str = _T("");
	m_editCtrl_Edit.GetWindowTextW(str);
	if (!str.IsEmpty())
		input_edit_title = str;
	else
		input_edit_title = _T("");
	UpdateData(FALSE);
}

void CShelfDeBestDlg::OnCbnSelchangeComboType()
{
	// TODO: Add your control notification handler code here
	m_comboBoxCtrl_Type.GetLBText(m_comboBoxCtrl_Type.GetCurSel(), input_main_type);
	UpdateData(FALSE);

}

void CShelfDeBestDlg::OnCbnSelchangeComboTypeEdit()
{
	// TODO: Add your control notification handler code here
	m_comboBoxCtrl_edit.GetLBText(m_comboBoxCtrl_edit.GetCurSel(), input_edit_type);
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
		input_main_title = str;
	else
		input_main_title = _T("");
	UpdateData(FALSE);

}

void CShelfDeBestDlg::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here


	if(MainInputIsEmpty()){ return;}

	CString toPrint = _T("");

	if(Add(input_main_title, input_main_type))
	{
		toPrint += _T("ADD SUCCEED:\nNew ");
		toPrint += input_main_type;
		toPrint += " ";
		toPrint += input_main_title;
		toPrint += _T(" added to Basket");

		CleanAllRedo();

		done_actions.push(_T("Add"));
		done_titles_main.push(input_main_title);
		done_types_main.push(input_main_type);
	}
	else
	{
		toPrint += _T("ADD FAILED:\n");
		toPrint += input_main_type;
		toPrint += _T(" ");
		toPrint += input_main_title;
		toPrint += _T(" already exist in the basket");

	}
	AfxMessageBox(toPrint);
}

void CShelfDeBestDlg::OnBnClickedButtonDelete()
{

	// TODO: Add your control notification handler code here

	if(MainInputIsEmpty()) { return; }

	CString toPrint = _T("");

	if(Delete(input_main_title))
	{
		toPrint += _T("DELETE SUCCEED\n");
		toPrint += input_main_title;
		toPrint += _T(" moved from Basket to Trash");

		done_actions.push(_T("Delete"));
		done_titles_main.push(input_main_title);
		done_types_main.push(input_main_type);

		CleanAllRedo();
	}
	else
	{
		toPrint += _T("DELETE Failed\nThe ");
		toPrint += input_main_type;
		toPrint += " ";
		toPrint += input_main_title;
		toPrint += _T(" does not exists in the Basket\nNo delete was executed.");
	}

	AfxMessageBox(toPrint);
}


void CShelfDeBestDlg::OnBnClickedButtonEdit()
{

	if(MainInputIsEmpty()) { return; }
	if(EditInputIsEmpty()) { return; }

	if(basket.count(input_edit_title)>0)
	{
		CString toPrint = _T("EDIT FAILE\nCan't edit to new title ");
		toPrint += input_edit_title;
		toPrint +=_T("\nAn item with this title already exists.");
		AfxMessageBox(toPrint);
		return;
	}

	CString toPrint = _T("");

	if(Edit(input_main_title , input_edit_title , input_edit_type))
	{

		toPrint += _T("EDIT SUCEED\nThe ");
		toPrint += input_main_type;
		toPrint += " ";
		toPrint += input_main_title;
		toPrint += " edited to the ";
		toPrint += input_edit_type;
		toPrint += _T(" ");
		toPrint += input_edit_title;

		done_actions.push(_T("Edit"));
		done_titles_main.push(input_main_title);
		done_types_main.push(input_main_type);
		done_titles_edit.push(input_edit_title);
		done_types_edit.push(input_edit_type);

		CleanAllRedo();

	}
	else
	{
		toPrint += _T("EDIT FAILED\n");
		toPrint += input_main_type;
		toPrint += _T(" ");
		toPrint += input_main_title;
		toPrint += _T(" is not in the basket and wasn't edited to ");
		toPrint += input_edit_title;
	}

	AfxMessageBox(toPrint);
}


void CShelfDeBestDlg::OnBnClickedButtonUndo()
{
	// TODO: Add your control notification handler code here

	if(done_actions.empty())
	{
		AfxMessageBox(_T("No actions to Undo"));
		return;
	}

	bool undo_succeed = true;
	CString action_to_reverse = done_actions.top();
	CString title_to_reverse = done_titles_main.top();
	CString type_to_reverse = done_types_main.top();
	CString toPrint = _T("");

	if(action_to_reverse == "Add" )
	{
		if(Delete(title_to_reverse))
		{
			toPrint += _T("UNDO SUCCEED\n");
			toPrint += title_to_reverse;
			toPrint += _T(" UnAdded and moved to Trash");
			action_to_reverse = "Delete";
		}
		else
		{
			toPrint += _T("UNDO failed: ");
			toPrint += title_to_reverse;
			toPrint += _T(" was not found in Basket and was not UnAdded");
			undo_succeed = false;
		}
	}

	else if(action_to_reverse == "Delete")
	{
		if(trash.count(title_to_reverse)>0){
			if(Add(title_to_reverse , type_to_reverse))
			{
				trash.erase(title_to_reverse);
				toPrint += _T("UNDO SUCEED\n");
				toPrint += title_to_reverse;
				toPrint += _T(" UnDeleted and moved back to Basket");
				action_to_reverse = "Add";
			}
			else
			{
				toPrint += _T("UNDO FAILED\n");
				toPrint += title_to_reverse;
				toPrint += _T(" is already in Basket and was not UnAdded");
				undo_succeed = false;
			}

		}
		else
		{
			toPrint += _T("UNDO Failed\n");
			toPrint += title_to_reverse;
			toPrint += _T(" was not found in Trash and was not UnDeleted");
			undo_succeed = false;
		}
	}

	else if(action_to_reverse == "Edit")
	{
		CString title_new = done_titles_main.top();
		CString type_new = done_types_main.top();
		CString title_old = done_titles_edit.top();
		CString type_old = done_types_edit.top();

		if(basket.count(title_new)>0)
		{
			toPrint += _T("UNDO FAILED\nCan't ReEdit to title ");
			toPrint += title_new;
			toPrint +=_T("/nAn item with this title already in Basket");
			undo_succeed = false;
		}

		else if(Edit(title_old , title_new , type_new))
		{															

			toPrint += _T("UNDO SUCEED\nThe ");
			toPrint += type_old;
			toPrint += _T(" ");
			toPrint += title_old;
			toPrint += " UnEdited to the ";
			toPrint += type_new;
			toPrint += _T(" ");
			toPrint += title_new;

			undone_titles_edit.push(title_old);
			undone_types_edit.push(type_old);
			done_titles_edit.pop();
			done_types_edit.pop();
		}
		else
		{

			toPrint += _T("UNDO FAILED\n");
			toPrint += type_old;
			toPrint += _T(" ");
			toPrint += title_old;
			toPrint += _T(" is not in the basket and wasn't edited to ");
			toPrint += type_new;
			toPrint += " ";
			toPrint += title_new;
			undo_succeed = false;
		}

	}

	if(undo_succeed)
	{
		undone_actions.push(action_to_reverse);
		undone_titles_main.push(title_to_reverse);
		undone_types_main.push(type_to_reverse);

		done_actions.pop();
		done_titles_main.pop();
		done_types_main.pop();
	}

	AfxMessageBox(toPrint);

}


void CShelfDeBestDlg::OnBnClickedButtonRedo()
{

	if(undone_actions.empty())
	{
		AfxMessageBox(_T("No actions to Redo"));
		return;
	}

	bool redo_succeed = true;
	CString action_to_reverse = undone_actions.top();
	CString title_to_reverse = undone_titles_main.top();
	CString type_to_reverse = undone_types_main.top();
	CString toPrint = _T("");

	if(action_to_reverse == "Add" )
	{
		if(Delete(title_to_reverse))
		{
			toPrint += _T("ReDO SUCCEED\n");
			toPrint += title_to_reverse;
			toPrint += _T(" ReAdded and moved to Trash");
			action_to_reverse = "Delete";
		}
		else
		{
			toPrint += _T("UNDO failed: ");
			toPrint += title_to_reverse;
			toPrint += _T(" was not found in Basket and was not UnAdded");
			redo_succeed = false;
		}
	}

	else if(action_to_reverse == "Delete")
	{
		if(trash.count(title_to_reverse)>0){
			if(Add(title_to_reverse , type_to_reverse))
			{
				trash.erase(title_to_reverse);
				toPrint += _T("REDO SUCEED\n");
				toPrint += title_to_reverse;
				toPrint += _T(" ReDeleted and moved back to Basket");
				action_to_reverse = "Add";
			}
			else
			{
				toPrint += _T("REDO FAILED\n");
				toPrint += title_to_reverse;
				toPrint += _T(" is already in Basket and was not ReAdded");
				redo_succeed = false;
			}

		}
		else
		{
			toPrint += _T("REDO Failed\n");
			toPrint += title_to_reverse;
			toPrint += _T(" was not found in Trash and was not ReDeleted");
			redo_succeed = false;
		}
	}

	else if(action_to_reverse == "Edit")
	{
		CString title_new = undone_titles_edit.top();
		CString type_new = undone_types_edit.top();
		CString title_old = undone_titles_main.top();
		CString type_old = undone_types_main.top();

		if(basket.count(title_new)>0)
		{
			toPrint += _T("REDO FAILED\nCan't ReEdit to title ");
			toPrint += title_new;
			toPrint +=_T("/nAn item with this title already in Basket");
			redo_succeed = false;
		}

		else if(Edit(title_old , title_new , type_new))
		{															

			toPrint += _T("REDO SUCEED\nThe ");
			toPrint += type_old;
			toPrint += _T(" ");
			toPrint += title_old;
			toPrint += " ReEdited to the ";
			toPrint += type_new;
			toPrint += _T(" ");
			toPrint += title_new;

			done_titles_edit.push(title_new);
			done_types_edit.push(type_new);
			undone_titles_edit.pop();
			undone_types_edit.pop();
		}
		else
		{

			toPrint += _T("REDO FAILED\n");
			toPrint += type_old;
			toPrint += _T(" ");
			toPrint += title_old;
			toPrint += _T(" is not in the basket and wasn't edited to ");
			toPrint += type_new;
			toPrint += " ";
			toPrint += title_new;
			redo_succeed = false;
		}

	}

	if(redo_succeed)
	{
		done_actions.push(action_to_reverse);
		done_titles_main.push(title_to_reverse);
		done_types_main.push(type_to_reverse);

		undone_actions.pop();
		undone_titles_main.pop();
		undone_types_main.pop();
	}

	AfxMessageBox(toPrint);


}


void CShelfDeBestDlg::OnBnClickedButtonUse()
{
	if(MainInputIsEmpty()) { return; }

	else if(basket.count(input_main_title)>0)
		basket[input_main_title]->Use();
	else{AfxMessageBox(_T("No object with a such name to use"));}
}


void CShelfDeBestDlg::OnBnClickedButtonCleanAll()
{
	// TODO: Add your control notification handler code here
	basket.clear();
	trash.clear();
	CleanAllRedo();
	CleanAllDone();
	AfxMessageBox(_T("Baskets and Trash are empty"));
}


void CShelfDeBestDlg::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here

	CFile file(L"shelfile.bin", CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store); 

	ar << basket.size() << trash.size() ;
	
	ar << undone_actions.size() << undone_titles_main.size()  << undone_types_main.size() 
		<< undone_titles_edit.size() << undone_types_edit.size();
	
	ar << done_actions.size() << done_titles_main.size() << done_types_main.size()
		<< done_titles_edit.size() << done_types_edit.size();

	for (auto it = basket.cbegin(); it != basket.cend(); ++it)
		ar << it->first << it->second;
	
	for (auto it = trash.cbegin(); it != trash.cend(); ++it)
		ar << it->first << it->second;
	
	while(!undone_actions.empty())     { ar << undone_actions.top();     undone_actions.pop(); }
	while(!undone_titles_main.empty()) { ar << undone_titles_main.top(); undone_titles_main.pop(); }
	while(!undone_types_main.empty())  { ar << undone_types_main.top();  undone_types_main.pop(); }
	while(!undone_titles_edit.empty()) { ar << undone_titles_edit.top(); undone_titles_edit.pop(); }
	while(!undone_types_edit.empty())  { ar << undone_types_edit.top();  undone_types_edit.pop(); }

	while(!done_actions.empty())       { ar << done_actions.top(); done_actions.pop(); }
	while(!done_titles_main.empty())   { ar << done_titles_main.top(); done_titles_main.pop(); }
	while(!done_types_main.empty())    { ar << done_types_main.top(); done_types_main.pop(); }
	while(!done_titles_edit.empty())   { ar << done_titles_edit.top(); done_titles_edit.pop(); }
	while(!done_types_main.empty())    { ar << done_types_main.top(); done_types_main.pop(); }
	

	AfxMessageBox(_T("Basket is saved to the memory"));
}


void CShelfDeBestDlg::OnBnClickedButtonLoad()
{
	// TODO: Add your control notification handler code here


	basket.clear();
	trash.clear();
	CleanAllRedo();
	CleanAllDone();

	Shelf * sh;
	CString key;

	int basket_size;
	int trash_size;

	int undone_actions_size;    
	int undone_titles_main_size;
	int undone_types_main_size;
	int undone_titles_edit_size;
	int undone_types_edit_size;
	 
	int done_actions_size;      
	int done_titles_main_size;
	int done_types_main_size;
	int done_titles_edit_size;
	int done_types_edit_size;

	CString temp;


	CFile file(L"shelfile.bin", CFile::modeRead);
	CArchive ar(&file, CArchive::load);

	ar >> basket_size >> trash_size ;
	
	ar >> undone_actions_size >> undone_titles_main_size  >> undone_types_main_size 
		>> undone_titles_edit_size >> undone_types_edit_size;
	
	ar >> done_actions_size >> done_titles_main_size >> done_types_main_size
		>> done_titles_edit_size >> done_types_edit_size;

	for(int i = 0 ; i < basket_size ; i++)
	{
		ar >> key >> sh;
		basket[key] = sh;
	}

	for(int i = 0 ; i < trash_size ; i++)
	{
		ar >> key >> sh;
		trash[key] = sh;
	}

	
	for(int i = 0; i < undone_actions_size; i++)    { ar >> temp; undone_actions.push(temp);}
	for(int i = 0; i < undone_titles_main_size; i++) { ar >> temp; undone_titles_main.push(temp);}
	for(int i = 0; i < undone_types_main_size; i++)  { ar >> temp; undone_types_main.push(temp);}
	for(int i = 0; i < undone_titles_edit_size; i++) { ar >> temp; undone_titles_edit.push(temp);}
	for(int i = 0; i < undone_types_edit_size; i++)  { ar >> temp; undone_types_edit.push(temp);}
	
	for(int i = 0; i < done_actions_size; i++)     { ar >> temp; done_actions.push(temp);}
	for(int i = 0; i < done_titles_main_size; i++)  { ar >> temp; done_titles_main.push(temp);}
	for(int i = 0; i < done_types_main_size; i++)  { ar >> temp; done_types_main.push(temp);}
	for(int i = 0; i < done_titles_edit_size ; i++) { ar >> temp; done_titles_edit.push(temp);}
	for(int i = 0; i < done_titles_edit_size; i++)  { ar >> temp; undone_types_edit.push(temp);}
				  
	AfxMessageBox(_T("All baskets are loaded from the memory"));
}


void CShelfDeBestDlg::OnBnClickedButtonExists()
{
	// TODO: Add your control notification handler code here

	if(MainInputIsEmpty()) { return;}

	if(!(basket.count(input_main_title)>0))
	{
		AfxMessageBox(_T("This item does not exist the basket"));
	}
	else
	{
		AfxMessageBox(_T("This item exist the basket"));
	}

}

void CShelfDeBestDlg::OnBnClickedButtonPrintAllBasket()
{
	// TODO: Add your control notification handler code here

	if(basket.size() == 0)
	{
		AfxMessageBox(_T("Basket is empty. No objects to print"));
		return;
	}

	AfxMessageBox(_T("Prints all items of basket"));
	for (auto it = basket.cbegin(); it != basket.cend(); ++it)
	{
		CString name = it->first;
		AfxMessageBox(name);
	}
}

void CShelfDeBestDlg::CleanAllRedo()
{
	while (!undone_actions.empty())     { undone_actions.pop();}
	while (!undone_titles_main.empty()) { undone_titles_main.pop();}
	while (!undone_types_main.empty())  { undone_types_main.pop();}
	while (!undone_titles_edit.empty()) { undone_titles_edit.pop();}
	while (!undone_types_edit.empty())  { undone_types_edit.pop();}
}

void CShelfDeBestDlg::CleanAllDone()
{
	while (!done_actions.empty())       { done_actions.pop();} 
	while (!done_titles_main.empty())   { done_titles_main.pop();}
	while (!done_types_main.empty())    { done_types_main.pop();}
	while (!done_titles_edit.empty())   { done_titles_edit.pop();}
	while (!done_types_edit.empty())    { done_types_edit.pop();}
}


bool CShelfDeBestDlg::Add(CString title, CString type)
{

	if(!(basket.count(title)>0))
	{
		if(type == "Book")
		{
			Book *book = new Book(title);
			basket[title] = book;
		}
		else if(type == "Movie")
		{
			Movie *movie = new Movie(title);
			basket[title] = movie;
		}
		else
		{
			TvShow *tvshow = new TvShow(title);
			basket[title] = tvshow;
		}

		return true;
	}

	return false;

}

bool CShelfDeBestDlg::Delete(CString title){

	if(basket.count(title)>0)
	{
		Shelf *sh = basket[title];
		basket.erase(title);
		trash[title] = sh;
		return true;
	}

	return false;
}

bool CShelfDeBestDlg::Edit(CString title_old, CString title_new , CString type_new)
{
	if(basket.count(title_old)>0)
	{
		basket.erase (title_old);

		if(type_new == "Book")
		{
			Book *book = new Book(title_new);
			basket[title_new] = book;
		}
		else if(type_new == "Movie")
		{
			Movie *movie = new Movie(title_new);
			basket[title_new] = movie;
		}
		else
		{
			TvShow *tvshow = new TvShow(title_new);
			basket[title_new] = tvshow;
		}

		return true;
	}

	return false;
}


bool CShelfDeBestDlg::MainInputIsEmpty()
{
	if(input_main_title== "")
	{
		AfxMessageBox(_T("Input title"));
		return true;
	}

	if(input_main_type == "")
	{
		AfxMessageBox(_T("Input type"));
		return true;
	}

	return false;
}

bool CShelfDeBestDlg::EditInputIsEmpty()
{
	if(input_edit_title == "")
	{
		AfxMessageBox(_T("Input new title"));
		return true;
	}

	if(input_edit_type == "")
	{
		AfxMessageBox(_T("Input new type"));
		return true;
	}
	return false;
}
