#pragma once
//シーンの基底クラス
#include "gameObject.h"
#include <list>

class Scene
{
protected:
	std::list<GameObject*> m_gameObject[3];
	

public:
	template <typename T>
	T* AddObject(int i) {

		T* gameObject = new T();
		gameObject->Init();
		m_gameObject[i].push_back(gameObject);
		return gameObject;
	}
	template <typename T>
	T* GetGameObject() {
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_gameObject[i])
			{
				//ダイナミックキャスト型中に入ってる物があっていたらポインタを返すあってなかったらnullを返す
				T* ret = dynamic_cast<T*>(object);
				if (ret != nullptr)
				{
					return ret;
				}

			}
		}

		return nullptr;
	}
	template <typename T>
	std::list<T*> GetEntitylist() {
		std::list<T*> list;
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_gameObject[i])
			{
				//ダイナミックキャスト型中に入ってる物があっていたらポインタを返すあってなかったらnullを返す
				T* ret = dynamic_cast<T*>(object);
				if (ret != nullptr)
				{
					list.push_back(ret);
				}

			}
		}
		return list;
	}
	virtual ~Scene() {};
	virtual void Init() {};
	virtual void Uninit() {};
	virtual void Update() {};
	virtual void Draw() {};
	virtual void fadein() {};
};