#include <Window.hpp>
#include <Utils.hpp>
#include <Texture.hpp>

Window::GlobalDestructor Window::g_globalDestructor;
GLFWwindow *Window::g_window = nullptr;

void Window::create(int width, int height, const char *title)
{
    if (!glfwInit()) {
        throw Utils::RuntimeFailure("Failed to initialize GLFW window");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    Window::g_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (nullptr == Window::g_window) {
        throw Utils::RuntimeFailure("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(Window::g_window);
    glfwSwapInterval(0); // Disable v-sync.

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw Utils::RuntimeFailure("Failed to initialize GLAD");
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(Window::g_window, Window::window_resize_callback);
    Texture::constructGlobalData();
}
bool Window::isOpen()
{
    return !glfwWindowShouldClose(Window::g_window);
}
void Window::close()
{
    glfwSetWindowShouldClose(Window::g_window, true);
}
void Window::updateKeys()
{
    glfwPollEvents();
}
void Window::updateFrame()
{
    glfwSwapBuffers(Window::g_window);
}
void Window::fill(glm::vec3 color)
{
    glClearColor(static_cast<GLfloat>(color.x), static_cast<GLfloat>(color.y), static_cast<GLfloat>(color.z), static_cast<GLfloat>(1.0f));
    glClear(GL_COLOR_BUFFER_BIT);
}
int Window::getFps()
{
    static int count = 0;
    static int fps = 0;
    static double lastTime = 0.0; // Will be always have an integer like value for better results.

    double deltaTime = glfwGetTime() - lastTime;
    if (deltaTime >= 1.0)
    {
        fps = count;
        count = 0;
        lastTime += 1.0;
    }
    count++;

    return fps;
}
int Window::getKey(int key)
{
    return glfwGetKey(Window::g_window, key);
}
bool Window::canProcessLogic()
{
    constexpr double TICK = 1.0 / 60.0; // 60.0 is the simulated fps target.
    static double lastTime = 0.0; // Will be always have an integer like value for better results.

    double deltaTime = glfwGetTime() - lastTime;
    if (deltaTime >= TICK) {
        lastTime += TICK;
        return true;
    }
    
    return false;
}

Window::GlobalDestructor::~GlobalDestructor()
{
    Texture::destructGlobalData();
    if (Window::g_window) {
        glfwDestroyWindow(Window::g_window);
    }
    glfwTerminate();
}
void Window::window_resize_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}