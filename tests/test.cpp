// #define BOOST_TEST_MODULE your_test_module
// #include <boost/test/included/unit_test.hpp>

#include <stdio.h>
#include <iostream>
#include "MkMatrix.hpp"
#include "MkPoint.hpp"

bool point_test()
{
    MkPoints pnts(10);

    try
    {
        for (int i; i < pnts.GetSize() + 1; i++)
            printf("pnts (%f, %f, %f)\n", pnts[i].X, pnts[i].Y, pnts[i].Z);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    puts(" pnts test \n");
    std::vector<MkPoint> p(20);
    MkPoints pnts2(p);
    printf("before %d %d\n", pnts2.GetSize(), pnts2.GetCapacity());
    pnts2.Add(MkPoint(1, 1, 1));
    printf("after %d \n", pnts2.GetSize());
    pnts2[10].X = 2;
    printf("pnts2 (%f, %f, %f)\n", pnts2[10].X, pnts2[10].Y, pnts2[10].Z);
    pnts2.Reserve(10);
    puts("");
    return true;
}

bool array_test()
{
    MkArray<float> a(10, 10);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            a(i, j) = i * j;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d %d %f \n", i, j, a(i, j));
        }
    }

    MkArray<float> b(10, 10);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            b(i, j) = i + j;
        }
    }

    a = b;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d %d %f \n", i, j, a(i, j));
        }
    }

    try
    {
        puts(" *** test message 1");
        MkArray<int> arr(2, 3, 5);
        puts(" *** test message 2");
        arr(1, 1, 1) = 5;
        printf("arr(1,1,1) is %d \n", arr(1, 1, 1));
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    puts(" -------------- arr test \n");
    try
    {
        puts(" *** test message 1");
        MkArray<int> arr1(2, 2, 2);
        puts(" *** test message 2");
        arr1(1, 1, 1) = 5;
        printf("arr1(1,1,1) is %d \n", arr1(1, 1, 1));
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    puts(" arr test 2 --------------------\n");

    return true;
}

// BOOST_AUTO_TEST_CASE(pnt_test_case_01)
// {
//     MkPoint a(1, 1, 1);
//     MkPoint b(1, 1, 1);
//     MkPoint c(2, 1, 1);
//     BOOST_TEST(a == b);
//     BOOST_TEST(a != MkPoint(3, 1, 1));
// }

int main()
{

    // point_test();
    // array_test();

    MkPoint a(1, 1, 1);
    const MkPoint b(1, 1, 1);
    MkPoint c(2, 1, 1);
    double fa, fb, fc;

    assert(MkPoint(1, 1, 1) == MkPoint(1, 1, 1));
    assert(MkPoint(1, 1, 1) == b);
    assert(a != MkPoint(2, 1, 1));
    assert(a != c);
    a.GetAng(fa, fb, fc);
    printf("alpha %f beta %f gamma %f \n", fa, fb, fc);

    assert(fa == 0);
    // printf("a == b? ,1 %s\n", (MkPoint(1, 1, 1) == MkPoint(1, 1, 1)) ? "true" : "false");
    // printf("a == b? ,2 %s\n", (MkPoint(1, 1, 1) == b) ? "true" : "false");
    // printf("a == b? ,3 %s\n", (a != MkPoint(1, 1, 1)) ? "true" : "false");
    // printf("a == b? ,4 %s\n", (a != b) ? "true" : "false");

    return 0;
}