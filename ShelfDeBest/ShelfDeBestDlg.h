
// ShelfDeBestDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include <iostream>

using namespace std;


// CShelfDeBestDlg dialog
class CShelfDeBestDlg : public CDialogEx
{
// Construction
public:
	CShelfDeBestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SHELFDEBEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnCbnSelchangeComboType();
	afx_msg void OnEnChangeEditTitle();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonUndo();
	
	CComboBox m_comboBoxCtrl_Type; //combo of the type
	
	CEdit m_editCtrl_Title; //Edit box of the title
	CEdit m_editCtrl_Edit;  //
	
	CString input_main_type; //input of the type box
	CString input_main_title;  //input of the title box
	CString input_edit_title;

	CString last_title;
	CString last_type;
	CString last_edit;
	CString last_action;
	
	afx_msg void OnBnClickedButtonUse();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonCleanAll();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonRedo();
	afx_msg void OnBnClickedButtonExists();

	bool Add(CString title, CString type);
	bool Delete(CString title);
	bool Edit(CString title_old , CString title_new , CString type);

	void CleanAllRedo();
	void CleanAllDone();
	bool MainInputIsEmpty();
	bool EditInputIsEmpty();

	afx_msg void OnBnClickedButtonPrintAllBasket();
	CComboBox m_comboBoxCtrl_edit; //control of edit combo box
	CString input_edit_type;       //input of edit type
	afx_msg void OnCbnSelchangeComboTypeEdit();
	afx_msg void OnEnChangeEditNewTitle();
};
