#pragma once
#include<string >
#include<vector>
#include<chrono>
class user
{
public:
	//�û�
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
	//����Ⱥ
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
	//�˳�Ⱥ
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

	//��¼���
	bool check(std::wstring name , std::wstring pwd)
	{
		return this->name == name && this->pwd == pwd;
	}
	//������Ϣ
	void say(std::wstring speech)
	{
		speechs.push_back(speech);
	}
	//������Ϣ
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
	//������Ϣ
	void alter (std::wstring speech)
	{
		bool find = false;
		for (auto &speech1 : speechs)
		{
			if(speech1 == speech)
				speech1 = speech;
		}
	}


	//�����ϵ��
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
	//ɾ����ϵ��
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
