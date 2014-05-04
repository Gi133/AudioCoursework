/*
File:	Main_AudioCoursework.cpp
Version:	1.0
Date: 29th April 2013.
Author:	Andreas Xirotyris.

Uses:	windows.h, memory, WinCore.hpp, IState.hpp, XACore.hpp, WaveFileManager.hpp, GameController.hpp.

Description:
Based on Allan Milne's Main_RoomEscape.cpp version 1.0.

A main code file containing the Windows application entry point
for use with the Allan Milne's windows/audio framework.

Additional Changes from Allan Milne's original code:
*	New variables to control the window settings, there have the prefix "window".
*	The code now includes GameController.
*	Various small changes to the code structure to bring it closer to the structure of the rest of the project (eg. line-break before {).

*/

//--- system includes.
#include <windows.h>
#include <memory>

//--- framework includes.
#include "WinCore.hpp"
#include "IState.hpp"
#include "XACore.hpp"
#include "WaveFileManager.hpp"
using namespace AllanMilne;
using namespace AllanMilne::Audio;

//--- Application specific include.
#include "GameController.h"

// Anonymous name space to define window and other settings.
namespace
{
	string windowName = "Audio Coursework - Evade the Monster!";
	int windowWidth = 800;
	int windowHeight = 600;
	bool windowFullScreen = false;
}

//=== Application entry point. ===
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	std::unique_ptr<WinCore> windowApp;
	std::unique_ptr<IState> frameProcessor;

	//--- Create the singleton XACore object that will initialize XAudio2 and X3DAudio.
	//--- Must do this before creating/initializing other objects since these may require XAudio2 functionality in creating sounds, etc.
	XACore::CreateInstance();
	if (XACore::GetStatus() != XACore::OK)
	{
		MessageBox(NULL, TEXT("Error initializing XAudio2 - application aborted."), TEXT("Main Application"), MB_OK | MB_ICONERROR);
		return 0;
	}

	//--- create the object that encapsulates frame processing.
	frameProcessor.reset(new GameController());

	//--- Create the WinCore object composed with the frame processor.
	windowApp.reset(new WinCore(frameProcessor.get()));

	//--- Initialize the WinCore object including creating the application window;
	//--- this will also call the IState::Initialize() method of the frame processor.
	bool ok = windowApp->Initialize(windowName, windowWidth, windowHeight, windowFullScreen, hinstance);
	if (!ok)
	{
		MessageBox(NULL, TEXT("Error occurred while initializing WinCore; application aborted."), TEXT(" Main Application"), MB_OK | MB_ICONERROR);
		return 0;
	}

	//--- Run the application Windows message loop and associated frame processing.
	windowApp->RunApp();

	//--- Delete resources.
	//--- NB order of deletion is important - is in opposite order of creation.

	//--- delete the WinCore instance explicitly before we delete other resources.
	windowApp.release();

	//--- as above, delete the IState object.
	frameProcessor.release();

	//--- Delete the XACore singleton instance - will clear up all XAudio2 resources.
	XACore::DeleteInstance();

	//--- Delete the WaveFileManager Instance to release all PCMWave objects that might have been created.
	WaveFileManager::DeleteInstance();

	return 0;
} // end WinMain function.

// end of code.