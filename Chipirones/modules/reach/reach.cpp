#include "../modules.h"
#include "../../chipirones/chipirones.h"
#include "../../utils/utils.h"
const long double ENTITY_WIDTH { 0.6 };

void reach::handle(std::unique_ptr<cminecraft> &mc)  {
	auto is_okay = [&]() {
		auto players = mc->get_world().get_players();
		if (&players == nullptr || players.empty()) return false;
		return (mc->get_local_player().player_instance  && mc->get_world().world_instance && cheat->reach_enabled);
	};

	if (is_okay())
	{
		float distance = cheat->reach_distance;
		vec3d position = mc->get_local_player().get_position();

		for (const auto& entity : mc->get_world().get_players())
		{
			if (lc->env->IsSameObject(mc->get_local_player().player_instance, entity->player_instance))
				continue;

			auto entity_position = entity->get_position();

			auto hypho_dist = hypot(position.x - entity_position.x, position.z - entity_position.z);

			if (distance > hypho_dist)
				distance -= hypho_dist;

			auto angles = utils::get_view(position, entity_position);

			if (std::abs(utils::normalize_yaw(-(mc->get_local_player().get_yaw() - angles.first)))) continue;

			float yaw_sin = std::sin(utils::deg_to_radiants(angles.first + 90.0f));
			float yaw_cos = std::cos(utils::deg_to_radiants(angles.first + 90.0f));

			double x = entity_position.x;
			double z = entity_position.z;
			x -= (yaw_cos * distance);
			z -= (yaw_sin * distance);

			long double box_width = ENTITY_WIDTH / 2.0f;

			splayer_axis current_box = entity->get_bounding_box()->get_boundingbox();
			splayer_axis bb{};
			
			bb.minX = x - box_width;
			bb.minY = current_box.minY;
			bb.minZ = z - box_width;

			bb.maxX = x + box_width;
			bb.maxY = current_box.maxY;
			bb.maxZ = z + box_width;

			entity->get_bounding_box()->set_boundingbox(bb);
		}
	}
}