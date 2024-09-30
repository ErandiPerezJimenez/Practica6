#include<iostream>

//#define GLEW_STATIC

/*
Practica 3 Modelado Geométrico
Erandi Pérez
29/08/2024.

*/

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado geometrico_Erandi", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	
	float vertices[] = {
	-0.5f, -0.5f, 0.5f, 1.0f, 0.4f, 0.4f, // Front (Red)
	 0.5f, -0.5f, 0.5f, 1.0f, 0.4f, 0.4f,
	 0.5f,  0.5f, 0.5f, 1.0f, 0.4f, 0.4f,
	 0.5f,  0.5f, 0.5f, 1.0f, 0.4f, 0.4f,
	-0.5f,  0.5f, 0.5f, 1.0f, 0.4f, 0.4f,
	-0.5f, -0.5f, 0.5f, 1.0f, 0.4f, 0.4f,

	-0.5f, -0.5f,-0.5f, 1.0f, 0.4f, 0.4f, // Back (Red)
	 0.5f, -0.5f,-0.5f, 1.0f, 0.4f, 0.4f,
	 0.5f,  0.5f,-0.5f, 1.0f, 0.4f, 0.4f,
	 0.5f,  0.5f,-0.5f, 1.0f, 0.4f, 0.4f,
	-0.5f,  0.5f,-0.5f, 1.0f, 0.4f, 0.4f,
	-0.5f, -0.5f,-0.5f, 1.0f, 0.4f, 0.4f,

	 0.5f, -0.5f,  0.5f, 1.0f, 0.7f, 0.7f, // Right (Light Red)
	 0.5f, -0.5f, -0.5f, 1.0f, 0.7f, 0.7f,
	 0.5f,  0.5f, -0.5f, 1.0f, 0.7f, 0.7f,
	 0.5f,  0.5f, -0.5f, 1.0f, 0.7f, 0.7f,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.7f, 0.7f,
	 0.5f, -0.5f,  0.5f, 1.0f, 0.7f, 0.7f,

	-0.5f,  0.5f,  0.5f, 1.0f, 0.7f, 0.7f, // Left (Light Red)
	-0.5f,  0.5f, -0.5f, 1.0f, 0.7f, 0.7f,
	-0.5f, -0.5f, -0.5f, 1.0f, 0.7f, 0.7f,
	-0.5f, -0.5f, -0.5f, 1.0f, 0.7f, 0.7f,
	-0.5f, -0.5f,  0.5f, 1.0f, 0.7f, 0.7f,
	-0.5f,  0.5f,  0.5f, 1.0f, 0.7f, 0.7f,

	-0.5f, -0.5f, -0.5f, 1.0f, 0.7f, 0.7f, // Bottom (Light Red)
	 0.5f, -0.5f, -0.5f, 1.0f, 0.7f, 0.7f,
	 0.5f, -0.5f,  0.5f, 1.0f, 0.7f, 0.7f,
	 0.5f, -0.5f,  0.5f, 1.0f, 0.7f, 0.7f,
	-0.5f, -0.5f,  0.5f, 1.0f, 0.7f, 0.7f,
	-0.5f, -0.5f, -0.5f, 1.0f, 0.7f, 0.7f,

	-0.5f,  0.5f, -0.5f, 1.0f, 0.7f, 0.7f, // Top (Light Red)
	 0.5f,  0.5f, -0.5f, 1.0f, 0.7f, 0.7f,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.7f, 0.7f,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.7f, 0.7f,
	-0.5f,  0.5f,  0.5f, 1.0f, 0.7f, 0.7f,
	-0.5f,  0.5f, -0.5f, 1.0f, 0.7f, 0.7f,
	}; 

	float vertices_negro[] = {
		// Posiciones          // Colores
		-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 0.0f, // Frente
		 0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, 0.5f,   0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, 0.5f,   0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.5f,   0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,-0.5f,   0.0f, 0.0f, 0.0f, // Atrás
		 0.5f, -0.5f,-0.5f,   0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,-0.5f,   0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,-0.5f,   0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,-0.5f,   0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,-0.5f,   0.0f, 0.0f, 0.0f,

		 0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.0f, // Derecha
		 0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f, // Izquierda
		-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f, // Inferior
		 0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f, // Superior
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 0.0f,
	};
    
	GLuint VBO_black, VAO_black; 
	glGenVertexArrays(1, &VAO_black); 
	glGenBuffers(1, &VBO_black); 

	// Enlazar VAO
	glBindVertexArray(VAO_black); 

	// Enlazar y llenar VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO_black); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_negro), vertices_negro, GL_STATIC_DRAW); 

	// Configurar atributos de vértices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); 
	glEnableVertexAttribArray(0); 

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); 
	glEnableVertexAttribArray(1); 

	// Desvincular VBO y VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	GLuint VBO, VAO; 
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.529f, 0.808f, 0.980f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);


		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		///////////////////////////////////////////////////////////////////////////////////////////////////

		// Dibuja el cubo negro
		glBindVertexArray(VAO_black);  // Usar VAO del cubo negro 

		//ojo 1 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.2f));  // Ajustar el tamaño según sea necesario
		model = glm::translate(model, glm::vec3(1.4f, 7.4f, 3.0f));  // Posición para el cubo negro  

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);  // Dibuja el cubo negro

		//ojo2
		model = glm::mat4(1.0f); 
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.2f));  // Ajustar el tamaño según sea necesario
		model = glm::translate(model, glm::vec3(-1.4f, 7.4f, 3.0f));  // Posición para el cubo negro  

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		glDrawArrays(GL_TRIANGLES, 0, 36);  // Dibuja el cubo negro
		///////////////////////////////////////////////////////////////////////////////////////////////////////


		glBindVertexArray(VAO);

		//base del cangrejo 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(4.0f, 2.0f, 3.0f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(0.0f, 0.6f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//brazo izq del cangrejo
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.5f, 0.4f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-1.5f, 3.7f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//brazo izq del cangrejo (parte arriba)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 1.5f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-7.5f, 1.35f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//pinza izq del cangrejo (parte de abajo)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.5f, 0.4f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-2.0f, 7.1f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//pinza izq del cangrejo (parte de arriba)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 1.0f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-5.5f, 3.5f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//pinza izq del cangrejo (parte de arriba)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 1.0f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-9.5f, 3.5f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		///////////////////////////////pinza derecha//////////////////////////////////////////

		//brazo izq del cangrejo
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.5f, 0.4f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(1.5f, 3.7f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//brazo izq del cangrejo (parte arriba)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 1.5f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(7.5f, 1.35f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//pinza izq del cangrejo (parte de abajo)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.5f, 0.4f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(2.0f, 7.1f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//pinza izq del cangrejo (parte de arriba)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 1.0f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(5.5f, 3.5f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//pinza izq del cangrejo (parte de arriba)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 1.0f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(9.5f, 3.5f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		///////////////////////////// PATAS CANGREJO PARTE IZQ /////////////////////////////////

		//pata izq (uno) (horizontal)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.5f, 0.4f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-1.5f, 1.5f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//pata izq (uno) (vertical)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, -1.5f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-7.5f, 0.1f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//pata izq (dos) (horizontal)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.5f, 0.4f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-1.5f, 1.5f, 2.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//pata izq (dos) (vertical)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, -1.5f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-7.5f, 0.1f, 2.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//pata izq (tres) (horizontal)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.5f, 0.4f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-1.5f, 1.5f, -2.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//pata izq (tres) (vertical)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, -1.5f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-7.5f, 0.1f, -2.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		////////////////////////////PATAS CANGREJO PARTE DERECHA/////////////////////////////

		//pata izq (uno) (horizontal)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.5f, 0.4f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(1.5f, 1.5f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//pata izq (uno) (vertical)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, -1.5f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(7.5f, 0.1f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//pata izq (dos) (horizontal)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.5f, 0.4f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(1.5f, 1.5f, 2.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//pata izq (dos) (vertical)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, -1.5f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(7.5f, 0.1f, 2.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//pata izq (tres) (horizontal)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.5f, 0.4f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(1.5f, 1.5f, -2.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//pata izq (tres) (vertical)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, -1.5f, 0.5f)); //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(7.5f, 0.1f, -2.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		////////////////////////////////OJOS DEL CANGREJO/////////////////////////////////////

		// Ojo izq del cangrejo 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 0.5f));  //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-1.5f, 2.7f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));  //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(-0.7f, 3.7f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Ojo der del cangrejo
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 0.5f));  //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(1.5f, 2.7f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));  //Ancho, grosor, profundidad
		model = glm::translate(model, glm::vec3(0.7f, 3.7f, 0.0f)); 

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		glDrawArrays(GL_TRIANGLES, 0, 36); 


		
		glBindVertexArray(0); 
		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		 movY += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		 movY -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.4f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.4f;
 }


