#pragma once
#include "Builder.h"

template <typename T>
class SpecializedBuilder : public Builder<T> {
public:
	SpecializedBuilder() : Builder<T>() {

	}
};
