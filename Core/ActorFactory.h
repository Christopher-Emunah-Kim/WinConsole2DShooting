#pragma once
#include <type_traits>
#include "Enums.h"
#include "Objects/K_Actor.h"
#include "singleton.h"
#include "GameMaster.h"


class Factory : public Singleton<Factory>
{
	friend class Singleton<Factory>;

public:
	template <typename T>
	typename std::enable_if<std::is_base_of<Actor, T>::value, T*>::type
	SpawnActor(EObjectType type, ERenderLayer layer = ERenderLayer::Actor)
	{
		T* NewActor = new T(type);

		NewActor->SetRenderLayer(layer);
		NewActor->Init();

		GameMaster::GetInstance()->RegisterActor(NewActor);

		return NewActor;
	}

private:
	Factory() = default;
	virtual ~Factory() = default;
};