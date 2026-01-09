#pragma once
#include "KamataEngine.h"
#include <vector>

enum class MapChipType { kBlank, kBlock };



struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

class MapChipField {
private:
	

	// 1ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;
	// ブロックの数
	static inline const uint32_t kNumBlockVertical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	MapChipData mapChipData_;

public:
	struct IndexSet {
		uint32_t xIndex;
		uint32_t yIndex;
	};

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
	KamataEngine::Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);
	IndexSet GetMapChipIndexSetByPosition(const KamataEngine::Vector3& position);
	Rect GetRectByIndex(uint32_t xIndex,uint32_t yIndex);
};
