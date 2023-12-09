#ifndef __SHADER_HPP__
#define __SHADER_HPP__

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

class Shader {
    public:
        // constructor reads and builds the shader
        Shader(const char* vertex_file_path, const char* fragment_file_path);
        // destructor
        ~Shader();

        // use/activate the shader
        void use();

        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        
        GLuint getProgramID();
    private:
        GLuint programID;
};



#endif