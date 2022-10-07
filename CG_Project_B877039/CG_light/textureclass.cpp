////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "textureclass.h"
#include "DDSTextureLoader.h"

using namespace DirectX;

TextureClass::TextureClass()
{
	m_texture[0] = 0;
	m_texture[1] = 0;
}


TextureClass::TextureClass(const TextureClass& other)
{
}


TextureClass::~TextureClass()
{
}


bool TextureClass::Initialize(ID3D11Device* device, const WCHAR* filename1,  const WCHAR* filename2)
{
	HRESULT result;

	// Load texture data from a file by using DDS texture loader.
	result = CreateDDSTextureFromFile(device, filename1, nullptr, &m_texture[0]);
	if (FAILED(result))
	{
		return false;
	}

	result = CreateDDSTextureFromFile(device, filename2, nullptr, &m_texture[1]);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}


void TextureClass::Shutdown()
{
	// Release the texture resource.
	if(m_texture[0])
	{
		m_texture[0]->Release();
		m_texture[0] = 0;
	}
	if (m_texture[1])
	{
		m_texture[1]->Release();
		m_texture[1] = 0;
	}
	return;
}


ID3D11ShaderResourceView** TextureClass::GetTexture()
{
	return m_texture;
}