////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_TextureShader = 0;

	m_Eye = XMVectorSet(0.0f, 5.0f, -30.0f, 1.0f);
	m_At = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	m_Up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);

	m_Light1 = 0;
	m_Light2 = 0;
	m_Light3 = 0;
	m_Light4 = 0;
	rotate = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{

}


GraphicsClass::~GraphicsClass()
{

}

float GraphicsClass::RandNum(int num)
{
	float num0 = (float)num;

	int temp = rand() % 8;
	if (temp > 4) {
		temp -= 4;
		num0 += ((float)temp / 20);
		return num0;
	}
	else {
		num0 -= ((float)temp/ 20);
		return num0;
	}
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);	// for cube
		
	XMFLOAT3 treeScail = XMFLOAT3(10.0f, 10.0f, 10.0f);
	XMFLOAT3 floorScail = XMFLOAT3(500.0f, 0.3f,500.0f);
	XMFLOAT3 houseScail = XMFLOAT3(7.0f, 7.0f, 7.0f);
	XMFLOAT3 rockScail = XMFLOAT3(4.0f, 2.0f, 4.0f);
	XMFLOAT3 fenceScail = XMFLOAT3(1.0f, 3.0f, 1.0f);
	XMFLOAT3 dogScail = XMFLOAT3(15.0f, 15.0f, 15.0f);
	XMFLOAT3 tableScail = XMFLOAT3(0.3f, 0.25f, 0.3f);
	XMFLOAT3 chairScail = XMFLOAT3(7.0f, 7.0f, 7.0f);
	
	vector<XMFLOAT3> treePosition;

	srand((unsigned int)time(NULL));

	for (int i = -11; i < -2; i++) // red
	{
		for (int j = 5; j < 17; j++) {
			treePosition.push_back(XMFLOAT3(RandNum(i), 0.0f, RandNum(j)));
		}
	}
	for (int i = 3; i < 12; i++) // blue
	{
		for (int j = 5; j < 16; j++) {
			treePosition.push_back(XMFLOAT3(RandNum(i), 0.0f, RandNum(j)));
		}
	}
	for (int i =-11; i < -8; i++) // pink
	{
		for (int j = -16; j < 5; j++) {
			treePosition.push_back(XMFLOAT3(RandNum(i), 0.0f, RandNum(j)));
		}
	}
	for (int i = 9; i < 12; i++) // orange
	{
		for (int j = -16; j < 5; j++) {
			treePosition.push_back(XMFLOAT3(RandNum(i), 0.0f, RandNum(j)));
		}
	}
	for (int i = -8; i < 9; i++) // green
	{
		for (int j = -16; j < -10; j++) {
			treePosition.push_back(XMFLOAT3(RandNum(i), 0.0f, RandNum(j)));
		}
	}

	vector<XMFLOAT3> floorPosition = {
		XMFLOAT3(0.0f, 0.0f, 0.0f),
	};

	vector<XMFLOAT3>housePosition = {
		XMFLOAT3(0.0f, -1.0f, -8.0f),
	};

	vector<XMFLOAT3>rockPosition;
	for (int i = 10; i < 41; i++)
	{
		rockPosition.push_back(XMFLOAT3(5.0f, 0.0f, float(i)));
		rockPosition.push_back(XMFLOAT3(-5.0f, 0.0f, float(i)));
	}
	for (int i = 6; i < 21; i++)
	{
		rockPosition.push_back(XMFLOAT3(float(i), 0.0f, 10.0f));
		rockPosition.push_back(XMFLOAT3(float(i) * -1, 0.0f, 10.0f));
	}
	for (int i = -25; i < 10; i++)
	{
		rockPosition.push_back(XMFLOAT3(20.0f, 0.0f, float(i)));
		rockPosition.push_back(XMFLOAT3(-20.0f, 0.0f, float(i)));
	}
	for (int i = -20; i < 20; i++)
	{
		rockPosition.push_back(XMFLOAT3(float(i), 0.0f, -25.0f));
	}
	vector<XMFLOAT3>fencePosition = {
		XMFLOAT3(-55.0f, -1.0f, -55.0f)
	};

	vector<XMFLOAT3> dogPosition = {
	XMFLOAT3(-0.0f, 0.0f, -0.0f)
	};

	vector<XMFLOAT3> tablePosition = {
		XMFLOAT3(30.0f, 0.0f, -220.0f)
	};

	vector<XMFLOAT3> chairPosition = {
	XMFLOAT3( 1.8f, 0.0f, -8.0f),
	XMFLOAT3( 0.8f, 0.0f, -8.0f)
	};

	// Create the model object.
	m_Models.push_back(new ModelClass(m_D3D->GetDevice(), L"./data/tree.obj", L"./data/tree.dds", L"./data/tree_normal.dds",treePosition, 1, treeScail));
	m_Models.push_back(new ModelClass(m_D3D->GetDevice(), L"./data/floor.obj", L"./data/SandMud.dds", L"./data/SandMud.dds",floorPosition, 1, floorScail));
	m_Models.push_back(new ModelClass(m_D3D->GetDevice(), L"./data/NewWoodHouse.obj", L"./data/WoodHouse.dds", L"./data/WoodHouse.dds",housePosition, 1, houseScail));
	m_Models.push_back(new ModelClass(m_D3D->GetDevice(), L"./data/rock.obj", L"./data/rock.dds", L"./data/rock.dds",rockPosition, 1, rockScail));
	m_Models.push_back(new ModelClass(m_D3D->GetDevice(), L"./data/Woood.obj", L"./data/chair_d.dds", L"./data/chair_d.dds", fencePosition, 1, fenceScail));
	m_Models.push_back(new ModelClass(m_D3D->GetDevice(), L"./data/Dog.obj", L"./data/Dog.dds", L"./data/Dog.dds", dogPosition, 0, dogScail));
	m_Models.push_back(new ModelClass(m_D3D->GetDevice(), L"./data/tableobj.obj", L"./data/table.dds", L"./data/table.dds", tablePosition, 1, tableScail));
	m_Models.push_back(new ModelClass(m_D3D->GetDevice(), L"./data/chair.obj", L"./data/table.dds", L"./data/table.dds", chairPosition, 1, chairScail));


	for (auto* i : m_Models)
	{
		if (!i)
		{
			return false;
		}
	}

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}
	// 입력값에 따라 빛의 강도를 조절하여 lightning effects 조절

	// Create the first light object.
	m_Light1 = new LightClass;
	if (!m_Light1)
	{
		return false;
	}

	// Initialize the first light object

	m_Light2 = new LightClass;
	if (!m_Light2)
	{
		return false;
	}



	m_Light3 = new LightClass;
	if (!m_Light3)
	{
		return false;
	}

	// Initialize the third light object.

	m_Light4 = new LightClass;
	if (!m_Light4)
	{
		return false;
	}
	m_Light1->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light1->SetPosition(5.0f, 5.0f, -5.0f);

	m_Light2->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light2->SetPosition(0.0f, 50.0f, 10.0f);

	m_Light3->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light3->SetPosition(-0.0f, 50.0f, -0.0f);
	// Initialize the fourth light object.
	m_Light4->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light4->SetPosition(-5.0f, 5.0f, 5.0f);

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, -1.0f, 0.0f);
	m_Light->SetSpecularColor(1.0f,1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	return true;
}
void GraphicsClass::SetAmbientEffect()
{
	m_LightShader->LightSet(0);
}
void GraphicsClass::SetDiffuseEffect()
{
	m_LightShader->LightSet(1);
}
void GraphicsClass::SetSpecularColorEffect()
{
	m_LightShader->LightSet(2);
}

