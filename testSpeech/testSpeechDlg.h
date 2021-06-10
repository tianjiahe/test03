
// testSpeechDlg.h: 头文件
//

#include "PngButton.h"
#include "SmartButton.h"


#include <conio.h>          // 调试用控制台

#pragma once


#define PNG_ROW     4
#define PNG_COL     4
#define PNG_CNT     (PNG_ROW * PNG_COL)

#define WM_RECORD   WM_USER + 100								// 定义消息
//#define IDC_PNG_BUTTON(row,col)   (6000 + row * 4 + col)      // 按钮组的起始ID
#define IDC_PNG_BUTTON(index)   (6000 + index)					// 按钮组的起始ID

#define SCORE_MAX     (10)                                      // 题目总数量 

// CtestSpeechDlg 对话框
class CtestSpeechDlg : public CDialogEx
{
// 构造
public:
	CtestSpeechDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTSPEECH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL PreTranslateMessage(MSG* pMsg);

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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnPngButton();       
	afx_msg LRESULT OnSpeechRecognition(WPARAM, LPARAM);
	
	// 用作语音测试的文本
	CString m_txt2Speech;

	//定义变量,用作语音识别
	CComPtr<ISpRecognizer>  m_cpRecoEngine;	// 语音识别引擎(recognition)的接口。
	CComPtr<ISpRecoContext> m_cpRecoCtxt;	// 识别引擎上下文(context)的接口。
	CComPtr<ISpRecoGrammar> m_cpCmdGrammar;	// 识别文法(grammar)的接口。
	CComPtr<ISpStream>      m_cpInputStream;// 流()的接口。
	CComPtr<ISpObjectToken> m_cpToken;		// 语音特征的(token)接口。
	CComPtr<ISpAudio>       m_cpAudio;		// 音频(Audio)的接口。(用来保存原来默认的输入流)
	ULONGLONG				ullGrammerID;   //  

	void MSSListen();						// 语音识别初始化函数
	void MSSSpeak(LPCTSTR m_txt2Speech);

	bool m_bGotReco;

	CStringList  m_nameList;
	CStringArray m_nameArray;

	CPngButton	 m_btnA, m_btnB, m_btnC, m_btnD;

	
	CPngButton   m_btnArray[ PNG_CNT ];

	//vector<CPngButton> m_btnArray;
	//CSmartButton m_btnA, m_btnB, m_btnC, m_btnD;

	CString  m_curSelect, m_rightSelect;          // 当前选择,正确选择
	CString  m_strMsg;


	void GetFileFromDir(CString csDirPath);
	// 连续语音播放
	BOOL m_isContinue;
	// 计分板
	int m_nScore;
	int m_nErrScore;
	CString m_sTip;
	CButton m_btnTip;
};


