/*
Michael Polonio
50:198:456/556
Assignment 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common.h"
#include "mat.h"

char mesh[10000];
int test, numVerts = 0, numFaces = 0, numEdges = 0, facepoints = 0;
int mode = 0, meshMode;

GLfloat vertices[MAXFACES][3];
GLushort faces[MAXFACES];
GLfloat colorv[46000];

GLuint vao, vbo[2], program, pos = 0, color = 0;

GLuint ModelView, Projection;

GLfloat transform[16];
GLfloat view[16];
GLfloat projection[16];

GLfloat t[3] = { 0.0f, 0.0f, 0.0f };	   /* translation control */
GLfloat scow[3] = { 1.5f, 1.5f, 1.5f };    /* scaling control */
GLfloat sbunny[3] = { 1.5f, 1.5f, 1.5f };
GLfloat s[3] = { 0.5f, 0.5f, 0.5f };
GLfloat spin[3] = { 0.0f, 0.0f, 0.0f };	   /* rotation control */
//int animation = FALSE;

GLfloat eyeMug[3] = { 0.0f, 1.0f, 3.0f };
GLfloat atMug[3] = { 0.0f, 1.0f, 0.0f };
GLfloat upMug[3] = { 0.0f, 1.0f, 0.0f };
GLfloat translateMug[3] = { 0.0f, 0.0f, 0.0f };
GLfloat scaleMug[3] = { 0.5f, 0.5f, 0.5f };
GLfloat spinMug[3] = { 270.0f, 0.0f, 0.0f };

GLfloat eyeTeapot[3] = { 3.0f, 1.0f, 3.0f };
GLfloat atTeapot[3] = { 0.0f, 1.0f, 0.0f };
GLfloat upTeapot[3] = { 0.0f, 1.0f, 0.0f };

GLfloat eyeCow[3] = { 0.0f, 2.0f, 0.5f };
GLfloat atCow[3] = { 0.0f, 1.0f, 0.0f };
GLfloat upCow[3] = { 0.0f, 1.0f, 0.0f };

GLfloat eyeHand[3] = { -6.0f, -18.0f, 6.0f };
GLfloat atHand[3] = { 0.0f, 0.0f, 0.0f };
GLfloat upHand[3] = { 0.0f, 1.0f, 0.0f };

GLfloat eyeArma[3] = { 0.0f, 40.0f, -75.0f };
GLfloat atArma[3] = { 0.0f, 25.0f, 0.0f };
GLfloat upArma[3] = { 0.0f, 1.0f, 0.0f };

GLfloat eyeBunny[3] = { 0.0f, 1.0f, 0.5f };
GLfloat atBunny[3] = { 0.0f, 0.0f, 0.0f };
GLfloat upBunny[3] = { 0.0f, 1.0f, 0.0f };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void init(void) {
	
	glGenBuffers(2, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorv), colorv, GL_STATIC_DRAW);

	// Load shaders and use the resulting shader program
	program = initshader("<enter path here>  \\vshader.glsl",
					   	"<enter path here> \\fragShader.glsl");
	glUseProgram(program);

	// Create a vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Initialize the vertex position attribute from the vertex shader
	pos = glGetAttribLocation(program, "vPos");
	glEnableVertexAttribArray(pos);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	color = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	ModelView = glGetUniformLocation(program, "modelview");
	Projection = glGetUniformLocation(program, "projection");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
