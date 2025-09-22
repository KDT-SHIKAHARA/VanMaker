#include "loader_Texture.h"

#include<DxLib.h>

/// <summary>
/// 指定されたファイルパスからテクスチャを作成し、Resourceの共有ポインタを返します。
/// </summary>
/// <param name="filePath">テクスチャファイルのパスを表す文字列。</param>
/// <returns>作成されたResourceオブジェクトのstd::shared_ptr。ロードに失敗した場合はnullptrを返します。</returns>
std::shared_ptr<Resource> TextureLoader::createTexture(const std::string& filePath)
{
	//  DxLibでテクスチャをロード
    int handle = LoadGraph(filePath.c_str());
    if (handle == -1) {
        // ロード失敗
        return nullptr;
    }
	return std::make_shared<Resource>(handle);
}

/// <summary>
/// 指定されたファイルパスからテクスチャを読み込み、共有ポインタとして返します。既に読み込まれている場合はキャッシュされたテクスチャを返します。
/// </summary>
/// <param name="filePath">読み込むテクスチャファイルのパス。</param>
/// <returns>読み込まれたテクスチャの std::shared_ptr<Resource>。</returns>
std::shared_ptr<Resource> TextureLoader::LoadTexture(const std::string& filePath)
{
    //  検索
	auto it= textures_.find(filePath);
    //  存在していたら
    if (it != textures_.end()) {
		return it->second;
    }

	//  存在していなかったら新規作成して登録
	auto texture = createTexture(filePath);
	textures_.insert({ filePath, texture });
	return texture;
}
