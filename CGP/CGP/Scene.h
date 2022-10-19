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
	vector<ModelClass*> m_arrModel[(UINT)GROUP_TYPE::END];	// 오브젝트를 저장 및 관리할 벡터를 그룹만큼 선언
	wstring				m_strName;							// Scene 이름

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

	virtual void init(D3DClass* D3D) = 0;	// 해당 Scene 에 진입 시 호출
	virtual void Exit() = 0;	// 해당 Scene 을 탈출 시 호출

	Pos getPlayerPos() { return m_arrModel[(UINT)GROUP_TYPE::PLAYER][0]->getPos() ; }

	bool isModelArrEmpty(GROUP_TYPE type) { return m_arrModel[(UINT)type].size() == 0; }

protected:


public:
	Scene();
	virtual ~Scene();

};

