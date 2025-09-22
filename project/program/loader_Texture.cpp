#include "loader_Texture.h"

#include<DxLib.h>

/// <summary>
/// �w�肳�ꂽ�t�@�C���p�X����e�N�X�`�����쐬���AResource�̋��L�|�C���^��Ԃ��܂��B
/// </summary>
/// <param name="filePath">�e�N�X�`���t�@�C���̃p�X��\��������B</param>
/// <returns>�쐬���ꂽResource�I�u�W�F�N�g��std::shared_ptr�B���[�h�Ɏ��s�����ꍇ��nullptr��Ԃ��܂��B</returns>
std::shared_ptr<Resource> TextureLoader::createTexture(const std::string& filePath)
{
	//  DxLib�Ńe�N�X�`�������[�h
    int handle = LoadGraph(filePath.c_str());
    if (handle == -1) {
        // ���[�h���s
        return nullptr;
    }
	return std::make_shared<Resource>(handle);
}

/// <summary>
/// �w�肳�ꂽ�t�@�C���p�X����e�N�X�`����ǂݍ��݁A���L�|�C���^�Ƃ��ĕԂ��܂��B���ɓǂݍ��܂�Ă���ꍇ�̓L���b�V�����ꂽ�e�N�X�`����Ԃ��܂��B
/// </summary>
/// <param name="filePath">�ǂݍ��ރe�N�X�`���t�@�C���̃p�X�B</param>
/// <returns>�ǂݍ��܂ꂽ�e�N�X�`���� std::shared_ptr<Resource>�B</returns>
std::shared_ptr<Resource> TextureLoader::LoadTexture(const std::string& filePath)
{
    //  ����
	auto it= textures_.find(filePath);
    //  ���݂��Ă�����
    if (it != textures_.end()) {
		return it->second;
    }

	//  ���݂��Ă��Ȃ�������V�K�쐬���ēo�^
	auto texture = createTexture(filePath);
	textures_.insert({ filePath, texture });
	return texture;
}
