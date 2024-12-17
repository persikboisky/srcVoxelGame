#include "header.h"

int main()
{
    Window::initializateWindow("openGL", 1280, 720); 
    Window::setWindowIcon("./assets/texture/cubes.png");

    unsigned int shaderID = shader::getShaderProgram("./assets/shaders/main.frag", "./assets/shaders/main.vert");
    unsigned int textureID = texture::loadText("./assets/texture/block.png");

    Event::Init();
    Event::key::init();
    glm::mat4 model(1.0f);

    glClearColor(0.6f, 0.62f, 0.65f, 1);

    cursor::disableCursor(true);

    while (!Event::isCloseWindow())
    {
        Event::update();
        glClear(GL_COLOR_BUFFER_BIT);

        if (Event::key::getKey(GLFW_KEY_ESCAPE)) Window::setShouldClose(true);

        shader::select(shaderID);
        shader::use();
        shader::setValueUniform(model, "model");
        player::update();

        renderVoxel::render(0, 0, -1, 1);

        Window::swapBuffer();
    }

    Window::terminate();
    return 0;
}