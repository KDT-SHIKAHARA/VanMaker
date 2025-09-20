#pragma once

/// <summary>
/// Dxlibで取得したリソースのハンドルを保管する。
/// リソースの削除は管理クラス側で行う。
/// </summary>
class Resource {
public:
	Resource(int a_handle)
		:m_handle(a_handle) {
	}
	virtual ~Resource() = default;

	int GetHandle()const { return m_handle; }
	bool HasHandle()const { return m_handle != -1; }
private:
	int m_handle = -1;
};