#pragma once
#include "../framework.h"

class Component;

class Actor
{
public:
	Actor() = delete;
	explicit Actor(EObjectType type);
	virtual ~Actor();

private:
	void LoadImage(const std::wstring& imagePath);

public:
	virtual void Init();
	virtual void Tick(float deltaSeconds);
	virtual void Render(Gdiplus::Graphics& graphics);
	virtual void Release();

	virtual void OverlapWith(Actor* other);

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	template<typename T>
	T* GetComponent() const
	{
		static_assert(std::is_base_of<Component, T>::value, "T mus be derived from Component");

		for (Component* comp : m_components)
		{
			if (T* castedComp = dynamic_cast<T*>(comp))
			{
				return castedComp;
			}
		}

		return nullptr;
	};

	void SetPosition(float x, float y);
	void SetPivot(float x, float y);
	void SetSize(int width, int height);
	void SetRenderLayer(ERenderLayer layer);

	void MarkPendingDestroy();

	inline const Position& GetPosition() const { return m_position; }
	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
	inline ERenderLayer GetRenderLayer() const { return targetLayer; }
	inline bool IsPendingDestroy() const { return isPendingDestroy; }
protected:
	Position m_position;
	Position m_pivot;
	std::vector<Component*> m_components;

	int m_width;
	int m_height;

	Gdiplus::Bitmap* m_image;

private:
	ERenderLayer targetLayer = ERenderLayer::Default;
	bool isPendingDestroy = false;
};

