#include "Engine.h"

//prototypes
LRESULT CALLBACK WndProc(HWND, UINT, UINT, LPARAM);
int DrawGLScene(GLvoid);
void OrtographicProection();

//consts
const float MAPINFO_WIDTH = 195.83f;
const float MAPINFO_HEIGHT = 130.83f;
const int BUILDING_RANGE = 100;
const int SIDES = 4;
const int TEXTURES = 8;

//высота одного этажа здания
float h = 0.5;

//количество этажей каждого здания
int Floors[BUILDING_RANGE];
//тип дома (текстура)
int TypeofBuildings[BUILDING_RANGE];
//параметры модели света
float Ambient[SIDES] = {0.4f, 0.4f, 0.4f, 0.0f};
//начальные позиции света
float LightPosition[SIDES] = {0.0f, 0.0f, 50.0f, 1.0f};
//массив для текстур
GLuint Texture[TEXTURES];

//контекст дисплея
HDC hDC = NULL;
HGLRC hRC = NULL;
//дескриптор окна
HWND hWnd = NULL;
//дескриптор экземпляра
HINSTANCE hInstance = NULL;


//настройка системы координат
void OrtographicProection()
{
	glOrtho(-MAPINFO_WIDTH / 2 - MAPINFO_WIDTH * 0.1, MAPINFO_WIDTH / 2 + MAPINFO_WIDTH * 0.1, -MAPINFO_WIDTH / 4, MAPINFO_WIDTH / 2 + MAPINFO_WIDTH / 4 + MAPINFO_WIDTH * 0.2, MAPINFO_WIDTH / 2 + MAPINFO_WIDTH * 0.1 , -MAPINFO_WIDTH / 2 - MAPINFO_WIDTH * 0.1);
	glRotated(-130, 1, 0, 0);
	glRotated(145, 0, 0, 1);
}

