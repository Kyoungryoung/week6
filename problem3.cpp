#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <vector>
#include "math.h"
using namespace std;

const int width = 700;
const int height = 300;

float* pixels = new float[width*height * 3];

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue);
void circle(const int& i, const int& j, const int& r, const float& red, const float& green, const float& blue);
void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue);
void drawOnPixelBuffer();

class GeometricObjectInterface
{
public:
	virtual void draw() {}
		/*   T_HOW_TO_DRAW DrawInColor;
		DrawInColor.draw();*/
};

template<class T_OPERATION>
class GeometricObject: public GeometricObjectInterface
{
public:
	void draw(){
		T_OPERATION operation;
		operation.draw();
	}
};

class DrawBox
{
public:
		void draw() {
			drawLine(60, 10, 140, 10, 1.0f, 0.0f, 0.0f);
			drawLine(140, 10, 140, 90, 1.0f, 0.0f, 0.0f);
			drawLine(60, 90, 140, 90, 1.0f, 0.0f, 0.0f);
			drawLine( 60, 10,60, 90, 1.0f, 0.0f, 0.0f);
		}
};

class DrawCircle
{
public:
	void draw() {
		circle(200, 50, 40, 1.0f, 0.0f, 0.0f);
	}
};

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i0 == i1)
	{
		for (int j = j0; j < j1; j++)
			drawPixel(i0, j, red, green, blue);
		return;
	}

	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void circle(const int& i, const int& j, const int& r, const float& red, const float& green, const float& blue)
{
	double d = 0.0;
	float angle = 360.0;
	int x = 0, y = 0;

	for (angle = 0; angle < 360; angle++)
	{
		d = angle*(3.14 / 180);
		x = i + r*sin(d);
		y = j + r*cos(d);
		drawPixel(x, y, red, green, blue);
		drawPixel(x + 1, y, red, green, blue);
		drawPixel(x, y - 1, red, green, blue);
	}

}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

	for (int i = 0; i<width*height; i++) {
		pixels[i * 3 + 0] = 1.0f; // red 
		pixels[i * 3 + 1] = 1.0f; // green
		pixels[i * 3 + 2] = 1.0f; // blue
	}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);
}

int main() {
	
	std::vector<GeometricObjectInterface*> obj_list;
	obj_list.push_back(new GeometricObject<DrawBox>);
	obj_list.push_back(new GeometricObject<DrawCircle>);

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer();

	/*	for (int i = 0; i < 2; i++) {
			my_object[i]->draw();
		}*/

		for (auto itr : obj_list)
			itr->draw();

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);



		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 


	return 0;
}