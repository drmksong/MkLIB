#include "glLib.hpp"

glLib::glLib() {
    window = NULL;
    shader = NULL;
}

glLib::~glLib() {
    if (window != NULL) {
        glfwDestroyWindow(window);
        window = NULL;
    }
    if (shader != NULL) {
        delete shader;
        shader = NULL;
    }
    glfwTerminate();
}

void glLib::init() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // new OpenGL
    window = glfwCreateWindow(1024, 768, "Learn OpenGL", NULL, NULL);
    if (window == NULL) {
        throw std::runtime_error("Failed to open GLFW window");
    }

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    glfwMakeContextCurrent(window); // initialize GLEW
    glewExperimental = GL_TRUE; // needed in core profile
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    glViewport(0, 0, screenWidth, screenHeight);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // dark blue background, not working??? obsolete to be removed

    
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO); // generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind buffer to GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW); // copy vertices to buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0); // 1st attribute buffer: vertices
    glEnableVertexAttribArray(0);


// shader = std::make_shared<Shader>("vertex.shader", "fragment.shader");
    shader = new Shader("./vertex.shader", "./fragment.shader");
    shader->use();
    
}

void glLib::loop() {
    do {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}

void glLib::terminate() {
    if (window != NULL) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void glLib::display() {
    glClearColor(1.0f, 0.0f, 0.4f, 1.0f); // dark blue background, not working??? obsolete to be removed
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);

}

