#include <math.h>
#include "Vector.h"

vec3 RotateX(vec3 v, float angle) {
	vec3 rotatedVector = {
		v.x,
		v.y * cos(angle) - v.z * sin(angle),
		v.y * sin(angle) + v.z * cos(angle)
	};
	return rotatedVector;
}

vec3 RotateY(vec3 v, float angle) {
	vec3 rotatedVector = {
		v.x * cos(angle) - v.z * sin(angle),
		v.y,
		v.x * sin(angle) + v.z * cos(angle)
	};
	return rotatedVector;
}

vec3 RotateZ(vec3 v, float angle) {
	vec3 rotatedVector = {
		v.x* cos(angle) - v.y * sin(angle),
		v.x * sin(angle) + v.y * cos(angle),
		v.z
	};
	return rotatedVector;
}
