#include "pch.h"
#include "ResourceManager.h"

void ResourceManager::LoadAllResources()
{
	for(size_t i = 0; i < m_imageTypes.size(); ++i)
	{
		//enum 기준으로 파일 경로 생성
		std::wstring path = IMAGE_PATH + ToWstring(m_imageTypes[i]) + IMAGE_EXT;

		Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromFile(path.c_str(), FALSE);

		if(bitmap)
		{
			if(bitmap->GetLastStatus() == Gdiplus::Ok)
			{
				m_imageBitmapsMap[m_imageTypes[i]].push_back(bitmap);
			}
			else
			{
				delete bitmap;
				bitmap = nullptr;
			}
		}
		else
		{
			//파일 로드 실패
			//assert(false && "Failed to load image file");
		}
	}
}

void ResourceManager::ReleaseAllResources()
{
	for(auto& pair : m_imageBitmapsMap)
	{
		for(Gdiplus::Bitmap* bitmap : pair.second)
		{
			if(bitmap)
			{
				delete bitmap;
				bitmap = nullptr;
			}
		}
		pair.second.clear();
	}
	m_imageBitmapsMap.clear();
	m_imageTypes.clear();
}

void ResourceManager::AddObjectType(EObjectType type)
{
	m_imageTypes.push_back(type);
}
std::wstring ResourceManager::ToWstring(EObjectType type)
{
	switch (type)
	{
	case EObjectType::Player:		return L"Player";
	case EObjectType::Enemy:		return L"Enemy";
	case EObjectType::Block:		return L"Block";
	case EObjectType::Bullet:		return L"Bullet";
	case EObjectType::Goal:			return L"Goal";
	case EObjectType::BackGround_1:	return L"BackGround_1";
	case EObjectType::Background_2:	return L"Background_2";

	default:						return L"Unknown";
	}
}
\
Gdiplus::Bitmap* ResourceManager::GetImage(EObjectType type, size_t idx)
{
	//맵에서 해당 이미지 종류의 벡터를 찾아서
	//벡터가 비어있지 않으면
	//0번째 비트맵 리턴(임시)
	auto it = m_imageBitmapsMap.find(type);
	if(it != m_imageBitmapsMap.end() && !it->second.empty())
	{
		return it->second[idx];
	}
	return nullptr;
}
