// #define BOOST_TEST_MODULE your_test_module
// #include <boost/test/included/unit_test.hpp>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <random>
#include <chrono>
#include <boost/make_shared.hpp>
#include "MkMatrix.hpp"
#include "MkPoint.hpp"
#include "MkLine.hpp"
#include "MkRect.hpp"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

// TODO: 
// 1. Add test for drawing routines for the walls and columns 
// 2. Add test for gl key input
// 3. Add test for correct position of the camera
// 4. Add test for candidate positions of the camera
// 5. Add test for compare the correct and candidate positions of the camera
// 6. Add test for ???

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // clear color buffer
    glColor3f(1.0, 0.0, 0.0); // draw in red
    glBegin(GL_POLYGON); // draw a polygon
    glColor3f(1.0, 0.0, 0.0); glVertex3f(0.25, 0.25, 0.0);
    glColor3f(0.0, 1.0, 0.0); glVertex3f(0.75, 0.25, 0.0);
    glColor3f(1.0, 0.0, 0.0); glVertex3f(0.75, 0.75, 0.0);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(0.25, 0.75, 0.0);
    glEnd();
    glFlush(); // flush output to screen
}

int main(int argc,char **argv) // gl test
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500); // window size
    glutInitWindowPosition(0, 0); // window position
    glutCreateWindow("OpenGL Test"); // show window
    glutDisplayFunc(display); // draw callback function
    glutMainLoop(); // enter main loop
    return 0;
}


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

bool read_file(std::string fname,MkLines &lines) 
{
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
            // std::cout << sx << ", " << sy << ", " << ex << ", " << ey << "\n";
            MkPoint sp(sx,sy,0),ep(ex,ey,0);
            MkLine line(sp,ep);
            line.SetFiniteness(true);
            lines.Add(line);
        }
    }

    ifs.close();
    return flag;
}


// TODO: make wall and column version read_file function

bool read_file(std::string fname, MkRect &wall, MkRects &cols) 
{
    // TODO: should implement
    return true;
}

