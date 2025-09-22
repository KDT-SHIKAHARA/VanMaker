#include "loader_Sound.h"

#include<DxLib.h>

/// <summary>
/// 指定されたファイルパスからサウンドをロードし、Resourceオブジェクトの共有ポインタを作成します。
/// </summary>
/// <param name="filePath">ロードするサウンドファイルのパス。</param>
/// <returns>正常にロードされた場合はResourceのstd::shared_ptr、失敗した場合はnullptrを返します。</returns>
std::shared_ptr<Resource> SoundLoader::createSound(const std::string& filePath)
{
	// DxLibでサウンドをロード
	int handle = LoadSoundMem(filePath.c_str());
	if (handle == -1) {
		// ロード失敗
		return nullptr;
	}
	return std::make_shared<Resource>(handle);
}

/// <summary>
/// 指定されたファイルパスのサウンドリソースをロードし、共有ポインタとして返します。既にロード済みの場合はキャッシュから取得します。
/// </summary>
/// <param name="filePath">ロードするサウンドファイルのパス。</param>
/// <returns>ロードされたサウンドリソースへの std::shared_ptr。</returns>
std::shared_ptr<Resource> SoundLoader::LoadSound(const std::string& filePath)
{
	//	検索
   auto it = sounds_.find(filePath);
   //	存在していたら
   if (it != sounds_.end()) {
	   return it->second;
   };

   //	存在していなかったら新規作成して登録
   auto sound = createSound(filePath);
   sounds_.insert({ filePath,sound });
   return sound;
}
