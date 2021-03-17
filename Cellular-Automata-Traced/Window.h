#pragma once
#include <Windows.h>
#include "Renderer.h"
#include "GridProcessor.h"

#include "GL/glut.h"
#include "GL/freeglut.h"

unsigned int framesInSec = 0;
time_t startTime = clock() + 1000;

AutomotaGrid* _automota = new AutomotaGrid();
Camera* _camera = new Camera();

void drawFrame()
{
	glDrawPixels(w, h, GL_RGBA, GL_UNSIGNED_INT, Frame);
	glutSwapBuffers();
}

void triggerReDraw()
{
	completion_future frame = RenderFrame();

	framesInSec++;

	_camera->MoveCamera(Vec3(0.01f, 0.01f, 0.1f));
	_camera->RotateCamera(Vec3(0, -0.01f, -0.01f));

	if (clock() - startTime >= 1000)
	{
		printf_s("You averaged %d fps\n", framesInSec);
		framesInSec = 0;
		startTime = clock();

		GameOfLife(_automota);
	}

	frame.wait();

	glutPostRedisplay();
}

void SetupFrame(int argc, char** argv)
{
	Setup(_automota, _camera);

	glutInit(&argc, argv);
	glutInitWindowSize(w, h);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("glDrawPixels example");

	glutDisplayFunc(drawFrame);
	glutIdleFunc(triggerReDraw);

	//glutPassiveMotionFunc(MouseMove);
	//glutKeyboardFunc(KeyboardDepressed);

	glutMainLoop();
}
