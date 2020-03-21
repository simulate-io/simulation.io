#pragma once

class IBattle
{
public:

	virtual void BeginFight() = 0;

	virtual ~IBattle() = default;
};