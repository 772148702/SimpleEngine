#pragma once

#ifndef _SHADERMANAGERCLASS_H_
#define _SHADERMANAGERCLASS_H_


#include "d3dclass.h"
#include "lightshaderclass.h"


// facade pattern
// ÿ�� Shader �������һ����, ���ⲿ���� Shader ͳͳͨ�����������, ����ֱ�Ӱ����Ǹ� Shader ��
class ShaderManagerClass
{
public:
	ShaderManagerClass();
	ShaderManagerClass(const ShaderManagerClass&);
	~ShaderManagerClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	bool RenderLightShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*,
		D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4, D3DXVECTOR3, D3DXVECTOR4, float);

private:
	LightShaderClass* m_LightShader;
};


#endif