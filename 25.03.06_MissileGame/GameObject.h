#pragma once
#include "pch.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
	void Init();			//��� ������ �ʱ�ȭ, �޸� �Ҵ�
	void Release();			//�޸� ����
	void Update();			//������ ������ ���� ���� ����(������ ���)
	void Render(HDC hdc);	//������ ������ ���(�̹���, �ؽ�Ʈ ��)

public:

};

