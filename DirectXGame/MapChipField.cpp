#include "MapChipField.h"
#include <fstream>
#include <map>
#include <sstream>

using namespace KamataEngine;
using namespace NemotoLibrary;

// 名づけ
namespace {
std::map<char, MapChipType> mapChipTypeTable = {
    {'B', MapChipType::kBlock },
    {'P', MapChipType::kPlayer},
    {'E', MapChipType::kEnemy },
};
}

// マップチップリセット
void MapChipField::ResetMapChipData() {
	mapChipData_.data.clear();
	mapChipData_.data.resize(kNumBlockVertical);
	for (std::vector<MapChipDataUnit>& mapChipDataLine : mapChipData_.data) {
		mapChipDataLine.resize(kNumBlockHorizontal);
	}
}

// CSVからマップチップを読み込む
void MapChipField::LoadMapChipCsv(const std::string& filePath) {
	ResetMapChipData();

	// ファイルを開いて内容を保管
	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	std::stringstream mapChipCsv;
	mapChipCsv << file.rdbuf();

	file.close();

	for (uint32_t i = 0; i < kNumBlockVertical; ++i) {
		std::string line;
		getline(mapChipCsv, line);

		std::istringstream lineStream(line);

		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			std::string word;
			std::getline(lineStream, word, ',');

			if (word.empty()) {
				continue;
			}

			if (!mapChipTypeTable.contains(word[kChipType])) {
				continue;
			}

			mapChipData_.data[i][j].type = mapChipTypeTable[word[kChipType]];

			if (word.size() <= kChipSubID) {
				continue;
			}

			mapChipData_.data[i][j].subID = static_cast<uint8_t>(word[kChipSubID] - '0');
		}
	}
}

MapChipType MapChipField::GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) {
	if (xIndex < 0 || kNumBlockHorizontal - 1 < xIndex) {
		return MapChipType::kBlank;
	}

	if (yIndex < 0 || kNumBlockVertical - 1 < yIndex) {
		return MapChipType::kBlank;
	}

	return mapChipData_.data[yIndex][xIndex].type;
}

uint8_t MapChipField::GetMapChipSubIDByIndex(uint32_t xIndex, uint32_t yIndex) {
	if (xIndex < 0 || kNumBlockHorizontal - 1 < xIndex) {
		return static_cast<uint8_t>(255);
	}

	if (yIndex < 0 || kNumBlockVertical - 1 < yIndex) {
		return static_cast<uint8_t>(255);
	}

	return mapChipData_.data[yIndex][xIndex].subID;
}

NemotoLibrary::SelfVec3 MapChipField::GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex) {
	return SelfVec3(kBlockWidth * static_cast<float>(xIndex), kBlockHeight * static_cast<float>(kNumBlockVertical - 1 - yIndex), 0.0f);
}

IndexSet MapChipField::GetMapChipIndexSetByPosition(const SelfVec3& position) {
	IndexSet indexSet = {};
	indexSet.xIndex = static_cast<uint32_t>((position.x + (kBlockWidth / 2.0f)) / kBlockWidth);
	indexSet.yIndex = kNumBlockVertical - 1 - static_cast<uint32_t>((position.y + (kBlockHeight / 2.0f)) / kBlockHeight);
	return indexSet;
}

MapChipField::Rect MapChipField::GetRectByIndex(uint32_t xIndex, uint32_t yIndex) {
	SelfVec3 center = GetMapChipPositionByIndex(xIndex, yIndex);
	Rect rect;
	rect.left = center.x - kBlockWidth / 2.0f;
	rect.right = center.x + kBlockWidth / 2.0f;
	rect.top = center.y + kBlockHeight / 2.0f;
	rect.bottom = center.y - kBlockHeight / 2.0f;

	return rect;
}