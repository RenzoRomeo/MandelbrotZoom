#version 460 core

in vec2 fUV;

uniform sampler2D screen;

out vec4 FragColor;

void main() {
	FragColor = texture(screen, fUV);
}

//#version 460 core
//
//in vec2 fUV;
//
//out vec4 FragColor;
//
//vec2 complex_sqr(vec2 a) {
//	return vec2(a.x * a.x - a.y * a.y, 2 * a.x * a.y);
//}
//
//float map(float value, float inMin, float inMax, float outMin, float outMax) {
//	return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
//}
//
//void main() {
//	ivec2 storePos = ivec2(gl_FragCoord.xy);
//	ivec2 size = ivec2(1280, 720);
//
//	const int limit = 200;
//
//	const float xa = -2.0;
//	const float xb = 2.0;
//	const float ya = -2.0;
//	const float yb = 2.0;
//
//	float a = storePos.x / float(size.x) * (xb - xa) + xa;
//	float b = storePos.y / float(size.y) * (yb - ya) + ya;
//
//	vec2 c = vec2(a, b);
//	vec2 z = vec2(0.0, 0.0);
//
//	int i;
//	for (i = 0; i < limit; i++) {
//		if (length(z) >= 2)
//			break;
//		z = complex_sqr(z) + c;
//	}
//
//	float color = map(i, 0.0, float(limit), 0.0, 1.0);
//
//	FragColor = vec4(color, color, color, 1.0);
//}