MkDouble &get_fblr(double theta, MkPoint &pnt, MkLines &lines) 
{

    // std::cout << "get_fblr entered \n\n\n\n";
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
    fl.SetFiniteness(true);
    bl.SetFiniteness(true);
    ll.SetFiniteness(true);
    rl.SetFiniteness(true);
    // std::cout << "fl coord:" << fl[0].X << " " << " " << fl[0].Y << " " << fl[1].X << " " << fl[1].Y << std::endl;

    for (int i=0;i<lines.GetSize();i++) {
        MkLine line = lines[i];
        // std::cout << "line["<< i <<"] coord:" << line[0].X << " " << " " << line[0].Y << " " << line[1].X << " " << line[1].Y << std::endl;        
        if (fl.IsIntersect(line)) {
            // std::cout << "fl intersect before add "<< fpnts.GetSize() << std::endl;
            fpnt = fl.GetIntPoint(line);
            // std::cout << "fpnt coord:" << fpnt.X << " " << " " << fpnt.Y << std::endl;        
            fpnts.Add(fpnt);
            // std::cout << "fl intersect after  add "<< fpnts.GetSize() << std::endl;

        }
        if (bl.IsIntersect(line)) {
            // std::cout << "bl intersect before add "<< bpnts.GetSize() << std::endl;
            bpnt = bl.GetIntPoint(line);
            // std::cout << "bpnt coord:" << bpnt.X << " " << " " << bpnt.Y << std::endl;        
            bpnts.Add(bpnt);
            // std::cout << "bl intersect after  add "<< bpnts.GetSize() << std::endl;            
            
        }
        if (ll.IsIntersect(line)) {
            // std::cout << "ll intersect before add "<< lpnts.GetSize() << std::endl;
            lpnt = ll.GetIntPoint(line);
            // std::cout << "lpnt coord:" << lpnt.X << " " << " " << lpnt.Y << std::endl;        
            lpnts.Add(lpnt);
            // std::cout << "ll intersect after  add "<< lpnts.GetSize() << std::endl;            

        }
        if (rl.IsIntersect(line)) {
            // std::cout << "rl intersect before add "<< rpnts.GetSize() << std::endl;
            rpnt = rl.GetIntPoint(line);
            // std::cout << "rpnt coord:" << rpnt.X << " " << " " << rpnt.Y << std::endl;        
            rpnts.Add(rpnt);
            // std::cout << "rl intersect after  add "<< rpnts.GetSize() << std::endl;
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

// This is MkRect version of get_fblr
// 05-05-2023, made this correct, by debugging MkRect GetLine function
// which uses the same static return and probally cause side effects
// MkLine line(this[0],this[1]) <- this is the problem
// sp = this[0]; ep = this[1]; MkLine line(sp,ep) <- this is the solution
MkDouble &get_fblr(double theta, MkPoint &pnt, MkRect &wall, MkRects &cols) 
{

    // std::cout << "get_fblr entered \n\n\n\n";
    static MkDouble fblr(4);
    double x = pnt.X;
    double y = pnt.Y;
    double z = pnt.Z;

    MkPoint fp,bp,lp,rp;
    MkPoints fpnts,bpnts,lpnts,rpnts;
    MkPoint fpnt,bpnt,lpnt,rpnt;

    MkLines lines;

    for (int i=0;i<4;i++) {
        lines.Add(wall.GetLine(i));
    }

    for (int j=0;j<cols.GetSize();j++) {
        MkRect col = cols[j];
        for (int i=0;i<4;i++) {
            lines.Add(col.GetLine(i));
        }
    }

    // printf("\nlines size %d\n\n",lines.GetSize());
    for (int i=0;i<lines.GetSize();i++) {
        lines[i].SetFiniteness(true);
        // std::cout << lines[i][0].X << " " << lines[i][0].Y << " " << lines[i][1].X << " " << lines[i][1].Y << std::endl;
    }

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
    fl.SetFiniteness(true);
    bl.SetFiniteness(true);
    ll.SetFiniteness(true);
    rl.SetFiniteness(true);
    // std::cout << "fl coord:" << fl[0].X << " " << " " << fl[0].Y << " " << fl[1].X << " " << fl[1].Y << std::endl;

    for (int i=0;i<lines.GetSize();i++) {
        MkLine line = lines[i];
        // std::cout << "line["<< i <<"] coord:" << line[0].X << " " << " " << line[0].Y << " " << line[1].X << " " << line[1].Y << std::endl;        
        if (fl.IsIntersect(line)) {
            // std::cout << "fl intersect before add "<< fpnts.GetSize() << std::endl;
            fpnt = fl.GetIntPoint(line);
            // std::cout << "fpnt coord:" << fpnt.X << " " << " " << fpnt.Y << std::endl;        
            fpnts.Add(fpnt);
            // std::cout << "fl intersect after  add "<< fpnts.GetSize() << std::endl;

        }
        if (bl.IsIntersect(line)) {
            // std::cout << "bl intersect before add "<< bpnts.GetSize() << std::endl;
            bpnt = bl.GetIntPoint(line);
            // std::cout << "bpnt coord:" << bpnt.X << " " << " " << bpnt.Y << std::endl;        
            bpnts.Add(bpnt);
            // std::cout << "bl intersect after  add "<< bpnts.GetSize() << std::endl;            
            
        }
        if (ll.IsIntersect(line)) {
            // std::cout << "ll intersect before add "<< lpnts.GetSize() << std::endl;
            lpnt = ll.GetIntPoint(line);
            // std::cout << "lpnt coord:" << lpnt.X << " " << " " << lpnt.Y << std::endl;        
            lpnts.Add(lpnt);
            // std::cout << "ll intersect after  add "<< lpnts.GetSize() << std::endl;            

        }
        if (rl.IsIntersect(line)) {
            // std::cout << "rl intersect before add "<< rpnts.GetSize() << std::endl;
            rpnt = rl.GetIntPoint(line);
            // std::cout << "rpnt coord:" << rpnt.X << " " << " " << rpnt.Y << std::endl;        
            rpnts.Add(rpnt);
            // std::cout << "rl intersect after  add "<< rpnts.GetSize() << std::endl;
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

// simple test for MkPoint add member function
// ridiculous error in the add member function found and corrected. 04/27/2023
void pnts_tst()
{
    MkPoint apnt(1,1,1);
    MkPoints pnts;

    pnts.Add(apnt);
    printf("%f %f %f\n",pnts[0].X,pnts[0].Y,pnts[0].Z);
}

// implementation trial for scanning algorithm with given angle,fr,br,lr,rr
void scan_test(MkLines &lines,double ang, MkDouble &fblr)
{
   
    MkDouble res;
    MkDouble contour(10,10,4);

    for (double fi=0.001;fi<100;fi+=10) {
        for (double fj=0.001;fj<100;fj+=10) {
            MkPoint pnt(fi,fj,0);
            res = get_fblr(ang,pnt,lines);
            contour(int(fi/10),int(fj/10),0) = fabs(res[0]-fblr[0]);
            contour(int(fi/10),int(fj/10),1) = fabs(res[1]-fblr[1]);
            contour(int(fi/10),int(fj/10),2) = fabs(res[2]-fblr[2]);
            contour(int(fi/10),int(fj/10),3) = fabs(res[3]-fblr[3]);
        }
    }

    printf("i:  j:  %f %f %f %f\n",fblr(0),fblr(1),fblr(2),fblr(3));

    for (int i=0;i<contour.getSzX();i++) {
        for (int j=0;j<contour.getSzY();j++) {
            printf("i:%d j:%d \t %5.1f \t %5.1f \t %5.1f \t %5.1f \t %5.1f\n",i*10,j*10,(contour(i,j,0)+contour(i,j,1)+contour(i,j,2)+contour(i,j,3)),contour(i,j,0),contour(i,j,1),contour(i,j,2),contour(i,j,3));
        }
    }
}
// TODO:---------------------------------------------------------------------
// implement random walk algorithm, that is, given a point, find the next point
// where the next point is not in the columns but in the wall
// therefore, those information should be given as input, 
// so that read_file function should be revised accordingly
// ---------------------------------------------------------------------------
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> randis(0,1);
std::uniform_real_distribution<double> ranang(-180,180);

MkPoint & walk(MkPoint &ori, MkRect &wall, MkRects &cols)
{

    static double d_dist=0,d_ang=0;
    static MkPoint nextpnt;

    if (d_dist==0) {
        d_dist = randis(gen);
    }
    if (d_ang==0) {
        d_ang = ranang(gen);
    }

    d_dist += 0.1 * randis(gen);
    d_ang += 0.1 * ranang(gen);    

    printf("%5.2f %5.2f : ",d_dist,d_ang);
    nextpnt = ori + MkPoint(d_dist*cos(d_ang*3.14/180),d_dist*sin(d_ang*3.14/180),0);

    return nextpnt;
}


void setup_wall(MkRect &wall, MkRects &cols);

void rw_test() 
{
    MkRect wall;
    MkRects cols(4);
    MkPoint pnt(50,50,0);
    setup_wall(wall,cols);
    for (int i=0;i<50;i++) {
        pnt = walk(pnt,wall,cols);
        printf("%5.2f %5.2f \n",pnt.X,pnt.Y);
    }
    return;
}

void setup_wall(MkRect &wall, MkRects &cols)
{
    // MkRect wall(MkPoint(0,0));
    wall.SetHeight(100);
    wall.SetWidth(100);
    wall.SetCenter(MkPoint(50,50));
    for (int i=0;i<4;i++) {
        wall.GetLine(i).SetFiniteness(true);
        MkLine line = wall.GetLine(i);
        // std::cout << " wall " << line[0].X << "  " << line[0].Y << "  " << line[1].X << "  " << line[1].Y << std::endl;
    }
    
    // MkRects cols(4);
    cols[0].SetOrigin(MkPoint(20,20)); cols[0].SetCenter(MkPoint(30,30));
    cols[1].SetOrigin(MkPoint(60,20)); cols[1].SetCenter(MkPoint(70,30));
    cols[2].SetOrigin(MkPoint(20,60)); cols[2].SetCenter(MkPoint(30,70));
    cols[3].SetOrigin(MkPoint(60,60)); cols[3].SetCenter(MkPoint(70,70));

    for (int i=0;i<4;i++)   {
        cols[i].SetHeight(20);
        cols[i].SetWidth(20);
    }

    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            cols[i].GetLine(j).SetFiniteness(true);
            MkLine line = cols[i].GetLine(j);
            // std::cout << " cols " << line[0].X << "  " << line[0].Y << "  " << line[1].X << "  " << line[1].Y << std::endl;

        }
    }
}

void fblr_test()
{
    MkRect wall;
    MkRects cols(4);
    setup_wall(wall,cols);
    //TODO: to revise read_file to setup wall and columns from the file
    MkPoints ori;
    MkPoints trace;
    MkDouble res;
    MkLines lines;
    std::string fname = "../wall_column.dat";
    read_file(fname,lines); // -> read_file(fname, wall, cols);


    {
        MkPoint pnt(50,50,0);
        double theta = -43; // counter clockwise
        for (int i=0;i<lines.GetSize();i++) {lines[i].SetFiniteness(true);}
        // std::cout << "lines size: " << lines.GetSize() << "\n";

        // res = get_fblr(theta, pnt, wall, cols);
        // res = get_fblr(theta, pnt, lines); // -> get_fblr(theta, pnt, wall, cols);
        res = get_fblr(theta, pnt, wall, cols);

        std::cout << "fblr: " << res[0] << ", " << res[1] << ", " << res[2] << ", " << res[3] << "\n";
        scan_test(lines,theta,res);
    }
}

int main_()
{
    // TODO: to incorporate GLFW, GLAD for the testing
    // int argc;
    // char *argv;
    // gl_main(argc, &argv);

    // point_test();
    // array_test();

    // arr_test_move_op();

    // shared_test();

    // fblr_test();

        for (int i=0;i<4;i++)   {
            cols[i].SetHeight(20);
            cols[i].SetWidth(20);
        }

        MkPoints ori;
        MkPoints trace;
        MkDouble res;
        MkLines lines;
        std::string fname = "../wall_column.dat";
        read_file(fname,lines); // -> read_file(fname, wall, cols);


        {
            MkPoint pnt(50,50,0);
            double theta = -43; // counter clockwise
            for (int i=0;i<lines.GetSize();i++) {lines[i].SetFiniteness(true);}
            std::cout << "lines size: " << lines.GetSize() << "\n";

            // res = get_fblr(theta, pnt, wall, cols);
            // res = get_fblr(theta, pnt, lines); // -> get_fblr(theta, pnt, wall, cols);
            res = get_fblr(theta, pnt, wall, cols);

            std::cout << "f: " << res[0] << ", b:" << res[1] << ", l:" << res[2] << ", r:" << res[3] << "\n";
            scan_test(lines,theta,res);
        }
    }

    // pnts_tst();
    
    return 0;
}

