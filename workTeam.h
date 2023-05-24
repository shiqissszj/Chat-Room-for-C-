#pragma once
#include<string>
#include<vector>
//room 
class workTeam
{
public:
	workTeam(std::wstring name,int id)
	{
		this->name = name;
		this->id=  id;
	}

	//join in chat
	void join(int userID)
	{
		for (auto userID1 : users)
		{
			if (userID1 == userID)
			{
				return;
			}
		}
		users.push_back(userID);

	}

	//exit room
	void exit(int userID)
	{
		int i = 0;
		for (auto user1 : users)
		{
			if (user1 == userID)
			{
				users.erase(users.begin() + i);
				break;
			}
			i++;
		}
	}
	void Save()
	{

	}
	//Team( id
	int id;

	//Team( name
	std::wstring name;

	std::vector<int> users;
};

