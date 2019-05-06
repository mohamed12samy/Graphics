#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <bits/stdc++.h>
using namespace std;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

fstream file;
vector <int>vec;

HMENU hmenu;
void AddMenus(HWND hwnd){
    hmenu = CreateMenu();
    HMENU men1 = CreateMenu();
    HMENU men2 = CreateMenu();
    HMENU men3 = CreateMenu();
    HMENU men4 = CreateMenu();
    HMENU men5 = CreateMenu();
    HMENU hh = CreateMenu();

    AppendMenu(hmenu , MF_POPUP,(UINT_PTR)men1,"line");
    AppendMenu(hmenu , MF_POPUP,(UINT_PTR)men2,"ellipse");
    AppendMenu(hmenu , MF_POPUP,(UINT_PTR)men3,"Curve");
    AppendMenu(hmenu , MF_POPUP,(UINT_PTR)men4,"clipping");
    AppendMenu(hmenu , MF_POPUP,(UINT_PTR)men5,"Save&load");

    AppendMenu(men1,MF_STRING , 1,"Parametric Line");
    AppendMenu(men1,MF_STRING , 2,"DDA Line");
    AppendMenu(men1,MF_STRING , 3,"Mid Point Line");

    AppendMenu(men2,MF_STRING , 4,"Direct Ellipse");
    AppendMenu(men2,MF_STRING , 5,"Polar Ellipse");
    AppendMenu(men2,MF_STRING , 6,"Mid point Ellipse");

    AppendMenu(men3,MF_STRING , 7,"Splines");
    AppendMenu(men3,MF_STRING , 8,"bezier Curve");
    AppendMenu(men3,MF_STRING , 9,"hermite Curve");

    AppendMenu(men4,MF_STRING , 10,"Polygon Cliping");
    AppendMenu(men4,MF_STRING , 11,"Line Cliping");

    AppendMenu(men5,MF_STRING , 12,"Save");
    AppendMenu(men5,MF_STRING , 13,"load");

    SetMenu(hwnd,hmenu);
}



int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/****************************************DRAWING FUNCTIONS************************************************/
int Round(int x){

    return (int)(x+0.5);
}
void drawLineParametric(HDC hdc , int x1 , int y1 , int x2 , int y2){
    vec.push_back(x1);
    vec.push_back(y1);
    vec.push_back(x2);
    vec.push_back(y2);
    vec.push_back(1);
    vec.push_back(102030);
    for(double t=0 ; t<=1 ; t+=0.001){
        int x = Round(x1+t*(x2-x1));
        int y = Round(y1+t*(y2-y1));
        //cout<<x<<"    "<<y<<endl;
        SetPixel(hdc , x,y,RGB(255,0,0));
    }
}

void drawLineDDA(HDC hdc , int x1 , int y1 , int x2 , int y2)
{
    /*if(x1 > x2 ){
        int t1 ,t2;
        t1 = x1 ;
        x1 = x2 ;
        x2 = t1 ;
        t2 = y1 ;
        y1 = y2 ;
        y2 = t2 ;
    }*/

    vec.push_back(x1);
    vec.push_back(y1);
    vec.push_back(x2);
    vec.push_back(y2);
    vec.push_back(2);
    vec.push_back(102030);
    int x= x1, y=y1,
    dx = x2-x1 , dy = y2-y1,
    e = 2*dy-dx , e1 = 2*(dy-dx) , e2 = 2*dy;
    SetPixel(hdc , x,y,RGB(100,100,100));

        while(x<x2)
        {
            x++;
            if(e>=0)
            {
                y++;
                e += e1;
            }
            else e += e2;
            SetPixel(hdc , x,y,RGB(100,100,100));
        }

}
void drawLineMIDPOINT(HDC hdc , int x1 , int y1 , int x2 , int y2)
{
    /*if(x1 > x2 ){
        int t1 ,t2;
        t1 = x1 ;
        x1 = x2 ;
        x2 = t1 ;
        t2 = y1 ;
        y1 = y2 ;
        y2 = t2 ;
    }*/
    vec.push_back(x1);
    vec.push_back(y1);
    vec.push_back(x2);
    vec.push_back(y2);
    vec.push_back(3);
    vec.push_back(102030);
    int x = x1 , y = y1,
    dx = x2-x1 , dy = y2-y1,
    d = dx + (2*dy+1-2*y1) - 2*dy*(x1+1-x1);
    SetPixel(hdc , x,y,RGB(0,0,0));
    while(x<x2)
    {
        if(d>0){
            x++;
            d +=(-2*dy);
           }
           else {
                x++;
                y++;
                d += (-2*dy)+(2*dx);
           }
           SetPixel(hdc , x,y,RGB(0,0,0));
        }
    }

