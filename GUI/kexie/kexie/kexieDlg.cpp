
// kexieDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "kexie.h"
#include "kexieDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



void Send_Command(CMscomm1 *m_ms, byte command);

typedef struct
{
	int num;
	long time;
} key_t;

key_t key_buf[7];

byte rxdata[1024];//设置BYTE数组  
unsigned int pointer=0;
static int show_flag=1;



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CkexieDlg 对话框

CkexieDlg::CkexieDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CkexieDlg::IDD, pParent)
	, m_send_data(_T(""))
	, m_receive_data(_T(""))
	, m_state(_T(""))
	, m_num1(_T(""))
	, m_num2(_T(""))
	, m_time2(_T(""))
	, m_num3(_T(""))
	, m_num4(_T(""))
	, m_num5(_T(""))
	, m_num6(_T(""))
	, m_num7(_T(""))
	, m_time3(_T(""))
	, m_time4(_T(""))
	, m_time5(_T(""))
	, m_time6(_T(""))
	, m_time7(_T(""))
	, m_no1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CkexieDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, m_mscom);
	DDX_Control(pDX, IDC_COM, m_com);
	DDX_Control(pDX, IDC_BAUD, m_baud);
	DDX_Text(pDX, IDC_EDIT1, m_receive_data);
	DDX_Text(pDX, IDC_STATE, m_state);
	DDX_Text(pDX, IDC_NUM1, m_num1);
	DDX_Text(pDX, IDC_NUM2, m_num2);
	DDX_Text(pDX, IDC_TIME2, m_time2);
	DDX_Control(pDX, IDC_EDIT1, m_rev_edit);
	DDX_Text(pDX, IDC_NUM3, m_num3);
	DDX_Text(pDX, IDC_NUM4, m_num4);
	DDX_Text(pDX, IDC_NUM5, m_num5);
	DDX_Text(pDX, IDC_NUM6, m_num6);
	DDX_Text(pDX, IDC_NUM7, m_num7);
	DDX_Text(pDX, IDC_TIME3, m_time3);
	DDX_Text(pDX, IDC_TIME4, m_time4);
	DDX_Text(pDX, IDC_TIME5, m_time5);
	DDX_Text(pDX, IDC_TIME6, m_time6);
	DDX_Text(pDX, IDC_TIME7, m_time7);
	DDX_Control(pDX, IDC_NUM1, m_edit_num1);
	DDX_Control(pDX, IDC_NO1, m_edit_no1);
	DDX_Text(pDX, IDC_NO1, m_no1);
}

BEGIN_MESSAGE_MAP(CkexieDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, &CkexieDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_EXIT, &CkexieDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_SEND, &CkexieDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDOK, &CkexieDlg::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CkexieDlg 消息处理程序

BOOL CkexieDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CString str;
	int i;

	//装入数据串口号选择的下拉控件
	for(i=0;i<15;i++)
	{
		str.Format(_T("COM%d"), i+1);
		m_com.InsertString(i, str);
	}
	m_com.SetCurSel(4);									//预置COM

	//装入波特率选择的下拉控件
	CString str1[12]={_T("300"),_T("600"),_T("1200"),_T("2400"),_T("4800"),_T("9600"),
		            _T("19200"),_T("38400"),_T("43000"),_T("56000"),_T("57600"),_T("115200")};

	for(int i=0;i<12;i++)								//装入数据波特率控件
	{
		int judge_tf = m_baud.InsertString(i, str1[i]);

		if((judge_tf==CB_ERR)||(judge_tf==CB_ERRSPACE))
			MessageBox(_T("Baud Error!"));				//波特率错误
	}
	m_baud.SetCurSel(7);								//预置波特率

	m_mscom.put_InBufferCount(0);						//清空接收缓存区
	m_mscom.put_OutBufferCount(0);						//清空发送缓存区

	m_state=_T("DISCONNECTED");							//初始化连接状态
	m_no1=_T("No.1");									//
	UpdateData(false);									//更新
	
	//设置第一名的显示字体
	m_font.CreatePointFont(220, _T("黑体"));
	m_font2.CreatePointFont(120, _T("黑体"));
	m_edit_num1.SetFont(&m_font);
	m_edit_no1.SetFont(&m_font2);

	return TRUE;										 // 除非将焦点设置到控件，否则返回 TRUE
}

void CkexieDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CkexieDlg::OnPaint()
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CkexieDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//连接串口函数

