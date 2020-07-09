#pragma once

class IBattle
{
public:

	virtual void LogResults() const = 0;

	virtual void BeginFight() = 0;

	virtual ~IBattle() = default;
};