void drawDirectEllipse(HDC hdc , int xc , int yc ,int r1,int r2){
    vec.push_back(xc);
    vec.push_back(yc);
    vec.push_back(r1);
    vec.push_back(r2);
    vec.push_back(4);
    vec.push_back(102030);
    for(double t=0 ; t<=2 ; t+=0.001){
        int x = r1*cos(t);
        int y = r2*sin(t);
        SetPixel(hdc, xc + x, yc + y,RGB(100,100,100));
        SetPixel(hdc, xc - x, yc + y,RGB(100,100,100));
        SetPixel(hdc, xc - x, yc - y,RGB(100,100,100));
        SetPixel(hdc, xc + x, yc - y,RGB(100,100,100));
    }
}
void drawPolarEllipse(HDC hdc , int xc , int yc ,int r1,int r2){
        vec.push_back(xc);
    vec.push_back(yc);
    vec.push_back(r1);
    vec.push_back(r2);
    vec.push_back(5);
    vec.push_back(102030);
    double t = 0;
    while(t <360)
    {
        int x = r1*cos(t) + xc;
        int y = r2*sin(t) +yc;
        t+=0.01;
        SetPixel(hdc,x,y,RGB(100,100,100));
    }
}

void drawMidPointEllipse(HDC hdc , int xc , int yc ,int r1,int r2){
    vec.push_back(xc);
    vec.push_back(yc);
    vec.push_back(r1);
    vec.push_back(r2);
    vec.push_back(6);
    vec.push_back(102030);
   int x = 0, y = r2;

    int p = pow(r2,2.0)- pow(r1,2)*r2 + pow(r1,2)/4;


    while(2.0*r2*r2*x <= 2.0*r1*r1*y)
    {
        if(p < 0)
        {
            x++;
            p = p+2*r2*r2*x+r2*r2;
        }
        else
        {
            x++;
            y--;
            p = p+2*r2*r2*x-2*r1*r1*y-r2*r2;
        }
        SetPixel(hdc, xc + x, yc + y,RGB(100,100,100));
        SetPixel(hdc, xc - x, yc + y,RGB(100,100,100));
        SetPixel(hdc, xc - x, yc - y,RGB(100,100,100));
        SetPixel(hdc, xc + x, yc - y,RGB(100,100,100));
    }

    p=r2*r2*(x+0.5)*(x+0.5)+r1*r1*(y-1)*(y-1)-r1*r1*r2*r2;
    while(y > 0)
    {
        if(p <= 0)
        {
            x++;
            y--;
            p = p+2*r2*r2*x-2*r1*r1*y+r1*r1;
        }
        else
        {
            y--;
            p = p-2*r1*r1*y+r1*r1;
        }
        SetPixel(hdc, xc + x, yc + y,RGB(100,100,100));
        SetPixel(hdc, xc - x, yc + y,RGB(100,100,100));
        SetPixel(hdc, xc - x, yc - y,RGB(100,100,100));
        SetPixel(hdc, xc + x, yc - y,RGB(100,100,100));
    }
}
void splines( HDC hdc,int x1,int y1,int x2,int y2,int x3,int y3 )
{
    vec.push_back(x1);
    vec.push_back(y1);
    vec.push_back(x2);
    vec.push_back(y2);
    vec.push_back(x3);
    vec.push_back(y3);
    vec.push_back(7);
    vec.push_back(102030);

     double xu = 0.0 , yu = 0.0 , u = 0.0 ,s0,s1,s2,k0,k1,k2;
     s0=x1;
     s1=-3*x1+4*x2-x3;
     s2=2*x3-4*x2+2*x1;
     k0=y1;
     k1=-3*y1+4*y2-y3;
     k2=2*y3-4*y2+2*y1;
    for(u = 0.0 ; u <= 1.0 ; u += 0.0001)
    {
        xu = s0+s1*u+s2*u*u;
        yu = k0+k1*u+k2*u*u;
        SetPixel(hdc, xu, yu, RGB(200,250,200));
    }
}
void bezierCurve( HDC hdc,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4  )
{
    vec.push_back(x1);
    vec.push_back(y1);
    vec.push_back(x2);
    vec.push_back(y2);
    vec.push_back(x3);
    vec.push_back(y3);
    vec.push_back(x4);
    vec.push_back(y4);
    vec.push_back(8);
    vec.push_back(102030);

    double xu = 0.0 , yu = 0.0 , u = 0.0 ;
    for(u = 0.0 ; u <= 1.0 ; u += 0.0001)
    {
        xu = pow(1-u,3)*x1+3*u*pow(1-u,2)*x2+3*pow(u,2)*(1-u)*x3
             +pow(u,3)*x4;
        yu = pow(1-u,3)*y1+3*u*pow(1-u,2)*y2+3*pow(u,2)*(1-u)*y3
            +pow(u,3)*y4;
        SetPixel(hdc, xu, yu,RGB(150,200,100));
    }
}

