#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<stdio.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void DrawCube(float centerPosX, float centerPosY, float centerPosZ, float edgelegth);

float rotationX = 0.0f;
float rotationY = 0.0f;
float axisZ = 0.0f;
float transX = 0.0f;
float transY = 0.0f;
static float moveX = 0.0f;
static float moveY = 0.0f;



int main(void)
{
	GLFWwindow *window;
	if (!glfwInit())
	{
		return -1;
	}

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glViewport(0.0f, 0.0f, screenWidth, screenHeight); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
	glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
	glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000); // essentially set coordinate system
	glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
	glLoadIdentity(); // same as above comment
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLfloat SizeLebar = SCREEN_WIDTH / 2;
	GLfloat SizeTinggi = SCREEN_HEIGHT / 2;





	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render OpenGL here
		glPushMatrix();
	
		glTranslatef(SizeLebar, SizeTinggi, -500);
		glTranslatef(moveX, moveY, 0);
		glTranslatef(transX, 0, 0);
		glTranslatef(0, transY, 0);
		glRotatef(rotationX, 1, 0, 0);
		glRotatef(rotationY, 0, 1, 0);
		glRotatef(axisZ, 0, 0, 1);
		glTranslatef(-SizeLebar, -SizeTinggi, 500);
		DrawCube(SizeLebar, SizeTinggi, -500, 200);

		glPopMatrix();

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	const float rotationSpeed = 5;
	const float translateSpeed = 20;
	static float angle = 1.0;


	// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key)
		{
		//Berputar pada sumbu X
		case GLFW_KEY_UP:
			rotationX += rotationSpeed;
			break;

		case GLFW_KEY_DOWN:
			rotationX -= rotationSpeed;
			break;

		//Berputar pada sumbu Y
		case GLFW_KEY_RIGHT:
			rotationY -= rotationSpeed;
			break;

		case GLFW_KEY_LEFT:
			rotationY += rotationSpeed;
			break;

		//Berputar pada sumbu Z
		case GLFW_KEY_N:
			axisZ += rotationSpeed;
			break;

		case GLFW_KEY_M:
			axisZ -= rotationSpeed;
			break;

		//Bergerak pada sumbu Y sesuai gelombang sinus
		case GLFW_KEY_K:
			angle -= translateSpeed;
			moveX = 30 * cos(angle* 3.14 / 180);
			moveY = angle / 6;
			break;

		case GLFW_KEY_I:
			angle += translateSpeed;
			moveX = 30 * cos(angle* 3.14 / 180);
			moveY = angle / 6;
			break;

		//Bergerak pada sumbu X sesuai gelombang cosinus
		case GLFW_KEY_L:
			angle += translateSpeed;
			moveX = angle / 6;
			moveY = 30 * sin(angle* 3.14 / 180);
			break;

		case GLFW_KEY_J:
			angle -= translateSpeed;
			moveX = angle / 6;
			moveY = 30 * sin(angle* 3.14 / 180);
			break;

		//bergerak pada sumbu X
		case GLFW_KEY_A:
			transX -= translateSpeed;
			break;

		case GLFW_KEY_D:
			transX += translateSpeed;
			break;

		//Bergerak pada sumbu Y
		case GLFW_KEY_W:
			transY += translateSpeed;
			break;

		case GLFW_KEY_S:
			transY -= translateSpeed;
			break;

		}
	}
}

void DrawCube(float centerPosX, float centerPosY, float centerPosZ, float edgeLengt)
{
	float Size =  edgeLengt * 0.5f;
	float vertices[] =
	{
		// Depan
		centerPosX - Size, centerPosY + Size, centerPosZ + Size, // TL
		centerPosX + Size, centerPosY + Size, centerPosZ + Size, // TR
		centerPosX + Size, centerPosY - Size, centerPosZ + Size, // BR
		centerPosX - Size, centerPosY - Size, centerPosZ + Size, // BL

		// Belakang
		centerPosX - Size, centerPosY + Size, centerPosZ - Size,
		centerPosX + Size, centerPosY + Size, centerPosZ - Size,
		centerPosX + Size, centerPosY - Size, centerPosZ - Size,
		centerPosX - Size, centerPosY - Size, centerPosZ - Size,

		// Kiri
		centerPosX - Size, centerPosY + Size, centerPosZ + Size,
		centerPosX - Size, centerPosY + Size, centerPosZ - Size,
		centerPosX - Size, centerPosY - Size, centerPosZ - Size,
		centerPosX - Size, centerPosY - Size, centerPosZ + Size,

		// Kanan
		centerPosX + Size, centerPosY + Size, centerPosZ + Size,
		centerPosX + Size, centerPosY + Size, centerPosZ - Size,
		centerPosX + Size, centerPosY - Size, centerPosZ - Size,
		centerPosX + Size, centerPosY - Size, centerPosZ + Size,

		// Bawah
		centerPosX - Size, centerPosY + Size, centerPosZ + Size,
		centerPosX - Size, centerPosY + Size, centerPosZ - Size,
		centerPosX + Size, centerPosY + Size, centerPosZ - Size,
		centerPosX + Size, centerPosY + Size, centerPosZ + Size,

		// Atas
		centerPosX - Size, centerPosY - Size, centerPosZ + Size,
		centerPosX - Size, centerPosY - Size, centerPosZ - Size,
		centerPosX + Size, centerPosY - Size, centerPosZ - Size,
		centerPosX + Size, centerPosY - Size, centerPosZ + Size
	};

	GLfloat colors[] =
	{ 
	  1, 0, 1,
	  0, 0, 1,
	  0, 1, 0,
	  0, 1, 0,
	  0, 1, 1,
	  1, 0, 1,
	  1, 1, 1,
	  1, 1, 0,
	  0, 1, 1,
	  0, 0, 1,
	  1, 0, 1,
	  1, 0, 0,
	  0, 1, 0,
	  0, 1, 1,
	  1, 1, 1,
	  1, 1, 0,
	  0, 1, 1,
	  0, 1, 0,
	  1, 1, 0,
	  1, 0, 0,
	  1, 0, 0,
	  0, 1, 1,
	  1, 1, 1,
	  1, 0, 1
	  /*
		1, 1, 1,
		1, 1, 1,
		1, 1, 1,
		1, 1, 1,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 0, 0,
		1, 0, 1,
		1, 0, 1,
		1, 0, 1,
		1, 0, 1,
		1, 1, 0,
		1, 1, 0,
		1, 1, 0,
		1, 1, 0,*/
	};

	//We have a color array and a vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	//Draw Vertex
	glDrawArrays(GL_QUADS, 0, 24);

	//Cleanup states
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);


}