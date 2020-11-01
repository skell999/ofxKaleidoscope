#include "ofxKaleidoscope.h"

ofxKaleidoscope::ofxKaleidoscope()
{

}

ofxKaleidoscope::~ofxKaleidoscope()
{
}

void ofxKaleidoscope::allocate(int width, int height)
{
	fbo.allocate(width, height);

	copyShaderToBin();

	shader.load("ofxKaleidoscopeShader/kaleidoscope");
}

void ofxKaleidoscope::update(ofTexture& inputImage, float div, float rotate, glm::vec2 translate, float spin, float zoom, bool enableRepitition, float repetitions, glm::vec2 stretch, bool enablePowDistortX, bool enablePowDistortY, glm::vec2 powDistort, bool flipImage)
{
	fbo.begin();

	shader.begin();
	shader.setUniformTexture("inputImage", inputImage, 1);
	shader.setUniform2f("resolution", fbo.getWidth(), fbo.getHeight());

	shader.setUniform1f("div", div);
	shader.setUniform1f("rotate", rotate);
	shader.setUniform2f("translate", translate);

	shader.setUniform1f("spin", spin);
	shader.setUniform1f("zoom", zoom);

	shader.setUniform1f("enableRepitition", enableRepitition);
	shader.setUniform1f("repetitions", repetitions);

	shader.setUniform2f("stretch", stretch);

	shader.setUniform1f("enablePowDistortX", enablePowDistortX);
	shader.setUniform1f("enablePowDistortY", enablePowDistortY);
	shader.setUniform2f("powDistort", powDistort);

	shader.setUniform1f("flipImage", flipImage);

	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofDrawPlane(ofGetWidth(), ofGetHeight());
	ofPopMatrix();

	shader.end();

	fbo.end();
}

void ofxKaleidoscope::draw(int x, int y)
{
	fbo.draw(x, y);
}

ofFbo& ofxKaleidoscope::getFbo()
{
	return fbo;
}

ofShader& ofxKaleidoscope::getShader()
{
	return shader;
}

bool ofxKaleidoscope::copyShaderToBin()
{
	ofDirectory dir;

	bool result = true;
	if (!dir.doesDirectoryExist("ofxKaleidoscopeShader")) {
		if (!dir.createDirectory("ofxKaleidoscopeShader"))
		{
			cout << "Create Directory ofxKaleidoscopeShader FAILED" << endl;
			result = false;
		}
	}

	if (!ofFile::copyFromTo("../../../../../addons/ofxKaleidoscope/src/shader/kaleidoscope.vert", "ofxKaleidoscopeShader/kaleidoscope.vert", true, true) && !result)
	{
		cout << "Copy ImageSweep.vert FAILED" << endl;
		result = false;
	}

	if (!ofFile::copyFromTo("../../../../../addons/ofxKaleidoscope/src/shader/kaleidoscope.frag", "ofxKaleidoscopeShader/kaleidoscope.frag", true, true) && !result)
	{
		cout << "Copy ImageSweep.frag FAILED" << endl;
		result = false;
	};

	return result;
}
