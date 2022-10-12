#pragma once
#include "Strategy.h"
class StrategyContext
{
public:
	StrategyContext();
	void setStrategy(Strategy* strategy);
	void execute();
private:
	Strategy* m_strategy;
};

