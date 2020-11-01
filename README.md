# ofxKaleidoscope
Gpu based kaleidoscope. Openframeworks addon.

## Basic usage

### ofApp members
```cpp
ofxKaleidoscope kal;
ofImage image;
```

### Setup
```cpp
ofDisableArbTex();
kal.allocate(ofGetWidth(), ofGetHeight());
image.load("yourImageFile.jpg");
image.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
```

### Update
```cpp
float div = 8;
float rotate = 0;
auto translate = glm::vec2(0.0, 0.0);

float spin = 0.0;
float zoom = 1.0;

bool enableRepitition = false;
float repetitions = 4.0;

auto stretch = glm::vec2(1.0, 1.0);

bool enablePowDistortX = false;
bool enablePowDistortY = false;
auto powDistort = glm::vec2(1.0, 1.0);

bool flipImage = false;

rotate = ofGetElapsedTimef() * 0.08;

kal.update(
	pic[currentImage].getTexture(), 
	div, 
	rotate, 
	translate, 
	spin, 
	zoom, 
	enableRepitition, 
	repetitions, 
	stretch, 
	enablePowDistortX, 
	enablePowDistortY, 
	powDistort, 
	flipImage
);
```

### Draw
```cpp
kal.draw(0,0);
```