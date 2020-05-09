
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <fstream>
#include <cassert>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fmt/format.h>

#include "GLDebugMessageCallback.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

std::string tryReadFile(const std::string& filepath)
{
    std::stringstream ss;
    std::ifstream fs(filepath);
    if (!fs) {
        fmt::print("Error loading file: {}\n", filepath);
        return "";
    }
    ss << fs.rdbuf();
    return ss.str();
}

GLuint compileShader(unsigned int type, const std::string& source)
{
    // create shader
    GLuint id = glCreateShader(type);
    const char* src = source.c_str();

    // specify shader source for created shader and compile it
    glShaderSource(id, 1, &src, nullptr); //length=NULL means source is null-terminated
    glCompileShader(id);

    // handle compilation errors
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result); // returns parameter from shader obj
    if (result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);

        fmt::print("Failed to compile {} shader:\n{}\n",
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment"),
            message
        );

        glDeleteShader(id); // delete it
        delete[] message;
        return 0; // 0 = failure
    }

    return id;
}

GLuint createShaderProgram(const std::string& vertexSrc, const std::string& fragmentSrc) {

    GLuint program = glCreateProgram();   
    GLuint vs = compileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    // attach and link shaders to the program
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // they are linked to the program, we can delete them from memory
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void) {

    /* Initialize GLFW */
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync


    // Init GLEW
    if (glewInit() != GLEW_OK) fmt::print("GLEW init error");
    printf("GL version: %s\n", glGetString(GL_VERSION));

    // GL setup
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, nullptr);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // data...
    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
    };

    
    // VAO
    VertexArray va;

    // VBO -> VAO
    VertexBuffer* vb = new VertexBuffer(vertices, sizeof(vertices));

    // IBO (slot GL_ELEMENT_ARRAY_BUFFER) -> VAO
    va.bind(); // TODO: bind IBO inside VertexArray class
    IndexBuffer* ib = new IndexBuffer(indices, 6);

    // layout
    VertexBufferLayout layout;
    layout.addAttrib(GL_FLOAT, 2);
    va.addBuffer(*vb, layout);

    GLuint testShader = createShaderProgram(
        tryReadFile("shaders/red.vert"),
        tryReadFile("shaders/red.frag")
    );
    GLint u_Secs = glGetUniformLocation(testShader, "u_Secs");
    GLint u_Color = glGetUniformLocation(testShader, "u_Color");

    // unbind all, imporant: unbind VAO first because
    // binding VBO and IBO also links them to VAO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);
    

    float r = 0.0f;
    double xpos, ypos;
    int width, height;



    while (!glfwWindowShouldClose(window))
    {
        glfwGetCursorPos(window, &xpos, &ypos);
        glfwGetWindowSize(window, &width, &height);
        glClear(GL_COLOR_BUFFER_BIT);

        if (r > 1.0f) r = 0.0f;
        r += 0.05f;

        glUseProgram(testShader);
        glUniform1f(u_Secs, clock() / (float)CLOCKS_PER_SEC);
        glUniform4f(u_Color, r, 0.3f, 0.8f, 1.0f);

        va.bind();

        glUniform4f(u_Color, r, 0.3f, 0.8f, 1.0f);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(0));

        glUniform4f(u_Color, 1 - r, 0.3f, 0.8f, 1.0f);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * 4));

        /*GLint varrayid;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &varrayid);
        fmt::print("current vao = {}\n", varrayid);*/

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete vb;
    delete ib;

    glfwTerminate();
    return 0;
}