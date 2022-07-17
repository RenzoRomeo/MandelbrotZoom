#version 460 core

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
layout(rgba32f, binding = 0) uniform image2D screen;

uniform highp float xa;
uniform highp float xb;
uniform highp float ya;
uniform highp float yb;

vec2 complex_sqr(vec2 a) {
	return vec2(a.x * a.x - a.y * a.y, 2 * a.x * a.y);
}

float map(float value, float inMin, float inMax, float outMin, float outMax) {
	return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

void main() {
	ivec2 storePos = ivec2(gl_GlobalInvocationID.xy);
	ivec2 size = imageSize(screen);

	const int limit = 200;

	float a = (float(size.x) - storePos.x) / float(size.x) * (xb - xa) + xa;
	float b = storePos.y / float(size.y) * (yb - ya) + ya;

	vec2 c = vec2(a, b);
	vec2 z = vec2(0.0, 0.0);

	int i;
	for (i = 0; i < limit; i++) {
		if (length(z) >= 2)
			break;
		z = complex_sqr(z) + c;
	}

	float color = map(i, 0.0, float(limit), 0.0, 1.0);

	imageStore(screen, storePos, vec4(color, color, color, 1.0));
}