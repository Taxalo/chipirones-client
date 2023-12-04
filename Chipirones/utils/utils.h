#include <utility>
#include "../java.h"

const long double M_PI {3.141592653589793};

namespace utils {
	inline float radiants_to_deg(float x)
	{
		return x * 180.f / M_PI;
	}

	inline float deg_to_radiants(float r)
	{
		return r * M_PI / 180;
	}

	inline float normalize_yaw(float value)
	{
		if (value >= 180.f)
			value -= 360.f;
		if (value < -180.f)
			value += 360.f;
		return value;
	}

	inline std::pair<float, float> get_view(vec3d pos, vec3d pos1)
	{
		double dx = pos1.x - pos.x;
		double dy = pos1.y - pos.y;
		double dz = pos1.z - pos.z;

		double hypho = sqrt(dx * dx + dz * dz);
		float yaw = radiants_to_deg(atan2(dz, dx)) - 90.f;
		float pitch = radiants_to_deg(-atan2(dy, hypho));

		return std::make_pair(yaw, pitch);
	}

	static double distance(double x, double y) {
		return sqrt(pow(x, 2) + pow(y, 2));
	}

	static double distance(double x1, double y1, double z1, double x2, double y2, double z2) {
		return distance(y1 - y2, distance(x1 - x2, z1 - z2));
	}
}