void CkexieDlg::OnBnClickedConnect()
{
	// TODO: 在此添加控件通知处理程序代码

	CString str, str1, n;					//定义字符串

	GetDlgItemText(IDC_CONNECT,str);
	CWnd * h1;
	h1 = GetDlgItem(IDC_CONNECT);			//指向控件的caption
	
	if(!m_mscom.get_PortOpen())							//未连接状态中......
	{
		m_baud.GetLBText(m_baud.GetCurSel(),str1);		//取得所选的字符串，并存放在str1里面

		str1= str1+','+'n'+','+'8'+','+'1';				//这句话很关键
		
		m_mscom.put_CommPort( (m_com.GetCurSel()+1) );	//选择串口 comb控件中获取
		m_mscom.put_InputMode(1);						//设置输入方式为二进制方式		//二进制
		m_mscom.put_Settings(str1);						//波特率为（波特率组Á合框）无校验，8数据位，1个停止位
		m_mscom.put_InputLen(1024);						//设置当前接收区数据长度为1024
		m_mscom.put_RThreshold(1);						//缓冲区一个字符引发事件
		m_mscom.put_RTSEnable(1);						//设置RT允许
			
		m_mscom.put_PortOpen(true);				//开启连接

		if( m_mscom.get_PortOpen() )			//如果成功打开则改变按钮名称
		{
			str=_T(" ▶  Disconnect   ");		//改变按钮名称
			UpdateData(true);					//
			h1->SetWindowText(str);				//更新

			m_state=_T("  CONNECTED");			//连接状态，编辑框
			UpdateData(false);					//更新

			SetTimer(1,1000,NULL);				//延迟1s

			Send_Command(&m_mscom, 0x77);		//发送已连接指令，连接成功反馈
		}		
	}
	
	else											//连接状态中......
	{	
		m_mscom.put_PortOpen(false);				//关闭连接

		if(str!=_T("Disconnect"))					//该表按钮名字
		{
			str=_T(" ▶   Connect     ");
			UpdateData(true);
			h1->SetWindowText(str);					//改变按钮名称

			m_state=_T("DISCONNECTED");				//改变状态编辑框
			UpdateData(false);						//更新
		}
	}
}


// 退出程序按钮响应函数

void CkexieDlg::OnBnClickedExit()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_mscom.get_PortOpen())				//如果串口有被打开
		m_mscom.put_PortOpen(false);

	CDialogEx::OnCancel();					//销毁对话框
}


// 按钮响应函数：发送测试按钮

void CkexieDlg::OnBnClickedSend()		//Test
{
	// TODO: 在此添加控件通知处理程序代码
	Send_Command(&m_mscom, 0x44);
}


