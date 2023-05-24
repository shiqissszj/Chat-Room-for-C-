#pragma once
#include<mysql.h>
#include<vector>
#include<iostream>
#include <string>
#include <sstream>
#include"user.h"
#include"workTeam.h"
#include<map>
#include <codecvt>
class SQLTool
{
public:
	//初始化SQL工具
	SQLTool()
	{
		MYSQL_RES* res;
		MYSQL_ROW row;
		mysql_init(&mysql);
		mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");

		if (mysql_real_connect(
			&mysql, "localhost", "root", "123456", "mysql", 3306, NULL, 0
		) == NULL)
		{
			std::cout << "error\n";
			exit(-1);
		}
		InitTables();
	}
	//初始化表
	void InitTables()
	{

		{
			std::string sql =
				"CREATE TABLE IF NOT EXISTS `t_user`  ( \
				`id` bigint ,\
				`name` varchar(256),\
				`phoneNum` varchar(256),\
				`address` varchar(1024),\
				`birth` varchar(256),\
				`pwd` varchar(256),\
				`TeamIDs` varchar(2046),\
				`UserIDs` varchar(2046),\
				`speechs` TEXT(20480),\
				PRIMARY KEY(`id`)\
			) ";
			int re = mysql_query(&mysql, sql.c_str());//从字符串换成const char*
			if (re != 0)
			{
				auto sd = mysql_error(&mysql);
				std::cout << "mysql_query failed!" << mysql_error(&mysql) << std::endl;
			}
		}
		{

			std::string sql = "CREATE TABLE IF NOT EXISTS `t_Team`  ( \
			`id` bigint ,\
			`name` varchar(1024),\
			`UserIDs` varchar(2046),\
			PRIMARY KEY(`id`)\
			) ";
			int re = mysql_query(&mysql, sql.c_str());
			if (re != 0)
			{
				std::cout << "mysql_query failed!" << mysql_error(&mysql) << std::endl;
			}
		}

	}
	//加载用户数据
	void LoadUser(std::map<int, user*>&users)
	{
		std::string sql = "SELECT * FROM `t_user`";
		int ret = mysql_query(&mysql,sql.c_str());
		if (ret != 0)
		{
			std::cout << "insert failed!" << mysql_error(&mysql) << std::endl;
		}
		else
		{
			auto result = mysql_store_result(&mysql);
			if (mysql_fetch_row(result) == NULL)
			{
				std::cout << "empty\n";
			}
			else
			{
				std::vector<int> indexes;
				
				MYSQL_ROW row;
				int num_field = mysql_num_fields(result);
				while (row = mysql_fetch_row(result))
				{
					int i = 0;
					//id
					auto id = converter.from_bytes(row[i++]);
					auto name = converter.from_bytes(row[i++]);
					auto phoneNum = converter.from_bytes(row[i++]);
					auto address = converter.from_bytes(row[i++]);
					auto birth = converter.from_bytes(row[i++]);
					auto pwd = converter.from_bytes(row[i++]);

					auto TeamIDs = converter.from_bytes(row[i++]);
					auto UserIDs = converter.from_bytes(row[i++]);
					auto speechs = converter.from_bytes(row[i++]);
					auto user1 = new user(name, phoneNum, address, birth, pwd, _wtoi(id.c_str()));
					users.insert({ _wtoi(id.c_str()),user1 });
					user1->TeamIDs = SplitInt(TeamIDs);
					user1->UserIDs = SplitInt(UserIDs);
					user1->speechs = SplitWString(speechs);
				}
				
			}
		}
	}
	//加载群组数据
	void LoadTeams(std::map<int, workTeam*>& teams)
	{
		std::string sql = "SELECT * FROM `t_team`";
		int ret = mysql_query(&mysql, sql.c_str());
		if (ret != 0)
		{
			std::cout << "insert failed!" << mysql_error(&mysql) << std::endl;
		}
		else
		{
			auto result = mysql_store_result(&mysql);
			if (mysql_fetch_row(result) == NULL)
			{
				std::cout << "empty\n";
			}
			else
			{
				std::vector<int> indexes;

				MYSQL_ROW row;
				int num_field = mysql_num_fields(result);
				while (row = mysql_fetch_row(result))
				{
					int i = 0;
					//id
					auto id = converter.from_bytes(row[i++]);
					auto name = converter.from_bytes(row[i++]);

					auto UserIDs = converter.from_bytes(row[i++]);
					auto team = new workTeam(name, _wtoi(id.c_str()));
					team->users = SplitInt(UserIDs);
					teams.insert({ _wtoi(id.c_str()),team });
				}

			}
		}

	}
	//将int值连城字符串数组
	std::wstring MergeInt(std::vector<int> values)
	{
		std::wstringstream ss;
		for (auto value : values)
		{
			ss << std::to_wstring(value) << "|";
		}
		return ss.str();
	}

	//将字符串数组拆成int值
	std::vector<int> SplitInt(std::wstring s)
	{
		std::vector<int> values;
		std::wstringstream ss;
		ss.clear();
		ss.str(L"");
		ss.str(s);
		std::wstring tmp;
		while (getline(ss, tmp, L'|'))
			values.push_back(_wtoi(tmp.c_str()));

		return values;
	}
	//将字符串值连城字符串数组

	std::wstring MergeWString(std::vector<std::wstring> values)
	{
		std::wstringstream ss;
		for (auto value : values)
		{
			ss << value << "|";
		}
		return ss.str();
	}
	//将字符串数组拆成字符串值
	std::vector <std::wstring> SplitWString(std::wstring s)
	{
		std::vector<std::wstring> values;
		std::wstringstream ss;
		ss.clear();
		ss.str(L"");
		ss.str(s);
		std::wstring tmp;
		while (getline(ss, tmp, L'|'))
			values.push_back(tmp.c_str());
		return values;
	}

