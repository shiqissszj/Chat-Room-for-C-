
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include<easyx.h>
#include"Register.h"
CRegister registerInstance;
user* currentUser = nullptr;
struct SSRECT
{
	SSRECT(int x, int y, int w, int h)
	{
		l = x;
		t = y;
		r = x + w;
		b = y + h;
		
		this->w = w;
		this->h = h;

	}


	bool contain(int x, int y)
	{
		return ((l < x&& r > x) && (t < y&& b > y));
	}

	int l;
	int t;
	int r;
	int b;
	int w;
	int h;
};
void ShowSpeechsPage();
void ShowContactsPage();
void ShowTeamsPage();
void RegisterPage();
void PersonPage();
void FirstPage();
void ModifyUserPage();
#include<vector>
//注册页
void RegisterPage()
{
	//只要进入程序就读取数据——获取当前NowStudentNums
//	ReadInfor();
	
	int window[] = { 760,460 };
	int button_width = 150;

	initgraph(window[0], window[1]);

	std::vector<std::wstring> buttonName = {
		L"input name",
		L"input address",
		L"input birth day",
		L"input password",
		L"input phone number",
		L"OK",
	};
	std::vector<std::wstring> buttonNameValue(5);
	int border = 100;

	int button_height = 0;
	{
		int h = window[1] - border * 2;
		button_height = h / buttonName.size();
	}

	//鼠标操作1
	MOUSEMSG m1;


	cleardevice();
	//IMAGE picture1;
	//loadimage(&picture1, "./firstbc.jpg", 760, 760);
	//putimage(0, 0, &picture1);
	setbkmode(TRANSPARENT);
	std::vector<SSRECT> rectButtons;
	{
		int height = button_height * 0.75;
		int space = button_height * 0.25;
		for (int i = 0; i < buttonName.size(); i++)
		{
			int top = border + button_height * i;
			int left = (window[0] - button_width) / 2;
			int height = button_height * 0.75;
			int width = button_width;
			rectButtons.push_back(SSRECT(left,top,width,height));
		}
	}

	setfillcolor(GREEN);

	wchar_t FirstTitle[20] = { L"resign new user" };
	
	outtextxy(150, 50, FirstTitle);

	//三个选项的背景
	for (auto &rect : rectButtons)
	{

		fillrectangle(rect.l, rect.t, rect.r, rect.b);
	}

	setbkmode(TRANSPARENT);

	for (int i = 0 ; i  < buttonName.size();i++)
	{
		auto name = buttonName[i];
		auto& rect = rectButtons[i];
		outtextxy(rect.l + 15, rect.t +10, name.c_str());
	}

	//进入主界面选项操作界面
	while (1)
	{
		bool b = false;
		m1 = GetMouseMsg();//获取鼠标操作
		for (int i = 0; i < buttonName.size(); i++)
		{
			auto& rect = rectButtons[i];

			if (rect.contain(m1.x, m1.y))
			{
				b = true;
				setlinecolor(RED);
				rectangle(rect.l, rect.t, rect.r, rect.b);
				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					if(buttonName[i] == L"OK")
					{
						bool bempty = false;
						for (auto value : buttonNameValue)
						{
							if (value.empty())
							{
								bempty = true;
								break;
							}
						}
						if (bempty)
						{
							MessageBox(NULL, L"Register Fail ,please Fill info", L"RegisterPage", MB_OK);

						}
						else
						{
							registerInstance.resignUser(buttonNameValue[0],
								buttonNameValue[4], buttonNameValue[1],
								buttonNameValue[2], buttonNameValue[3]);
							MessageBox(NULL, L"Register success", L"RegisterPage", MB_OK);
							cleardevice();
							FirstPage();
						}
					}
					else
					{
						wchar_t retuenV[1000];
						if (InputBox(retuenV, 1000, buttonName[i].c_str(), 0L, buttonNameValue[i].c_str()))
						{
							buttonNameValue[i] = std::wstring(retuenV);
						}
					}
				}
			}
		}

		if(!b)
		{
			setlinecolor(WHITE);
			for (auto& rect : rectButtons)
			{
				rectangle(rect.l, rect.t, rect.r, rect.b);
			}
		}
	}

}
//修改页
void ModifyUserPage()
{
	//只要进入程序就读取数据——获取当前NowStudentNums
//	ReadInfor();

	int window[] = { 760,460 };
	int button_width = 150;

	initgraph(window[0], window[1]);

	std::vector<std::wstring> buttonName = {
		L"input name",
		L"input address",
		L"input birth day",
		L"input password",
		L"input phone number",
		L"OK",
	};
	std::vector<std::wstring> buttonNameValue(5);
	int border = 100;

	int button_height = 0;
	{
		int h = window[1] - border * 2;
		button_height = h / buttonName.size();
	}

	//鼠标操作1
	MOUSEMSG m1;


	cleardevice();
	//IMAGE picture1;
	//loadimage(&picture1, "./firstbc.jpg", 760, 760);
	//putimage(0, 0, &picture1);
	setbkmode(TRANSPARENT);
	std::vector<SSRECT> rectButtons;
	{
		int height = button_height * 0.75;
		int space = button_height * 0.25;
		for (int i = 0; i < buttonName.size(); i++)
		{
			int top = border + button_height * i;
			int left = (window[0] - button_width) / 2;
			int height = button_height * 0.75;
			int width = button_width;
			rectButtons.push_back(SSRECT(left, top, width, height));
		}
	}

	setfillcolor(GREEN);

	wchar_t FirstTitle[20] = { L"user info modify" };

	outtextxy(150, 50, FirstTitle);

	//三个选项的背景
	for (auto& rect : rectButtons)
	{

		fillrectangle(rect.l, rect.t, rect.r, rect.b);
	}

	setbkmode(TRANSPARENT);

	for (int i = 0; i < buttonName.size(); i++)
	{
		auto name = buttonName[i];
		auto& rect = rectButtons[i];
		outtextxy(rect.l + 15, rect.t + 10, name.c_str());
	}

	//进入主界面选项操作界面
	while (1)
	{
		bool b = false;
		m1 = GetMouseMsg();//获取鼠标操作
		for (int i = 0; i < buttonName.size(); i++)
		{
			auto& rect = rectButtons[i];

			if (rect.contain(m1.x, m1.y))
			{
				b = true;
				setlinecolor(RED);
				rectangle(rect.l, rect.t, rect.r, rect.b);
				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					if (buttonName[i] == L"OK")
					{
						cleardevice();
						PersonPage();
					}
					else
					{
						wchar_t retuenV[1000];
						if (InputBox(retuenV, 1000, buttonName[i].c_str(), 0L, buttonNameValue[i].c_str()))
						{
							buttonNameValue[i] = std::wstring(retuenV);
						}
					}
				}
			}
		}

		if (!b)
		{
			setlinecolor(WHITE);
			for (auto& rect : rectButtons)
			{
				rectangle(rect.l, rect.t, rect.r, rect.b);
			}
		}
	}

}
//用户使用页
void PersonPage()
{
	int window[] = { 760,460 };
	int button_width = 300;

	initgraph(window[0], window[1]);

	wchar_t FirstTitle[] = { L"chat room" };
	std::vector<std::wstring> buttonName = {
		L"add team",
		L"add person to chat",
		L"publish My Speech",
		L"Modify Self infomation",
		L"show Contacts and speechs",
		L"show My Contacts",
		L"show My Team",
		L"Create My Team",
		L"exit",
	};
	std::vector<std::wstring> buttonNameValue(buttonName.size());
	int border = 100;

	int button_height = 0;
	{
		int h = window[1] - border * 2;
		button_height = h / buttonName.size();
	}

	//鼠标操作1
	MOUSEMSG m1;


	cleardevice();
	//IMAGE picture1;
	//loadimage(&picture1, "./firstbc.jpg", 760, 760);
	//putimage(0, 0, &picture1);
	setbkmode(TRANSPARENT);
	std::vector<SSRECT> rectButtons;
	{
		int height = button_height * 0.75;
		int space = button_height * 0.25;
		for (int i = 0; i < buttonName.size(); i++)
		{
			int top = border + button_height * i;
			int left = (window[0] - button_width) / 2;
			int height = button_height * 0.75;
			int width = button_width;
			rectButtons.push_back(SSRECT(left, top, width, height));
		}
	}

	setfillcolor(GREEN);


	outtextxy(150, 50, FirstTitle);

	//三个选项的背景
	for (auto& rect : rectButtons)
	{

		fillrectangle(rect.l, rect.t, rect.r, rect.b);
	}

	setbkmode(TRANSPARENT);

	for (int i = 0; i < buttonName.size(); i++)
	{
		auto name = buttonName[i];
		auto& rect = rectButtons[i];
		outtextxy(rect.l + 15, rect.t + 10, name.c_str());
	}

	//进入主界面选项操作界面
	while (1)
	{
		bool b = false;
		m1 = GetMouseMsg();//获取鼠标操作
		for (int i = 0; i < buttonName.size(); i++)
		{

			auto& rect = rectButtons[i];

			if (rect.contain(m1.x, m1.y))
			{
				b = true;
				setlinecolor(RED);
				rectangle(rect.l, rect.t, rect.r, rect.b);
				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					if (buttonName[i] == L"add team")
					{
						wchar_t retuenV[1000];
						auto list = registerInstance.showAllTeams();
						std::wstring names = L"team name :";
						for (auto it : list)
						{
							names.append(it);
							names.append(L"\n");
						}
						if (InputBox(retuenV, 1000, names.c_str(),
							0L, buttonNameValue[i].c_str()))
						{
							buttonNameValue[i] = std::wstring(retuenV);
							bool bbb = false;
							for (auto team : registerInstance.teams)
							{
								if (buttonNameValue[i] == team.second->name)
								{
									bbb = true;
									registerInstance.connectTeamAndUser(
										team.second, currentUser);
								}
							}

							if(!bbb)
							{
								MessageBox(NULL, L"Can't find team,please create it", L"UserPage", MB_OK);
							}
						}
					}
					else if(buttonName[i] == L"add person to chat")
					{
						auto list = registerInstance.showAllUsers();
						std::wstring names = L"user name :";
						for (auto it : list)
						{
							names.append(it);
							names.append(L"\n");
						}
						wchar_t retuenV[1000];
						if (InputBox(retuenV, 1000, names.c_str(),
							0L, buttonNameValue[i].c_str()))
						{
							buttonNameValue[i] = std::wstring(retuenV);
							bool bbb = false;
							for (auto user : registerInstance.users)
							{
								if (buttonNameValue[i] == user.second->name)
								{
									bbb = true;
									registerInstance.connectUserAndUser(currentUser,user.second);
								}
							}

						if(!bbb)
						{
							MessageBox(NULL, L"Can't find team,please create it",
								L"UserPage", MB_OK);
						}
						}
					}
					else if (buttonName[i] == L"publish My Speech")
					{
						wchar_t retuenV[1000];
						if (InputBox(retuenV, 1000, buttonName[i].c_str(),
							0L, buttonNameValue[i].c_str()))
						{
							buttonNameValue[i] = std::wstring(retuenV);
							currentUser->say(buttonNameValue[i]);
						}
					}
					else if (buttonName[i] == L"Modify Self infomation")
					{
						cleardevice();
						ModifyUserPage();
					}

					else if (buttonName[i] == L"show Contacts and speechs")
					{
						cleardevice();
						ShowSpeechsPage();
					}
					else if (buttonName[i] == L"show My Contacts")
					{
						cleardevice();
						ShowContactsPage();
					}
					else if (buttonName[i] == L"show My Team")
					{
						cleardevice();
						ShowTeamsPage();
					}

					else if (buttonName[i] == L"Create My Team")
					{
						wchar_t retuenV[1000] = {L""};
						if (InputBox(retuenV, 1000, buttonName[i].c_str(),
							0L, buttonNameValue[i].c_str()))
						{
							registerInstance.resignWorkTeam(std::wstring(retuenV));
						}
					}
					else if (buttonName[i] == L"exit")
					{
						currentUser = nullptr;
						cleardevice();
						FirstPage();
					}
					else
					{
						wchar_t retuenV[1000];
						if (InputBox(retuenV, 1000, buttonName[i].c_str(), 0L, buttonNameValue[i].c_str()))
						{
							buttonNameValue[i] = std::wstring(retuenV);
						}
					}
				}
			}
		}

		if (!b)
		{
			setlinecolor(WHITE);
			for (auto& rect : rectButtons)
			{
				rectangle(rect.l, rect.t, rect.r, rect.b);
			}
		}
	}

}
//展示消息页
void ShowSpeechsPage()
{
	int window[] = { 760,460 };
	int button_width = 150;

	initgraph(window[0], window[1]);
	std::vector<std::wstring> buttonName;
	auto p = registerInstance.showSpeechs(currentUser);
	for (auto userId : p)
	{
		buttonName.push_back(userId.first);
	}
	buttonName.push_back(L"exit");
	int border = 100;

	int button_height = 0;
	{
		int h = window[1] - border * 2;
		button_height = h / buttonName.size();
	}

	//鼠标操作1
	MOUSEMSG m1;


	cleardevice();
	
	setbkmode(TRANSPARENT);
	std::vector<SSRECT> rectButtons;
	{
		int height = button_height * 0.75;
		int space = button_height * 0.25;
		for (int i = 0; i < buttonName.size(); i++)
		{
			int top = border + button_height * i;
			int left = (window[0] - button_width) / 2;
			int height = button_height * 0.75;
			int width = button_width;
			rectButtons.push_back(SSRECT(left, top, width, height));
		}
	}

	setfillcolor(GREEN);

	wchar_t FirstTitle[60] = { L"Show Speechs,click name to show speechs" };

	outtextxy(150, 50, FirstTitle);

	//三个选项的背景
	for (auto& rect : rectButtons)
	{

		fillrectangle(rect.l, rect.t, rect.r, rect.b);
	}

	setbkmode(TRANSPARENT);

	int i = 0;
	for (auto name :  buttonName)
	{
		auto& rect = rectButtons[i];
		outtextxy(rect.l + 15, rect.t + 10, name.c_str());
		i++;
	}

	//进入主界面选项操作界面
	while (1)
	{
		bool b = false;
		m1 = GetMouseMsg();//获取鼠标操作
		for (int i = 0; i < buttonName.size(); i++)
		{
			auto& rect = rectButtons[i];

			if (rect.contain(m1.x, m1.y))
			{
				b = true;
				setlinecolor(RED);
				rectangle(rect.l, rect.t, rect.r, rect.b);
				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					if (buttonName[i] == L"exit")
					{
						cleardevice();
						PersonPage();
					}
					else
					{
						for (auto user : p)
						{
							if (user.first == buttonName[i])
							{
								std::wstring speeshAll;
								int idedede = 0;
								for (auto speech : user.second)
								{
									speeshAll.append(std::to_wstring(++idedede) + L". ");
									speeshAll.append(speech);
									speeshAll.append(L"\n");
								}
								MessageBox(NULL, speeshAll.c_str(), buttonName[i].c_str(), MB_OK);
							}
						}
					}
				}
			}
		}

		if (!b)
		{
			setlinecolor(WHITE);
			for (auto& rect : rectButtons)
			{
				rectangle(rect.l, rect.t, rect.r, rect.b);
			}
		}
	}

}
//展示联系人页
void ShowContactsPage()
{
	int window[] = { 760,460 };
	int button_width = 150;

	initgraph(window[0], window[1]);
	std::vector<std::wstring> buttonName;
	for (auto userId : currentUser->UserIDs)
	{
		buttonName.push_back(registerInstance.users[userId]->name);
	}
	buttonName.push_back(L"exit");
	int border = 100;

	int button_height = 0;
	{
		int h = window[1] - border * 2;
		button_height = h / buttonName.size();
	}

	//鼠标操作1
	MOUSEMSG m1;


	cleardevice();
	//IMAGE picture1;
	//loadimage(&picture1, "./firstbc.jpg", 760, 760);
	//putimage(0, 0, &picture1);
	setbkmode(TRANSPARENT);
	std::vector<SSRECT> rectButtons;
	{
		int height = button_height * 0.75;
		int space = button_height * 0.25;
		for (int i = 0; i < buttonName.size(); i++)
		{
			int top = border + button_height * i;
			int left = (window[0] - button_width) / 2;
			int height = button_height * 0.75;
			int width = button_width;
			rectButtons.push_back(SSRECT(left, top, width, height));
		}
	}

	setfillcolor(GREEN);

	wchar_t FirstTitle[20] = { L"Show Contacts" };

	outtextxy(150, 50, FirstTitle);

	//三个选项的背景
	for (auto& rect : rectButtons)
	{
		fillrectangle(rect.l, rect.t, rect.r, rect.b);
	}

	setbkmode(TRANSPARENT);

	int i = 0;
	for (auto name : buttonName)
	{
		auto& rect = rectButtons[i];
		outtextxy(rect.l + 15, rect.t + 10, name.c_str());
		i++;
	}

	//进入主界面选项操作界面
	while (1)
	{
		bool b = false;
		m1 = GetMouseMsg();//获取鼠标操作
		for (int i = 0; i < buttonName.size(); i++)
		{
			auto& rect = rectButtons[i];

			if (rect.contain(m1.x, m1.y))
			{
				b = true;
				setlinecolor(RED);
				rectangle(rect.l, rect.t, rect.r, rect.b);
				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					if (buttonName[i] == L"exit")
					{
						cleardevice();
						PersonPage();
					}
					else
					{
						for (auto user : registerInstance.users)
						{
							if (user.second->name == buttonName[i])
							{
								if (MessageBox(NULL, L"Do you want eare this", L"remove it", MB_OKCANCEL))
								{
									currentUser->easeUser(user.first);
									cleardevice();
									PersonPage();
								}
							}
						}
					}
				}
			}
		}

		if (!b)
		{
			setlinecolor(WHITE);
			for (auto& rect : rectButtons)
			{
				rectangle(rect.l, rect.t, rect.r, rect.b);
			}
		}
	}

}
//展示群组页
void ShowTeamsPage()
{
	int window[] = { 760,460 };
	int button_width = 150;

	initgraph(window[0], window[1]);
	std::vector<std::wstring> buttonName;
	for (auto userId : currentUser->TeamIDs)
	{
		buttonName.push_back(registerInstance.teams[userId]->name);
	}
	buttonName.push_back(L"exit");
	int border = 100;

	int button_height = 0;
	{
		int h = window[1] - border * 2;
		button_height = h / buttonName.size();
	}

	//鼠标操作1
	MOUSEMSG m1;


	cleardevice();
	//IMAGE picture1;
	//loadimage(&picture1, "./firstbc.jpg", 760, 760);
	//putimage(0, 0, &picture1);
	setbkmode(TRANSPARENT);
	std::vector<SSRECT> rectButtons;
	{
		int height = button_height * 0.75;
		int space = button_height * 0.25;
		for (int i = 0; i < buttonName.size(); i++)
		{
			int top = border + button_height * i;
			int left = (window[0] - button_width) / 2;
			int height = button_height * 0.75;
			int width = button_width;
			rectButtons.push_back(SSRECT(left, top, width, height));
		}
	}

	setfillcolor(GREEN);

	wchar_t FirstTitle[20] = { L"Show Teams" };

	outtextxy(150, 50, FirstTitle);

	//三个选项的背景
	for (auto& rect : rectButtons)
	{

		fillrectangle(rect.l, rect.t, rect.r, rect.b);
	}

	setbkmode(TRANSPARENT);

	int i = 0;
	for (auto name : buttonName)
	{
		auto& rect = rectButtons[i];
		outtextxy(rect.l + 15, rect.t + 10, name.c_str());
		i++;
	}

	//进入主界面选项操作界面
	while (1)
	{
		bool b = false;
		m1 = GetMouseMsg();//获取鼠标操作
		for (int i = 0; i < buttonName.size(); i++)
		{
			auto& rect = rectButtons[i];

			if (rect.contain(m1.x, m1.y))
			{
				b = true;
				setlinecolor(RED);
				rectangle(rect.l, rect.t, rect.r, rect.b);
				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					if (buttonName[i] == L"exit")
					{
						cleardevice();
						PersonPage();
					}
					else
					{
						for (auto user : registerInstance.teams)
						{
							if (user.second->name == buttonName[i])
							{
								if (MessageBox(NULL, L"Do you want eare this", L"remove it", MB_OKCANCEL))
								{
									currentUser->easeRoom(user.first);
									cleardevice();
									PersonPage();
								}
							}
						}
					}
				}
			}
		}

		if (!b)
		{
			setlinecolor(WHITE);
			for (auto& rect : rectButtons)
			{
				rectangle(rect.l, rect.t, rect.r, rect.b);
			}
		}
	}

}
//登录首页
void FirstPage()
{
	int window[] = { 760,460 };
	int button_width = 150;

	initgraph(window[0], window[1]);

	std::vector<std::wstring> buttonName = {
		L"input name",
		L"input password",
		L"confirm",
		L"resign",
	};
	std::vector<std::wstring> buttonNameValue(2);
	int border = 100;

	int button_height = 0;
	{
		int h = window[1] - border * 2;
		button_height = h / buttonName.size();
	}

	//鼠标操作1
	MOUSEMSG m1;


	cleardevice();
	//IMAGE picture1;
	//loadimage(&picture1, "./firstbc.jpg", 760, 760);
	//putimage(0, 0, &picture1);
	setbkmode(TRANSPARENT);
	std::vector<SSRECT> rectButtons;
	{
		int height = button_height * 0.75;
		int space = button_height * 0.25;
		for (int i = 0; i < buttonName.size(); i++)
		{
			int top = border + button_height * i;
			int left = (window[0] - button_width) / 2;
			int height = button_height * 0.75;
			int width = button_width;
			rectButtons.push_back(SSRECT(left, top, width, height));
		}
	}

	setfillcolor(GREEN);

	wchar_t FirstTitle[20] = { L"login chat room" };

	outtextxy(150, 50, FirstTitle);

	//三个选项的背景
	for (auto& rect : rectButtons)
	{

		fillrectangle(rect.l, rect.t, rect.r, rect.b);
	}

	setbkmode(TRANSPARENT);

	for (int i = 0; i < buttonName.size(); i++)
	{
		auto name = buttonName[i];
		auto& rect = rectButtons[i];
		outtextxy(rect.l + 15, rect.t + 10, name.c_str());
	}

	//进入主界面选项操作界面
	while (1)
	{
		bool b = false;
		m1 = GetMouseMsg();//获取鼠标操作
		for (int i = 0; i < buttonName.size(); i++)
		{
			
			auto& rect = rectButtons[i];

			if (rect.contain(m1.x, m1.y))
			{
				b = true;
				setlinecolor(RED);
				rectangle(rect.l, rect.t, rect.r, rect.b);
				if (m1.uMsg == WM_LBUTTONDOWN)
				{
					if (buttonName[i] == L"confirm")
					{
						bool b = false;
						for (auto user : registerInstance.users)
						{
							if (user.second->check(buttonNameValue[0], buttonNameValue[1]))
							{
								b = true;
								currentUser = user.second;
								cleardevice();
								PersonPage();
							}
						}
							if(!b)
							{
								MessageBox(NULL, L"error password", L"confirm tip", MB_OK);
							}
					}
					else if (buttonName[i] == L"resign")
					{
						cleardevice();
						RegisterPage();
					}
					else
					{
						wchar_t retuenV[1000];
						if (InputBox(retuenV, 1000, buttonName[i].c_str(), 0L, buttonNameValue[i].c_str()))
						{
							buttonNameValue[i] = std::wstring(retuenV);
						}
					}
				}
			}
		}

		if (!b)
		{
			setlinecolor(WHITE);
			for (auto& rect : rectButtons)
			{
				rectangle(rect.l, rect.t, rect.r, rect.b);
			}
		}
	}

}

int main()
{
	// 初始化绘图窗口
	initgraph(640, 480);

	// 设置背景色为蓝色
	setbkcolor(BLUE);
	// 用背景色清空屏幕
	cleardevice();

	// 设置绘图色为红色
	setcolor(RED);
	// 画矩形
	rectangle(100, 100, 300, 300);

	// 按任意键退出
	FirstPage();
	return 0;
}