void hermiteCurve( HDC hdc,int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4  )
{
    vec.push_back(x1);
   vec.push_back(x2);
    vec.push_back(y2);
    vec.push_back(x3);
    vec.push_back(y3);
    vec.push_back(x4);
    vec.push_back(y4);
    vec.push_back(9);
    vec.push_back(102030);

    double xu = 0.0 , yu = 0.0 , u = 0.0 ;
    for(u = 0.0 ; u <= 1.0 ; u += 0.0001)
    {
        xu=(2*pow(u,3)-3*pow(u,2)+1)*x1+(-2*pow(u,3)+3*pow(u,2))*x2+(pow(u,3)-2*pow(u,2)+u)*x3+(pow(u,3)-pow(u,2))*x4;
        yu=(2*pow(u,3)-3*pow(u,2)+1)*y1+(-2*pow(u,3)+3*pow(u,2))*y2+(pow(u,3)-2*pow(u,2)+u)*y3+(pow(u,3)-pow(u,2))*y4;
        SetPixel(hdc, xu, yu,RGB(300,100,100));
    }
}

/******clipping******/

struct vertex
{

    double x, y;
    vertex(double x1=0 , double y1=0)
    {
        x = x1;
        y = y1;
    }
};
typedef bool (*Is_inside)(vertex& v,int edge);
typedef vertex (*Intersect)(vertex& v1,vertex& v2,int edge);
vector<vertex> ClipWithEdge(vector<vertex> p,int edge,Is_inside inside ,Intersect intersection )
{
    vector<vertex> output;
    vertex v = p[p.size()-1];
    bool v_inside = inside(v,edge);

    for(int i=0; i<(int)p.size(); i++)
    {
        vertex v2=p[i];
        bool v2_in=inside(v2,edge);
        if(!v_inside && v2_in)
        {
            output.push_back(intersection(v,v2,edge));
            output.push_back(v2);
        }
        else if(v_inside && v2_in) output.push_back(v2);
        else if(v_inside) output.push_back(intersection(v,v2,edge));
        v=v2;
        v_inside=v2_in;
    }
    return output;
}
bool InLeft(vertex& v,int edge)
{
    return v.x>=edge;
}
bool InRight(vertex& v,int edge)
{
    return v.x<=edge;
}
bool InTop(vertex& v,int edge)
{
    return v.y>=edge;
}
bool InBottom(vertex& v,int edge)
{
    return v.y<=edge;
}

