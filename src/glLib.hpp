#ifndef __GLLIB_HPP__
#define __GLLIB_HPP__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
//GLEW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#endif

#include "Shader.hpp"

class glLib {
    public:
        glLib();
        ~glLib();
        void init();
        void display();
        void loop();
        void terminate();
    private:
        GLFWwindow* window;
        // std::shared_ptr<Shader> shader;
        Shader* shader;
        float vert[9] = {
            -0.5f, -0.5f, 0.0f, // left
             0.5f, -0.5f, 0.0f, // right
             0.0f,  0.5f, 0.0f  // top
        };

};




#endif