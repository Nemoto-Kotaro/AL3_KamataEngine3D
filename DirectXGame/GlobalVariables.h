#pragma once
#include "SelfVector.h"
#include <map>
#include <string>
#include <variant>

class GlobalVariables {
public:
	static GlobalVariables* GetInstance();
	void CreatGroup(const std::string& groupName);

	void AddItem(const std::string& groupName, const std::string& key, int32_t value);
	void AddItem(const std::string& groupName, const std::string& key, float value);
	void AddItem(const std::string& groupName, const std::string& key, const NemotoLibrary::SelfVec3 value);

	void SetValue(const std::string& groupName, const std::string& key, int32_t value);
	void SetValue(const std::string& groupName, const std::string& key, float value);
	void SetValue(const std::string& groupName, const std::string& key, const NemotoLibrary::SelfVec3 value);

	int32_t GetIntValue(const std::string& groupName, const std::string& key) const;
	float GetFloatValue(const std::string& groupName, const std::string& key) const;
	NemotoLibrary::SelfVec3 GetVector3Value(const std::string& groupName, const std::string& key) const;

	void Update();

	void SaveFile(const std::string& groupName);
	void LoadFiles();
	void LoadFile(const std::string& groupName);

private:

	GlobalVariables() = default;
	~GlobalVariables() = default;
	GlobalVariables(const GlobalVariables&) = delete;
	GlobalVariables& operator=(const GlobalVariables&) = delete;

	using Item = std::variant<int32_t, float, NemotoLibrary::SelfVec3>;

	using Group = std::map<std::string, Item>;

	std::map<std::string, Group> datas_;

	const std::string kDirectoryPath = "Resources/GlobalVariables/";
};
