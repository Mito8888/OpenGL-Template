#include <iostream>
#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "engine/shader.h"

using namespace std;
using namespace glm;

const int WIDTH = 1024;
const int HEIGHT = 800;

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
};

GLuint vertexBuffer()
{
    GLuint vertex_buffer;

    //Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertex_buffer);

    //The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

    //Give vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    return vertex_buffer;
}

GLuint vertexArray()
{
    GLuint vertex_array;

    glGenVertexArrays(1, &vertex_array);

    glBindVertexArray(vertex_array);

    return vertex_array;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(int args, char** argv)
{
    if(!glfwInit())
    {
        cout << "Failed to initialize GLFW. " << endl;
    }

    filesystem::current_path(filesystem::path(argv[0]).remove_filename());

    glfwWindowHint(GLFW_SAMPLES, 4); //4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Draw Triangle", nullptr, nullptr);

    if(!window)
    {
        cout << "Failed to Open GLFW Window. " << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Make the context of window on current thread
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // check opengl version
    cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl; //segmentation fault

    glClearColor(0.0f, 0.1f, 0.0f, 0.0f);

    //Shaders
    Shader shader("src/shaders/vertex.vs", "src/shaders/fragment.fs");

    //Create Vertex Array Object
    GLuint vertex_array = vertexArray();

    //Create Vertex Buffer Object
    GLuint vertex_buffer = vertexBuffer();

    shader.use();

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

        glVertexAttribPointer(
            0, //attribute 0. No particular reason for 0, but must match the layout in the shader.
            3, //size
            GL_FLOAT, //type 
            GL_FALSE, //normalized?
            0, //stride
            (void*)0 //aarray buffer offset
            
        );

        //Draw triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        //Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    glDeleteVertexArrays(1, &vertex_array);
    glDeleteBuffers(1, &vertex_buffer);

    glfwTerminate();

    return 0;
}
