#include "DXUT.h"
#include "Utility.h"


D3DLIGHT9 GetDirectionalLight(Vec3 * dir, D3DXCOLOR * color)
{
	D3DLIGHT9 light;
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = *color * 0.4f;
	light.Diffuse = *color;
	light.Specular = *color * 0.4f;
	light.Direction = *dir;

	return light;
}

int RandNum(int min, int max) {
	return rand() % (max - min) + min;
}

