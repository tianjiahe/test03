
// testSpeechDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "testSpeech.h"
#include "testSpeechDlg.h"
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


// CtestSpeechDlg 对话框



CtestSpeechDlg::CtestSpeechDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTSPEECH_DIALOG, pParent)
	, m_txt2Speech(_T(""))
	, m_strMsg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bGotReco = FALSE;
}

void CtestSpeechDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SPEECH, m_txt2Speech);
	DDX_Text(pDX, IDC_STATIC_MSG, m_strMsg);
}

BEGIN_MESSAGE_MAP(CtestSpeechDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CtestSpeechDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CtestSpeechDlg::OnBnClickedButton2)
	ON_MESSAGE(WM_RECORD,      &CtestSpeechDlg::OnSpeechRecognition)

	//ON_BN_CLICKED(IDC_PNG_BUTTON0, OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON0, OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON1, OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON2, OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON3, OnPngButton)

    ON_BN_CLICKED(IDC_PNG_BUTTON(0),  OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON(1),  OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON(2),  OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON(3),  OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON(4),  OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON(5),  OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON(6),  OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON(7),  OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON(8),  OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON(9),  OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON(10), OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON(11), OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON(12), OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON(13), OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON(14), OnPngButton)
	ON_BN_CLICKED(IDC_PNG_BUTTON(15), OnPngButton)



END_MESSAGE_MAP()


// CtestSpeechDlg 消息处理程序

BOOL CtestSpeechDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// MSSListen(); 

	//m_btnA.Create(L"btn0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 10, 100, 100), this, IDC_PNG_BUTTON0);
	//m_btnB.Create(L"btn1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 10, 100, 100), this, IDC_PNG_BUTTON1);
	//m_btnC.Create(L"btn2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 10, 100, 100), this, IDC_PNG_BUTTON2);
	//m_btnD.Create(L"btn3", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 10, 100, 100), this, IDC_PNG_BUTTON3);

	//for (int i = 0; i < ROW; i++)  for (int j = 0; j < COL; j++)
	//m_btnArr[i][j].Create(L"-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(0, 0, 64, 64), this, IDC_PNG_BUTTON(i,j));

	for (int i = 0; i < PNG_CNT ; i++)
		m_btnArray[i].Create( _T("-"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(0, 0, 64, 64), this, IDC_PNG_BUTTON(i));

	//m_btnA.SetImagePath(_T("./res/苹果.png"), _T("./res/Background.png"));
	//m_btnA.InitMyButton(16, 8, 100, 100, true);
	//m_btnB.SetImagePath(_T("./res/桔子.png"), _T("./res/Background.png"));
	//m_btnB.InitMyButton(545, 8, 27, 21, true);
	
	GetFileFromDir(L"./assets/en/");

	/*
	m_nameArray.Add(_T("apple"));
	m_nameArray.Add(_T("orange"));
	m_nameArray.Add(_T("grapes"));
	m_nameArray.Add(_T("tomatoes"));
	*/

	CString  btnFile;
	for (int i = 0; i < m_nameArray.GetCount(); i++)
	{
		m_btnArray[i].SetWindowText(m_nameArray[i]);
		btnFile = _T("./assets/en/") + m_nameArray[i] + _T(".png");
		m_btnArray[i].SetButtonNormalBitmapEx(btnFile);
		m_btnArray[i].SetButtonDownBitmapEx(btnFile);
		m_btnArray[i].SetButtonUpBitmapEx(btnFile);
	}

	
	// 16个候选图片，4*4 排列
	for (int i = 0; i < PNG_ROW; i++)  {
		for (int j = 0; j < PNG_COL; j++)
		{
			m_btnArray[ i * PNG_ROW + j].MoveWindow( i * 64 + 16, j * 64 + 100, 64, 64);
		}
	}

		   	
	//m_btnA.SetWindowText(m_nameArray[0]);
	//m_btnA.MoveWindow(0 + 16,100,64,64);
	//m_btnA.SetButtonNormalBitmapEx(_T("./res/apple.png")); 
	//m_btnA.SetButtonDownBitmapEx(_T("./res/apple.png"));
	//m_btnA.SetButtonUpBitmapEx(_T("./res/apple.png"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtestSpeechDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtestSpeechDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}


}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CtestSpeechDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 监听语音转文字
void CtestSpeechDlg::MSSSpeak(LPCTSTR m_txt2Speech)
{
	ISpVoice *pVoice = NULL;
	//获取SpVoice接口
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
	if (SUCCEEDED(hr))
	{
		pVoice->SetVolume((USHORT)100);		//设置音量，范围是 0 -100
		pVoice->SetRate(0);					//设置速度，范围是 -10 - 10

		hr = pVoice->Speak(m_txt2Speech, 0, NULL);
		pVoice->Release();
		pVoice = NULL;
	}
}

