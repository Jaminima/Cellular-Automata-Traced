#pragma once
#include <Windows.h>
#include "Renderer.h"
#include "Inputs.h"
#include "GridProcessor.h"

#include "GL/glut.h"
#include "GL/freeglut.h"

unsigned int framesInSec = 0;
time_t fpsTime = clock() + 1000;
time_t tickTime = clock() + 1000;

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

	if (clock() - fpsTime >= 1000)
	{
		printf_s("You averaged %d fps\n", framesInSec);
		framesInSec = 0;
		fpsTime = clock();
	}

	if (*doGameTicks)
		if (clock() - tickTime >= 500)
		{
			gme = GameOfLife(_automota);
			tickTime = clock();
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
