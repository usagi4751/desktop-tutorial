//==================================
// シーンの床の情報
// 512 * 512 のタイルの感じで作った
// trueで床がある
//==================================
#pragma once
#include "main.h"
#include "Component.h"
#include "gameObject.h"

typedef struct {
	bool flugx[512];
}FloorCell;
typedef struct {
	FloorCell flugy[512];
}FloorCube;

class Floor :public GameObject
{
private:
	FloorCube m_floordata;
public:
	Floor() {
		for (int i = 0; i < 512; i++)
		{
			for (int j = 0; j < 512; j++)
			{
				m_floordata.flugy[j].flugx[i] = false;
			}
		}
	};
	~Floor() {};
	void SetFloor(FloorCube floor) { m_floordata = floor; };
	void SetFloor(XMFLOAT2 pos, bool flug) 
	{ 
		if (pos.x >= 0  && pos.x <  512 && pos.y >= 0 && pos.y < 512)
		{
			m_floordata.flugy[(int)pos.y ].flugx[(int)pos.x] = flug;
		}
		
	};
	bool GetFloor(XMFLOAT2 pos) {
	if (pos.x >=0 && pos.x < 512 && pos.y >= 0 && pos.y < 512) {
	return m_floordata.flugy[(int)pos.y].flugx[(int)pos.x];
	}
	return false;
	}
	void LoadFloor(const char* MapFilePath);
	virtual void Init() override {};
	virtual void Uninit() override {};
	virtual void Update() override {};
	virtual void Draw() override {};
};
