#pragma once
#include "../../java.h"
#include "../axis/player_axis.h"

class cplayer
{
public:
	cplayer(jobject instance);
	jclass get_class();
	vec3d get_position();
	bool is_sneaking();

	float get_pitch();
	float get_yaw();
	std::shared_ptr<cplayer_axis> get_bounding_box();
	void clean();
	jobject player_instance;
};