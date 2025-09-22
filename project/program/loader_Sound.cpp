#include "loader_Sound.h"

#include<DxLib.h>

/// <summary>
/// �w�肳�ꂽ�t�@�C���p�X����T�E���h�����[�h���AResource�I�u�W�F�N�g�̋��L�|�C���^���쐬���܂��B
/// </summary>
/// <param name="filePath">���[�h����T�E���h�t�@�C���̃p�X�B</param>
/// <returns>����Ƀ��[�h���ꂽ�ꍇ��Resource��std::shared_ptr�A���s�����ꍇ��nullptr��Ԃ��܂��B</returns>
std::shared_ptr<Resource> SoundLoader::createSound(const std::string& filePath)
{
	// DxLib�ŃT�E���h�����[�h
	int handle = LoadSoundMem(filePath.c_str());
	if (handle == -1) {
		// ���[�h���s
		return nullptr;
	}
	return std::make_shared<Resource>(handle);
}

/// <summary>
/// �w�肳�ꂽ�t�@�C���p�X�̃T�E���h���\�[�X�����[�h���A���L�|�C���^�Ƃ��ĕԂ��܂��B���Ƀ��[�h�ς݂̏ꍇ�̓L���b�V������擾���܂��B
/// </summary>
/// <param name="filePath">���[�h����T�E���h�t�@�C���̃p�X�B</param>
/// <returns>���[�h���ꂽ�T�E���h���\�[�X�ւ� std::shared_ptr�B</returns>
std::shared_ptr<Resource> SoundLoader::LoadSound(const std::string& filePath)
{
	//	����
   auto it = sounds_.find(filePath);
   //	���݂��Ă�����
   if (it != sounds_.end()) {
	   return it->second;
   };

   //	���݂��Ă��Ȃ�������V�K�쐬���ēo�^
   auto sound = createSound(filePath);
   sounds_.insert({ filePath,sound });
   return sound;
}
