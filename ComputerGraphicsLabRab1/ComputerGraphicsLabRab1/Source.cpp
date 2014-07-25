#include "LabRab1.h"

HWND button_gl_point;
HWND button_gl_line;
HWND button_gl_line_strip;
HWND button_gl_line_loop;
HWND button_gl_triangle;
HWND button_gl_triangle_strip;
HWND button_gl_triangle_fan;
HWND button_gl_quad;
HWND button_gl_quad_strip;
HWND button_gl_polygon;
HWND button_gl_sin;

HINSTANCE h_gInstance;
HDC hDC = NULL;
HGLRC hRC = NULL;
HWND hWnd = NULL;


LRESULT CALLBACK WndProc(HWND, UINT, UINT, LPARAM);
GLvoid ReSizeGLScene(GLsizei, GLsizei);
int InitGL(GLvoid);
int DrawGLScene(GLvoid);
GLvoid KillGLWindow(GLvoid);
BOOL CreateGLWindow(int, int, int, bool);
pair<GLfloat, GLfloat> GetPair(GLfloat a, GLfloat b);
float GetRand();

//GL global variables
bool fullscreen = TRUE;
bool active = TRUE;
bool keys[256];

//shapes var
int type = -1;
DrawingClass shape;
pair<GLfloat, GLfloat> pair_array[] = { GetPair(0.0f, 0.0f) };
float xPos;
float yPos;
float wid;
float hei;
int N = 0;
bool flagz = FALSE;

