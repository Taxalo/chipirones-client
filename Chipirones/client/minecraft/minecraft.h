#pragma once
#include "../java.h"
#include "../world/world.h"
#include "../player/player.h"

class cminecraft
{
public:
	jclass get_class();
	jobject get_instance();
	cworld get_world();
	cplayer get_local_player();
	bool in_menu();
};

