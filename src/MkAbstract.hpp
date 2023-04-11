#ifndef __MK_ABSTRACT_H__
#define __MK_ABSTRACT_H__

#include <string>
class MkAbstract {
public:
    // class Alloc
    // {
    // public:
    //     std::string What;
    //     Alloc(std::string what) : What(what) {}
    //     const char *what() { return What.c_str(); }
    // };
    // class Size
    // {
    // public:
    //     std::string What;
    //     int X, Y, Z;
    //     Size(std::string what, int x, int y, int z) : What(what), X(x), Y(y), Z(z) {}
    //     Size(std::string what, int x, int y) : What(what), X(x), Y(y), Z(1) {}
    //     Size(std::string what, int x) : What(what), X(x), Y(1), Z(1) {}
    //     const char *what() { return What.c_str(); }
    // };
    // class Range
    // {
    // public:
    //     std::string What;
    //     int N;
    //     Range(std::string what, int n) : What(what), N(n) {}
    //     const char *what() { return What.c_str(); }
    // };

    class Alloc
    {
    public:
        std::string What;
        Alloc(std::string what) : What(what) {}
        std::string what() { return What; }
    };
    class Size
    {
    public:
        std::string What;
        int X, Y, Z;
        Size(std::string what, int x, int y, int z) : What(what), X(x), Y(y), Z(z) {}
        Size(std::string what, int x, int y) : What(what), X(x), Y(y), Z(1) {}
        Size(std::string what, int x) : What(what), X(x), Y(1), Z(1) {}
        std::string what() { return What; }
    };
    class Range
    {
    public:
        std::string What;
        int N;
        Range(std::string what, int n) : What(what), N(n) {}
        std::string what() { return What; }
    };    
};  

#endif