TCHAR WinName[] = _T("OpenGL");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	BOOL done = FALSE;
	//if (MessageBox(NULL, L"Would You Like To Run In Fullscreen Mode?", L"Start FullScreen?", MB_YESNO | MB_ICONQUESTION) == IDNO)
		fullscreen = FALSE;

	

	if (!CreateGLWindow(820, 480, 16, fullscreen))
	{
		return 0;
	}
		
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				done = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (active)
			{
				if (keys[VK_ESCAPE] == TRUE)
				{
					done = TRUE;
				}
				else
				{
					DrawGLScene();
					if (type != -1)
						switch (type)
						{
							case 0:
								shape.dcPoint(GetPair(0.0f, -2.0f), -1.5f, 0.0f, -6.0f);  
								break;
							case 1:
								break;
							case 2:
								break;
							case 3:
								break;
							case 4:
								break;
							case 5:
								shape.dcTriangleStrip(xPos, yPos, hei, wid);
								break;
							case 6:
								break;
							case 7:
								break;
							case 8:
								break;
							case 9:
								break;
							case 10:
								shape.dcSin(0.0f, 0.0f, -6.0f, 0.01f, 1);
								break;
							case 11:
								break;
							default:
								break;
						}
					SwapBuffers(hDC);
				}
			}
			
			if (keys[VK_F1])						
			{
				keys[VK_F1] = FALSE;					
				KillGLWindow();						
				fullscreen =! fullscreen;			
				if (!CreateGLWindow(640, 480, 16, fullscreen))
				{
					return 0;		
				}
			}
		}
	}

	KillGLWindow();
	return (msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	PAINTSTRUCT p_struct;
	switch (message)
	{
		case WM_MOUSEMOVE:
		{
			xPos = (float)GET_X_LPARAM(lParam);
			yPos = (float)GET_Y_LPARAM(lParam);
			if (type == 5)
				InvalidateRect(hWnd, NULL, FALSE);
			return 0;
		}
		case WM_ACTIVATE:       
		{
			if(!HIWORD(wParam))         
			{
				active = true;          
			}
			else
			{
				active = false;         
			} 
			return 0;            
		}

		case WM_SYSCOMMAND:           
		{
			switch (wParam)        
			{
				case SC_SCREENSAVE:        
				case SC_MONITORPOWER:     
				return 0;       
			}
			break;         
		}

		case WM_KEYDOWN:           
		{
			keys[wParam] = true;       
			return 0;          
		}

		case WM_KEYUP:          
		{
			keys[wParam] = false;          
			return 0;            
		}

		case WM_SIZE:
		{
			ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));
			wid = LOWORD(lParam);
			hei = HIWORD(lParam);
			return 0;
		}

		case WM_CREATE:
			button_gl_point = CreateWindow(L"BUTTON", L"Point", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 30, 50, 50, 30, hWnd, (HMENU)BUTTON_GL_POINT, h_gInstance, NULL);
			button_gl_line = CreateWindow(L"BUTTON", L"Line", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 80, 50, 50, 30, hWnd, (HMENU)BUTTON_GL_LINE, h_gInstance, NULL);
			button_gl_line_strip = CreateWindow(L"BUTTON", L"LineStrip", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 130, 50, 70, 30, hWnd, (HMENU)BUTTON_GL_LINE_STRIP, h_gInstance, NULL);
			button_gl_line_loop = CreateWindow(L"BUTTON", L"LineLoop", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 200, 50, 70, 30, hWnd, (HMENU)BUTTON_GL_LINE_LOOP, h_gInstance, NULL);
			button_gl_triangle = CreateWindow(L"BUTTON", L"Triangle", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 270, 50, 70, 30, hWnd, (HMENU)BUTTON_GL_TRIANGLE, h_gInstance, NULL);
			button_gl_triangle_strip = CreateWindow(L"BUTTON", L"TriangleStrip", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 340, 50, 100, 30, hWnd, (HMENU)BUTTON_GL_TRIANGLE_STRIP, h_gInstance, NULL);
			button_gl_triangle_fan = CreateWindow(L"BUTTON", L"TriangleFan", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 440, 50, 90, 30, hWnd, (HMENU)BUTTON_GL_TRIANGLE_FAN, h_gInstance, NULL);
			button_gl_quad = CreateWindow(L"BUTTON", L"Quad", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 530, 50, 50, 30, hWnd, (HMENU)BUTTON_GL_QUAD, h_gInstance, NULL);
			button_gl_quad_strip = CreateWindow(L"BUTTON", L"QuadStrip", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 580, 50, 70, 30, hWnd, (HMENU)BUTTON_GL_QUAD_STRIP, h_gInstance, NULL);
			button_gl_polygon = CreateWindow(L"BUTTON", L"Polygon", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 650, 50, 70, 30, hWnd, (HMENU)BUTTON_GL_POLYGON, h_gInstance, NULL);
			button_gl_sin = CreateWindow(L"BUTTON", L"Sin", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 720, 50, 50, 30, hWnd, (HMENU)BUTTON_GL_SIN, h_gInstance, NULL);
			break;

		case WM_PAINT:
			{
				hDC = BeginPaint(hWnd, &p_struct);
				if (flagz == FALSE)
				{
					DrawGLScene();
					glTranslatef(0.0f, 0.0f, -6.0f);
					glBegin(GL_TRIANGLE_STRIP);					

					glColor3f(GetRand(), GetRand(), GetRand());
				}

				//ReleaseDC(hWnd, hDC);
				EndPaint(hWnd, &p_struct);
			}
			break;

		case WM_COMMAND: 
			{   
				switch(LOWORD(wParam))
				{
				case BUTTON_GL_POINT:
					{
						type = 0;
						return 0;
					}
				case BUTTON_GL_LINE:
					{
						type = 1;
						return 0;
					}
				case BUTTON_GL_LINE_STRIP:
					{
						type = 2;
						return 0;
					}
				case BUTTON_GL_LINE_LOOP:
					{
						type = 3;
						return 0;
					}
				case BUTTON_GL_TRIANGLE:
					{
						type = 4;
						return 0;
					}
				case BUTTON_GL_TRIANGLE_STRIP:
					{
						type = 5;										
						return 0;
					}
				case BUTTON_GL_TRIANGLE_FAN:
					{
						type = 6;
						return 0;
					}
				case BUTTON_GL_QUAD:
					{
						type = 7;
						return 0;
					}
				case BUTTON_GL_QUAD_STRIP:
					{
						type = 8;
						return 0;
					}
				case BUTTON_GL_POLYGON:
					{
						type = 9;
						return 0;
					}
				case BUTTON_GL_SIN:
					{
						type = 10;
						return 0;
					}

				}
			}
			return 0;
		case WM_DESTROY:   
			{
				PostQuitMessage(0);
				break;
			}

		default:

			return DefWindowProc(hWnd, message, wParam, lParam);

	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height) 
{
	if (height == 0)           
	{
		height = 1;
	}    
    glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();         
 
    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f );
 
    glMatrixMode(GL_MODELVIEW);        
    glLoadIdentity();              
}

int InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	return TRUE;
}

int DrawGLScene(GLvoid)            
{
		//static float dx = 0.0f;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      
        glLoadIdentity();

		//glTranslatef(-1.5f, 0.0f, -4.0f);
		//glBegin(GL_TRIANGLES); 
		//glColor3f(0.0f, 0.0f, 1.0f);// Drawing Using Triangles
		//glVertex3f(0.0f, 1.0f, 0.0f);              // Top
		//glColor3f(0.0f, 1.0f, 0.0f);
		//glVertex3f(-1.0f,-1.0f, 0.0f);              // Bottom Left
		//glVertex3f( 1.0f,-1.0f, 0.0f);              // Bottom Right
		//
		//glEnd();  

		//glTranslatef(1.5f-dx,0.0f, 4.0f);
		//glTranslatef(-1.5f+dx,0.0f,-6.0f);
		//glBegin(GL_TRIANGLES);
		//glColor3f(1.0f,0.0f,0.0f);				// Drawing Using Triangles
		//glVertex3f( 0.0f, 1.0f, 0.0f);              // Top
		//glVertex3f(-1.0f,-1.0f, 0.0f);              // Bottom Left
		//glVertex3f( 1.0f,-1.0f, 0.0f);              // Bottom Right
		//glEnd();  

		//(dx < 2) ? dx += 0.001f : dx = 0.0f;

        return true;                
}

