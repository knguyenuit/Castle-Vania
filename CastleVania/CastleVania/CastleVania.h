#ifndef __CCASTLEVANIA_H__
#define __CCASTLEVANIA_H__

#pragma once
#include "Game.h"
#include "ViewWindows.h"
using namespace CastleVania;

class CCastleVania : public CGame
{
public:
	CCastleVania();
	~CCastleVania() {};
protected:
	virtual void Init();
	virtual void ProcessInput();
	virtual void Destroy();
};
#endif // !__CCASTLEVANIA_H__
