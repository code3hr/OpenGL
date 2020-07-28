#include<glew.h> //for modern opengl
#include <GLFW/glfw3.h> //It provides a simple API for creating windows
#include<iostream>
#include <fstream>
#include <string>
#include<sstream>

//go to docs.gl for opengl documentary

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};
static ShaderProgramSource ParseShader(const std::string filepath) {
    std::ifstream stream(filepath);
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    ShaderType type = ShaderType::NONE;
    std::string line;
    std::stringstream ss[2];
    while (getline(stream, line))
    {

        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                //set mode to vertex
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                //set mode to fragment
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
}
static unsigned int CompileShader(unsigned int type, const std::string& source)
{
  unsigned int id =   glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  // Error Handlig
  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE)
  {
      int length;
      glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
      char* message =(char*) _malloca(length*sizeof(char));//allocating mem on the stack dynamically
      glGetShaderInfoLog(id, length, &length, message);
      std::cout << "Failed to compile " <<
          (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
          << "shader !" << std::endl;
      std::cout << message << std::endl;
      glDeleteShader(id);
      return 0;
  }
  return id;
}
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {

  unsigned int program =   glCreateProgram();
  unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs); 

  return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
        std::cout << "error!" << std::endl;;
    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
        -0.5f, -0.5f, //0
        0.5f, -0.5f, //1
        0.5f, 0.5f, //2
        -0.5f, 0.5f //3
      
      
        
        
    };
  //  how to draw a square
    unsigned int indices[] = {
0,1,2,
2,3,0
    };
    //creating buffer on nvram
    unsigned int buffer;
    glGenBuffers(1, &buffer); //create 1 buffer and the id of the generated buffer 
    glBindBuffer(GL_ARRAY_BUFFER, buffer);// what is the purpose of the buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);//put data into the buffer and specifies its usage


    //interpreting the bufferData

    //0 is the index cus is the first attribute
    //2 means 2 vertex attribute i.e X,Y in this case when reading the data
    // GL_FLOAT Is the type of data
    // GL_FALSE normalized the data
    // the next is the stride and pointer, amount of byte between each vertex
    // pointer is the offset within the vertex, i.e in other to meet another attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2,0);
    //we enable the vertex attribute
    glEnableVertexAttribArray(0); //0 is the index u want to enable

    //interpreting the indices to draw a square
    unsigned int ibo;
    glGenBuffers(1, &ibo); //create 1 buffer and the id of the generated buffer 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);// what is the purpose of the buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);//put data into the buffer and specifies its usage

         //writing shaders
  
    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
      unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
      glUseProgram(shader);
/* Loop until the user closes the window  */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        // legacy opengl
      
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES,  6, GL_UNSIGNED_INT,nullptr); //Draw the currently bind buffer
        /*
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f );
        glVertex2f(0.5f, -0.5f);
        // Swap front and back buffers 
        glEnd();
        */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}