//загрузка текстур
void LoadGLTextures()
{
	AUX_RGBImageRec *t_0, *t_1, *t_2, *t_3, *t_4, *t_5, *t_6, *t_7, *t_8;
	//загрузка  текстур
	t_0 = auxDIBImageLoad(L"Grass.bmp");
	t_1 = auxDIBImageLoad(L"Roof_1.bmp");
	t_2 = auxDIBImageLoad(L"Roof_2.bmp");
	t_3 = auxDIBImageLoad(L"House_floor_1-2.bmp");
	t_4 = auxDIBImageLoad(L"House_floor_3-5.bmp");
	t_5 = auxDIBImageLoad(L"House_floor_3-5.bmp");
	t_6 = auxDIBImageLoad(L"Fences.bmp");
	t_7 = auxDIBImageLoad(L"Road.bmp");
	t_8 = auxDIBImageLoad(L"Stadion.bmp");

	//создание текструры
	glGenTextures(TEXTURES, &Texture[0]);

	//трава
	glBindTexture(GL_TEXTURE_2D, Texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, t_0->sizeX, t_0->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, t_0->data);

	//крыша
	glBindTexture(GL_TEXTURE_2D, Texture[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, t_1->sizeX, t_1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, t_1->data);

	glBindTexture(GL_TEXTURE_2D, Texture[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, t_2->sizeX, t_2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, t_2->data);

	//стены домов, окна
	glBindTexture(GL_TEXTURE_2D, Texture[3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, t_3->sizeX, t_3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, t_3->data);
 
	glBindTexture(GL_TEXTURE_2D, Texture[4]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, t_4->sizeX, t_4->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, t_4->data);

	glBindTexture(GL_TEXTURE_2D, Texture[5]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, t_5->sizeX, t_5->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, t_5->data);

	//Забор
	glBindTexture(GL_TEXTURE_2D, Texture[6]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, t_6->sizeX, t_6->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, t_6->data);

	//дорога
	glBindTexture(GL_TEXTURE_2D, Texture[7]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, t_7->sizeX, t_7->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, t_7->data);

	//стадион
	glBindTexture(GL_TEXTURE_2D, Texture[8]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, t_8->sizeX, t_8->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, t_8->data);
}



//main func
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWndMain;
	char szClassName [] = "MyClass";
	MSG msg; WNDCLASSEX wc;
	// Заполнить структуру класса окна
	wc.cbSize = sizeof (wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor (NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"ClassWindow";
	wc.hIconSm = LoadIcon (NULL, IDI_APPLICATION);


	// Зарегистрировать класс окна
	if ( !RegisterClassEx (&wc) )
	{
		MessageBox (NULL, L"Cannot register class", L"Error", MB_OK); 
		return 1;
	}
	// Создать основное окно приложения
	hWndMain = CreateWindow(L"ClassWindow", 
		L"Coursework(B02-191-2, Petrov Leon)",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 
		0, 
		1024, 
		640, 
		(HWND) NULL, 
		(HMENU) NULL, 
		(HINSTANCE) hInstance, 
		NULL);
	if ( !hWndMain )
	{
		MessageBox (NULL, L"Cannot create main window", L"Error", MB_OK); 
		return 1;
	}
	// Показать окно
	ShowWindow (hWndMain, nCmdShow);
	// Цикл обработки сообщений до закрытия приложения
	while ( GetMessage (&msg, NULL, 0, 0) )
	{
		TranslateMessage(&msg); DispatchMessage (&msg);
	}
	return msg.wParam;
}

//callback (default)
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	PAINTSTRUCT p_struct;
	int wid=1000,heg=1000;
	//углы поворота для работы с клавишами WSAD
	float zAngle1=0;
	float zAngle2=0;
	float xAngle1=0;
	float xAngle2=0;

	switch (message)
	{
		//вызыватся при создании окна win32
		case WM_CREATE:
			// установить формат пиксела:
			hDC=GetDC(hWnd);
			int PixelFormat;
			PIXELFORMATDESCRIPTOR pfd;
			memset(&pfd,0,sizeof(PIXELFORMATDESCRIPTOR));
			pfd.dwFlags=PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
			PixelFormat=ChoosePixelFormat(hDC, &pfd);
			SetPixelFormat(hDC, PixelFormat, &pfd);
			//установить контекст воспроизведения:
			hRC=wglCreateContext(hDC);
			wglMakeCurrent(hDC,hRC);
			//установить цвет фона:
			glClearColor(0.3,0.6,0.95,0.0);
			OrtographicProection();
			glEnable(GL_DEPTH_TEST);
			LoadGLTextures();

			break;

		//обработка при ждущем режме компьютера
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

		//событие при нажатии клавиши
		case WM_KEYDOWN:
			switch (wParam) 
			{
				case VK_LEFT:
					//изменение координаты X при нажатии клавиши <-
					LightPosition[0]+=10.0;
					//перерисовка, фон оснается без изменений
					InvalidateRect(hWnd,NULL,false);
					break;

				case VK_RIGHT:
					LightPosition[0]-=10.0;
					InvalidateRect(hWnd,NULL,false);
					break;

				case VK_UP:
					LightPosition[1]+=10.0;
					InvalidateRect(hWnd,NULL,false);
					break;

				case VK_DOWN:
					LightPosition[1]-=10.0;
					InvalidateRect(hWnd,NULL,false);
					break;

				case VK_NEXT: // PageDown
					LightPosition[2]-=10.0;
					InvalidateRect(hWnd,NULL,false);
					break;

				case VK_PRIOR: // PageUp
					LightPosition[2]+=10.0;
					InvalidateRect(hWnd,NULL,false);
					break;

				case 'A':

					zAngle1+=5;
					//вращение по оси Z
					glRotatef(zAngle1,0,0,1);
					SendMessage(hWnd,WM_PAINT,wParam,lParam);
					break;

				case 'D':
					zAngle2-=5;
					glRotatef(zAngle2,0,0,1);
					SendMessage(hWnd,WM_PAINT,wParam,lParam);
					break;

				case 'W':
					xAngle1+=5;
					glRotatef(xAngle1,1,0,0);
					SendMessage(hWnd,WM_PAINT,wParam,lParam);
					break;

				case 'S':
					xAngle2-=5;
					glRotatef(xAngle2,1,0,0);
					SendMessage(hWnd,WM_PAINT,wParam,lParam);
					break;

				case 'O':
					glScalef(2, 2, 1);
					SendMessage(hWnd,WM_PAINT,wParam,lParam);
					break;

				case 'P':
					glScalef(0.5, 0.5, 1);
					SendMessage(hWnd,WM_PAINT,wParam,lParam);
					break;
			}
			break;

		//прорисовка окна
		case WM_PAINT:
			{
				BeginPaint(hWnd,&p_struct);
				glViewport(0,0,wid,heg);
				//очистка цвета
				glClear(GL_COLOR_BUFFER_BIT);
				//очистка глубины
				glClear(GL_DEPTH_BUFFER_BIT);
			
				//сцена рисования
				DrawGLScene();
				//х2 буферизация
				SwapBuffers(hDC);
				EndPaint (hWnd, &p_struct);
			}
			break;

			//закрытие окна
		case WM_CLOSE:
			DestroyWindow (hWnd);
			break;

		case WM_DESTROY:
			// освободить и удалить контекст воспроизведения:
			wglMakeCurrent(0,0);
			wglDeleteContext(hRC);
			//освободить и удалить контекст устройства:
			ReleaseDC(hWnd,hDC);
			DeleteDC(hDC);
			PostQuitMessage (0);
			break;

		default:

			return DefWindowProc(hWnd, message, wParam, lParam);

	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

//drawing
int DrawGLScene(GLvoid)            
{
	// включить освещение
	glEnable(GL_LIGHTING);

	//фоновое освещение
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Ambient);

	// текущий цвет объектов
	//glEnable(GL_COLOR_MATERIAL);

	//включить нулевой источник света
	glEnable(GL_LIGHT0);

	//настройка нулевого источника света
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

	// нормализация векторов нормалей
	glEnable(GL_NORMALIZE);
	
	//Разрешение наложение текстуры
	glEnable(GL_TEXTURE_2D);

	int n;
	float ax[100],ay[100];	
	char str[300], tmp[30];

	//улица
	freopen("street.MIF","r",stdin);
	//разрешение автоматической генерации текстуры
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	//алгоритм генерации
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	while (gets(str)!=NULL)
	{
		if (strstr(str,"Region")!=NULL)
		{
			//привязка текстыра
			glBindTexture(GL_TEXTURE_2D, Texture[7]);
			glBegin(GL_POLYGON);
				//установка нормали
				glNormal3f(0,0,1);
				gets(str);
				sscanf(str,"%d",&n);
				for (int i=0;i<n;++i)
				{
					gets(str);
					float x,y;
					sscanf(str,"%f %f",&x,&y);
					ax[i]=x;
					ay[i]=y;
					glNormal3f(0,0,1);
					//наложение текстуры
					glTexCoord2f(-(ax[i] - MAPINFO_WIDTH / 2), ay[i] - MAPINFO_HEIGHT / 2); 					
					glVertex3f(-(ax[i] - MAPINFO_WIDTH / 2),ay[i] - MAPINFO_HEIGHT / 2,0 + n * 0.01);
				}
			glEnd();
		}
	}

	//Кварталы
	glBindTexture(GL_TEXTURE_2D, Texture[0]);
	freopen("quarters.MIF","r",stdin);
	glEnable(GL_TEXTURE_GEN_S); 
	glEnable(GL_TEXTURE_GEN_T);
	while (gets(str)!=NULL)
	{
		if (strstr(str,"Region")!=NULL)
		{
			glColor3ub(65,167,55);
			glBegin(GL_POLYGON);
				gets(str);
				sscanf(str,"%d",&n);
				for (int i=0; i<n; ++i)
				{
					gets(str);
					float x,y;
					sscanf(str,"%f %ff",&x,&y);
					float xGL = x - MAPINFO_WIDTH / 2;
					float yGL = y - MAPINFO_HEIGHT / 2;
					glNormal3f(0,0,1);
					glTexCoord2f(-xGL/2, yGL/2);
					glVertex3f(-xGL, yGL, 0);
				}
			glEnd();
		}
	}

	//стадион
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glBindTexture(GL_TEXTURE_2D,Texture[8]);
	freopen("playground.MIF","r",stdin);
	while (gets(str)!=NULL)
	{
		if (strstr(str,"Region")!=NULL)
		{
			glColor3ub(152,255,152);
			glBegin(GL_POLYGON);
				gets(str);
				sscanf(str,"%d",&n);
				for (int i=0; i<n; ++i)
				{
					gets(str);
					float x,y;
					sscanf(str,"%f %ff",&x,&y);
					float xGL = x - MAPINFO_WIDTH / 2;
					float yGL = y - MAPINFO_HEIGHT / 2;
					glNormal3f(0,0,1);
					switch (i)
					{
						case 0:
							glTexCoord2f(0, 1); 
							break;
						case 1:
							glTexCoord2f(0, 0); 
							break;
						case 2:
							glTexCoord2f(1, 0); 
							break;
						case 3:
							glTexCoord2f(1, 1); 
							break;
					}
					//glTexCoord2f(-xGL, yGL);
					glVertex3f(-xGL, yGL, 0.01f);
				}
			glEnd();
		}
	}

	//дома
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	int k = 0;
	int color = 0;
	int shablone = 0;
	freopen("buildings.MIF","r",stdin);
	while (gets(str)!=NULL)
	{
		if (strstr(str,"Brush")!=NULL)
		{
			sscanf(str,"%s (%d,%d", tmp, &shablone, &color);
			//распределение цвета по этажам
			switch (color)
			{
			case 16711680:
				Floors[k] =	1;
				TypeofBuildings[k] = 1;
				break;
			case 16744448:
				Floors[k] =	2;
				TypeofBuildings[k] = 1;
				break;
			case 16776960:
				Floors[k] =	3;
				TypeofBuildings[k] = 2;
				break;
			case 255:
				Floors[k] =	4;
				TypeofBuildings[k] = 2;
				break;
			case 8388736:
				Floors[k] =	3;
				TypeofBuildings[k] = 2;
				break;
			}
			k++;
		}
	}

	k = -1;

	//структура точки
	struct cwPoint
	{
		float x;
		float y;
		float z;
	};

	//структура вектора
	struct cwVector
	{
		float x;
		float y;
		float z;
	};

	glBindTexture(GL_TEXTURE_2D,Texture[2]);
	
	float x,y;
	freopen("buildings.MIF","r",stdin);
	while (gets(str)!=NULL)
	{
		if (strstr(str,"Region")!=NULL)
		{
			k++;
			glColor3ub(0,83,160);
			gets(str);
			sscanf(str,"%d",&n);
			gets(str);
			sscanf(str,"%f %ff",&x,&y);
			float xGL = x - MAPINFO_WIDTH / 2;
			float yGL = y - MAPINFO_HEIGHT / 2;
				for (int i=0; i<n; ++i)
				{
					gets(str);
					float x,y;
					sscanf(str,"%f %ff",&x,&y);
					float xGL1 = x - MAPINFO_WIDTH / 2;
					float yGL1 = y - MAPINFO_HEIGHT / 2;
					float z=0.5;
					float hh;
					float ll;
					
					switch (Floors[k])
					{
						case 1:
							z=0.05 * MAPINFO_WIDTH / 2;
							hh=1;
							ll=sqrt((xGL1-xGL)*(xGL1-xGL)+(yGL1-yGL)*(yGL1-yGL))*hh / z;
							glBindTexture(GL_TEXTURE_2D,Texture[3]);
							break;
						case 2:
							z=0.1 * MAPINFO_WIDTH / 2;
							hh=2;
							ll=sqrt((xGL1-xGL)*(xGL1-xGL)+(yGL1-yGL)*(yGL1-yGL))*hh / z;
							glBindTexture(GL_TEXTURE_2D,Texture[3]);
							break;
						case 3:
							z=0.15 * MAPINFO_WIDTH / 2;
							hh=3;
							ll=sqrt((xGL1-xGL)*(xGL1-xGL)+(yGL1-yGL)*(yGL1-yGL))*hh / z;
							glBindTexture(GL_TEXTURE_2D,Texture[5]);
							break;
						case 4:
							z=0.2 * MAPINFO_WIDTH / 2;
							hh=4;
							ll=sqrt((xGL1-xGL)*(xGL1-xGL)+(yGL1-yGL)*(yGL1-yGL))*hh / z;
							glBindTexture(GL_TEXTURE_2D,Texture[5]);
							break;
						case 5:
							z=0.25 * MAPINFO_WIDTH / 2;
							hh=5;
							ll=sqrt((xGL1-xGL)*(xGL1-xGL)+(yGL1-yGL)*(yGL1-yGL))*hh / z;
							glBindTexture(GL_TEXTURE_2D,Texture[5]);
							break;
						default:
							break;
					}

					cwPoint M1;
					M1.x = xGL1;
					M1.y = yGL1;
					M1.z = 0;

					cwPoint M2;
					M2.x = xGL;
					M2.y = yGL;
					M2.z = 0;

					cwPoint M3;
					M3.x = xGL;
					M3.y = yGL;
					M3.z = h;

					cwPoint M2M1;
					M2M1.x = M2.x - M1.x;
					M2M1.y = M2.y - M1.y;
					M2M1.z = M2.z - M1.z;

					cwPoint M3M1;
					M3M1.x = M3.x - M1.x;
					M3M1.y = M3.y - M1.y;
					M3M1.z = M3.z - M1.z;

					cwVector normal;
					normal.x = M2M1.y * M3M1.z - M3M1.y * M2M1.z;
					normal.y = M2M1.x * M3M1.z - M3M1.x * M2M1.z;
					normal.z = M2M1.x * M3M1.y - M3M1.x * M2M1.y;

					glBegin(GL_QUADS);
					glNormal3f(-normal.x, -normal.y, normal.z);

					glTexCoord2f(0, 0);
					glVertex3f(-xGL, yGL,z);
					glTexCoord2f(0, hh*2);
					glVertex3f(-xGL, yGL, 0);
					glTexCoord2f(ll, hh*2);
					glVertex3f(-xGL1, yGL1, 0);
					glTexCoord2f(ll, 0);
					glVertex3f(-xGL1, yGL1,z);
					
					
					xGL=xGL1;
					yGL=yGL1;
					glEnd();
				}
		}
	}

	k=-1;
	//крыши домов
	freopen("buildings.MIF","r",stdin);
	while (gets(str)!=NULL)
	{
		if (strstr(str,"Region")!=NULL)
		{
			k++;
			gets(str);
			sscanf(str,"%d",&n);
				for (int i=0; i<n; ++i)
				{
					gets(str);
					float x,y;
					sscanf(str,"%f %ff",&x,&y);
					float xGL = x - MAPINFO_WIDTH / 2;
					float yGL = y - MAPINFO_HEIGHT / 2;
					float z=0.05f * MAPINFO_WIDTH / 2;
					
					switch (Floors[k])
					{
						case 1:
							z=0.05 * MAPINFO_WIDTH / 2;
							glBindTexture(GL_TEXTURE_2D,Texture[1]);
							break;
						case 2:
							z=0.1 * MAPINFO_WIDTH / 2;
							glBindTexture(GL_TEXTURE_2D,Texture[1]);
							break;
						case 3:
							z=0.15 * MAPINFO_WIDTH / 2;
							glBindTexture(GL_TEXTURE_2D,Texture[2]);
							break;
						case 4:
							z=0.2 * MAPINFO_WIDTH / 2;
							glBindTexture(GL_TEXTURE_2D,Texture[2]);
							break;
						case 5:
							z=0.25 * MAPINFO_WIDTH / 2;
							glBindTexture(GL_TEXTURE_2D,Texture[2]);
							break;
						default:
							z=0.1 * MAPINFO_WIDTH / 2;
							glBindTexture(GL_TEXTURE_2D,Texture[2]);
							break;
					}
					glBegin(GL_POLYGON);
						glNormal3f(0,0,1);
						glTexCoord2f(-xGL / 10, yGL / 10);
						glVertex3f(-xGL, yGL, z);
				}
			glEnd();
		 }
	}
	
	//ограждения
	glBindTexture(GL_TEXTURE_2D,Texture[6]);
	freopen("fences.MIF","r",stdin);
	while (gets(str)!=NULL)
	{
		if (strstr(str,"Region")!=NULL)
		{
			k++;
			glColor3ub(0,83,160);
			gets(str);
			sscanf(str,"%d",&n);
			gets(str);
			sscanf(str,"%f %ff",&x,&y);
			float xGL = x - MAPINFO_WIDTH / 2;
			float yGL = y - MAPINFO_HEIGHT / 2;
				for (int i=0; i<n; ++i)
				{
					gets(str);
					float x,y;
					sscanf(str,"%f %ff",&x,&y);
					float xGL1 = x - MAPINFO_WIDTH / 2;
					float yGL1 = y - MAPINFO_HEIGHT / 2;
					float z=0.5;
					float hh;
					float ll;

					z=0.02 * MAPINFO_WIDTH / 2;
					hh=1;
					ll=sqrt((xGL1-xGL)*(xGL1-xGL)+(yGL1-yGL)*(yGL1-yGL))*hh / z;
					glBindTexture(GL_TEXTURE_2D,Texture[6]);

					cwPoint M1;
					M1.x = xGL1;
					M1.y = yGL1;
					M1.z = 0;

					cwPoint M2;
					M2.x = xGL;
					M2.y = yGL;
					M2.z = 0;

					cwPoint M3;
					M3.x = xGL;
					M3.y = yGL;
					M3.z = h;

					cwPoint M2M1;
					M2M1.x = M2.x - M1.x;
					M2M1.y = M2.y - M1.y;
					M2M1.z = M2.z - M1.z;

					cwPoint M3M1;
					M3M1.x = M3.x - M1.x;
					M3M1.y = M3.y - M1.y;
					M3M1.z = M3.z - M1.z;

					cwVector normal;
					normal.x = M2M1.y * M3M1.z - M3M1.y * M2M1.z;
					normal.y = M2M1.x * M3M1.z - M3M1.x * M2M1.z;
					normal.z = M2M1.x * M3M1.y - M3M1.x * M2M1.y;

					glBegin(GL_QUADS);

					glNormal3f(-normal.x, -normal.y, normal.z);

					glTexCoord2f(0, 0);
					glVertex3f(-xGL, yGL,z);
					glTexCoord2f(0, hh*2);
					glVertex3f(-xGL, yGL, 0);
					glTexCoord2f(ll, hh*2);
					glVertex3f(-xGL1, yGL1, 0);
					glTexCoord2f(ll, 0);
					glVertex3f(-xGL1, yGL1,z);					
					
					xGL=xGL1;
					yGL=yGL1;
					glEnd();
				}
			glEnd();
		}
	}
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_GEN_S);      // Запретить сферическое наложение
    glDisable(GL_TEXTURE_GEN_T);      // Запретить сферическое наложение
	//цвет солнца
	glColor3f(1.0,1.0,1.0);
	GLUquadricObj *quadObj1;
	quadObj1 = gluNewQuadric();
	glPushMatrix();
	//смещение осей коррдинат
	glTranslated(LightPosition[0], LightPosition[1], LightPosition[2]);
	gluQuadricDrawStyle(quadObj1, GLU_FILL);
	//свойства солнца
	gluSphere(quadObj1, 2.00, 30, 30);
	gluDeleteQuadric(quadObj1);
	glPopMatrix();
	//разрешение освещения
	glEnable(GL_LIGHTING);
		
    return true;                
}