//	glCullFace(GL_FRONT);
	glClearColor(0.2, 0.2, 0.2, 1.0);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	identity(transform);

	if (meshMode == 0) {
		lookat(transform, eyeMug, atMug, upMug);
		scale(transform, s);
		rotate(transform, spin[0]+270, 1.0, 0.0, 0.0);
		rotate(transform, spin[1], 0.0, 1.0, 0.0);
		rotate(transform, spin[2], 0.0, 0.0, 1.0);
	}
	else
		if (meshMode == 1) {
			lookat(transform, eyeTeapot, atTeapot, upTeapot);
			translate(transform, t);
			scale(transform, s);
			rotate(transform, spin[0], 1.0, 0.0, 0.0);
			rotate(transform, spin[1], 0.0, 1.0, 0.0);
			rotate(transform, spin[2], 0.0, 0.0, 1.0);
		}
		else
			if (meshMode == 2) {
				lookat(transform, eyeCow, atCow, upCow);
				translate(transform, t);
				scale(transform, s);
				rotate(transform, spin[0]+300, 1.0, 0.0, 0.0);
				rotate(transform, spin[1], 0.0, 1.0, 0.0);
				rotate(transform, spin[2], 0.0, 0.0, 1.0);
			}
			else
				if (meshMode == 3) {
					lookat(transform, eyeHand, atHand, upHand);
					translate(transform, t);
					scale(transform, s);
					rotate(transform, spin[0], 1.0, 0.0, 0.0);
					rotate(transform, spin[1], 0.0, 1.0, 0.0);
					rotate(transform, spin[2], 0.0, 0.0, 1.0);
				}
				else
					if (meshMode == 4) {
						lookat(transform, eyeArma, atArma, upArma);
						translate(transform, t);
						scale(transform, s);
						rotate(transform, spin[0], 1.0, 0.0, 0.0);
						rotate(transform, spin[1], 0.0, 1.0, 0.0);
						rotate(transform, spin[2], 0.0, 0.0, 1.0);
					}
					else
						if (meshMode == 5) {
							lookat(transform, eyeBunny, atBunny, upBunny);
							translate(transform, t);
							scale(transform, sbunny);
							rotate(transform, spin[0], 1.0, 0.0, 0.0);
							rotate(transform, spin[1], 0.0, 1.0, 0.0);
							rotate(transform, spin[2], 0.0, 0.0, 1.0);
						}
	
	glUseProgram(program);
	glBindVertexArray(vao);
	glUniformMatrix4fv(ModelView, 1, GL_FALSE, transform);
	glUniformMatrix4fv(Projection, 1, GL_FALSE, projection);

	if (meshMode == 0)
		numFaces = MUGFACES;
	else
		if (meshMode == 1)
			numFaces = TEAPOTFACES;
		else
			if (meshMode == 2)
				numFaces = COWFACES*4;
			else
				if (meshMode == 3)
					numFaces = HANDFACES*4;
				else
					if (meshMode == 4)
						numFaces = ARMADILLOFACES;
					else
						if (meshMode == 5)
							numFaces = MAXFACES;


	if(mode == 0)	// face mode
		glDrawElements(GL_TRIANGLES, numFaces, GL_UNSIGNED_SHORT, faces);
	else
		if(mode == 1) // edge mode
			glDrawElements(GL_LINES, numFaces, GL_UNSIGNED_SHORT, faces);
		else
			if(mode == 2)	// vertex mode
				glDrawElements(GL_POINTS, numFaces, GL_UNSIGNED_SHORT, faces);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void readMesh(void) {
	FILE *fp;
	int count = 0;

	if (meshMode == 0)
		fp = fopen(mug, "r");
	else
		if (meshMode == 1)
			fp = fopen(teapot, "r");
		else
			if (meshMode == 2)
				fp = fopen(cow, "r");
			else
				if (meshMode == 3)
					fp = fopen(hand, "r");
				else
					if (meshMode == 4)
						fp = fopen(arma, "r");
					else
						if (meshMode == 5)
							fp = fopen(bunny, "r");
					
	if (fp == NULL) {
		printf("Could not open file");
		exit(EXIT_FAILURE);
	}
	fseek(fp, 0L, SEEK_END); // putting cursor at end of file for size
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	for (int i = 0; i < size; i++) {	// parsing .off file
		if (fgets(mesh, size, fp) != NULL) {
			if (i == 1) {
				sscanf(mesh, "%d %d %d", &numVerts, &numFaces, &numEdges);
			//	printf("numVerts = %d : numFaces = %d\n", numVerts, numFaces);
			}	else
				if (i >= 2 && i < numVerts + 2) // first row of vertices
					sscanf(mesh, "%f %f %f", &vertices[i - 2][0], &vertices[i - 2][1], &vertices[i - 2][2]);
				else
					if (i >= numVerts + 2) {
						sscanf(mesh, "%d %d %d %d", &facepoints, &faces[count], &faces[count + 1], &faces[count + 2]);
						count += 3;
					}
		}
	}

	//	for (int i = 0; i < numVerts; i++) {
	//		for (int j = 0; j < 3; j++)
	//			printf("verticiesFinal[%d][%d] = %f\n", i, j, vertices[i][j]);
	//	}
	//	for (int i = 0; i < numFaces * 3; i++)
	//		printf("faces[%d] = %d\n", i, faces[i]);
	fclose(fp);

	for (int i = 0; i < 50000; i++) {	// generate random color
		colorv[i] = (float)rand() / (float)(RAND_MAX / 1.0);;
		if (colorv[i] >= .99f)
			colorv[i] = 0.0f;
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void update(void) {
	spin[0] += 0.1;
	spin[1] += 0.15;
	spin[2] -= 0.1;
	if (spin[0] > 360.0)
		spin[0] -= 360.0;
	if (spin[1] > 360.0)
		spin[1] -= 360.0;
	if (spin[2] < 360.0)
		spin[2] += 360.0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void keyboard(GLFWwindow *w, int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_UP:
//		spin[0] -= 10;
		break;
	case GLFW_KEY_E: /* edge mode */
		mode = 1;
		break;
	case GLFW_KEY_F: /* face mode */
		mode = 0;
		break;
	case GLFW_KEY_V: /* vertex mode */
		mode = 2;
		break;
	case GLFW_KEY_X:
//		if (mods == GLFW_MOD_SHIFT) {
//			eyeMug[0] += 0.1f;
//			atMug[0] += 0.1f;
//		}
//		else {
//			eyeMug[0] -= 0.1f;
//			atMug[0] -= 0.1f;
//			}
	case GLFW_KEY_N:
//		if (meshMode == 4)
//			meshMode = 0;
//		else
//		meshMode++;
//		readMesh();
//		init();
		break;
	case GLFW_KEY_P:
//		if (meshMode == 0)
//			meshMode = 4;
//		else
//		meshMode--;
//		readMesh();
//		init();
		break;
	case GLFW_KEY_DOWN:
//		spin[0] += 10;
		break;
	case GLFW_KEY_LEFT:
		if( meshMode == 0)
			spin[2] -= 10.1;
		else
			if(meshMode == 1)
				spin[1] -= 10.1;
			else
				if (meshMode == 2)
					spin[1] -= 10.1;
				else
					if (meshMode == 3)
						spin[1] -= 10.1;
					else
						if (meshMode == 4)
							spin[1] -= 10.1;
						else
							if (meshMode == 5)
								spin[1] -= 10.1;
		break;
	case GLFW_KEY_RIGHT:
		if (meshMode == 0)
			spin[2] += 10.1;
		else
			if (meshMode == 1)
				spin[1] += 10.1;
			else
				if (meshMode == 2)
					spin[1] += 10.1;
				else
					if (meshMode == 3)
						spin[1] += 10.1;
					else
						if (meshMode == 4)
							spin[1] += 10.1;
						else
							if (meshMode == 5)
								spin[1] += 10.1;
		break;
	case GLFW_KEY_MINUS:
		t[2] -= 0.1;
		break;
	case GLFW_KEY_EQUAL:
		t[2] += 0.1;
		break;
	case GLFW_KEY_A:
		if (action == GLFW_PRESS)
//			animation = !animation;
		break;
	case GLFW_KEY_R:
//		animation = FALSE;
		spin[0] = spin[1] = spin[2] = 0;
		break;
	case GLFW_KEY_Q:
		glfwSetWindowShouldClose(w, GL_TRUE);
		break;
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(w, GL_TRUE);
		break;
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void reshape(GLFWwindow *w, int width, int height) {
	glViewport(0, 0, width, height);
	perspective(projection, 67, (float)width / ((float)height), 0.1f, 100.0f);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(int argc, char *argv[]) 
{	
	int input;

	printf("Which mesh do you want to load?\n\t");
	printf("1: Mug\n\t2: Teapot\n\t3: Cow\n\t4: Hand\n\t5: Armadillo\n\t6: Bunny\n");
	scanf("%d", &input);
	if (input != 1 && input != 2 && input != 3 && input != 4 && input != 5 && input != 6) {
		printf("Invalid input. Exiting.\n");
		return 0;
	}
	meshMode = input - 1;

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	printf("%s\n", glGetString(GL_VERSION));
	
	GLFWwindow *window = glfwCreateWindow(712, 712, "", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	

	readMesh();
	init();
	reshape(window, 712, 712);
	glfwSetKeyCallback(window, keyboard);
	glfwSetWindowSizeCallback(window, reshape);

	while (!glfwWindowShouldClose(window)) {
		
		draw();
		
		glfwSwapBuffers(window);
	//	if (animation)
	//	update();
		
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
