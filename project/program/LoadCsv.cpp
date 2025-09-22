#include "LoadCsv.h"
#include<sstream>
#include<fstream>
#include<exception>

/// <summary>
/// CSV�`����1�s�̕�������J���}��؂�ŕ������A�e�Z���𕶎���̃x�N�^�[�Ƃ��ĕԂ��܂��B
/// </summary>
/// <param name="line">��������CSV�`����1�s�̕�����B</param>
/// <returns>�������ꂽ�e�Z�����i�[����std::vector<std::string>�B</returns>
std::vector<std::string> LoadCsv::splitCsvLine(const std::string& line)
{
	//	���������f�[�^���i�[����x�N�^�[
	std::vector<std::string> result;
	//	������X�g���[���ɕϊ�
	std::stringstream ss(line);
	//	�J���}��؂�ŕ���
	std::string cell;

	while (std::getline(ss, cell, ',')) {
		result.push_back(cell);
	}

	return result;
}


/// <summary>
/// �w�肳�ꂽ�t�@�C���p�X����CSV�t�@�C����ǂݍ��݁A�e�s�𕶎���̃x�N�^�[�Ƃ��ĕԂ��܂��B
/// </summary>
/// <param name="filePath">�ǂݍ���CSV�t�@�C���̃p�X�B</param>
/// <returns>CSV�t�@�C���̊e�s��\��������̃x�N�^�[�̃x�N�^�[�B</returns>
std::vector<std::vector<std::string>> LoadCsv::Load(const std::string& filePath)
{
	//	�t�@�C���W�J
	std::ifstream file(filePath);
	//	�J���Ȃ��������O�𓊂���
	if (!file.is_open()) {
		throw std::runtime_error("csv���J���܂���ł���: " + filePath);
	}
	//	�ǂݍ��񂾃f�[�^���i�[����x�N�^�[
	std::vector<std::vector<std::string>> rows;
	//	1�s���ǂݍ���
	std::string line;

	//	�w�b�_�[�s��ǂݔ�΂�
	if(std::getline(file, line)){}

	//	�f�[�^�s��ǂݍ���
	while (std::getline(file, line)) {
		//	1�s�𕪊����ăx�N�^�[�ɒǉ�
		rows.push_back(splitCsvLine(line));
	}

	return rows;
}
