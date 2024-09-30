/*
Practica 4 Modelado Jerárquico
Erandi Pérez
8/09/2024.

*/


#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);


const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard
float	movX = -3.0f,
movY = 0.0f,
movZ = -10.0f,
rot = 0.0f;

//For model
float	hombro = 0.0f;
float	codo = 0.0f;
float	muneca = 0.0f;
float	dedo1 = 0.0f;
float	dedo1_B = 0.0f;
float	dedo2 = 0.0f;
float	Dedo2_B = 0.0f;
float	dedo3 = 0.0f;
float	Dedo3_B = 0.0f;
float	dedo4 = 0.0f;
float	Dedo4_B = 0.0f;


float max_angle_up = 45.0f; // Máximo ángulo hacia arriba en grados
float max_angle_down = -45.0f; // Máximo ángulo hacia abajo en grados
float increment = 0.03f; // Incremento por cada paso


float max_hombro = 90.0f; // Máximo 90 grados
float min_hombro = 0.0f;  // Mínimo 0 grados


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 4: Modelado Jerarquico_Erandi ", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificaci�n de errores de creacion  ventana
	if (nullptr == window)
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
	// use with Orthographic Projection




	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f,  0.5f, 0.5f,
		0.5f,  0.5f, 0.5f,
		-0.5f,  0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,

		-0.5f, -0.5f,-0.5f,
		 0.5f, -0.5f,-0.5f,
		 0.5f,  0.5f,-0.5f,
		 0.5f,  0.5f,-0.5f,
		-0.5f,  0.5f,-0.5f,
		-0.5f, -0.5f,-0.5f,

		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  -0.5f, 0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	glm::mat4 projection = glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp2



		//View set up 
		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint uniformColor = ourShader.uniformColor;

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));


		glBindVertexArray(VAO);

		//Model Bicep
		model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0, 1.0f)); //hombro
		//para recorrer el pivote (caja mide 3, recorro 1.5 para que el pivote este al inicio y no en el centro)
		modelTemp = model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		//envio el tamaño de la caja
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		//mando el  color
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//A

		//Model Antebrazo
		model = glm::translate(modelTemp, glm::vec3(1.5f, 0.0, 0.0f));// valor anterior para antebrazo (bicep)
		model = glm::rotate(model, glm::radians(codo), glm::vec3(0.0f, 1.0, 0.0f));
		// recorremos el pivote (caja mide 2 , recorro 1.5 para que el pivote este al inicio y no en el centro) 
		modelTemp = model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f)); // valor anterior para palma
		//envio el tamaño de la caja
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		//mando el  color
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//B 

		//Model Palma
		//regresar al valor anterior para no inicializar la matriz desde el origen
		model = glm::translate(modelTemp, glm::vec3(1.0f, 0.0, 0.0f));// valor anterior para palma (antebrazo) 
		model = glm::rotate(model, glm::radians(muneca), glm::vec3(1.0f, 0.0, 0.0f));
		//recorremos el pivote (caja mide 0.5 , recorro 0.25 para que el pivote este al inicio y no en el centro) 
		modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));//valor anterior para dedo1
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//C


	   //Model dedo1
		model = glm::translate(modelTemp, glm::vec3(0.005f, 0.35f, 0.375f));
		model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 0.0, 1.0f)); 
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); 
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 0.8f, 1.0f); // Azul aurora boreal
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//Dedo1_B
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.00f, 0.0f)); 
		model = glm::rotate(model, glm::radians(dedo1_B), glm::vec3(0.0f, 0.0, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); 
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.75f, 0.8f); // Rosa claro
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//F 


		//Dedo2
		model = glm::translate(modelTemp2, glm::vec3(0.005f, 0.35f, -0.0f));
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); 
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 1.0f, 1.0f); // Azul agua (cyan)
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//Model Dedo2_B
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0));
		model = glm::rotate(model, glm::radians(Dedo2_B), glm::vec3(0.0f, 0.0, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); 
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.5f, 0.5f); // Rojo claro
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Model dedo3
		model = glm::translate(modelTemp2, glm::vec3(0.005f, 0.35f, -0.4f));
		model = glm::rotate(model, glm::radians(dedo3), glm::vec3(0.0f, 0.0, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); 
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0f, 0.5f, 0.0f); // Naranja
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//Model Dedo3_B
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0));
		model = glm::rotate(model, glm::radians(Dedo3_B), glm::vec3(0.0f, 0.0, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); 
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(0.5f, 0.5f, 0.5f); // Gris
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//J 


		//Model dedo4
		model = glm::translate(modelTemp2, glm::vec3(0.005f, -0.35f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo4), glm::vec3(0.0f, 0.0, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); 
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(0.8f, 0.6f, 1.0f); // Morado claro
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//Model Dedo4_B
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0));
		model = glm::rotate(model, glm::radians(Dedo4_B), glm::vec3(0.0f, 0.0, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); 
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 0.8f, 1.0f); // Azul aurora boreal
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
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


void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.001f;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		movY += 0.11f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		movY -= 0.11f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot += 0.11f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot -= 0.11f;


	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		hombro = (hombro >= max_hombro) ? max_hombro : hombro + increment;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		hombro = (hombro <= min_hombro) ? min_hombro : hombro - increment;


	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		codo += increment;
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		codo -= increment;

	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		muneca += increment;
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		muneca -= increment;


	// Dedo1
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		dedo1 = (dedo1 >= max_angle_up) ? dedo1 : dedo1 + increment;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		dedo1 = (dedo1 <= max_angle_down) ? dedo1 : dedo1 - increment;

	// Dedo1_B
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		dedo1_B = (dedo1_B >= max_angle_up) ? dedo1_B : dedo1_B + increment;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		dedo1_B = (dedo1_B <= max_angle_down) ? dedo1_B : dedo1_B - increment;

	// Dedo2
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		dedo2 = (dedo2 >= max_angle_up) ? dedo2 : dedo2 + increment;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		dedo2 = (dedo2 <= max_angle_down) ? dedo2 : dedo2 - increment;

	// Dedo2_B
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		Dedo2_B = (Dedo2_B >= max_angle_up) ? Dedo2_B : Dedo2_B + increment;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		Dedo2_B = (Dedo2_B <= max_angle_down) ? Dedo2_B : Dedo2_B - increment;

	// Dedo3
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		dedo3 = (dedo3 >= max_angle_up) ? dedo3 : dedo3 + increment;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		dedo3 = (dedo3 <= max_angle_down) ? dedo3 : dedo3 - increment;

	// Dedo3_B
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		Dedo3_B = (Dedo3_B >= max_angle_up) ? Dedo3_B : Dedo3_B + increment;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		Dedo3_B = (Dedo3_B <= max_angle_down) ? Dedo3_B : Dedo3_B - increment;

	// Dedo4
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		dedo4 = (dedo4 <= -max_angle_up) ? dedo4 : dedo4 - increment;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		dedo4 = (dedo4 >= -max_angle_down) ? dedo4 : dedo4 + increment;

	// Dedo4_B
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		Dedo4_B = (Dedo4_B <= -max_angle_up) ? Dedo4_B : Dedo4_B - increment;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		Dedo4_B = (Dedo4_B >= -max_angle_down) ? Dedo4_B : Dedo4_B + increment;		


}


