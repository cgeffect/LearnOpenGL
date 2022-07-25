#include"Base.h"
#include"Shader.h"
#include"ffImage.h"
#include"Camera.h"

uint VAO_cube = 0;
uint VAO_sun = 0;
glm::vec3 light_pos(1.0f);
glm::vec3 light_color(1.0f);


ffImage*    _pImage = NULL;

Shader          _shader_cube;
Shader          _shader_sun;
Shader          _shader_dir;
Shader          _shader_point;
Shader          _shader_spot;

//光照贴图
uint            _textureBox = 0;
uint            _textureSpec = 0;


Camera          _camera;

glm::mat4 _projMatrix(1.0f);
int       _width = 800;
int       _height = 600;

void rend()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };



    _camera.update();
    _projMatrix = glm::perspective(glm::radians(45.0f), (float)_width / (float)_height, 0.1f, 100.0f);
    glm::mat4 _modelMatrix(1.0f);
    _modelMatrix = glm::translate(_modelMatrix, glm::vec3(0.0f, 0.0f, -3.0f));

    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureBox);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _textureSpec);


    _shader_spot.start();
    _shader_spot.setVec3("view_pos", _camera.getPosition());
    
    //传入光照属性
    _shader_spot.setVec3("myLight.m_ambient" , light_color * glm::vec3(0.1f));
    _shader_spot.setVec3("myLight.m_diffuse", light_color * glm::vec3(0.9f));
    _shader_spot.setVec3("myLight.m_specular", light_color * glm::vec3(0.9f));

    _shader_spot.setVec3("myLight.m_pos", _camera.getPosition());
    _shader_spot.setVec3("myLight.m_direction", _camera.getDirection());
    _shader_spot.setFloat("myLight.m_cutOff", glm::cos(glm::radians(12.5f)));
    _shader_spot.setFloat("myLight.m_outCutOff", glm::cos(glm::radians(20.5f)));

    _shader_spot.setFloat("myLight.m_c", 1.0f);
    _shader_spot.setFloat("myLight.m_l", 0.07f);
    _shader_spot.setFloat("myLight.m_q", 0.017f);
 

    //传入物体材质属性
    _shader_spot.setInt("myMaterial.m_specular", 1);
    _shader_spot.setFloat("myMaterial.m_shiness" , 32);
  
    _shader_spot.setMatrix("_viewMatrix", _camera.getMatrix());
    _shader_spot.setMatrix("_projMatrix", _projMatrix);

    for (int i = 0; i < 10; i++)
    {
        _modelMatrix = glm::mat4(1.0f);
        _modelMatrix = glm::translate(_modelMatrix, cubePositions[i]);
        _modelMatrix = glm::rotate(_modelMatrix, glm::radians(i * 20.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        _shader_spot.setMatrix("_modelMatrix", _modelMatrix);
        glBindVertexArray(VAO_cube);
        glDrawArrays(GL_TRIANGLES, 0, 36);

    }
        
    _shader_spot.end();



   _shader_sun.start();
   _shader_sun.setMatrix("_modelMatrix", _modelMatrix);
   _shader_sun.setMatrix("_viewMatrix", _camera.getMatrix());
   _shader_sun.setMatrix("_projMatrix", _projMatrix);

   _modelMatrix = glm::mat4(1.0f);
   _modelMatrix = glm::translate(_modelMatrix, light_pos);
   _shader_sun.setMatrix("_modelMatrix", _modelMatrix);
   glBindVertexArray(VAO_sun);
   glDrawArrays(GL_TRIANGLES, 0, 36);
   _shader_sun.end();
}

uint createModel()
{
    uint _VAO = 0;
    uint _VBO = 0;

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,           0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,           0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,           0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,           0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,           0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,           0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,           0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,           0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,           0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,           0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,           0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,           0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,           -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,           -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,           -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,           -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,           -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,           -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,           1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,           1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,           1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,           1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,           1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,           1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,           0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,           0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,           0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,           0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,           0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,           0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,           0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,           0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,           0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,           0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,           0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,           0.0f,  1.0f,  0.0f,
    };


    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 5));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return _VAO;
}

uint createTexture(const char* _fileName)
{
    _pImage = ffImage::readFromFile(_fileName);
    uint _texture = 0;
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _pImage->getWidth(), _pImage->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _pImage->getData());
    
    return _texture;
}
    
void initShader(const char* _vertexPath, const char* _fragPath)
{
    _shader_cube.initShader(_vertexPath, _fragPath);
    _shader_sun.initShader("/Users/jason/Desktop/LearnOpenGL/09光源种类分类/OpenGL/shader/vsunShader.glsl", "/Users/jason/Desktop/LearnOpenGL/09光源种类分类/OpenGL/shader/fsunShader.glsl");
    _shader_dir.initShader("/Users/jason/Desktop/LearnOpenGL/09光源种类分类/OpenGL/shader/dirShaderv.glsl", "/Users/jason/Desktop/LearnOpenGL/09光源种类分类/OpenGL/shader/dirShaderf.glsl");
    _shader_point.initShader("/Users/jason/Desktop/LearnOpenGL/09光源种类分类/OpenGL/shader/pointShaderv.glsl", "/Users/jason/Desktop/LearnOpenGL/09光源种类分类/OpenGL/shader/pointShaderf.glsl");
    _shader_spot.initShader("/Users/jason/Desktop/LearnOpenGL/09光源种类分类/OpenGL/shader/spotShaderv.glsl", "/Users/jason/Desktop/LearnOpenGL/09光源种类分类/OpenGL/shader/spotShaderf.glsl");
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        _camera.move(CAMERA_MOVE::MOVE_FRONT);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        _camera.move(CAMERA_MOVE::MOVE_BACK);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        _camera.move(CAMERA_MOVE::MOVE_LEFT);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        _camera.move(CAMERA_MOVE::MOVE_RIGHT);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    _camera.onMouseMove(xpos, ypos);
}


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

    glViewport(0, 0, _width, _height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);



    _camera.lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    _camera.setSpeed(0.1f);

    VAO_cube = createModel();
    VAO_sun = createModel();
    light_pos = glm::vec3(2.0f, 0.0f, 0.0f);
    light_color = glm::vec3(1.0f, 1.0f, 1.0f);

    _textureBox = createTexture("/Users/jason/Desktop/LearnOpenGL/res/box.png");
    _textureSpec = createTexture("/Users/jason/Desktop/LearnOpenGL/res/specular.png");
    initShader("/Users/jason/Desktop/LearnOpenGL/09光源种类分类/OpenGL/shader/vertexShader.glsl", "/Users/jason/Desktop/LearnOpenGL/09光源种类分类/OpenGL/shader/fragmentShader.glsl");

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        rend();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
