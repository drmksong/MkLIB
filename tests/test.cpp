// #define BOOST_TEST_MODULE your_test_module
// #include <boost/test/included/unit_test.hpp>

#include <stdio.h>
#include <iostream>
#include <vector>
#include <boost/make_shared.hpp>
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
    boost::shared_ptr<MkPoint[]> p = boost::make_shared<MkPoint[]>(20);
    MkPoints pnts2(20,p);
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

void point_tst2()
{
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
}

void arr_test_move_op()
{

    MkArray<int> a;
    MkArray<int> b(5, 10);
    MkArray<int> c, d(5,10);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            b(i, j) = i + j;
        }
    }

    printf("before:: a %ld, %ld, 0x%p\n", a.getSzX(), a.getSzY(), (void *) &a.F);
    printf("before:: b %ld, %ld, 0x%p\n", b.getSzX(), b.getSzY(), (void *) &b.F);
    a = std::move(b);

    if (a == b)
    {
        printf("a == b \n");
    }
    else
    {
        printf("a != b \n");
    }
    
    // a = (b);
    printf("after:: a %ld, %ld, 0x%p\n", a.getSzX(), a.getSzY(), (void *) &a.F);
    printf("after:: b %ld, %ld, 0x%p\n", b.getSzX(), b.getSzY(), (void *) &b.F);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("b(%d,%d) = %d ", i, j, b(i, j));
        }
        printf("\n");
    }

    c = a - b;

    b(1, 1) = 10;
    b(2, 2) = 20;

    d += 5;
    d *= 2;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("d(%d,%d) = %d ", i, j, d(i, j));
        }
        printf("\n");
    }

    if (a == b)
    {
        printf("a == b \n");
    }
    else
    {
        printf("a != b \n");
    }
}

void shared_test()
{

    boost::shared_ptr<MkPoint[]> pnts;
    pnts = boost::make_shared<MkPoint[]>(100);

    for (int i=0;i<100;i++) {
        pnts[i] = MkPoint(i,i,i);
    }

    MkPoints pts(100,pnts);
        
    for (int i=0; i<100; i++) {
        printf("i:%d, %f, %f, %f \n",i, pts[i].X, pts[i].Y, pts[i].Z);
    }

    // pnts.reset();
}

int main()
{
    for (int i=0; i<10; i++) {
        printf("0> i:%d\n",i);
    }

    shared_test();

    // point_test();
    // array_test();

    // arr_test_move_op();
    
    return 0;
}