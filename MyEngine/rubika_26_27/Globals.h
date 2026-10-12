#pragma once

class DebugMgr;
class Logger;
class TextureMgr;

class Globals
{
public:
	Globals();
	~Globals();

	void Init();
	void Shut();
	void Destroy();

	void IncrementFrameCount();

	unsigned long long FrameCount;

	TextureMgr* TextureMgr;
	DebugMgr* DebugMgr;
	Logger* Logger;
};

extern Globals gData;