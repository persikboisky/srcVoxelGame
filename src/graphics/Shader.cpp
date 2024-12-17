/*
 * Shader.cpp
 *
 * Created on Nov 24, 2024
 *         Author: persikboisky
 */

#include "Shader.hpp"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

unsigned int shader::id;

static std::string readFile(const char* filename)
{
    std::string text = "";
    std::ifstream file(filename, std::ios::in); // ��������� ���� �� ������
    // ���� ���� �������� � ������� ������
    if (file.is_open())
    {
        std::stringstream sstr; // ����� ��� ������
        sstr << file.rdbuf();   // ��������� ����
        text = sstr.str();      // ����������� ����� � ������
        file.close();           // ��������� ����
    }
    else
    {
        std::cerr << "Failed read file: " << filename << std::endl;
    }

    file.close();

    return text;
}

GLuint LoadShaders(const char* vertex_file, const char* fragment_file)
{
    // �������� ������������ ���������� � ������������ ��������
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // ���������� ��� ��������� ����������
    GLint result = GL_FALSE;
    int infoLogLength;

    // ��������� ����� ���������� �������
    std::string code = readFile(vertex_file);
    const char* pointer = code.c_str(); // �������������� � ��������� �� const char, ��� ��� ������� ��������� ������ ��-�����

    // ���������� ���� ���������� �������
    glShaderSource(vertexShaderID, 1, &pointer, NULL);
    glCompileShader(vertexShaderID);

    // �������� ���������� ����������
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        char* errorMessage = new char[infoLogLength + 1];
        glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, errorMessage);
        std::cerr << errorMessage;
        delete[] errorMessage;
    }
    else
    {
        std::cout << "OK compile shader: " << vertex_file << std::endl;
    }

    // ��������� ����� ������������ �������
    code = readFile(fragment_file);
    pointer = code.c_str(); // �������������� � ��������� �� const char, ��� ��� ������� ��������� ������ ��-�����

    // ���������� ���� ������������ �������
    glShaderSource(fragmentShaderID, 1, &pointer, NULL);
    glCompileShader(fragmentShaderID);

    // �������� ���������� ����������
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        char* errorMessage = new char[infoLogLength + 1];
        glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, errorMessage);
        std::cout << errorMessage;
        delete[] errorMessage;
    }
    else
    {
        std::cout << "OK compile shader: " << fragment_file << std::endl;
    }

    // �������� ���������������� ��������
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    // �������� ���������
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        char* errorMessage = new char[infoLogLength + 1];
        glGetProgramInfoLog(programID, infoLogLength, NULL, errorMessage);
        std::cout << errorMessage;
        delete[] errorMessage;
    }

    // ������������ ������������ ��������
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}

void shader::select(unsigned int id)
{
    shader::id = id;
}

unsigned int shader::getShaderProgram(const char* frag, const char* vert)
{
    return LoadShaders(vert, frag);
}

void shader::use()
{
    glUseProgram(id);
}

void shader::Delete(unsigned int id)
{
    glDeleteProgram(id);
}

void shader::setValueUniform(const float value, const char* name)
{
    GLint locate = glGetUniformLocation(id, name);
    if (locate >= 0)
    {
        glUniform1f(locate, GLfloat(value));
    }
    else
    {
        std::cerr << "Failed locate Uniform: " << name << std::endl;
    }
}

void shader::setValueUniform(glm::mat4 matrix, const char* name)
{
    GLint locate = glGetUniformLocation(id, name);
    if (locate >= 0)
    {
        glUniformMatrix4fv(locate, 1, GL_FALSE, glm::value_ptr(matrix));
    }
    else
    {
        std::cerr << "Failed locate Uniform: " << name << std::endl;
    }
}