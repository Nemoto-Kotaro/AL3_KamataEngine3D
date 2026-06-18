#pragma once
#include <variant>
#include "SelfVector.h"
#include <map>
#include <string>

class GlobalVariables {
public:
	static GlobalVariables* GetInstance();
	void CreatGroup(const std::string& groupName);
	void SetValue(const std::string& groupName, const std::string& key, int32_t value);
	void SetValue(const std::string& groupName, const std::string& key, float value);
	void SetValue(const std::string& groupName, const std::string& key, const NemotoLibrary::SelfVec3 value);

	void Update();

private:
	GlobalVariables() = default;
	~GlobalVariables() = default;
	GlobalVariables(const GlobalVariables&) = delete;
	GlobalVariables& operator=(const GlobalVariables&) = delete;

	struct Item {
		std::variant<int32_t, float, NemotoLibrary::SelfVec3> value;
	};

	struct Group {
		std::map<std::string, Item> items;
	};

	std::map<std::string, Group> datas_;

};