	//插入用户
	void insertUser(user* user1)
	{
		std::stringstream ss;
		ss << "insert `t_user` (`id`,`name`,`phoneNum`,`address`,`birth`,`pwd`,`TeamIDs`,`UserIDs`,`speechs`)\
			values(";
		ss << std::to_string(user1->id) << ","
			<< "'" << converter.to_bytes(user1->name.c_str())					<< "',"
			<< "'" << converter.to_bytes(user1->phoneNum.c_str())				<< "',"
			<< "'" << converter.to_bytes(user1->address.c_str())				<< "',"
			<< "'" << converter.to_bytes(user1->birth.c_str())					<< "',"
			<< "'" << converter.to_bytes(user1->pwd.c_str())					<< "',"
			<< "'" << converter.to_bytes(MergeInt(user1->TeamIDs).c_str())		<< "',"
			<< "'" << converter.to_bytes(MergeInt(user1->UserIDs).c_str())		<< "',"
			<< "'" << converter.to_bytes(MergeWString(user1->speechs).c_str())	<< "')";
		std::string sql = ss.str();

		auto re = mysql_query(&mysql, sql.c_str());
		if (re == 0)
		{
			int count = mysql_affected_rows(&mysql);
			std::cout << "mysql_affected_rows " << count << " id =" <<
				mysql_insert_id(&mysql) << std::endl;
		}
		else
		{
			std::cout << "insert failed!" << mysql_error(&mysql) << std::endl;
		}
	}
	//插入群组
	void insertTeam(workTeam* team)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::stringstream ss;
		ss << "insert `t_team` (`id`,`name`,`UserIDs`)\
			values(";
		ss << std::to_string(team->id)  << "',"
			<< "'" << converter.to_bytes(team->name.c_str())            << "',"
			<< "'" << converter.to_bytes(MergeInt(team->users).c_str()) << "')";
		std::string sql = ss.str();

		auto re = mysql_query(&mysql, sql.c_str());
		if (re == 0)
		{
			int count = mysql_affected_rows(&mysql);
			std::cout << "mysql_affected_rows " << count << " id =" <<
				mysql_insert_id(&mysql) << std::endl;
		}
		else
		{
			std::cout << "insert failed!" << mysql_error(&mysql) << std::endl;
		}
	}
	//修改用户
	void modifyUser(user* user1)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::stringstream ss;
		ss << "update t_user set "
			<< "`name`='" << converter.to_bytes(user1->name.c_str()) << "',"
			<< "`phoneNum`='" << converter.to_bytes(user1->phoneNum.c_str()) << "',"
			<< "`address`='" << converter.to_bytes(user1->address.c_str()) << "',"
			<< "`birth`='" << converter.to_bytes(user1->birth.c_str()) << "',"
			<< "`pwd`='" << converter.to_bytes(user1->pwd.c_str()) << "',"
			<< "`TeamIDs`='" << converter.to_bytes(MergeInt(user1->TeamIDs).c_str()) << "',"
			<< "`UserIDs`='" << converter.to_bytes(MergeInt(user1->UserIDs).c_str()) << "',"
			<< "`speechs`='" << converter.to_bytes(MergeWString(user1->speechs).c_str()) << "'"
			<< " where id =" << std::to_string(user1->id);

		std::string sql = ss.str();
		auto re = mysql_query(&mysql, sql.c_str());
		
		if (re == 0)
		{
			int count = mysql_affected_rows(&mysql);
			std::cout << "update mysql_affected_rows " << count << std::endl;
		}
		else
		{
			std::cout << "update failed!" << mysql_error(&mysql) << std::endl;
		}
	}
	//修改群组
	void modifyTeam(workTeam* team)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::stringstream ss;
		ss << "update t_team set "
			<< "`name`='" << converter.to_bytes(team->name.c_str()) << "',"
			<< "`UserIDs`='" << converter.to_bytes(MergeInt(team->users).c_str()) << "'"
			<< " where id =" << std::to_string(team->id);

		std::string sql = ss.str();
		auto re = mysql_query(&mysql, sql.c_str());

		if (re == 0)
		{
			int count = mysql_affected_rows(&mysql);
			std::cout << "update mysql_affected_rows " << count << std::endl;
		}
		else
		{
			std::cout << "update failed!" << mysql_error(&mysql) << std::endl;
		}
	}

	//删除用户
	void removeUser(user* user1)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::stringstream ss;
		ss << "delete from t_user "
			<< " where id =" << std::to_string(user1->id);

		std::string sql = ss.str();
		auto re = mysql_query(&mysql, sql.c_str());

		if (re == 0)
		{
			int count = mysql_affected_rows(&mysql);
			std::cout << "delete mysql_affected_rows " << count << std::endl;
		}
		else
		{
			std::cout << "delete failed!" << mysql_error(&mysql) << std::endl;
		}
	}
	//删除群组
	void removeTeam(workTeam* team)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::stringstream ss;
		ss << "delete from t_team "
			<< " where id =" << std::to_string(team->id);

		std::string sql = ss.str();
		auto re = mysql_query(&mysql, sql.c_str());

		if (re == 0)
		{
			int count = mysql_affected_rows(&mysql);
			std::cout << "delete mysql_affected_rows " << count << std::endl;
		}
		else
		{
			std::cout << "delete failed!" << mysql_error(&mysql) << std::endl;
		}
	}


	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	MYSQL mysql;
};
