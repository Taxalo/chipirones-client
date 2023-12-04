#pragma once
#include "../../java.h"
#include "../player/player.h"
class cworld
{
public:
	cworld(jobject instance);
	std::vector<std::shared_ptr<cplayer>> get_players();
	void clean();
	jobject world_instance;
};