vertex VIntersect(vertex& v1,vertex& v2,int xedge)
{
    vertex res;
    res.x=xedge;
    res.y=v1.y+(xedge-v1.x)*(v2.y-v1.y)/(v2.x-v1.x);
    return res;
}

vertex HIntersect(vertex& v1,vertex& v2,int yedge)
{
    vertex res;
    res.y=yedge;
    res.x=v1.x+(yedge-v1.y)*(v2.x-v1.x)/(v2.y-v1.y);
    return res;
}
void PolygonClip(HDC hdc, int x1,int y1,int x2 , int y2,int x3,int y3,int x4 , int y4,int x5, int y5,int xleft,int ytop,int xright,int ybottom)
{
    vec.push_back(x1);
    vec.push_back(y1);
    vec.push_back(x2);
    vec.push_back(y2);
    vec.push_back(x3);
    vec.push_back(y3);
    vec.push_back(x4);
    vec.push_back(y4);
    vec.push_back(x5);
    vec.push_back(y5);
    vec.push_back(xleft);
    vec.push_back(ytop);
    vec.push_back(xright);
    vec.push_back(ybottom);
    vec.push_back(11);
    vec.push_back(102030);
    vector<vertex> vlist;
    vlist.push_back(vertex(x1,y1));
    vlist.push_back(vertex(x2,y2));
    vlist.push_back(vertex(x3,y3));
    vlist.push_back(vertex(x4,y4));
    vlist.push_back(vertex(x5,y5));
    vlist=ClipWithEdge(vlist,xleft,InLeft,VIntersect);
    vlist=ClipWithEdge(vlist,ytop,InTop,HIntersect);
    vlist=ClipWithEdge(vlist,xright,InRight,VIntersect);
    vlist=ClipWithEdge(vlist,ybottom,InBottom,HIntersect);
    vertex v1=vlist[vlist.size()-1];
    for(int i=0; i<(int)vlist.size(); i++)
    {

        vertex v2=vlist[i];
        drawLineParametric(hdc,v1.x,v1.y,v2.x,v2.y);
        v1=v2;
    }
}

/*****line clipping*****/

union OutCode
{
    unsigned All:4;
    struct
    {
        unsigned left:1,top:1,right:1,bottom:1;
    };
};

