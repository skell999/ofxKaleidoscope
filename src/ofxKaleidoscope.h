#pragma once

#include "ofMain.h"

class ofxKaleidoscope
{
public:
	ofxKaleidoscope();
	~ofxKaleidoscope();
	void allocate(int width, int height);
	void update(ofTexture& inputImage, float div, float rotate, glm::vec2 translate, float spin, float zoom, bool enableRepitition, float repetitions, glm::vec2 stretch, bool enablePowDistortX, bool enablePowDistortY, glm::vec2 powDistort, bool flipImage);
	void draw(int x, int y);
	ofFbo& getFbo();
	ofShader& getShader();
	bool copyShaderToBin();


private:
	ofFbo fbo;
	ofShader shader;

};
