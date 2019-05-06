
#include       "C:\dllBridge\Lego\WinMain.h"  
using namespace Lego;

#include <cmath>
#include <algorithm>
#include <vector>
#include <time.h>
using namespace std;

#define FieldX 24
#define FieldY 24

/*#define
#define
#define
#define*/
#define Pencil 6
#define Eraser 7
#define Sheet  8
#define Grid   9

HPEN pen;
HBRUSH brush;

const int Red    = RGB(255,  51,  51);
const int Blue   = RGB(  0, 102, 204);
const int Orange = RGB(255, 128,   0);
const int Green  = RGB(  0, 204,   0);
const int Gray   = RGB( 96,  96,  96);
const int Violet = RGB(153,  51, 255);
const int Pink   = RGB(255,   0, 127);
const int Yellow = RGB(255, 255,  51);
const int Black  = RGB(  0,   0,   0);
const int White  = RGB(255, 255, 255);

int CNfB[11] = {Black, White, Red, Pink,
				Orange, Yellow,   Green,
				Blue, Violet,     Gray};

const int FieldColor = RGB(62, 58, 63);

int Type = 1;

int ColorAuto = White;			
int CellCountX;
int CellCountY;

int PenSize = 1;

int Forms = 0;
int OldForms = 1;
int SizeCells = 6;
int Color;

bool TurnDrawing;

int Cells[67][67];
int OldCells[67][67];

Button ColorBtn[10];
Button ControlBtn[10];
Button RandomColor;

void CreateColorButton()
{	
	char NameImg[50];

	RandomColor.Create("Random", 25, 431, 50, 30);

	for(int i = 0; i < 10; i++)
	{		
		sprintf(NameImg, "%s%d%s", "ColorForButton\\", i, ".bmp");
		ColorBtn[i].CreateWithPic(NameImg, 80 + (i * 35), 431, 30, 30);	
	}
}

void CreateControlButtons()
{
	char NameImg[50];
	
	for(int i = 0; i < 10; i++)
	{		
		sprintf(NameImg, "%s%d%s", "IconforButton\\", i, ".bmp");
		ControlBtn[i].CreateWithPic(NameImg, 435, 25 + (i * 44), 40, 40);	
	}	
}

void Square(int x, int y, int Color, int sizeX, int sizeY)
{	
	hdc = GetDC(hWnd);

	brush = CreateSolidBrush(Color);	
	SelectObject(hdc, brush);	
	
	if(sizeX == 0 && sizeY == 0)
		Rectangle(hdc, x, y, x + SizeCells, y + SizeCells);	
	else
		Rectangle(hdc, x, y, x + sizeX, y + sizeY);
		
	ReleaseDC(hWnd,hdc);
}
	
struct MemoryofCells
{
	int x;
	int y;	
}MoC[67][67];

void ChekCells()
{	
	for(int a = 0; a < 67; a++) 
		for(int b = 0; b < 67; b++)
			if(Cells[a][b] != OldCells[a][b])
			{	
				Square(MoC[a][b].x, MoC[a][b].y, CNfB[Cells[a][b]] , 0, 0);
				OldCells[a][b] = Cells[a][b];
			}
}

void Reset()
{	
	for(int a = 0; a < 20; a++)
		for(int b = 0; b < 20; b++)	
			Cells[a][b] = 0;
			
	Square(FieldX, FieldY, Black, 450, 450);
}

void DrawingMesh(int x, int y)
{
	hdc = GetDC(hWnd);
					
	pen = CreatePen(PS_SOLID , 1 , FieldColor);	
	SelectObject (hdc, pen);								

	for(int i = 0; i < 67 + 1; i++)
	{	
		MoveToEx(hdc, x, y + (i * SizeCells), NULL);  // horizontal	
		LineTo(hdc, x + 403, y + (i * SizeCells));
		
		MoveToEx(hdc, x  + (i * SizeCells), y, NULL); // vertical 
		LineTo(hdc, x + (i * SizeCells), y + 403);
	}
	
	ReleaseDC(hWnd,hdc);
	OldForms = Forms;	
}

void Boundaries(int x, int y)
{	
	x = x - 2;
	y = y - 2;
	
	hdc = GetDC(hWnd);
					
	pen = CreatePen(PS_SOLID , 1 , FieldColor);	
	SelectObject (hdc, pen);	
	
	for(int i = 0; i < 2; i++)
	{	
		MoveToEx(hdc, x + (i * 406), y, NULL);  // horizontal	
		LineTo(hdc, x + (i * 406), y + 407);
			
		MoveToEx(hdc, x , y + (i * 406), NULL);  // vertical 	
		LineTo(hdc, x + 407, y + (i * 406));
	}
		
	ReleaseDC(hWnd,hdc);
}

void Control()
{	
	if(Key_Pressed == 117 || ControlBtn[9].Press()) // Forms
	{
		Forms++;
		Key_Pressed = 0;
	}
	
	if(Key_Pressed == 116 || ControlBtn[8].Press()) // ResetPicture
	{
		Reset();
		
		if(Forms % 2 != 0)
			DrawingMesh(FieldX, FieldY);
		Key_Pressed = 0;
	}	
	
	if(ControlBtn[Pencil].Press()) // Pencil
		Type = 1;
		
	if(ControlBtn[Eraser].Press()) // Eraser
		Type = 2;
}

