#pragma once

#include <string>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

// this is dummy class to check MkDouble can be used with std::vector
// do not use this class in real code

class MkObject
{
public:
    int no;
    std::string str;
    // boost::shared_ptr<int[]> parr{NULL};
    MkDouble db;
    // int *parr;

public:
    MkObject(std::string s, int no) : no{no}, str(s)
    {
        // parr = boost::make_shared<int[]>(no);
        // for (int i = 0; i < no; i++)
        //     parr[i] = i;
        db.Initialize(no);
        std::cout << " constructed\n";
    }

    MkObject(const MkObject &o) : no{o.no}, str{o.str} /*, parr{o.parr}*/, db{o.db}
    {
        std::cout << " copy constructed\n";
    }

    MkObject(MkObject &&o) : no{std::move(o.no)}, str(std::move(o.str)), db{std::move(o.db)} { std::cout << " move constructed\n"; }

    MkObject &operator=(const MkObject &other)
    {
        str = other.str;
        no = other.no;
        db = other.db;
        // parr = other.parr;
        std::cout << " copy assigned\n";
        return *this;
    }

    MkObject &operator=(MkObject &&other)
    {
        str = std::move(other.str);
        // parr = std::move(other.parr);
        std::cout << " move assigned\n";
        return *this;
    }
};