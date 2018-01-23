
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
	CComboBox m_comboBoxCtrl_Type; //combo of the type
	CString m_strTextCtrl_Type; //input of the type box
	afx_msg void OnCbnSelchangeComboType();
	CEdit m_editCtrl_Title; //Edit box of the title
	CString m_strTextCtrl_Title;  //input of the title box
	afx_msg void OnEnChangeEditTitle();
	afx_msg void OnBnClickedButtonAdd();
};
