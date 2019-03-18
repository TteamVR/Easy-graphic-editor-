
#include       "C:\dllBridge\Lego\WinMain.h"  
using namespace Lego;

#include <cmath>
#include <algorithm>
#include <vector>
#include <time.h>
using namespace std;

#define FieldX 24
#define FieldY 24

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

int CNfB[10] = {Black, White, Red, Pink,
				Orange, Yellow,   Green,
				Blue, Violet,     Gray};

const int FieldColor = RGB(62, 58, 63);

int Type = 1;

int ColorAuto = White;			
int CellCountX;
int CellCountY;

int PenSize = 1;

int Forms = 1;
int OldForms = 1;
int SizeCells = 6;
int Color;

bool TurnDrawing;
bool Cells[67][67];

Button ColorBtn[10];
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

struct MemoryofCells
{
	int x;
	int y;	
} MfCArray[67][67]; 

void Control()
{	
	if(Key_Pressed == 117)
	{
		Forms++;
		Key_Pressed = 0;
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
	
void Reset()
{	
	for(int a = 0; a < 20; a++)
		for(int b = 0; b < 20; b++)	
			Cells[a][b] = 0;			
}

void CheckCells()
{
	for(int a = 0; a < 67; a++)	
		for(int b = 0; b <  67; b++)
		{
			if(Cells[a][b] > 0)
				Square(MfCArray[a][b].x, MfCArray[a][b].x, ColorAuto, 0, 0);	
			if(Cells[a][b] < 1)
				Square(MfCArray[a][b].x, MfCArray[a][b].x, Black, 0, 0);
		}	
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

void DrawingBox(int x, int y)
{
	PushProcessing();
	Control();
	
	////////////////// Drawing of field //////////////////
 
	if(Forms % 2 != 0 && Forms != OldForms)
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

	if(Forms % 2 == 0 && Forms != OldForms)
	{
		Square(FieldX, FieldY, Black, 450, 450);
		OldForms = Forms;
	}
	////////////////// Drawing of field //////////////////
	
	
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
								
					if(Timer_CLK == 10)
					{
						MfCArray[a][b].x = Fx;
						MfCArray[a][b].y = Fy;
					}
					
					if(Type == 1)
					{	
						//...........Simple.point...........// 
						
						if(LMouseBtn)				
							if(xMFix == x && yMFix == y)  
							{
								Cells[a][b] += Color;	
								Square(Fx, Fy, ColorAuto, 0, 0);
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
								Cells[a][b]++;	
								Square(Fx, Fy, ColorAuto, 0, 0);
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
	DrawingBox(FieldX, FieldY);
}








//     Эта функция вызывается из оконной процедуры WndProc(), если пользователь выбрал:
// 1)  Какой-либо пункт меню.
// 2)  Нажал кнопку.	

////////////////////////////////////////////////////            
void ScanButtonsAndMenuItems(int item)            //                  
{
	


 
}





