#include "StageManager.h"
#include <cassert>
#include <fstream>
#include <sstream>

void StageManager::SetCurrentStageIndex(int32_t index) {
	assert(index >= 0 && index < static_cast<int32_t>(stageDatas_.size()));
	currentStageIndex_ = index;
}

const StageData& StageManager::GetStageData(int32_t index) const {
	assert(index >= 0 && index < static_cast<int32_t>(stageDatas_.size()));
	return stageDatas_[index];
}

void StageManager::SetCurrentStageIndexByName(const std::string& name) {
	for (size_t i = 0; i < stageDatas_.size(); i++) {
		if (stageDatas_[i].name == name) {
			currentStageIndex_ = static_cast<int32_t>(i);
			return;
		}
	}

	assert(false && "指定されたステージ名は存在しません");
}

void StageManager::StageLoadCSV() {
	const std::string filePath = "Resources/stageDatas.csv";
	std::ifstream file;
	file.open(filePath);
	assert(file.is_open() && "ステージデータファイルが存在しません");

	std::stringstream stageCSV;
	stageCSV << file.rdbuf();
	file.close();

	std::string line;

	while (getline(stageCSV, line)) {
		std::istringstream lineStream(line);

		StageData stageData;

		std::string word;
		std::getline(lineStream, word, ',');

		stageData.name = word;

		std::getline(lineStream, word, ',');
		stageData.timeLimit = std::stoi(word);

		stageDatas_.push_back(stageData);
	}
}