void GraphicsClass::Shutdown()
{
	if (m_Light1)
	{
		delete m_Light1;
		m_Light1 = 0;
	}

	if (m_Light2)
	{
		delete m_Light2;
		m_Light2 = 0;
	}

	if (m_Light3)
	{
		delete m_Light3;
		m_Light3 = 0;
	}

	if (m_Light4)
	{
		delete m_Light4;
		m_Light4 = 0;
	}
	for (auto* model : m_Models)
	{
		if (model)
		{
			model->Shutdown();
			delete model;
			model = 0;
		}
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	
	return;
}

bool GraphicsClass::Frame()
{
	bool result;
	bool isClip = true;
	static float rotation = 0.1f;

	// Update the rotation variable each frame.
	rotation += XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	DWORD dwCurTime = GetTickCount();
	static DWORD dwOldTime = GetTickCount();
	DWORD m_dwElapsedTime = dwCurTime - dwOldTime;
	dwOldTime = dwCurTime;

	float rotSpeed = 0.08f;
	float moveSpeed = 0.02f;

	if (GetAsyncKeyState(0x57))
	{
		XMVECTOR Direction;
		Direction = XMVector3Normalize(m_At - m_Eye);
		m_Eye += m_dwElapsedTime * Direction * moveSpeed;
		m_At += m_dwElapsedTime * Direction * moveSpeed;
	}

	if (GetAsyncKeyState(0x53)) 
	{
		XMVECTOR Direction;
		Direction = XMVector3Normalize(m_At - m_Eye);
		m_Eye -= m_dwElapsedTime * Direction * moveSpeed;
		m_At -= m_dwElapsedTime * Direction * moveSpeed;
	}

	if (GetAsyncKeyState(0x41))
	{
		XMVECTOR UpNormal, ForwardNormal, Direction;
		UpNormal = XMVector3Normalize(m_Up);
		ForwardNormal = XMVector3Normalize(m_At - m_Eye);
		Direction = XMVector3Cross(ForwardNormal, UpNormal);
		Direction = XMVector3Normalize(Direction);
		m_Eye += m_dwElapsedTime * Direction * moveSpeed;
		m_At += m_dwElapsedTime * Direction * moveSpeed;
	}

	if (GetAsyncKeyState(0x44)) 
	{
		XMVECTOR UpNormal, ForwardNormal, Direction;
		UpNormal = XMVector3Normalize(m_Up);
		ForwardNormal = XMVector3Normalize(m_At - m_Eye);
		Direction = XMVector3Cross(ForwardNormal, UpNormal);
		Direction = XMVector3Normalize(Direction);
		m_Eye -= m_dwElapsedTime * Direction * moveSpeed;
		m_At -= m_dwElapsedTime * Direction * moveSpeed;
	}

	POINT curPt;
	GetCursorPos(&curPt);
	DWORD _CurTime = GetTickCount();
	static DWORD _OldTime = GetTickCount();
	if (_CurTime - _OldTime > 500.f)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			if (isClip)
				isClip = false;
			else
				isClip = true;
			_OldTime = _CurTime;
		}
	}
	if (isClip) {
		SetCursorPos(m_screenWidth / 2, m_screenHeight / 2);
		if (curPt.y < m_screenHeight / 2)
		{
			XMVECTOR UpNormal;
			UpNormal = XMVector3Normalize(m_Up);
			m_At += m_dwElapsedTime * UpNormal * rotSpeed;
		}

		if (curPt.y > m_screenHeight / 2)
		{
			XMVECTOR UpNormal;
			UpNormal = XMVector3Normalize(m_Up);
			m_At -= m_dwElapsedTime * UpNormal * rotSpeed;
		}

		if (curPt.x < m_screenWidth / 2)
		{
			XMVECTOR UpNormal, ForwardNormal, Left;
			UpNormal = XMVector3Normalize(m_Up);
			ForwardNormal = XMVector3Normalize(m_At - m_Eye);
			Left = XMVector3Cross(ForwardNormal, UpNormal);
			Left = XMVector3Normalize(Left);
			m_At += m_dwElapsedTime * Left * rotSpeed;
		}

		if (curPt.x > m_screenWidth / 2)
		{
			XMVECTOR UpNormal, ForwardNormal, Right;
			UpNormal = XMVector3Normalize(m_Up);
			ForwardNormal = XMVector3Normalize(m_At - m_Eye);
			Right = XMVector3Cross(ForwardNormal, UpNormal);
			Right = XMVector3Normalize(Right);
			m_At -= m_dwElapsedTime * Right * rotSpeed;
		}
	}



	// Render the graphics scene.
	result = Render(rotation);
	if(!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Render(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;
	bool result;
	XMFLOAT4 diffuseColor[4];
	XMFLOAT4 lightPosition[4]; 
	XMFLOAT3 cameraPosition, modelPosition;
	double angle;

	rotate += 0.01f;
	if (rotate == 1.0f) rotate = 0.0f;

	// Create the diffuse color array from the four light colors.
	diffuseColor[0] = m_Light1->GetDiffuseColor();
	diffuseColor[1] = m_Light2->GetDiffuseColor();
	diffuseColor[2] = m_Light3->GetDiffuseColor();
	diffuseColor[3] = m_Light4->GetDiffuseColor();

	// Create the light position array from the four light positions.
	lightPosition[0] = m_Light1->GetPosition();
	lightPosition[1] = m_Light2->GetPosition();
	lightPosition[2] = m_Light3->GetPosition();
	lightPosition[3] = m_Light4->GetPosition();

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(173.0f/256, 216.0f/256, 230.0f/256, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	// viewMatrix에 이동 값을 기본적으로 더해 놓고 (ex . int cameraMove), 입력값에 따라 값을 더해주면서 카메라 이동
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	viewMatrix *= XMMatrixTranslation(0.0f, 3.0f, 20.0f) * XMMatrixLookAtLH(m_Eye, m_At, m_Up);

	// 카메라의 위치를 가져옵니다.
	cameraPosition = m_Camera->GetPosition();

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	for (auto* model : m_Models)
	{
		// Rotate the world matrix by the rotation value so that the triangle will spin.
		//worldMatrix = XMMatrixTranslation(model->m_x, model->m_y, model->m_z) * XMMatrixScaling(model->m_modelScail.x, model->m_modelScail.y, model->m_modelScail.z);
		worldMatrix = XMMatrixTranslation(model->m_x, model->m_y, model->m_z) * XMMatrixScaling(model->m_modelScail.x, model->m_modelScail.y, model->m_modelScail.z);

		if (model->m_RandScail == 0)
		{
			if (model->m_z > 2.0f) {
				isArrive = true;
			}
			if (model->m_z < 0.0f) {
				isArrive = false;
			}
			if (!isArrive) {
				model->m_z += 0.01f;
				worldMatrix = XMMatrixRotationY(3.1f) * XMMatrixTranslation(model->m_x, model->m_y, model->m_z) * XMMatrixScaling(model->m_modelScail.x, model->m_modelScail.y, model->m_modelScail.z);
			}
			else {
				model->m_z -= 0.01f;
				worldMatrix = XMMatrixTranslation(model->m_x, model->m_y, model->m_z) * XMMatrixScaling(model->m_modelScail.x, model->m_modelScail.y, model->m_modelScail.z);
			}
		}

		model->Render(m_D3D->GetDeviceContext());
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), model->GetVertexCount(),model->GetInstanceCount(),
			worldMatrix, viewMatrix, projectionMatrix,
			model->GetTextureArray(),
			m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), diffuseColor, lightPosition);

		if (!result)
		{
			return false;
		}
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}