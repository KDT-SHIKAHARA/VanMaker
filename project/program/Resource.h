#pragma once

/// <summary>
/// Dxlib�Ŏ擾�������\�[�X�̃n���h����ۊǂ���B
/// ���\�[�X�̍폜�͊Ǘ��N���X���ōs���B
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