#include<glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
//go to docs.gl for opengl documentary
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

    float positions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };
    //creating buffer on nvram
    unsigned int buffer;
    glGenBuffers(1, &buffer); //create 1 buffer and the id of the generated buffer 
    glBindBuffer(GL_ARRAY_BUFFER, buffer);// what is the purpose of the buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);//put data into the buffer and specifies its usage
    
    //interpreting the bufferData

    //0 is the index cus is the first attribute
    //2 means 2 vertex attribute i.e X,Y in this case when reading the data
    // GL_FLOAT Is the type of data
    // GL_FALSE normalized the data
    // the next is the stride and pointer, amount of byte between each vertex
    // pointer is the offset within the vertex, i.e in other to meet another attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void *)0);
    //we enable the vertex attribute
    glEnableVertexAttribArray(0); //0 is the index u want to enable

                                                                                

/* Loop until the user closes the window  */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        // legacy opengl
      
        glClear(GL_COLOR_BUFFER_BIT);
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

    glfwTerminate();
    return 0;
}