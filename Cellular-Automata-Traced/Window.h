#pragma once
#include <Windows.h>
#include "Renderer.h"
#include "Inputs.h"
#include "GridProcessor.h"

#include "GL/glut.h"
#include "GL/freeglut.h"

unsigned int framesInSec = 0;
time_t startTime = clock() + 5000;

AutomotaGrid* _automota = new AutomotaGrid();
Camera* _camera = new Camera();

void drawFrame()
{
	glDrawPixels(w, h, GL_RGBA, GL_UNSIGNED_INT, Frame);
	glutSwapBuffers();
}

completion_future frame;
completion_future gme;

void triggerReDraw()
{
	frame = RenderFrame();

	framesInSec++;

	if (clock() - startTime >= 1000)
	{
		printf_s("You averaged %d fps\n", framesInSec);
		framesInSec = 0;
		startTime = clock();

		gme = GameOfLife(_automota);
	}

	frame.wait();

	glutPostRedisplay();

	if (gme.valid()) gme.wait();
}

void SetupFrame(int argc, char** argv)
{
	_input_cam_ref = _camera;
	Setup(_automota, _camera);

	glutInit(&argc, argv);
	glutInitWindowSize(w, h);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("glDrawPixels example");

	glutDisplayFunc(drawFrame);
	glutIdleFunc(triggerReDraw);

	glutPassiveMotionFunc(MouseMove);
	glutKeyboardFunc(KeyboardDepressed);

	glutMainLoop();
}
