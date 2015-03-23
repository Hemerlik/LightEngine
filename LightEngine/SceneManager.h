#ifdef WIN32
#include <GL/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif

#include <iostream>
#include <Windows.h>
#include <iostream>
#include "Camera.h"

#ifndef MATRIX
#define MATRIX
#include "../MathTools/Matrix.h"
#endif

class SceneManager
{
public:
	SceneManager(int windowHeight, int windowWidth);
	~SceneManager();
	bool Initialize();
	void Update();
private:
	int _windowWidth;
	int _windowHeight;
	float _fps;
	Camera _activeCam;
};