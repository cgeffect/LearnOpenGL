#include"Base.h"
#include"Shader.h"
#include"ffImage.h"

unsigned int VBO = 0;

unsigned int VAO = 0;

unsigned int _texture = 0;


ffImage*    _pImage = NULL;

Shader          _shader;

void rend()
{
    glBindTexture(GL_TEXTURE_2D, _texture);
    _shader.start();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    _shader.end();
}

void initModel()
{
    float vertices[] =
    {
        0.5f,  0.5f, 0.0f,    1.0f , 0.0f , 0.0f,   1.0f , 1.0f,
        0.5f, -0.5f, 0.0f,    0.0f , 1.0f , 0.0f,   1.0f , 0.0f,
        -0.5f,  -0.5f, 0.0f,  0.0f , 0.0f , 1.0f,   0.0f , 0.0f,
        -0.5f, 0.5f, 0.0f,    0.0f , 1.0f , 0.0f,   0.0f , 1.0f,
    };

    unsigned int indices[] =
    {
        0 , 1 , 3 ,
        1 , 2 , 3
    };


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int EBO = 0;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float)*3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void initTexture()
{
    _pImage = ffImage::readFromFile("/Users/jason/Desktop/LearnOpenGL/res/rgba.jpg");

    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _pImage->getWidth(), _pImage->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _pImage->getData());
}
    
void initShader(const char* _vertexPath, const char* _fragPath)
{
    _shader.initShader(_vertexPath, _fragPath);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    //初始化GL上下文环境
    glfwInit();
    
    //将OpenGL主版本号(Major)和次版本号(Minor)都设为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    //使用的是核心模式(Core-profile)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //如果是macOS系统，则需要下面这行代码才能让配置起作用
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Core", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    initModel();
    initTexture();
    initShader("/Users/jason/Desktop/LearnOpenGL/02纹理贴图/OpenGL/vertexShader.glsl", "/Users/jason/Desktop/LearnOpenGL/02纹理贴图/OpenGL/fragmentShader.glsl");

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        rend();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
