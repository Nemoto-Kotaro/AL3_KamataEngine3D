#pragma once
#include "KamataEngine.h"

//====================
//便利な数学関数など
//====================

/// <summary>
/// クランプ(最小値,最大値止め)
/// </summary>
/// <param name="num">参照する値</param>
/// <param name="low">最小値</param>
/// <param name="high">最大値</param>
/// <returns>結果</returns>
int Clamp(const int& num, const int min, const int max);
float Clamp(const float& num, const float min, const float max);

/// <summary>
/// 全体に対する値の比率を取る(0~1)
/// 最小最大の外は丸められる
/// </summary>
/// <param name="value">値</param>
/// <param name="min">最小値</param>
/// <param name="max">最大値</param>
/// <returns>比率(0~1)</returns>
float Ratio(const int value, const int min, const int max);
float Ratio(const float value, const float min, const float max);

/// <summary>
/// 数字は範囲内か
/// </summary>
/// <param name="num">取る値</param>
/// <param name="min">範囲下限</param>
/// <param name="max">範囲上限</param>
/// <returns>真偽値</returns>
bool IsInRange(int num, const int min, const int max);

/// <summary>
/// 線形補間
/// </summary>
/// <param name="startPos">始まり</param>
/// <param name="endPos">終わり</param>
/// <param name="t">間の位置の比率</param>
/// <returns>その位置</returns>
float Lerp(const float& start, const float& end, const float t);


//degreeの角度
float DegTheta(float degree);

/// <summary>
/// 角度を円を分割した値で求める
/// 右回り
/// </summary>
/// <param name="index">どのくらいか</param>
/// <param name="divisions">全体の分割数</param>
/// <returns>2*MPI*index/divisions</returns>
float AngleByIndex(int index, int divisions);