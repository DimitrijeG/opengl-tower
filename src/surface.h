#pragma once


class Surface
{
public:
    Surface(const char* texturePath) {
        mesh.Init(vertices, 48, 6, true);
        textureId = loadTexture(texturePath); // Assumes you have this function
        model = glm::mat4(1.0f);
    }

    ~Surface() {
        glDeleteTextures(1, &textureId);
    }

    void Render(Shader& shader) {
        shader.SetBool("useTexture", true);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        shader.SetMatrix4fv("uM", model);

        mesh.Render();
    }
private:
    Mesh mesh;
    GLuint textureId;
    glm::mat4 model;

    static float vertices[];
};

float Surface::vertices[] = {
    // positions           // normals         // texture Coords
    -20.0f, 0.0f,  20.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
     20.0f, 0.0f,  20.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f,
     20.0f, 0.0f, -20.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,

    -20.0f, 0.0f,  20.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
     20.0f, 0.0f, -20.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
    -20.0f, 0.0f, -20.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f
};