void CtestSpeechDlg::GetFileFromDir(CString csDirPath)
{
	csDirPath += L"*.png";
	HANDLE file;
	WIN32_FIND_DATA fileData;
	//char line[1024];
	//char fn[1000];
	//mbstowcs(fn,csDirPath.GetBuffer(),999);  
	file = FindFirstFile( csDirPath.GetBuffer(), &fileData);
	//m_FileList.push_back(fileData.cFileName);
	//CString str = fileData.cFileName;
	//m_nameArray.Add(str.Left(str.GetLength() - 4));
	//string str = fileData.cFileName;
	
	if (fileData.cFileName == NULL)   return;
	bool bState = true;

	// TCHAR  *pChr = _tcsrchr(fileData.cFileName, L'.'); //pChr++;  // 某个字符最后出现的位置
	// *pChr = _T('\0');											 // 

	// wcout << fileData.cFileName << endl;
	// TRACE("%s", fileData.cFileName);
    // bState = FindNextFile(file, &fileData);
	while ( bState )
	{
		TCHAR  *pChr = _tcsrchr(fileData.cFileName, L'.');
		*pChr = _T('\0');
		//wcstombs(line,(const char*)fileData.cFileName,259);  
		//m_FileList.push_back(fileData.cFileName);
		m_nameArray.Add(fileData.cFileName);
		bState = FindNextFile(file, &fileData);


	}
}

//文字转语音
void CtestSpeechDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	if (m_txt2Speech != "") {
		MSSSpeak(m_txt2Speech);
		return;
	}

	int index = rand()%(m_nameArray.GetCount());
	m_rightSelect = m_nameArray[index];
	MSSSpeak(m_rightSelect);

}

//语音转文字
void CtestSpeechDlg::MSSListen()
{
	HRESULT hr = m_cpRecoEngine.CoCreateInstance(CLSID_SpSharedRecognizer);     // 创建Share型识别引擎
	if (SUCCEEDED(hr))
	{
		hr = m_cpRecoEngine->CreateRecoContext(&m_cpRecoCtxt);					// 创建识别上下文接口
		hr = m_cpRecoCtxt->SetNotifyWindowMessage(m_hWnd, WM_RECORD, 0, 0);		// 设置识别消息
		const ULONGLONG ullInterest = SPFEI(SPEI_SOUND_START) | SPFEI(SPEI_SOUND_END) | SPFEI(SPEI_RECOGNITION);//设置我们感兴趣的事件
		hr = m_cpRecoCtxt->SetInterest(ullInterest, ullInterest);

		hr = SpCreateDefaultObjectFromCategoryId(SPCAT_AUDIOIN, &m_cpAudio);
		m_cpRecoEngine->SetInput(m_cpAudio, true);

		//创建语法规则
	   //dictation听说式
	   //hr = m_cpRecoCtxt->CreateGrammar(GIDDICTATION, &m_cpDictationGrammar);
	   //if (SUCCEEDED(hr))
	   //{
	   //  hr = m_cpDictationGrammar->LoadDictation(NULL, SPLO_STATIC);//加载词典
	   //}

	   //C&C命令式，此时语法文件使用xml格式
		ullGrammerID = 1000;
		hr = m_cpRecoCtxt->CreateGrammar(ullGrammerID, &m_cpCmdGrammar);

		WCHAR wszXMLFile[20] = L"";			//加载语法
		MultiByteToWideChar(CP_ACP, 0, (LPCSTR)"CmdCtrl.xml", -1, wszXMLFile, 256);//ANSI转UNINCODE
		hr = m_cpCmdGrammar->LoadCmdFromFile(wszXMLFile, SPLO_DYNAMIC);

		MessageBox( (LPCWSTR)L"语音识别已启动！", (LPCWSTR)L"提示", MB_CANCELTRYCONTINUE );
	   //激活语法进行识别
	   //hr = m_cpDictationGrammar->SetDictationState(SPRS_ACTIVE);//dictation
		hr = m_cpCmdGrammar->SetRuleState(NULL, NULL, SPRS_ACTIVE);//C&C
		hr = m_cpRecoEngine->SetRecoState(SPRST_ACTIVE);
	}
	else
	{
		MessageBox( L"语音识别引擎启动出错！", L"警告", MB_OK);
		exit(0);
	}

	//释放com资源
	::CoUninitialize();
	//hr = m_cpCmdGrammar->SetRuleState(NULL, NULL, SPRS_INACTIVE);//C&C

}

