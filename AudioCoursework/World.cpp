/*
File:	World.cpp
Version:	1.0
Date: 4th May 2013.
Author:	Andreas Xirotyris.

Description:
Look at World.h for details
*/

#include "World.h"

World::World()
{
	ambientAudio = nullptr;
} // End of constructor.

World::~World()
{
	if (ambientAudio->IsValid())
		ambientAudio->Stop();
} // End of destructor.

void World::Start()
{
	if (ambientAudio->IsValid())
	{
		ambientAudio->SetLooped(true);
		ambientAudio->AdjustVolume(-10.0f);
		ambientAudio->Play();
	}
} // End of Start function.

void World::Stop()
{
	if (ambientAudio->IsValid())
		ambientAudio->Stop();
} // End of Stop function.