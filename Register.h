#pragma once
#include<Windows.h>
#include"user.h"
#include"workTeam.h"
#include<map>
#include"SQLTool.h"
class CRegister
{
public:
	CRegister()
	{
		last_userID = std::chrono::system_clock::now().time_since_epoch().count();
		last_TeamID = std::chrono::system_clock::now().time_since_epoch().count();
		toll.LoadUser(users);
		toll.LoadTeams(teams);
	}
	//ע���û�
	user* resignUser(std::wstring name,
		std::wstring phoneNum,
		std::wstring address,
		std::wstring birth, std::wstring pwd)
	{
		int id = std::chrono::system_clock::now().time_since_epoch().count();
		if (last_userID == id)
		{
			id++;
		}
		last_userID = id;
		auto user1 = new user(name, phoneNum, address, birth, pwd, id);

		toll.insertUser(user1);
		users.insert({ id,user1 });

		return user1;
	}

	//ɾ���û�
	void logoutUser(user* pUser)
	{
		users.erase(pUser->id);
		toll.removeUser(pUser);
	}

	//ע����ϵ��
	workTeam* resignWorkTeam(std::wstring name)
	{
		int id = std::chrono::system_clock::now().time_since_epoch().count();
		if (last_TeamID == id)
		{
			id++;
		}
		last_TeamID = id;
		auto team1 = new workTeam(name, id);
		toll.insertTeam(team1);
		teams.insert({ id,team1 });

		return team1;
	}

	//ɾ����ϵ��
	void logoutWorkTeam(workTeam* pTeam)
	{
		teams.erase(pTeam->id);
		toll.removeTeam(pTeam);
	}

	//�û�������ϵ��
	void connectTeamAndUser(workTeam* pTeam, user* pUser)
	{
		pTeam->join(pUser->id);
		pUser->addTeam(pTeam->id);
		toll.modifyTeam(pTeam);
		toll.modifyUser(pUser);
	}


	//�û���ϵ�û�����ϵ�˷����֣�һ.PersonA ӵ�� PersonB��������Ϣ����.PersonA ӵ�� ��A �� �����˵���Ϣ��
	void connectUserAndUser(user* pUser, user* pUser1)
	{
		pUser->addUser(pUser1->id);
		toll.modifyUser(pUser);
	}

	//ɾ����ϵ��
	void disconnectTeamAndUser(workTeam* pTeam, user* pUser)
	{
		pTeam->exit(pUser->id);
		pUser->easeRoom(pTeam->id);
		toll.modifyTeam(pTeam);
		toll.modifyUser(pUser);
	}

	//ɾ����ϵ��
	void disconnectUserAndUser(user* pUser, user* pUser1)
	{
		pUser->easeUser(pUser1->id);
		toll.modifyUser(pUser);
	}

	//��ʾ�û����е���Ϣ���ṹ����
	//me: {
	//1. I sleep all night
	//2. My classmates don't say martial ethics
	//3. John is my pet 
	// }
	//John:{
	//1. I'm not dog
	//2. what are you bark for?
	// }
	//Jackson:
	// {
	// 1.people mountain people sea }
	std::vector<std::pair<std::wstring,std::vector<std::wstring>>> showSpeechs(user* pUser)
	{
		std::vector<std::pair<std::wstring, std::vector<std::wstring>>> speechSet;
	

		//SELF
		pUser->speechs;

		//OTHER
		std::vector<int> userss;
		for (auto id : pUser->TeamIDs)
		{
			auto users1 = teams.find(id)->second->users;
			userss.insert(userss.end(), users1.begin(), users1.end());
		}


		std::map<int, int> map1;
		for (auto user213 :  userss)
		{
			map1.insert({ user213 ,user213 });
		}

		{
			speechSet.push_back({ pUser->name,pUser->speechs });
		}


		for (auto it : map1)
		{
			auto user = users[it.first];
			speechSet.push_back({ user->name,user->speechs });
		}
	
		return speechSet;
	}
	
	std::vector<std::wstring> showAllTeams()
	{
		std::vector<std::wstring> teaml;
		for (auto team : teams)
		{
			teaml.push_back(team.second->name);
		}
			return teaml;
	}

	std::vector<std::wstring> showAllUsers()
	{
		std::vector<std::wstring> users1;
		for (auto it : users)
		{
			users1.push_back(it.second->name);
		}
		return users1;
	}

	std::map<int, user*>users;
	std::map<int ,workTeam*>teams;
	SQLTool toll;
	int last_userID;
	int last_TeamID;
};

