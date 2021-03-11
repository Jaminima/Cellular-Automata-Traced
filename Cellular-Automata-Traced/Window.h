#pragma once
#include <Windows.h>
#include "Renderer.h"

#include "GL/glut.h"
#include "GL/freeglut.h"

unsigned int framesInSec = 0;
time_t startTime = clock();

AutomotaGrid *_automota = new AutomotaGrid();
Camera *_camera = new Camera();
Renderer _renderer = Renderer(_automota, _camera);

void drawFrame()
{
	glDrawPixels(_renderer.w, _renderer.h, GL_RGBA, GL_UNSIGNED_INT, _renderer.Frame);
	glutSwapBuffers();
}


void triggerReDraw()
{
	framesInSec++;

	//_camera->MoveCamera(Vec3(0, 0, 0.005f));
	_camera->RotateCamera(Vec3(0, 0.05f, 0));
	_renderer.RenderFrame();

	if (clock() - startTime >= 1000)
	{
		printf_s("You averaged %d fps\n", framesInSec);
		framesInSec = 0;
		startTime = clock();
	}

	glutPostRedisplay();
}

void SetupFrame(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(_renderer.w, _renderer.h);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("glDrawPixels example");

	glutDisplayFunc(drawFrame);
	glutIdleFunc(triggerReDraw);

	//glutPassiveMotionFunc(MouseMove);
	//glutKeyboardFunc(KeyboardDepressed);

	glutMainLoop();
}