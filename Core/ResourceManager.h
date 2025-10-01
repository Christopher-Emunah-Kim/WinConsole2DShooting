#pragma once
#include "singleton.h"
#include "../framework.h"

const std::wstring IMAGE_PATH = L"./Images/";
const std::wstring IMAGE_EXT = L".png";

//���ӿ��� ����� ��� �̹��� ���� ����
//���ϴ� �̹��� bitmap ����
//enum Ŭ������ �̹��� ���� ����
class ResourceManager : public Singleton<ResourceManager>
{
private:
	std::wstring ToWstring(EObjectType type);


public:
	void LoadAllResources(); 
	void ReleaseAllResources();
	
	void AddObjectType(EObjectType type);
	Gdiplus::Bitmap* GetImage(EObjectType type, size_t idx = 0);

private:
	std::vector<EObjectType> m_imageTypes;
	std::unordered_map<EObjectType, std::vector<Gdiplus::Bitmap*>> m_imageBitmapsMap;

};

