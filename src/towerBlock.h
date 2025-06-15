#pragma once

// (Include your Shader, Mesh, glm headers etc.)

class TowerBlock
{
public:
    // CHANGED: The size of the vertices array is now 216 (36 vertices * 6 floats)
    static void Init() { mesh.Init(vertices, 216, 36, false); }
    static void Clear() { mesh.Clear(); }

    TowerBlock(const glm::vec3& pos, const glm::vec3& scale, const glm::vec4& color)
        : pos(pos), scale(scale), color(color)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        model = glm::scale(model, scale);
    }

    void Render(Shader& shader) const {
        shader.SetBool("useTexture", false);
        shader.SetMatrix4fv("uM", model);
        // CHANGED: Your shader likely expects a vec3 for color now.
        // We send the .rgb part of the vec4.
        shader.SetVector3fv("uObjectColor", glm::vec3(color));
        // You can also keep it as uColor and use .rgb in the shader if you prefer.

        mesh.Render();
    }

    glm::vec3 getPosition() const { return pos; }
    glm::vec3 getScale() const { return scale; }
    // NEW: A convenient way to get the object's raw color
    glm::vec3 GetColor() const { return glm::vec3(color); }

private:
    glm::vec3 pos;
    glm::vec3 scale;
    glm::vec4 color;
    glm::mat4 model;

    static Mesh mesh;
    static float vertices[];
};

Mesh TowerBlock::mesh;
// CHANGED: Vertex array now includes normals
float TowerBlock::vertices[] = {
    // positions          // normals
    // Back face (-Z) - normal (0, 0, -1)
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     // Front face (+Z) - normal (0, 0, 1)
     -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     // Left face (-X) - normal (-1, 0, 0)
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     // Right face (+X) - normal (1, 0, 0)
      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      // Top face (+Y) - normal (0, 1, 0)
       0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
       0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
       // Bottom face (-Y) - normal (0, -1, 0)
       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f
};