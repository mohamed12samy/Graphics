#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
using namespace std;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");



HMENU hmenu;
void AddMenus(HWND hwnd){
    hmenu = CreateMenu();
    HMENU hh = CreateMenu();

    AppendMenu(hmenu , MF_POPUP,(UINT_PTR)hh,"choose to draw");
    AppendMenu(hh,MF_STRING , 1,"Parametric Line");
    AppendMenu(hh,MF_STRING , 2,"DDA Line");
    AppendMenu(hh,MF_STRING , 3,"Mid Point Line");
    AppendMenu(hh,MF_SEPARATOR , NULL,NULL);


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


/*  This function is called by the Windows function DispatchMessage()  */
/****************************************DRAWING FUNCTIONS************************************************/
int Round(int val){

    return (int)(val+0.5);
}
void drawLineParametric(HDC hdc , int x1 , int y1 , int x2 , int y2,COLORREF color){
    for(double t=0 ; t<=1 ; t+=0.001){
        int x = Round(x1+t*(x2-x1));
        int y = Round(y1+t*(y2-y1));
        //cout<<x<<"    "<<y<<endl;
        SetPixel(hdc , x,y,color);
    }
}

void drawLineDDA(HDC hdc , int x1 , int y1 , int x2 , int y2,COLORREF color){
    int x= x1, y=y1,
    dx = x2-x1 , dy = y2-y1,
    e = 2*dy-dx , e1 = 2*(dy-dx) , e2 = 2*dy;
    SetPixel(hdc , x,y,color);
    while(x<x2)
    {
        x++;
        if(e>=0)
        {
            y++;
            e += e1;
        }
        else e += e2;
        SetPixel(hdc , x,y,color);
    }
}
void drawLineMIDPOINT(HDC hdc , int x1 , int y1 , int x2 , int y2,COLORREF color)
{
    int x = x1 , y = y1,
    dx = x2-x1 , dy = y2-y1,
    d = dx + (2*dy+1-2*y1) - 2*dy*(x1+1-x1);
    SetPixel(hdc , x,y,color);
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
           SetPixel(hdc , x,y,color);
        }
    }


/*********************************************************************************************************/

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int x1 , y1 ,x2 ,y2;
     HDC hdc;
     hdc = GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {
     case WM_CREATE:
        AddMenus(hwnd);
        break;
 case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;

    case WM_LBUTTONDOWN:
            x1 = LOWORD(lParam);
            y1 = HIWORD(lParam);
            cout<<x1<<"    "<<y1<<endl;
            break;
    case WM_LBUTTONUP:
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);

            //drawLineParametric(hdc , x1,y1,x2,y2,RGB(255,0,0));
            ReleaseDC(hwnd,hdc);
            cout<<x2<<"    "<<y2<<endl;
            break;

        case WM_COMMAND:
        switch(wParam)
        {
        case 1:
            MessageBeep(MB_MODEMASK);
            drawLineParametric(hdc , x1,y1,x2,y2,RGB(255,0,0));
            break;
        case 2:
            MessageBeep(MB_APPLMODAL);
            drawLineDDA(hdc , x1,y1,x2,y2,RGB(255,0,0));
            break;
        case 3:
            MessageBeep(MB_APPLMODAL);
            drawLineMIDPOINT(hdc , x1,y1,x2,y2,RGB(0,0,0));
            break;
        }
        break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}


