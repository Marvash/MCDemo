#pragma once
#include "Utils/Builder/SpecializedBuilder.h"
#include "WorldSeeds.h"

class WorldSeedsBuilder : public SpecializedBuilder<WorldSeeds>
{
public:
	WorldSeedsBuilder();
	void generateSeeds();
	void loadSeeds();
	void reset() override;
};
