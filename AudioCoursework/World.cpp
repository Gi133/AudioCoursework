#include "World.h"

World::World()
{
	ambientAudio = nullptr;
}

World::~World()
{
	if (ambientAudio->IsValid())
		ambientAudio->Stop();
}

void World::Start()
{
	if (ambientAudio->IsValid())
	{
		ambientAudio->SetLooped(true);
		ambientAudio->AdjustVolume(-10.0f);
		ambientAudio->Play();
	}
}

void World::Stop()
{
	if (ambientAudio->IsValid())
		ambientAudio->Stop();
}

void World::LoadAmbientSound(std::string filePath)
{
	ambientAudio.reset(new XASound(filePath));
}