#pragma once
#include "pch.h"
#include "modelclass.h"
#include "bitmapclass.h"
#include "textureshaderclass.h"
#include "textureclass.h"
class ModelClass;
class CameraClass;
class LightClass;
class LightShaderClass;
class D3DClass;

class Scene
{
private:
	vector<ModelClass*> m_arrModel[(UINT)GROUP_TYPE::END];	// ������Ʈ�� ���� �� ������ ���͸� �׷츸ŭ ����
	wstring				m_strName;							// Scene �̸�

protected:
	ModelClass*			m_Model;
	CameraClass*		m_Camera;
	LightClass*			m_Light;
	LightShaderClass*	m_LightShader;

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	ModelClass* GetModel(){ return m_Model;}

	void render(D3DClass* D3D, float rotation) ;
	void update(D3DClass* D3D);

	void AddObject(D3DClass* D3D, GROUP_TYPE _eType);
	void ClearObjects(GROUP_TYPE _eType);

	virtual void init(D3DClass* D3D) = 0;	// �ش� Scene �� ���� �� ȣ��
	virtual void Exit() = 0;	// �ش� Scene �� Ż�� �� ȣ��

	Pos getPlayerPos() { return m_arrModel[(UINT)GROUP_TYPE::PLAYER][0]->getPos() ; }

	bool isModelArrEmpty(GROUP_TYPE type) { return m_arrModel[(UINT)type].size() == 0; }

protected:


public:
	Scene();
	virtual ~Scene();

};

