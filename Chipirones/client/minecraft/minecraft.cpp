#include "minecraft.h"

jclass cminecraft::get_class() {
	return lc->get_class("net.minecraft.client.Minecraft");
}

jobject cminecraft::get_instance() {

	jfieldID minecraft_field_id = lc->env->GetStaticFieldID(get_class(), "theMinecraft", "Lnet/minecraft/client/Minecraft;");
	jobject minecraft_instance = lc->env->GetStaticObjectField(get_class(), minecraft_field_id);

	return minecraft_instance;
}

cworld cminecraft::get_world() {
	jobject minecraft_instance = get_instance();

	auto world_field_id = lc->env->GetFieldID(get_class(), "theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;");

	jobject world_object = lc->env->GetObjectField(minecraft_instance, world_field_id);

	lc->env->DeleteLocalRef(minecraft_instance);

	return cworld(world_object);
}

cplayer cminecraft::get_local_player() {
	jobject minecraft_instance = get_instance();

	jfieldID local_player_id = lc->env->GetFieldID(get_class(), "thePlayer", "Lnet/minecraft/client/entity/EntityPlayerSP;");
	jobject local_player = lc->env->GetObjectField(minecraft_instance, local_player_id);

	lc->env->DeleteLocalRef(minecraft_instance);

	return cplayer(local_player);
}

bool cminecraft::in_menu() {
	jobject minecraft_instance = get_instance();


	lc->env->DeleteLocalRef(minecraft_instance);
	return false;
}