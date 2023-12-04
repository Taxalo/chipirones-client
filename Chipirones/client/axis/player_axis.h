#include "../../java.h"

struct splayer_axis {
	double minX, minY, minZ,
		maxX, maxY, maxZ;
};

class cplayer_axis {
private:
	jobject axis_aligned_obj;
public:
	cplayer_axis(jobject);
	~cplayer_axis();

	splayer_axis get_boundingbox();
	void set_boundingbox(splayer_axis target);
	

	void set(double minX, double minY, double minZ, double maxX, double maxY, double maxZ);
};