#pragma once

template <typename T>
class Builder
{
public:
	virtual void reset() {};
	T* getResult() {
		T* result = this->m_result;
		this->reset();
		return result;
	}
protected:
	Builder<T>() {
		reset();
	}
	T* m_result;
};