OutCode GetOutCode(double x,double y,int xleft,int ytop,int xright,int ybottom)
{
    OutCode out;
    out.All=0;
    if(x<xleft)
        out.left=1;
    else if(x>xright)
        out.right=1;
    if(y>ytop)
        out.top=1;
    else if(y<ybottom)
        out.bottom=1;
    return out;
}
pair<int, int> VIntersect(double xs,double ys,double xe,double ye,int x,double &xi,double &yi)
{
    pair<int,int> p;
    xi=x;
    yi=ys+(x-xs)*(ye-ys)/(xe-xs);
    p.first=xi;
    p.second=yi;
    return p;
}
pair<int, int> HIntersect(double xs,double ys,double xe,double ye,int y,double &xi,double &yi)
{
    pair<int,int> p;
    yi=y;
    xi=xs+(y-ys)*(xe-xs)/(ye-ys);
    p.first=xi;
    p.second=yi;
    return p;
}
void clipLine(HDC hdc,int xs,int ys,int xe,int ye,int xleft,int ytop,int xright,int ybottom,COLORREF C)
{
    vec.push_back(xs);
    vec.push_back(ys);
    vec.push_back(xe);
    vec.push_back(ye);
    vec.push_back(xleft);
    vec.push_back(ytop);
    vec.push_back(xright);
    vec.push_back(ybottom);
    vec.push_back(11);
    vec.push_back(102030);
    double x1=xs,y1=ys,x2=xe,y2=ye;
    OutCode out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
    OutCode out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
    while( (out1.All || out2.All) && !(out1.All & out2.All))
    {
        pair<int, int> point;
        double xi,yi;
        if(out1.All)
        {
            if(out1.left)
                point = VIntersect(x1,y1,x2,y2,xleft, xi, yi);
            else if(out1.top)
                point = HIntersect(x1,y1,x2,y2,ytop, xi, yi);
            else if(out1.right)
                point = VIntersect(x1,y1,x2,y2,xright, xi, yi);
            else
                point = HIntersect(x1,y1,x2,y2,ybottom, xi, yi);
            x1=point.first;
            y1=point.second;
            out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
        }
        else
        {
            if(out2.left)
                point = VIntersect(x1,y1,x2,y2,xleft,xi,yi);
            else if(out2.top)
                point = HIntersect(x1,y1,x2,y2,ytop,xi,yi);
            else if(out2.right)
                point = VIntersect(x1,y1,x2,y2,xright,xi,yi);
            else
                point = HIntersect(x1,y1,x2,y2,ybottom,xi,yi);
            x2=point.first;
            y2=point.second;
            out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
        }
    }
    if(!out1.All && !out2.All)
        drawLineParametric(hdc,x1,y1,x2,y2);

}
/*********************************************************************************************************/
/*********************************save&load************************************/
void save()
{
    file.open("file.txt",ios::out|ios::in);
    for(int i=0 ; i<vec.size() ; i++)
    {
        /*file << vec[i]; cout<<vec[i]<<"  ";
        file << " ";
        if(vec[i] == 00) file << "\n";
*/
        file.write((char*) &vec[i],sizeof(int));
        if(vec[i+1] == 102030 ){ i++; file << "\n"; continue;}
        file << " ";
    }

    file.close();
}
void load(HDC hdc)
{
    file.open("file.txt",ios::out|ios::in);
    int x = 0;string str="",s="";
    vec.clear();
    char c ;
   while(file.read((char*) &x,sizeof(int))){
        vec.push_back(x);
        cout<<x<<endl;
        c=file.get();
        if(c == '\n'){
            if(vec[vec.size()-1] == 1)
                drawLineParametric(hdc ,vec[0],vec[1],vec[2],vec[3]);

            else if(vec[vec.size()-1] == 2)
                    drawLineDDA(hdc ,vec[0],vec[1],vec[2],vec[3]);

            else if(vec[vec.size()-1] == 3)
                    drawLineMIDPOINT(hdc ,vec[0],vec[1],vec[2],vec[3]);

            else if(vec[vec.size()-1] == 4)
                    drawDirectEllipse(hdc , vec[0],vec[1],vec[2],vec[3]);

            else if(vec[vec.size()-1] == 5)
                    drawPolarEllipse(hdc , vec[0],vec[1],vec[2],vec[3]);

            else if(vec[vec.size()-1] == 6)
                    drawMidPointEllipse(hdc , vec[0],vec[1],vec[2],vec[3]);

            else if(vec[vec.size()-1] == 7)
                    splines(hdc,vec[0],vec[1],vec[2],vec[3],vec[4],vec[5]);

            else if(vec[vec.size()-1] == 8)
                    bezierCurve(hdc, vec[0],vec[1],vec[2],vec[3],vec[4],vec[5],vec[6],vec[7]);

            else if(vec[vec.size()-1] == 9)
                    hermiteCurve(hdc, vec[0],vec[1],vec[2],vec[3],vec[4],vec[5],vec[6],vec[7]);

            else if(vec[vec.size()-1] == 10)
                    PolygonClip(hdc,vec[0],vec[1],vec[2],vec[3],vec[4],vec[5],vec[6],vec[7],vec[8],vec[9],vec[10],vec[11],vec[12],vec[13]);

            else if(vec[vec.size()-1] == 11)
                    clipLine(hdc,vec[0],vec[1],vec[2],vec[3],vec[4],vec[5],vec[6],vec[7],RGB(0,0,0));
            vec.clear();

        }
    }
    file.close();
}
/**************************************************************************************/
int s=99;

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int x1 , y1 ,x2 ,y2,x3,y3,x4,y4,r1,r2,counter=-1, l,  t,  r,  b,x5,y5;

      HDC hdc;
     hdc = GetDC(hwnd);

    switch (message)
    {
    case WM_RBUTTONDOWN:
        if (counter != -1)break;
        l = LOWORD(lParam);
        t = HIWORD(lParam);
        break;
    case WM_RBUTTONUP:
        if (counter != -1) break;
        r = LOWORD(lParam);
        b = HIWORD(lParam);
        counter = 0;
        drawLineParametric(hdc, l, t, l, b);
        drawLineParametric(hdc, l, t, r, t);
        drawLineParametric(hdc, l, b, r, b);
        drawLineParametric(hdc, r, t, r, b);
        break;

     case WM_CREATE:
        AddMenus(hwnd);
        break;

    case WM_LBUTTONDOWN :
        if(counter==0)
        {
            x1 = LOWORD(lParam);
            y1 = HIWORD(lParam);

            cout<<x1<<"    "<<y1<<endl;
            counter++;
        }
        else if(counter==1)
        {
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);

            cout<<x2<<"    "<<y2<<endl;
            counter++;
        }
        else if(counter==2)
        {
            x3 = LOWORD(lParam);
            y3 = HIWORD(lParam);
            r1 = (int)sqrt(pow((x2-x1),2) + pow((y2-y1),2));
            r2 = (int)sqrt(pow((x3-x1),2) + pow((y3-y1),2));
            cout<<x3<<"    "<<y3<<endl;
            counter++;
        }
        else if(counter==3)
        {
            x4 = LOWORD(lParam);
            y4 = HIWORD(lParam);

            cout<<x4<<"    "<<y4<<endl;
            counter++;
        }
        else if(counter == 4)
        {
            x5 = LOWORD(lParam);
            y5 = HIWORD(lParam);
            cout<<x5<<"    "<<y5<<endl;
            counter++;
        }
        else if(counter==5)
        {
            counter=0;
        }
        break;

    case WM_COMMAND:
        switch(wParam)
        {
        case 1:
            drawLineParametric(hdc , x1,y1,x2,y2);
            counter=0;
            break;
        case 2:
            drawLineDDA(hdc , x1,y1,x2,y2);
            counter=0;
            break;
        case 3:
            drawLineMIDPOINT(hdc , x1,y1,x2,y2);
            counter=0;
            break;
         case 4:
            drawDirectEllipse(hdc , x1,y1,r1,r2);
            counter=0;
            break;
        case 5:
            drawPolarEllipse(hdc , x1,y1,r1,r2);
            counter=0;
            break;
        case 6:
            drawMidPointEllipse(hdc , x1,y1,r1,r2);
            counter=0;
            break;
        case 7 :
            splines(hdc,x1,y1,x2,y2,x3,y3);
            counter=0;
            break;

         case 8 :
                bezierCurve(hdc,x1,y1,x2,y2,x3,y3,x4,y4);
                counter=0;
                break;
         case 9 :
                hermiteCurve(hdc,x1,y1,x3,y3,x2,y2,x4,y4);
                counter=0;
                break;
         case 10:
            PolygonClip(hdc,x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,l,t,r,b);
            counter=0;
            break;
         case 11:
            clipLine(hdc,x1,y1,x2,y2,l,b,r,t,RGB(255,100,50));
            clipLine(hdc,x1,y1,x3,y3,l,b,r,t,RGB(255,100,50));
            clipLine(hdc,x3,y3,x2,y2,l,b,r,t,RGB(255,100,50));
            counter=0;
            break;
         case 12 :
                save();
                break;
         case 13 :
                load(hdc);
                break;
        }
        break;

         case WM_DESTROY:
            PostQuitMessage (0);
            break;
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
