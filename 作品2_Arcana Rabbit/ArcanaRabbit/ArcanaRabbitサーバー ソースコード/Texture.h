#pragma once
#include "main.h"
#include "renderer.h"
int LoadTexture(const wchar_t* fileName);
void UninitTexture(void);
ID3D11ShaderResourceView** GetTexture(int index);
