#pragma once

#ifndef _SHADERMANAGERCLASS_H_
#define _SHADERMANAGERCLASS_H_


#include <Graphics/DirectXPlatformManager.h>
#include "LightShaderClass.h"
#include "DepthShaderClass.h"
#include "ShadowShaderClass.h"


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

	bool RenderDepthShader(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,
		D3DXMATRIX projectionMatrix);

	bool RenderShadowShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4);

private:
	LightShaderClass* m_LightShader;
	DepthShaderClass* m_DepthShader;
	ShadowShaderClass* m_ShadowShader;
};


#endif