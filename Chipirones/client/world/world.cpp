#include "world.h"

cworld::cworld(jobject instance) {
	this->world_instance = instance;
}

void cworld::clean() {
	lc->env->DeleteLocalRef(this->world_instance);
}

std::vector<std::shared_ptr<cplayer>> cworld::get_players() {
	std::vector<std::shared_ptr<cplayer>> player_list{};

	if (&this->world_instance == nullptr || this->world_instance == NULL) return player_list;
	jclass world_class = lc->env->GetObjectClass(this->world_instance);
	if (world_class == NULL) return player_list;

	jfieldID player_entities = lc->env->GetFieldID(world_class, "playerEntities", "Ljava/util/List;");

	jclass list_class = lc->get_class("java.util.List");
	if (list_class == NULL) return player_list;

	jmethodID to_array_method = lc->env->GetMethodID(list_class, "toArray", "()[Ljava/lang/Object;");

	jobject world_player_entities = lc->env->GetObjectField(this->world_instance, player_entities);

	if (!world_player_entities)
		return player_list;

	jobjectArray player_list_array = reinterpret_cast<jobjectArray>(lc->env->CallObjectMethod(world_player_entities, to_array_method));
	
	if (!player_list_array)
		return player_list;

	size_t players_len = lc->env->GetArrayLength(player_list_array);

	for (int i = 0; i < players_len; ++i)
	{
		jobject player = lc->env->GetObjectArrayElement(player_list_array, i);

		player_list.push_back(std::make_shared<cplayer>(player));
	}

	lc->env->DeleteLocalRef(world_player_entities);
	lc->env->DeleteLocalRef(player_list_array);

	return player_list;
}