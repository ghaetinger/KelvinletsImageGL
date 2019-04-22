#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include "../include/KelvinletsObject.h"
#include "../include/glImageAbstraction.h"

using namespace std;

// double initX, initY;
// double nextPosX, nextPosY;
// bool button_down = false, save_checkpoint = false;
// GLfloat * vertices;
// Image * img;

void checkArgumentConsistency(int argc)
{
    if (argc != 4)
    {
        cout << "INPUT FORMAT :"
        " ./kelvin [image filepath] [poisson ratio] [elastic shear modulus]"
        << endl;
        exit(1);
    }
}

// CImg<unsigned char> loadImage(const char* filepath)
// {
//     CImg<unsigned char> image(filepath);
//     if (access( filepath, F_OK ) == -1)
//     {
//         cout << "FILE NOT FOUND!" << endl;
//         exit(2);
//     }
//     return image;
// }



vec2 getPos(GLfloat * v, int w, int x, int y)
{
  int index = 2 * (x + y * w);
  return vec2(v[index], v[index + 1]);
}

// GLFWwindow* initContextAndLibraries(int width,
//                                     int height,
//                                     const char* programName)
// {
//     if (!glfwInit()) exit(3);
//     GLFWwindow* window;
//     window = glfwCreateWindow(width, height, programName, NULL, NULL);
//     glfwSetWindowSizeLimits(window, width, height, width, height);

//     if (!window)
//     {
//         glfwTerminate();
//         exit(4);
//     }
//     glfwMakeContextCurrent(window);
//     if (glewInit() != GLEW_OK)
//     {
//         cout << "ERROR LOADING GLEW!" << endl;
//         exit(5);
//     }
//     return window;
// }

// static void mouse_callback(GLFWwindow* window, int button, int action, int mods)
// {
//   if (button == GLFW_MOUSE_BUTTON_LEFT) {
//     if(GLFW_PRESS == action)
//       {
//         button_down = true;
//         glfwGetCursorPos(window, &initX, &initY);
//         cout << initX << " " << initY << endl;
//         vec2 initPos = getPos(vertices, img->width, initX, initY);
//         initX = (initPos[0] + 1)*img->width/2;
//         initY = (initPos[1] + 1)*img->height/2;
//         nextPosX = initX;
//         nextPosY = initY;
//       }
//     else if(GLFW_RELEASE == action)
//       {
//         button_down = false;
//         save_checkpoint = true;
//       }
//   }
// }

// static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
// {
//   if(button_down)
//   {
//     if(xpos > img->width || xpos < 0 || ypos > img->height || ypos < 0)
//       {
//         nextPosX = initX;
//         nextPosY = initY;
//       }else{
//         glfwGetCursorPos(window, &nextPosX, &nextPosY);
//         vec2 next = getPos(vertices, img->width, nextPosX, nextPosY);
//         nextPosX = (next[0] + 1)*img->width/2;
//         nextPosY = (next[1] + 1)*img->height/2;
//     }
//   }
// }

int main(int argc, char* argv[])
{
    checkArgumentConsistency(argc);

    RenderableImage renderableImage(argv[1]);
    string vertex = "./shaders/vertexShader.glsl";
    string fragment = "./shaders/fragmentShader.glsl";
    GLFWwindow * window = init(renderableImage, vertex, fragment, "Kelvinlets");
    int width = renderableImage.getWidth();
    int height = renderableImage.getHeight();
    KelvinletsObject kelvin (width, height, atof(argv[2]), atof(argv[3]));


    // GLFWwindow* window;
    // window = initContextAndLibraries(img->width, img->height, "Kelvinlets");
    // glfwSetMouseButtonCallback(window, mouse_callback);
    // glfwSetCursorPosCallback(window, cursorPosCallback);

    // vertices = img->getVertices();
    // GLuint * indices = img->getIndices();
    // GLfloat * colors = img->getColors();

    // GLuint vertexBuffer;
    // glGenBuffers(1, &vertexBuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // glBufferData(GL_ARRAY_BUFFER,
    //              renderableImage.getNumOfVertices() * 2 * sizeof(GLfloat),
    //              renderableImage.getVertices(), GL_DYNAMIC_DRAW);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);


    // GLuint indexBuffer;
    // glGenBuffers(1, &indexBuffer);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER,
    //              renderableImage.getNumOfIndices() * sizeof(GLuint),
    //              renderableImage.getIndices(), GL_STATIC_DRAW);

    // GLuint colorBuffer;
    // glGenBuffers(1, &colorBuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    // glBufferData(GL_ARRAY_BUFFER,
    //              renderableImage.getNumOfVertices() * 3 * sizeof(GLuint),
    //              renderableImage.getColors(), GL_DYNAMIC_DRAW);
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);


    // string vs = ParseShader("./shaders/vertexShader.glsl");
    // string fs = ParseShader("./shaders/fragmentShader.glsl");

    // unsigned int shader = CreateShader(vs, fs);
    // glUseProgram(shader);

    GLfloat * test = (GLfloat *)malloc(512 * 512 * 2 * sizeof(GLfloat));
    test = renderableImage.getVertices();
    kelvin.grab(vec2(200, 200), vec2(0, 0), 50.0, renderableImage.getVertices(), test);
    int i = 0;
    while (!glfwWindowShouldClose(window))
    {
      i++;
      //kelvin.grab(vec2(200, 200), vec2(i/100, 0), 50.0, renderableImage.getVertices(), test);    
      glClear(GL_COLOR_BUFFER_BIT);

      // kelvin.grab(vec2(200, 200), vec2(i, 0), 100.0, renderableImage.getVertices(), test);
      //kelvin.grab(vec2(200, 200), vec2(-i/100, 0), 50.0, renderableImage.getVertices(), test);
        // if(button_down)
        //   {
        //     // vec2 initPos = vec2(initX, img->height - 1 - initY);
        //     // vec2 dif = vec2(nextPosX, img->height - 1 - nextPosY) - initPos;

        //     // vec2 initPos = getPos(vertices, img->width, initX, initY);
        //     // initPos[0] = (initPos[0] + 1)*img->width/2;
        //     // initPos[1] = (initPos[1] + 1)*img->height/2;
        //     // vec2 dif = getPos(vertices, img->width, nextPosX, nextPosY);
        //     // dif[0] = (dif[0] + 1)*img->width/2;
        //     // dif[1] = (dif[1] + 1)*img->height/2;
        //     // dif = dif - initPos;
        //     // cout << dif[0] << "   " << dif[1] << endl;

        //     vec2 dif = vec2(nextPosX, nextPosY) - vec2(initX, initY);
        //     kelvin.grab(vec2(initX, initY), dif, 200.0, vertices);

        //   }else if(save_checkpoint)
        //   {
        //     kelvin.setVertices(vertices);
        //     save_checkpoint = false;
        //   }

        // glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        // glBufferSubData(GL_ARRAY_BUFFER, 0, img->getNumOfVertices() * 2 * sizeof(GLfloat), vertices);
        // glEnableVertexAttribArray(0);

        // glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        // glBufferSubData(GL_ARRAY_BUFFER, 0, img->getNumOfVertices() * 3 * sizeof(GLfloat), kelvin.getImage()->getColors());
        // glEnableVertexAttribArray(1);

        reRender(window, renderableImage, test);
        glDrawElements(GL_TRIANGLE_STRIP,
                       renderableImage.getNumOfIndices(),
                       GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();


    exit(0);
}
