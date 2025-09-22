#pragma once
#include<string>
#include<vector>

class LoadCsv{
	LoadCsv() = default;
	~LoadCsv() = default;

	//	1行のCSVデータを分割してベクターで返す
	static std::vector<std::string> splitCsvLine(const std::string& line);
public:
	static std::vector<std::vector<std::string>> Load(const std::string& filePath);
};