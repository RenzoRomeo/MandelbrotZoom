#version 460 core

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
layout(rgba32f, binding = 0) uniform image2D screen;

uniform highp float xa;
uniform highp float xb;
uniform highp float ya;
uniform highp float yb;

const int limit = 500;

vec2 complex_sqr(vec2 a) {
	return vec2(a.x * a.x - a.y * a.y, 2 * a.x * a.y);
}

vec4 colorMap(int i) {
    if (i < limit && i > 0) {
        int n = i % 16;
        vec4 mapping[16];
        mapping[0] = vec4(66.0, 30.0, 15.0, 1.0);
        mapping[1] = vec4(25.0, 7.0, 26.0, 1.0);
        mapping[2] = vec4(9.0, 1.0, 47.0, 1.0);
        mapping[3] = vec4(4.0, 4.0, 73.0, 1.0);
        mapping[4] = vec4(0.0, 7.0, 100.0, 1.0);
        mapping[5] = vec4(12.0, 44.0, 138.0, 1.0);
        mapping[6] = vec4(24.0, 82.0, 177.0, 1.0);
        mapping[7] = vec4(57.0, 125.0, 209.0, 1.0);
        mapping[8] = vec4(134.0, 181.0, 229.0, 1.0);
        mapping[9] = vec4(211.0, 236.0, 248.0, 1.0);
        mapping[10] = vec4(241.0, 233.0, 191.0, 1.0);
        mapping[11] = vec4(248.0, 201.0, 95.0, 1.0);
        mapping[12] = vec4(255.0, 170.0, 0.0, 1.0);
        mapping[13] = vec4(204.0, 128.0, 0.0, 1.0);
        mapping[14] = vec4(153.0, 87.0, 0.0, 1.0);
        mapping[15] = vec4(106.0, 52.0, 3.0, 1.0);
        return mapping[n] / 255.0;
    }
    else return vec4(0.0, 0.0, 0.0, 1.0);
}

void main() {
	ivec2 storePos = ivec2(gl_GlobalInvocationID.xy);
	ivec2 size = imageSize(screen);

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

	imageStore(screen, storePos, colorMap(i));
}