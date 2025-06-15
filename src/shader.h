#pragma once

#include "glew.h"

class Shader
{
public:
    GLuint shaderId;

    Shader(const char* vertexLocation, const char* fragmentLocation) { shaderId = createShader(vertexLocation, fragmentLocation); }

    void Use() { glUseProgram(shaderId); }
    void SetMatrix4fv(const GLchar* name, const glm::mat4& matrix) { glUniformMatrix4fv(glGetUniformLocation(shaderId, name), 1, GL_FALSE, glm::value_ptr(matrix)); }
    void SetVector3fv(const GLchar* name, const glm::vec3& value) { glUniform3fv(glGetUniformLocation(shaderId, name), 1, glm::value_ptr(value)); }
    void SetVector4fv(const GLchar* name, const glm::vec4& value) { glUniform4fv(glGetUniformLocation(shaderId, name), 1, glm::value_ptr(value)); }
    void SetInteger(const GLchar* name, GLint value) { glUniform1i(glGetUniformLocation(shaderId, name), value); }
    void SetBool(const GLchar* name, GLboolean value) { glUniform1i(glGetUniformLocation(shaderId, name), value); }
	void SetFloat(const GLchar* name, GLfloat value) { glUniform1f(glGetUniformLocation(shaderId, name), value); }
    void Clear() { glDeleteProgram(shaderId); shaderId = 0; }

    ~Shader() { Clear(); }

private:
    unsigned int compileShader(GLenum type, const char* source) {
        std::string content = "";
        std::ifstream file(source);
        if (!file.is_open()) { std::cout << "Error reading shader file: " << source << std::endl; return 0; }
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();
        std::string temp = ss.str();
        const char* sourceCode = temp.c_str();
        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &sourceCode, NULL);
        glCompileShader(shader);
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "Shader compilation error in " << source << ":\n" << infoLog << std::endl;
        }
        return shader;
    }

    unsigned int createShader(const char* vsSource, const char* fsSource) {
        unsigned int program = glCreateProgram();
        unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vsSource);
        unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fsSource);
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return program;
    }
};