#version 330

#define PI 3.1415927

out vec4 color;
uniform sampler2D inputImage;
uniform vec2 resolution;

uniform float div; // Number of divisions in the kaleidoscope. Default 4.0
uniform float rotate; // Rotates image before kaleidoscope
uniform vec2 translate; // Translate the kaleidoscope around the image

uniform float spin; // Rotates kaleidoscope
uniform float zoom; // Zooms the image before kaleidoscope. Default 1.0

uniform bool enableRepitition; // Creates repetition 
uniform float repetitions; // Number of repetitions

uniform vec2 stretch; // Stretch the image. Default 1.0 1.0

uniform bool enablePowDistortX; // Enable pow x distortion
uniform bool enablePowDistortY; // Enable pow y distortion
uniform vec2 powDistort; // Distorts the image with pow in the y direction. Default 1.0 1.0

uniform bool flipImage;

// based on https://www.shadertoy.com/view/ltl3Dj
vec2 kale(vec2 uv, float div, float rotate, float spin) {
	float angle = PI/div;
	float a = atan(uv.y,uv.x)+spin;
	float d = length(uv);
	a = mod(a,angle*2.0);
	a = abs(a-angle);
	uv.x = sin(a+rotate)*d;
	uv.y = cos(a+rotate)*d;
    return uv;
}

void main(){
	vec2 uv = gl_FragCoord.xy / resolution;

	// Aspect ratio
	uv = (gl_FragCoord.xy - 0.5 * resolution) / resolution.y;

	// Repition
	if(enableRepitition){
		uv.x = sin(uv.x * PI * repetitions + 0);
		uv.y = cos(uv.y * PI * repetitions + (PI * 0.5));

	}

	// Kaleidoscope
	uv = kale(uv,div,rotate,spin) * zoom;
	
	// Flip Image
	if(flipImage){
		uv.y = -uv.y;
	}
	
	// Stretch
	uv = uv * stretch;

	// Distort pow x
	if(enablePowDistortX){
		uv.x = pow(uv.x,powDistort.x);	
	}

	// Distort pow y
	if(enablePowDistortY){
		uv.y = pow(uv.y,powDistort.y);
	}
	
	// Position
	uv.x += translate.x * 0.01;
	uv.y += translate.y * 0.1;

	color = texture(inputImage,uv);
}