BEGIN_EVENTSINK_MAP(CkexieDlg, CDialogEx)
	ON_EVENT(CkexieDlg, IDC_MSCOMM1, 1, CkexieDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


// 串口控件

void CkexieDlg::OnCommMscomm1()
{
// TODO: 在此处添加消息处理程序代码

	VARIANT variant_inp;  
	COleSafeArray safearray_inp;  
	long len,k;  
	byte rxdata[1024];//设置BYTE数组  
	int rxtime[7];
	CString strtemp;  
	

	if (m_mscom.get_CommEvent()==2)//值为2表示接收缓冲区内有字符  
	{
		//SetTimer(1, 1000, NULL);

		variant_inp = m_mscom.get_Input();//读取缓冲区			//***执行不了

		safearray_inp = variant_inp;	//变量转换  

		len = safearray_inp.GetOneDimSize();//得到有效的数据长度

		m_mscom.put_InBufferCount(0);	//清空缓存区

		for (k=0;k<len;k++)  
		{  
			safearray_inp.GetElement(&k,rxdata+k);		//转换成BYTE型数组
		}  
		
		// !!!!!
		if(rxdata[0]==0xA5 && rxdata[1]==0x5A && rxdata[23]==0xAA)
		{
			if(rxdata[2])					//一号
			{
				CNumoneDlg numone;
				strtemp.Format(_T("%d 号"), rxdata[2]);		//将byte转换成CString
				numone.m_numone=strtemp;					//弹出对话框中的编辑框记录下第一名的号数
				m_num1=strtemp;								//主编辑框记录下第一名的号数
				rxtime[0]=0;								//第一名的时间做标准，即为0

				if(show_flag)								//一个回合只弹出一个对话框；在Round_Again中将show_flag置一；
				{	
					show_flag=0;							//flag清零
					//numone.DoModal();						//弹出对话框
				}
			}
			if(rxdata[5])					//二号
			{
				strtemp.Format(_T("%d 号"), rxdata[5]);
				m_num2=strtemp;
				rxtime[1] = (rxdata[6]<<8)+rxdata[7];
				if(rxtime[1]<rxtime[0])						//单片机发送过来为16位，即最高为65535，若比上一次的时间小，则说明溢出
					rxtime[1]+=65535;						//溢出
				strtemp.Format(_T("-%d ms"), rxtime[1]);	//将时间显示主对话框中
				m_time2=strtemp;
			}

			if(rxdata[8])					//三号
			{
				strtemp.Format(_T("%d 号"), rxdata[8]);
				m_num3=strtemp;
				rxtime[2]=(rxdata[9]<<8)+rxdata[10];
				if(rxtime[2]<rxtime[1])
					rxtime[2]+=65535;
				strtemp.Format(_T("-%d ms"), rxtime[2]);
				m_time3=strtemp;
			}
			if(rxdata[11])					//四号
			{
				strtemp.Format(_T("%d 号"), rxdata[11]);
				m_num4=strtemp;
				rxtime[3]=(rxdata[12]<<8)+rxdata[13];
				if(rxtime[3]<rxtime[2])
					rxtime[3]+=65535;
				strtemp.Format(_T("-%d ms"), rxtime[3]);
				m_time4=strtemp;
			}
			if(rxdata[14])					//五号
			{
				strtemp.Format(_T("%d 号"), rxdata[14]);
				m_num5=strtemp;
				rxtime[4]=(rxdata[15]<<8) + rxdata[16];
				if(rxtime[4]<rxtime[3])
					rxtime[4]+=65535;
				strtemp.Format(_T("-%d ms"), rxtime[4]);
				m_time5=strtemp;
			}
			if(rxdata[17])					//六号
			{
				strtemp.Format(_T("%d 号"), rxdata[17]);
				m_num6=strtemp;
				rxtime[5]=(rxdata[18]<<8) + rxdata[19];
				if(rxtime[5]<rxtime[4])
					rxtime[5]+=65535;
				strtemp.Format(_T("-%d ms"),rxtime[5]);
				m_time6=strtemp;
			}
			if(rxdata[20])					//七号
			{
				strtemp.Format(_T("%d 号"), rxdata[20]);
				m_num7=strtemp;
				rxtime[6]=(rxdata[21]<<8) + rxdata[22];
				if(rxtime[6]<rxtime[5])
					rxtime[6]+=65535;
				strtemp.Format(_T("-%d ms"), rxtime[6]);
				m_time7=strtemp;
			}
		}
		/*
		// 将接收数据显示在接收编辑框内
		for (k=0;k<len;k++)  
		{  
			strtemp.Format(_T("%02x "),*(rxdata+k));	//转换成String
			m_receive_data+=strtemp;					//添加到编辑框中
		}  
		CString temp=_T("\r\r\n");						//添加换行
		m_receive_data+=temp;  
		*/
	}
	
	UpdateData(FALSE);									 //更新全部编辑框内容

	/*
	//将接收编辑框的下滑块拉到最低
	m_rev_edit.SetSel(-1, -1); 
	this->SetDlgItemTextW(IDC_EDIT1, m_receive_data);
	m_rev_edit.LineScroll(m_rev_edit.GetLineCount()-1,0);
	*/
}



//按钮响应函数：开始新一回合

void CkexieDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	CString temp=_T("");

	show_flag=1;						//将弹出对话框的标志位打开

	if(m_mscom.get_PortOpen())			//蓝牙已经连接
	{
		//发送重新开始新一回合的指令
		Send_Command(&m_mscom, 0x55);

		//将所有显示编辑框的内容都清空
		m_num1=temp;
		m_num2=temp;
		m_num3=temp;
		m_num4=temp;
		m_num5=temp;
		m_num6=temp;
		m_num7=temp;
		m_time2=temp;
		m_time3=temp;
		m_time4=temp;
		m_time5=temp;
		m_time6=temp;
		m_time7=temp;

		//更新对话框
		UpdateData(FALSE);
	}
	else
	{
		MessageBox(_T("No Connecting!"), _T("ERROR"));		//没有连接
	}
}


//发送消息指令到下位机
//参数：控件变量；
//命令：0x55 重新开始新一回合命令
//		0x44 测试是否成功发送命令
//		0x77 已经成功连接，发回的反馈
//返回值：无
void Send_Command(CMscomm1 *m_ms, byte command)
{
	byte data[4] = {0xA5, 0x5A, 0x00, 0xAA};

	data[2] = command;

	CByteArray  round;
	round.RemoveAll();
	
	round.SetSize(4);

	for(int i=0; i<4; i++)
	{
		round.SetAt(i, data[i]);
	}

	m_ms->put_OutBufferCount(0);		//清空输出缓存区
	m_ms->put_Output(COleVariant(round));
	m_ms->put_Output(COleVariant(round));
}


//改变编辑框字体颜色
//WM_CTLCOLOR消息
HBRUSH CkexieDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd-> GetDlgCtrlID()==IDC_NUM1)
	{
		pDC-> SetTextColor(RGB(255,0,0));			//设置字体颜色
		pDC-> SetBkMode(TRANSPARENT);				//设置字体背景为透明
	}
	if (pWnd-> GetDlgCtrlID()==IDC_NO1)
	{
		pDC-> SetTextColor(RGB(255,0,0));			//设置字体颜色
		pDC-> SetBkMode(TRANSPARENT);				//设置字体背景为透明
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
