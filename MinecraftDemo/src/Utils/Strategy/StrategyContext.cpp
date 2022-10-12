#include "StrategyContext.h"

StrategyContext::StrategyContext() : m_strategy(nullptr) {

}

void StrategyContext::setStrategy(Strategy* strategy) {
	m_strategy = strategy;
}

void StrategyContext::execute() {
	if (m_strategy != nullptr) {
		m_strategy->execute();
	}
}