void CtestSpeechDlg::OnPngButton()
{
	if (m_curSelect.IsEmpty() || m_rightSelect.IsEmpty())  return;
	//MessageBox((m_curSelect == m_rightSelect) ? L"哈！你答对了!" : L"哎,错了");
	bool isRight = (m_curSelect == m_rightSelect);
	m_strMsg = (isRight) ? L"哈！你答对了!" : L"哎,错了";
	if (isRight)
	{		//Beep(2000, 160);
		PlaySound(_T("./assets/sound/gou0.wav"), NULL, SND_FILENAME | SND_ASYNC );
	}else {
		PlaySound(_T("./assets/sound/yang0.wav"), NULL, SND_FILENAME | SND_ASYNC);
		//Beep(1000, 300);
	}
	m_curSelect.Empty();
	m_rightSelect.Empty();

	UpdateData(FALSE);

	Sleep(2000);            // 等待异步的语言播放结束后执行
	OnBnClickedButton1();   // 新的语言听写


	
}


void CtestSpeechDlg::OnBnClickedButton2()
{
	static bool  hasCtrlPan = false;
	bool ok =   (!hasCtrlPan)?  AllocConsole(): FreeConsole();
	if (ok) hasCtrlPan = !hasCtrlPan;
	
	//freopen("CONOUT$", "w", stdout);
}

LRESULT CtestSpeechDlg::OnSpeechRecognition(WPARAM, LPARAM)
{
 //消息处理函数
  USES_CONVERSION;
 
    CSpEvent event;
 
    if (m_cpRecoCtxt)
    {
        while (event.GetFrom(m_cpRecoCtxt) == S_OK)
		{
            switch (event.eEventId)
            {
            case SPEI_RECOGNITION:
						{
							//识别出了语音
							m_bGotReco = TRUE; 
							static const WCHAR wszUnrecognized[] = L"<Unrecognized>";
							CSpDynamicString dstrText;
							////取得识别结果 
							if (FAILED(event.RecoResult()->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, TRUE, &dstrText, NULL)))
							{
								dstrText = wszUnrecognized;
							}
 
							BSTR SRout;
							dstrText.CopyToBSTR(&SRout);
							CString Recstring;
							Recstring.Empty();
							Recstring = SRout;
 
							//做出反应（*****消息反应模块*****）
							if (Recstring == "发短信")
							{   //MessageBox(NULL, (LPCWSTR)L"好的", (LPCWSTR)L"提示", MB_OK);
								MSSSpeak(LPCTSTR(_T("好，马上发短信！")));
							}
							else if (Recstring == "李雷")
							{
								MSSSpeak(LPCTSTR(_T("好久没看见他了，真是 long time no see")));
							}   
						}
						break;
            }
        }
    }
	return 0l;
}

BOOL CtestSpeechDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	
	CWnd* pwnd = CWnd::FromHandle(pMsg->hwnd);
	int nID = 0;
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (NULL != pwnd)
		{
			nID = pwnd->GetDlgCtrlID();
			
			//if (     nID == IDC_PNG_BUTTON0) { GetDlgItemText(IDC_PNG_BUTTON0, m_curSelect); } // 选中的答案
			//else if (nID == IDC_PNG_BUTTON1) { GetDlgItemText(IDC_PNG_BUTTON1, m_curSelect); }
			//else if (nID == IDC_PNG_BUTTON2) { GetDlgItemText(IDC_PNG_BUTTON2, m_curSelect); }
			//else if (nID == IDC_PNG_BUTTON3) { GetDlgItemText(IDC_PNG_BUTTON3, m_curSelect); }

			for (int index = 0; index < PNG_CNT; index++)
			{
				if( nID == IDC_PNG_BUTTON(index))	GetDlgItemText(nID, m_curSelect);
			}

		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
