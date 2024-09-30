#include<iostream>

/*
Practica 1 Dibujo de primitivas en 2D
Erandi Pérez
16/08/2024.

*/ 



//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/


	//Nombre de la ventana
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D Erandi", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		

	   //cabeza 1
		-0.508f,  0.473f, 0.0f,    0.82f,0.71f,0.55f,//C
		-0.671f,  0.271f, 0.0f,    0.82f,0.71f,0.55f,//D
		-0.608f,  0.141f, 0.0f,    0.82f,0.71f,0.55f,//E

      //cabeza 2
		-0.305f,  0.453f, 0.0f,    0.0f,1.0f,1.0f,//G
		-0.608f,  0.141f, 0.0f,    0.0f,1.0f,1.0f,//E
		-0.508f,  0.473f, 0.0f,    0.0f,1.0f,1.0f,//C
     
	  //cabeza 3
		-0.372f,  0.226f, 0.0f,    1.0f,1.0f,1.0f,//F
		-0.608f,  0.141f, 0.0f,    1.0f,1.0f,1.0f,//E
		-0.305f,  0.453f, 0.0f,    1.0f,1.0f,1.0f,//G
	  
	 //cuello 1
		-0.172f,  0.291f, 0.0f,    1.0f,0.0f,1.0f,//H
		-0.305f,  0.453f, 0.0f,    1.0f,0.0f,1.0f,//G
		-0.372f,  0.226f, 0.0f,    1.0f,0.0f,1.0f,//F
	
	//cuello 2
		-0.263f,  0.095f, 0.0f,    1.0f,1.0f,1.0f,//I
		-0.172f,  0.291f, 0.0f,    1.0f,1.0f,1.0f,//H
		-0.372f,  0.226f, 0.0f,    1.0f,1.0f,1.0f,//F
     
	// lomo 1
		0.0f,  0.246f, 0.0f,    0.0f,0.75f,0.75f,//J
	   -0.086f,  0.0f, 0.0f,    0.0f,0.75f,0.75f,//K
	   -0.172f,  0.291f, 0.0f,  0.0f,0.75f,0.75f,//H
	
	//lomo 2
	   -0.172f,  0.291f, 0.0f,  0.2f,1.0f,1.0f,//H
	   -0.263f,  0.095f, 0.0f,  0.2f,1.0f,1.0f,//I
	   -0.086f,  0.0f,   0.0f,  0.2f,1.0f,1.0f,//K

	// mano 1
		-0.291f,  0.032f, 0.0f,  1.0f,1.0f,0.0f,//L
		-0.263f,  0.095f, 0.0f,  1.0f,1.0f,0.0f,//I
		-0.086f,  0.0f, 0.0f,    1.0f,1.0f,0.0f,//K
	
	//parte de mano 1
		-0.227f,  0.024f,  0.0f,  1.0f,0.84f,0.0f,//N
		-0.086f,  0.0f,    0.0f,  1.0f,0.84f,0.0f,//K
		-0.001f,  -0.117f, 0.0f,  1.0f,0.84f,0.0f,//M
     
    // parte de pierna
	   0.0f,  0.246f, 0.0f,    0.0f,1.0f,1.0f,//J
	  -0.086f,  0.0f, 0.0f,    0.0f,1.0f,1.0f,//K
	   0.173f,  0.044f, 0.0f,  0.0f,1.0f,1.0f,//0

    //Lomo 4
	   0.0f,  0.246f, 0.0f,    0.5f, 0.5f, 0.5f,//J
	   0.331f,0.116f, 0.0f,    0.5f, 0.5f, 0.5f,//P
	   0.173f,  0.044f, 0.0f,  0.5f, 0.5f, 0.5f,//0
    
	//parte de pierna 2
	  -0.086f,  0.0f, 0.0f,    0.5f,0.0f,0.5f,//K
	   0.173f,  0.044f, 0.0f,  0.5f,0.0f,0.5f,//0
	  -0.001f,  -0.117f, 0.0f, 0.5f,0.0f,0.5f,//M

	//parte pierna 3
	   0.173f,  0.044f, 0.0f,  1.0f,0.0f,0.0f,//0
	  -0.001f,  -0.117f, 0.0f, 1.0f,0.0f,0.0f,//M
	   0.104f,  -0.132f, 0.0f, 1.0f,0.0f,0.0f,//Q

	//parte pierna 4
	   0.104f,  -0.132f, 0.0f, 0.0f,0.0f,1.0f,//Q
	  -0.001f,  -0.117f, 0.0f, 0.0f,0.0f,1.0f,//M
	   0.012f,  -0.267f, 0.0f, 0.0f,0.0f,1.0f,//R
    
	//parte pierna 5
	   0.104f,  -0.132f, 0.0f, 1.0f,0.0f,1.0f,//Q
	   0.012f,  -0.267f, 0.0f, 1.0f,0.0f,1.0f,//R
	   0.109f,  -0.315f, 0.0f, 1.0f,0.0f,1.0f,//S


    //pie_otro_1
	  -0.198f,  -0.011f, 0.0f, 0.0f,0.0f,1.0f,//U
	  -0.001f,  -0.117f, 0.0f, 0.0f,0.0f,1.0f,//M
	  -0.154f,  -0.207f, 0.0f, 0.0f,0.0f,1.0f,//V

	//pie_otro_2
	  -0.001f,  -0.117f, 0.0f, 1.0f,1.0f,1.0f,//M
	  -0.154f,  -0.207f, 0.0f, 1.0f,1.0f,1.0f,//V
	  -0.056f,  -0.194f, 0.0f, 1.0f,1.0f,1.0f,//Z

	//pie_otro_3
	  -0.154f,  -0.207f, 0.0f, 0.0f,1.0f,0.0f,//V
	  -0.056f,  -0.194f, 0.0f, 0.0f,1.0f,0.0f,//Z
	  -0.092f,  -0.264f, 0.0f, 0.0f,1.0f,0.0f,//W

	//pie_otro_4
	   -0.154f,  -0.207f, 0.0f, 0.0f,1.0f,0.0f,//V
	   -0.092f,  -0.264f, 0.0f, 0.0f,1.0f,0.0f,//W
	   -0.212f,  -0.264f, 0.0f, 0.0f,1.0f,0.0f,//A1

	//cola_lomo_2
	    0.173f,  0.044f, 0.0f,  0.0f,1.0f,  0.0f,//0
	    0.331f, 0.116f,  0.0f,  0.0f, 1.0f, 0.0f,//P
		0.104f, -0.132f, 0.0f,  0.0f, 1.0f, 0.0f,//Q

	//cola_lomo_3
		0.331f, 0.116f, 0.0f,  1.0f, 0.5f, 0.0f,//P
		0.104f, -0.132f, 0.0f, 1.0f, 0.5f, 0.0f,//Q
		0.289f, -0.142f, 0.0f, 1.0f, 0.5f, 0.0f,//B1

     //cola_final
		0.325f, 0.087f,  1.0f, 1.0f, 1.0f, 0.0f,//C1
		0.867f, -0.184f, 1.0f, 1.0f, 1.0f, 0.0f,//D1
		0.290f, -0.116f, 1.0f, 1.0f, 1.0f, 0.0f,//E1
   
    // pie 1 
	   0.012f,  -0.267f, 1.0f, 1.0f,0.0f,1.0f,//R
	   0.109f,  -0.315f, 1.0f, 1.0f,0.0f,1.0f,//S
	  -0.042f,  -0.337f, 1.0f, 1.0f,0.0f,1.0f,//T

    //mano_2
	  -0.291f, 0.129f, 1.0f, 1.0f, 0.0f, 1.0f,//G1
	  -0.347f, 0.043f, 1.0f, 1.0f, 0.0f, 1.0f,//F1
	  -0.263f, 0.095f, 0.0f, 0.2f, 1.0f, 1.0f,//I

     //mano_3
	  -0.347f, 0.043f, 1.0f, 1.0f, 0.0f, 1.0f,//F1
	  -0.263f, 0.095f, 0.0f, 0.2f, 1.0f, 1.0f,//I
	  -0.291f, 0.032f, 0.0f, 1.0f, 1.0f, 0.0f,//L
		

		




		//-0.5f,  0.5f, 0.0f,   1.0f,1.0f,0.0f, // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		3,2,1,// second Triangle
		0,1,3,
		
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);


        //glPointSize(10);//Tamaño del vértice
        //glDrawArrays(GL_POINTS,0,9); //(elemento arreglo donde empezaremos, puntos que quiero poner)
        
        //glDrawArrays(GL_LINES,0,2); // solo cierra dos vertices nomas
        //glDrawArrays(GL_LINE_LOOP,0,4); //cierra cada uno de los vértices que se tengan
        
        glDrawArrays(GL_TRIANGLES,0,3); // (elemento arreglo donde empezaremos, toma las coordenadas de esos tres vertices y hace el triángulo)
		glDrawArrays(GL_TRIANGLES, 3, 6);
		glDrawArrays(GL_TRIANGLES, 6, 9);
		glDrawArrays(GL_TRIANGLES, 9, 12);
		glDrawArrays(GL_TRIANGLES, 12, 15);
		glDrawArrays(GL_TRIANGLES, 15, 18);
		glDrawArrays(GL_TRIANGLES, 18, 21);
		glDrawArrays(GL_TRIANGLES, 21, 24);
		glDrawArrays(GL_TRIANGLES, 24, 27);
		glDrawArrays(GL_TRIANGLES, 27, 30);
		glDrawArrays(GL_TRIANGLES, 30, 33);
		glDrawArrays(GL_TRIANGLES, 33, 36);
		glDrawArrays(GL_TRIANGLES, 36, 39);

		//glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT,0); //orden diferente para dibujar los triángulos 

        
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate(); 
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}