void PushProcessing()
{	
	srand(time(0));
	
	//..........Color..........//
	 
	if(RandomColor.Press())
		ColorAuto = CNfB[rand()%10];
	
	for(int i = 0; i < 10; i++)
		if(ColorBtn[i].Press())
			ColorAuto = CNfB[i];

	//..........Color..........//
	
}
void UpdateField(int x, int y)
{	
	////////////////// Drawing of field //////////////////
 
	if(Forms % 2 != 0)
	{
		DrawingMesh(x, y);
	}
	if(Forms % 2 == 0 && Forms != OldForms)
	{	
		Square(FieldX, FieldY, Black, 450, 450);
		OldForms = Forms;
	}
	////////////////// Drawing of field //////////////////
}

void DrawingBox(int x, int y)
{
	PushProcessing();
	Control();
	
	if(Timer_CLK > 1)
		ChekCells();
	
	UpdateField(x, y);
	
	////////////////// Cell survey //////////////////
	
	int Fx = FieldX, 
		Fy = FieldY;
	
	for(int a = 0; a < 67; a++)
	{	
		for(int b = 0; b < 67; b++)
		{	
			for(int x = Fx; x < (Fx + SizeCells); x++)
				for(int y = Fy; y < (Fy + SizeCells); y++)
				{	
					if(Timer_CLK < 3)
					{
						MoC[a][b].x = Fx;
						MoC[a][b].y = Fy; 
					}
					
					if(Type == 1 || Type == 2)
					{	
						//...........Simple.point...........// 
						
						if(LMouseBtn)				
							if(xMFix == x && yMFix == y)  
							{
								if(Type == 1)
								{
									Cells[a][b] = Color;
									Square(Fx, Fy, ColorAuto, 0, 0);
								}
								
								if(Type == 2)
								{
									Cells[a][b] = 0;	
									Square(Fx, Fy, Black, 0, 0);
								}
								LMouseBtn = 0;
							}	
							
						//...........Simple.point...........// 
						
						
						//...........Oblong.point...........// 
							
						if(LMouseBtn)              
							TurnDrawing = true;
						
						if(xMove > 427 || yMove > 427 || xMove < 23 || yMove < 23)
							TurnDrawing = false;
							
						if(xMove == x && yMove == y)         
						{
							if(TurnDrawing)
							{	
								if(Type == 1)
								{
									Cells[a][b] = Color;	
									Square(Fx, Fy, ColorAuto, 0, 0);
								}
								
								if(Type == 2)
								{
									Cells[a][b] = 0;
									Square(Fx, Fy, Black, 0, 0);
								}
							}
							
							if(LMouseBtnUp)
							{
								TurnDrawing = false;
								LMouseBtn = 0;
								LMouseBtnUp = 0;
							}
						}
							
						//...........Oblong.point...........// 
					}
					
				}
				
			Fx += SizeCells;
		}	
		Fy += SizeCells;
		Fx = FieldX;
	}
		////////////////// Cell survey //////////////////
			
}	

void DrawingUpdate()
{
	DrawingBox(FieldX, FieldY);
}

void INIT()
{			
	CreateControlButtons();
	CreateColorButton();
	SetTimer(hWnd, 3,  1, (TIMERPROC) DrawingUpdate);
}

void START()
{ 
	
}	



//			                                                                   (   )       
//													                          (    )
//													                           (    )
//													                          (    )
//													                            )  )
//													                           (  (                  /\
//													                            (_)                 /  \  /\
//													                    ________[_]________      /\/    \/  \
//													           /\      /\        ______    \    /   /\/\  /\/\
//													          /  \    //_\       \    /\    \  /\/\/    \/    \
//													   /\    / /\/\  //___\       \__/  \    \/
//													  /  \  /\/    \//_____\       \ |[]|     \
//													 /\/\/\/       //_______\       \|__|      \
//													/      \      /XXXXXXXXXX\                  \
//													        \    /_I_II  I__I_\__________________\
//													               I_I|  I__I_____[]_|_[]_____I
//													               I_II  I__I_____[]_|_[]_____I
//													               I II__I  I     XXXXXXX     I
//					                                             E-mail:    dllbridge@gmail.com







//     В этой функции Вы можете рисовать. Контекст уже захвачен функцией BeginPaint() и будет освобождён автоматически.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////     void mainPAINT()    /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mainPAINT()
{	
	
	Boundaries(FieldX, FieldY);	
	DrawingBox(FieldX, FieldY);
}








//     Эта функция вызывается из оконной процедуры WndProc(), если пользователь выбрал:
// 1)  Какой-либо пункт меню.
// 2)  Нажал кнопку.	

////////////////////////////////////////////////////            
void ScanButtonsAndMenuItems(int item)            //                  
{
	


 
}





