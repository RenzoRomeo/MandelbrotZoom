#include "Mandelbrot.h"

#include <stdlib.h>
#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Input.h"

GLfloat vertices[] = {
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
     1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
     1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
};

GLuint indices[] = {
    0, 2, 1,
    0, 3, 2
};

Mandelbrot& Mandelbrot::get(int width, int height)
{
    static Mandelbrot s_instance(width, height);
    return s_instance;
}

Mandelbrot::Mandelbrot(int width, int height)
    : m_Width(width), m_Height(height)
{
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW.\n";
        exit(1);
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(m_Width, m_Height, "Mandelbrot", NULL, NULL);
    if (!m_Window) {
        std::cout << "Failed to create GLFW window.\n";
        exit(1);
    }

    glfwMakeContextCurrent(m_Window);
    glfwSetScrollCallback(m_Window, Input::scrollCallback);
    glfwSetMouseButtonCallback(m_Window, Input::mouseButtonCallback);
    glfwSetKeyCallback(m_Window, Input::keyCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD.\n";
        glfwTerminate();
        exit(1);
    }

    glfwSwapInterval(1);
    glViewport(0, 0, m_Width, m_Height);

    glfwShowWindow(m_Window);
}

void Mandelbrot::userInput()
{
    if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
        m_ZoomXAmp -= m_ZoomSpeed * m_ZoomXAmp * m_dt;
        m_ZoomYAmp -= m_ZoomSpeed * m_ZoomYAmp * m_dt;
        m_HasToRender = true;
    }
    else if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
        m_ZoomXAmp += m_ZoomSpeed * m_ZoomXAmp * m_dt;
        m_ZoomYAmp += m_ZoomSpeed * m_ZoomYAmp * m_dt;
        m_HasToRender = true;
    }
    if (Input::isKeyPressed(GLFW_KEY_W)) {
        m_ZoomY += m_MoveSpeed * m_ZoomYAmp * m_dt;
        m_HasToRender = true;
    }
    if (Input::isKeyPressed(GLFW_KEY_S)) {
        m_ZoomY -= m_MoveSpeed * m_ZoomYAmp * m_dt;
        m_HasToRender = true;
    }
    if (Input::isKeyPressed(GLFW_KEY_D)) {
        m_ZoomX -= m_MoveSpeed * m_ZoomXAmp * m_dt;
        m_HasToRender = true;
    }
    if (Input::isKeyPressed(GLFW_KEY_A)) {
        m_ZoomX += m_MoveSpeed * m_ZoomXAmp * m_dt;
        m_HasToRender = true;
    }
    m_ZoomSpeed += Input::yoff * m_dt * 0.2;
}

void Mandelbrot::run() {
    GLuint screenTex;
    glCreateTextures(GL_TEXTURE_2D, 1, &screenTex);
    glTextureParameteri(screenTex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(screenTex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(screenTex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(screenTex, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureStorage2D(screenTex, 1, GL_RGBA32F, m_Width, m_Height);
    glBindImageTexture(0, screenTex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

    Shader display("Resources/Shaders/vertex.shader", "Resources/Shaders/fragment.shader");
    Shader compute("Resources/Shaders/compute_mandelbrot.shader");

    GLuint VAO, VBO, EBO;
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glCreateBuffers(1, &VBO);
    glCreateBuffers(1, &EBO);

    glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glNamedBufferData(EBO, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexArrayAttrib(VAO, 0);
    glVertexArrayAttribBinding(VAO, 0, 0);
    glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

    glEnableVertexArrayAttrib(VAO, 1);
    glVertexArrayAttribBinding(VAO, 1, 0);
    glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));

    glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 5 * sizeof(GLfloat));
    glVertexArrayElementBuffer(VAO, EBO);

    double beginTime = glfwGetTime();
    double endTime;

    while (!glfwWindowShouldClose(m_Window)) {
        glfwPollEvents();

        userInput();

        if (m_HasToRender) {
            compute.use();
            compute.setUniform1f("xa", m_ZoomX - m_ZoomXAmp);
            compute.setUniform1f("xb", m_ZoomX + m_ZoomXAmp);
            compute.setUniform1f("ya", m_ZoomY - m_ZoomYAmp);
            compute.setUniform1f("yb", m_ZoomY + m_ZoomYAmp);
            glDispatchCompute(m_Width, m_Height, 1);
            glMemoryBarrier(GL_ALL_BARRIER_BITS);
            m_HasToRender = false;
        }

        glBindTextureUnit(0, screenTex);
        display.use();
        display.setUniform1i("screen", 0);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(m_Window);
        endTime = glfwGetTime();
        m_dt = endTime - beginTime;
        beginTime = endTime;
        glfwSetWindowTitle(m_Window, std::to_string(1.0f / m_dt).c_str());
    }
}