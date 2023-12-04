#include "player_axis.h"

#include "../../java.h"

cplayer_axis::cplayer_axis(jobject obj)
{
	axis_aligned_obj = obj;
}

cplayer_axis::~cplayer_axis()
{
	lc->env->DeleteLocalRef(axis_aligned_obj);
}

splayer_axis cplayer_axis::get_boundingbox()
{
	jclass this_class = lc->env->GetObjectClass(axis_aligned_obj);

	jfieldID minX_fid = lc->env->GetFieldID(this_class, "minX", "D");
	jfieldID minY_fid = lc->env->GetFieldID(this_class, "minY", "D");
	jfieldID minZ_fid = lc->env->GetFieldID(this_class, "minZ", "D");

	jfieldID maxX_fid = lc->env->GetFieldID(this_class, "maxX", "D");
	jfieldID maxY_fid = lc->env->GetFieldID(this_class, "maxY", "D");
	jfieldID maxZ_fid = lc->env->GetFieldID(this_class, "maxZ", "D");

	splayer_axis box{};
	box.minX = lc->env->GetDoubleField(axis_aligned_obj, minX_fid);
	box.minY = lc->env->GetDoubleField(axis_aligned_obj, minY_fid);
	box.minZ = lc->env->GetDoubleField(axis_aligned_obj, minZ_fid);

	box.maxX = lc->env->GetDoubleField(axis_aligned_obj, maxX_fid);
	box.maxY = lc->env->GetDoubleField(axis_aligned_obj, maxY_fid);
	box.maxZ = lc->env->GetDoubleField(axis_aligned_obj, maxZ_fid);

	return box;
}

void cplayer_axis::set_boundingbox(splayer_axis target)
{
	set(target.minX, target.minY, target.minZ, target.maxX, target.maxY, target.maxZ);
}

void cplayer_axis::set(double minX, double minY, double minZ, double maxX, double maxY, double maxZ)
{
	auto this_class = lc->env->GetObjectClass(axis_aligned_obj);

	jfieldID minX_fid = lc->env->GetFieldID(this_class, "minX", "D");
	jfieldID minY_fid = lc->env->GetFieldID(this_class, "minY", "D");
	jfieldID minZ_fid = lc->env->GetFieldID(this_class, "minZ", "D");

	jfieldID maxX_fid = lc->env->GetFieldID(this_class, "maxX", "D");
	jfieldID maxY_fid = lc->env->GetFieldID(this_class, "maxY", "D");
	jfieldID maxZ_fid = lc->env->GetFieldID(this_class, "maxZ", "D");

	lc->env->SetDoubleField(axis_aligned_obj, minX_fid, minX);
	lc->env->SetDoubleField(axis_aligned_obj, minY_fid, minY);
	lc->env->SetDoubleField(axis_aligned_obj, minZ_fid, minZ);

	lc->env->SetDoubleField(axis_aligned_obj, maxX_fid, maxX);
	lc->env->SetDoubleField(axis_aligned_obj, maxY_fid, maxY);
	lc->env->SetDoubleField(axis_aligned_obj, maxZ_fid, maxZ);
}