GLvoid KillGLWindow(GLvoid)
{
	if (fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	if (hRC)
	{
		if (!wglMakeCurrent(NULL, NULL))
		{
			MessageBox( NULL, L"Release Of DC And RC Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
		}
		if (!wglDeleteContext(hRC))
		{
			MessageBox( NULL, L"Release Rendering Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
		}
		hRC = NULL;
	}
	
	if (hDC && !ReleaseDC(hWnd, hDC))
	{
		MessageBox( NULL, L"Release Device Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
        hDC = NULL;
	}

	if (hWnd && !DestroyWindow(hWnd))
	{
		MessageBox( NULL, L"Could Not Release hWnd.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
		hWnd = NULL;
	}

	if( !UnregisterClass(L"OpenGL", h_gInstance))        // Возможно ли разрегистрировать класс
	{
		MessageBox(NULL, L"Could Not Unregister Class.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		h_gInstance = NULL;                // Установить hInstance в NULL
	}
}

BOOL CreateGLWindow(int width, int height, int bits, bool fullscreenflag)
{
	GLuint PixelFormat;
	WNDCLASS wc;
	DWORD dwExStyle;
	DWORD dwStyle;
	
	RECT WindowRect;
	WindowRect.bottom = (long)height;
	WindowRect.left = (long)0;
	WindowRect.right = (long)width;
	WindowRect.top = (long)0;

	fullscreen = fullscreenflag;

	h_gInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;                
	wc.cbClsExtra = 0;                       
	wc.cbWndExtra = 0;                       
	wc.hInstance = h_gInstance;                    
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);         
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);        
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = _T("OpenGL");  

	if (!RegisterClass(&wc))                       
	{
		MessageBox(NULL, L"Failed To Register The Window Class.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                        
	}

	if (fullscreen)                           
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmPelsHeight = height;
		dmScreenSettings.dmBitsPerPel = bits;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL, L"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", L"NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;
			}
			else
			{
				MessageBox(NULL, L"Program Will Now Close.", L"ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
		}
	}

	if (fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(FALSE);
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW; 
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);

	if (!(hWnd = CreateWindowEx(dwExStyle,             
                _T("OpenGL"),               
                _T("LeonPetrov LabRab1 OpenGL"),                 
                WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle,             
                0, 
				0,                 
                WindowRect.right - WindowRect.left,   
                WindowRect.bottom - WindowRect.top,
                NULL,                   
                NULL,                 
                h_gInstance,             
                NULL)))
	{
		KillGLWindow();
		MessageBox(NULL, L"Window Creation Error.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	static  PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,                      
		PFD_TYPE_RGBA,                     
		bits,                               
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                        
		16,                             
		0, 0,                             
		PFD_MAIN_PLANE,                         
		0, 0, 0, 0                           
	};

	if (!(hDC = GetDC(hWnd)))
	{
		KillGLWindow();
		MessageBox(NULL, L"Can't Create A GL Device Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))        
	{
		KillGLWindow();
		MessageBox(NULL, L"Can't Find A Suitable PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
	{
		KillGLWindow();                
		MessageBox(NULL, L"Can't Set The PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                
	}

	if (!(hRC = wglCreateContext(hDC)))       
	{
		KillGLWindow();              
		MessageBox( NULL, L"Can't Create A GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;           
	}

	if (!wglMakeCurrent(hDC, hRC))        
	{
		KillGLWindow();          
		MessageBox( NULL, L"Can't Activate The GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	ShowWindow(hWnd,SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	ReSizeGLScene(width, height);    

	if( !InitGL())                  
	{
		KillGLWindow();              
		MessageBox(NULL, L"Initialization Failed.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                
	}

	return TRUE;
}

pair<GLfloat, GLfloat> GetPair(GLfloat a, GLfloat b)
{
	pair<GLfloat, GLfloat> return_pair;
	return_pair.first = a;
	return_pair.second = b;
	return return_pair;
}


float GetRand()
{
	float min = 0.0;
	float max = 1.0;
	srand(time_t(NULL));
	return (float)((rand() / (RAND_MAX + 1) * (max - min) + min) + 0.5);
}