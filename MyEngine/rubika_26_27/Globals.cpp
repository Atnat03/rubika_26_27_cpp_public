#include "Globals.h"

#include <DebugMgr.h>
#include <Logger.h>
#include <TextureMgr.h>

Globals gData;

Globals::Globals() : FrameCount(0)
{
	DebugMgr = new ::DebugMgr();
	Logger = new ::Logger();
	TextureMgr = new ::TextureMgr();

	gData.TextureMgr->LoadTexture("D:\\C++\\rubika_26_27_cpp_public\\MyEngine\\Ressources\\IsaacSprite.png");
}

Globals::~Globals()
{
	Destroy();
}

void Globals::Init()
{
	Logger->Init();
}

void Globals::Shut()
{
	Logger->Shut();
}

void Globals::Destroy()
{
	delete DebugMgr;
	DebugMgr = nullptr;

	delete Logger;
	Logger = nullptr;
}

void Globals::IncrementFrameCount()
{
	++FrameCount;
}
