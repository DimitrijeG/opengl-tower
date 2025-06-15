#define _CRT_SECURE_NO_WARNINGS

#include "src/glew.h"

#include "src/shader.h"
#include "src/mesh.h"
#include "src/camera.h"
#include "src/projection.h"
#include "src/surface.h"
#include "src/towerBlock.h"
#include "src/text.h"


const int MAX_TOWER_LAYERS = 6;


double scroll_y_offset = 0.0;
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    scroll_y_offset = yoffset;
}

void processInput(GLFWwindow* window, std::vector<TowerBlock>& towerBlocks, Camera& camera,
    std::array<std::unique_ptr<Projection>, 2>& projections, bool& isPerspective, float deltaTime);


int main(void)
{
    srand(time(0));

    // -- GLFW & GLEW Initialization --
    if (!glfwInit()) return 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    const int wWidth = mode->width, wHeight = mode->height;

    GLFWwindow* window = glfwCreateWindow(wWidth, wHeight, "Lego Tower", monitor, NULL);
    if (!window) { glfwTerminate(); return 2; }
    glfwMakeContextCurrent(window);
    glfwSetScrollCallback(window, scroll_callback);

    if (glewInit() != GLEW_OK) return 3;

    // -- OpenGL Configuration --
    glViewport(0, 0, wWidth, wHeight);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // -- Resource and Object Initialization --
     TextRenderer text(wWidth, wHeight);
    text.Load("res/font/Kanit-Bold.ttf", 52);
    
    Shader shader("res/shader/basic.vert", "res/shader/basic.frag");

    TowerBlock::Init();
    std::vector<TowerBlock> towerBlocks;

    Surface ground("res/texture/surface.jpg");
    Camera camera(0.0f, 10.0f, 5.0f);

    bool isPerspective = true;

    std::array<std::unique_ptr<Projection>, 2> projections;
    projections[0] = std::make_unique<OrthographicProjection>(wWidth, wHeight);
    projections[1] = std::make_unique<PerspectiveProjection>(wWidth, wHeight);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    glm::vec3 lightPos(5.0f, 20.0f, 10.0f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f); // Pure white light

    // -- Render Loop --
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, towerBlocks, camera, projections, isPerspective, deltaTime);
        camera.Update(deltaTime);

        glClearColor(0.5f, 0.7f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // --- Render 3D Scene ---
        glEnable(GL_DEPTH_TEST);
        shader.Use();

        shader.SetVector3fv("uLightPos", lightPos);
        shader.SetVector3fv("uLightColor", lightColor);
        shader.SetVector3fv("uViewPos", camera.GetPosition());

        shader.SetMatrix4fv("uP", projections[isPerspective]->GetMatrix());
        shader.SetMatrix4fv("uV", camera.GetViewMatrix());

        ground.Render(shader);
        for (const auto& block : towerBlocks)
        {
            block.Render(shader);
        }

        // --- Render HUD ---
        glDisable(GL_DEPTH_TEST);
        glm::vec3 color = towerBlocks.size() == MAX_TOWER_LAYERS ? glm::vec3(1.0f, 0.0f, 0.0f) : glm::vec3(1.0f, 1.0f, 1.0f);
        std::string block_count_text = "Blocks: " + std::to_string(towerBlocks.size());
        text.Render(block_count_text, 40.0f, 20.0f, 0.6f, color);
        text.Render("Dimitrije Gasic SV31/2021", 40.0f, wHeight - 70.0f, 1.0f, glm::vec3(1.0f));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // -- Cleanup --
    TowerBlock::Clear();
    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow* window, std::vector<TowerBlock>& towerBlocks, Camera& camera,
    std::array<std::unique_ptr<Projection>, 2>& projections, bool& isPerspective, float deltaTime)
{
    static bool w_pressed = false, s_pressed = false;
    static bool p_pressed = false;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // --- Projection toggle ---
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !p_pressed)
    {
        isPerspective = !isPerspective;
        p_pressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE) p_pressed = false;

    // --- Camera rotation inertia ---
    float rotationSpeed = 3.0f;
    float targetSpeed = 0.0f;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        targetSpeed -= rotationSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        targetSpeed += rotationSpeed;
    camera.SetRotationVelocity(targetSpeed);

    // --- Zoom ---
    if (scroll_y_offset != 0.0)
    {
        float zoomSensitivity = 1.5f;
        projections[isPerspective]->Zoom(scroll_y_offset * zoomSensitivity);
        scroll_y_offset = 0.0;
    }

    // Add a block
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && !w_pressed) {
        if (towerBlocks.size() < MAX_TOWER_LAYERS) {
            float last_y = 0.0f;
            float last_scale_y = 0.0f;

            if (!towerBlocks.empty()) {
                last_y = towerBlocks.back().getPosition().y;
                last_scale_y = towerBlocks.back().getScale().y;
            }

            glm::vec4 newColor((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, 1.0f);
            glm::vec3 newScale(1.8f, 0.5f, 1.2f);
            float new_y_pos = last_y + (last_scale_y / 2.0f) + (newScale.y / 2.0f);
            glm::vec3 newPosition(0.0f, new_y_pos, 0.0f);

            towerBlocks.emplace_back(newPosition, newScale, newColor);
        }
        w_pressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) w_pressed = false;

    // Remove a block
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && !s_pressed) {
        if (!towerBlocks.empty()) towerBlocks.pop_back();
        s_pressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) s_pressed = false;
}