#include "player.h"

cplayer::cplayer(jobject instance) {
	this->player_instance = instance;
}

void cplayer::clean() {
	lc->env->DeleteLocalRef(this->player_instance);
}

jclass cplayer::get_class() {
	return lc->get_class("net.minecraft.entity.Entity");

}

bool cplayer::is_sneaking() {

	jmethodID sneaking_method_id = lc->env->GetMethodID(get_class(), "isSneaking", "()Z");

	bool is_sneaking = lc->env->CallBooleanMethod(this->player_instance, sneaking_method_id);

	return is_sneaking;
}

float cplayer::get_pitch() {
	auto player_class = lc->env->GetObjectClass(this->player_instance);

	jfieldID pitch_fid = lc->env->GetFieldID(player_class, "rotationPitch", "F");

	return lc->env->GetFloatField(this->player_instance, pitch_fid);
}

float cplayer::get_yaw() {
	auto player_class = lc->env->GetObjectClass(this->player_instance);

	jfieldID yaw_fid = lc->env->GetFieldID(player_class, "rotationYaw", "F");

	return lc->env->GetFloatField(this->player_instance, yaw_fid);
}

vec3d cplayer::get_position() {
	auto player_class = lc->env->GetObjectClass(this->player_instance);

	jfieldID pos_x_fid = lc->env->GetFieldID(player_class, "posX", "D");
	jfieldID pos_y_fid = lc->env->GetFieldID(player_class, "posY", "D");
	jfieldID pos_z_fid = lc->env->GetFieldID(player_class, "posZ", "D");
	
	return vec3d{
		lc->env->GetDoubleField(this->player_instance, pos_x_fid),
		lc->env->GetDoubleField(this->player_instance, pos_y_fid),
		lc->env->GetDoubleField(this->player_instance, pos_z_fid)
	};
}

std::shared_ptr<cplayer_axis> cplayer::get_bounding_box()
{
	auto player_class = lc->env->GetObjectClass(this->player_instance);

	jfieldID boundingbox_fid = lc->env->GetFieldID(player_class, "boundingBox", "Lnet/minecraft/util/AxisAlignedBB;");

	return std::make_shared<cplayer_axis>(lc->env->GetObjectField(this->player_instance, boundingbox_fid));
}