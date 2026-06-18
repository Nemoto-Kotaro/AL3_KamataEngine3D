#pragma once
#include "KamataEngine.h"
#include "SelfVector.h"
#include <vector>

enum class MapChipType { kBlank, kBlock,kPlayer,kEnemy };

struct MapChipDataUnit {
	MapChipType type;
	uint8_t subID;
};

enum MapChipCharIndex { kChipType = 0, kChipSubID = 1 };

struct MapChipData {
	std::vector<std::vector<MapChipDataUnit>> data;
};

struct IndexSet {
	uint32_t xIndex;
	uint32_t yIndex;
};

class MapChipField {
private:
	// 1ブロックのサイズ
	static inline float kBlockWidth = 1.0f;
	static inline float kBlockHeight = 1.0f;
	// ブロックの数
	static inline const uint32_t kNumBlockVertical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	MapChipData mapChipData_;

public:
	struct Rect {
		float left;
		float right;
		float bottom;
		float top;
	};

	uint32_t GetNumBlockVertical() { return kNumBlockVertical; };
	uint32_t GetNumBlockHorizontal() { return kNumBlockHorizontal; };

	void ResetMapChipData();
	void LoadMapChipCsv(const std::string& filePath);
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);
	NemotoLibrary::SelfVec3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);
	IndexSet GetMapChipIndexSetByPosition(const NemotoLibrary::SelfVec3& position);
	uint8_t GetMapChipSubIDByIndex(uint32_t xIndex, uint32_t yIndex);
	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);
};
