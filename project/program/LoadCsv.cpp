#include "LoadCsv.h"
#include<sstream>
#include<fstream>
#include<exception>

/// <summary>
/// CSV形式の1行の文字列をカンマ区切りで分割し、各セルを文字列のベクターとして返します。
/// </summary>
/// <param name="line">分割するCSV形式の1行の文字列。</param>
/// <returns>分割された各セルを格納したstd::vector<std::string>。</returns>
std::vector<std::string> LoadCsv::splitCsvLine(const std::string& line)
{
	//	分解したデータを格納するベクター
	std::vector<std::string> result;
	//	文字列ストリームに変換
	std::stringstream ss(line);
	//	カンマ区切りで分割
	std::string cell;

	while (std::getline(ss, cell, ',')) {
		result.push_back(cell);
	}

	return result;
}


/// <summary>
/// 指定されたファイルパスからCSVファイルを読み込み、各行を文字列のベクターとして返します。
/// </summary>
/// <param name="filePath">読み込むCSVファイルのパス。</param>
/// <returns>CSVファイルの各行を表す文字列のベクターのベクター。</returns>
std::vector<std::vector<std::string>> LoadCsv::Load(const std::string& filePath)
{
	//	ファイル展開
	std::ifstream file(filePath);
	//	開けなかったら例外を投げる
	if (!file.is_open()) {
		throw std::runtime_error("csvが開けませんでした: " + filePath);
	}
	//	読み込んだデータを格納するベクター
	std::vector<std::vector<std::string>> rows;
	//	1行ずつ読み込み
	std::string line;

	//	ヘッダー行を読み飛ばす
	if(std::getline(file, line)){}

	//	データ行を読み込み
	while (std::getline(file, line)) {
		//	1行を分割してベクターに追加
		rows.push_back(splitCsvLine(line));
	}

	return rows;
}
