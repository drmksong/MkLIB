// #define BOOST_TEST_MODULE your_test_module
// #include <boost/test/included/unit_test.hpp>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <boost/make_shared.hpp>
#include "MkMatrix.hpp"
#include "MkPoint.hpp"
#include "MkLine.hpp"

// #include "gltest.hpp"
// int gl_main(int argc, char *argv[]);

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

bool read_file(std::string fname,MkLines &lines) {
    bool flag=false;
    std::ifstream ifs;
    float sx,sy,ex,ey;
    ifs.open(fname);
    flag = ifs.is_open();
    if (!flag) {
        std::cout << "file open error: " << fname << "\n";
        return flag;
    }
    else {
        while(!ifs.eof()) {
            ifs >> sx >> sy >> ex >> ey;
            std::cout << sx << ", " << sy << ", " << ex << ", " << ey << "\n";
            MkPoint sp(sx,sy,0),ep(ex,ey,0);
            MkLine line(sp,ep);
            lines.Add(line);
        }
    }

    ifs.close();
    return flag;
}

MkDouble &get_fblr(double theta, MkPoint &pnt, MkLines &lines) 
{

    std::cout << "get_fblr entered \n\n\n\n";
    static MkDouble fblr(4);
    double x = pnt.X;
    double y = pnt.Y;
    double z = pnt.Z;

    MkPoint fp,bp,lp,rp;
    MkPoints fpnts,bpnts,lpnts,rpnts;
    MkPoint fpnt,bpnt,lpnt,rpnt;

    fp.X += 200;
    bp.X -= 200;
    lp.Y += 200;
    rp.Y -= 200;

    fp.RotateInZ(-theta);
    bp.RotateInZ(-theta);
    lp.RotateInZ(-theta);
    rp.RotateInZ(-theta);

    fp += pnt;
    bp += pnt;
    lp += pnt;
    rp += pnt;

    MkLine fl(pnt,fp),bl(pnt,bp),ll(pnt,lp),rl(pnt,rp);
    std::cout << "fl coord:" << fl[0].X << " " << " " << fl[0].Y << " " << fl[1].X << " " << fl[1].Y << std::endl;

    for (int i=0;i<lines.GetSize();i++) {
        MkLine line = lines[i];
        std::cout << "line["<< i <<"] coord:" << line[0].X << " " << " " << line[0].Y << " " << line[1].X << " " << line[1].Y << std::endl;        
        if (fl.IsIntersect(line)) {
            std::cout << "fl intersect before add "<< fpnts.GetSize() << std::endl;
            fpnt = fl.GetIntPoint(line);
            std::cout << "fpnt coord:" << fpnt.X << " " << " " << fpnt.Y << std::endl;        
            fpnts.Add(fpnt);
            std::cout << "fl intersect after  add "<< fpnts.GetSize() << std::endl;

        }
        if (bl.IsIntersect(line)) {
            std::cout << "bl intersect before add "<< bpnts.GetSize() << std::endl;
            bpnt = bl.GetIntPoint(line);
            std::cout << "bpnt coord:" << bpnt.X << " " << " " << bpnt.Y << std::endl;        
            bpnts.Add(bpnt);
            std::cout << "bl intersect after  add "<< bpnts.GetSize() << std::endl;            
            
        }
        if (ll.IsIntersect(line)) {
            std::cout << "ll intersect before add "<< lpnts.GetSize() << std::endl;
            lpnt = ll.GetIntPoint(line);
            std::cout << "lpnt coord:" << lpnt.X << " " << " " << lpnt.Y << std::endl;        
            lpnts.Add(lpnt);
            std::cout << "ll intersect after  add "<< lpnts.GetSize() << std::endl;            

        }
        if (rl.IsIntersect(line)) {
            std::cout << "rl intersect before add "<< rpnts.GetSize() << std::endl;
            rpnt = rl.GetIntPoint(line);
            std::cout << "rpnt coord:" << rpnt.X << " " << " " << rpnt.Y << std::endl;        
            rpnts.Add(rpnt);
            std::cout << "rl intersect after  add "<< rpnts.GetSize() << std::endl;
        }

    }

    double dist = 1000;
    for (int i=0;i<fpnts.GetSize();i++) {
        dist = min(dist,CalDist(pnt,fpnts[i]));
    }
    fblr[0] = dist;

    dist = 1000;
    for (int i=0;i<bpnts.GetSize();i++) {
        dist = min(dist,CalDist(pnt,bpnts[i]));
    }
    fblr[1] = dist;

    dist = 1000;
    for (int i=0;i<lpnts.GetSize();i++) {
        dist = min(dist,CalDist(pnt,lpnts[i]));
    }

    fblr[2] = dist;

    dist = 1000;
    for (int i=0;i<rpnts.GetSize();i++) {
        dist = min(dist,CalDist(pnt,rpnts[i]));
    }
    fblr[3] = dist;

    return fblr;
}

void pnts_tst()
{
    MkPoint apnt(1,1,1);
    MkPoints pnts;

    pnts.Add(apnt);
    printf("%f %f %f\n",pnts[0].X,pnts[0].Y,pnts[0].Z);
}

int main()
{
    // TODO: to incorporate GLFW, GLAD for the testing
    // int argc;
    // char *argv;
    // gl_main(argc, &argv);

    // point_test();
    // array_test();

    // arr_test_move_op();

    // shared_test();
    {
        MkDouble res;
        MkLines lines;
        MkPoint pnt(10,10,0);
        double theta = -43; // counter clockwise
        std::string fname = "../wall_column.dat";
        read_file(fname,lines);
        std::cout << "lines size: " << lines.GetSize() << "\n";
        res = get_fblr(theta, pnt, lines);
        std::cout << "fblr: " << res[0] << ", " << res[1] << ", " << res[2] << ", " << res[3] << "\n";
    }

    // pnts_tst();
    
    return 0;
}
