#pragma once

// (Include your Shader, Mesh, glm, etc. headers)

class Surface
{
public:
    Surface(const char* texturePath) {
        // CHANGED: The vertex is now 8 floats (3 pos + 3 norm + 2 tex)
        // Total size = 6 vertices * 8 floats = 48
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

// CHANGED: Interleaved normals into the vertex data
float Surface::vertices[] = {
    // positions          // normals           // texture Coords
    -20.0f, 0.0f,  20.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
     20.0f, 0.0f,  20.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f,
     20.0f, 0.0f, -20.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,

    -20.0f, 0.0f,  20.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
     20.0f, 0.0f, -20.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
    -20.0f, 0.0f, -20.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f
};