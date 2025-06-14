#pragma once

class Mesh
{
public:
    Mesh()
    {
        VAO = 0;
        VBO = 0;
        vertexCount = 0;
    }

    void Init(const float* vertices, unsigned int numOfValues, unsigned int vertexSize, bool hasTexCoords)
    {
        vertexCount = vertexSize;

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numOfValues, vertices, GL_STATIC_DRAW);

        unsigned int stride = hasTexCoords ? 5 * sizeof(float) : 3 * sizeof(float);

        // Vertex Positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(0);

        if (hasTexCoords)
        {
            // Texture Coordinates
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Render()
    {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        glBindVertexArray(0);
    }

    void Clear()
    {
        if (VBO != 0)
        {
            glDeleteBuffers(1, &VBO);
            VBO = 0;
        }
        if (VAO != 0)
        {
            glDeleteVertexArrays(1, &VAO);
            VAO = 0;
        }
        vertexCount = 0;
    }

    ~Mesh()
    {
        Clear();
    }

private:
    GLuint VAO, VBO;
    GLsizei vertexCount;
};