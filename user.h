#pragma once
#include<string >
#include<vector>
#include<chrono>
class user
{
public:
	//用户
	user(std::wstring name,
		std::wstring phoneNum,
		std::wstring address,
		std::wstring birth,
		std::wstring pwd,
		int id
	) {
		this->name = name;
		this->phoneNum = phoneNum;
		this->address = address;
		this->birth = birth;
		this->id = id;
		this->pwd = pwd;
	}
	//加入群
	void addTeam(int TeamID)
	{
		for (auto TeamID1 : TeamIDs)
		{
			if (TeamID1 == TeamID)
			{
				return;
			}
		}
		TeamIDs.push_back(TeamID);
	}
	//退出群
	void easeRoom(int TeamID)
	{
		int i = 0;
		for (auto TeamID1 : TeamIDs)
		{
			if (TeamID1 == TeamID)
			{
				TeamIDs.erase(TeamIDs.begin() + i);
				break;
			}
			i++;
		}
	}

	//登录检查
	bool check(std::wstring name , std::wstring pwd)
	{
		return this->name == name && this->pwd == pwd;
	}
	//发送消息
	void say(std::wstring speech)
	{
		speechs.push_back(speech);
	}
	//撤回消息
	void withdrawal(std::wstring speech)
	{
		int i = 0;
		for (auto speech1 : speechs)
		{
			if (speech1 == speech)
			{
				speechs.erase(speechs.begin() + i);
				break;
			}
			i++;
		}
	}
	//更改消息
	void alter (std::wstring speech)
	{
		bool find = false;
		for (auto &speech1 : speechs)
		{
			if(speech1 == speech)
				speech1 = speech;
		}
	}


	//添加联系人
	void addUser(int id)
	{
		for (auto userid : UserIDs)
		{
			if (userid == id)
			{
				return;
			}
		}
		UserIDs.push_back(id);
	}
	//删除联系人
	void easeUser(int id)
	{
		int i = 0;
		for (auto userid : UserIDs)
		{
			if (userid == id)
			{
				UserIDs.erase(UserIDs.begin() + i);
				break;
			}
			i++;
		}
	}


	
	
	
	std::vector<int> TeamIDs;
	std::vector<int> UserIDs;
	std::vector<std::wstring> speechs;




	int id;

	std::wstring name;
	
	std::wstring phoneNum;
	std::wstring address;
	std::wstring birth;
	std::wstring pwd;
	
};
