
#include       "C:\dllBridge\Lego\WinMain.h"  
using namespace Lego;

#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

#define FieldX 24
#define FieldY 24

HPEN pen;
HBRUSH brush;

const int Red    = RGB(255, 51, 51);
const int Blue   = RGB(0, 102, 204);
const int Orange = RGB(255, 128, 0);
const int Green  = RGB(0, 204, 0);
const int Gray   = RGB(96, 96, 96);
const int Violet = RGB(153, 51, 255);
const int Pink   = RGB(255, 0, 127);
const int Black  = RGB(0, 0, 0);

const int FieldColor = RGB(62, 58, 63);

int Type = 1;

int ColorAuto = Violet;			
int CellCountX;
int CellCountY;

int SizeCells = 6;
int Color;

bool TurnDrawing;
bool Cells[67][67];

Button ColorBtn[10];

void ColorButton()
{	
	char NameImg[100];	
	char CharI;
		
	Print(0, 430, "Color:");
	
	for(int i = 0; i < 10; i++)
	{	
		sprintf(NameImg, "%s %s %s", "ColorForButton\\", CharI, ".bmp");
		ColorBtn[i].CreateWithPic(NameImg, 80 + (i * 35), 430, 30, 30);	
	}
}

void Square(int x, int y, int Color)
{	
	hdc = GetDC(hWnd);

	brush = CreateSolidBrush(Color);	
	SelectObject(hdc, brush);	
	
	Rectangle(hdc, x, y, x + SizeCells, y + SizeCells);	
	
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

}

void DrawingBox(int x, int y)
{
	////////////////// Drawing of field //////////////////
	
	if(ColorBtn[0].Press())
		ColorAuto = Black;

	if(ColorBtn[1].Press())
		ColorAuto = Gray;

	if(ColorBtn[2].Press())
		ColorAuto = Red;

	if(ColorBtn[3].Press())
		ColorAuto = Blue;

	if(ColorBtn[4].Press())
		ColorAuto = Orange;

	if(ColorBtn[5].Press())
		ColorAuto = Green;

	if(ColorBtn[6].Press())
		ColorAuto = Violet;

	if(ColorBtn[7].Press())
		ColorAuto = Black;

	if(ColorBtn[8].Press())
		ColorAuto = Black;

	if(ColorBtn[9].Press())
		ColorAuto = Black;
	
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
	
	////////////////// Drawing of field //////////////////
	
	
	////////////////// Cell survey //////////////////
	
	int Fx = FieldX, 
		Fy = FieldY;
	
	for(int a = 0; a < 67; a++)
	{	
		for(int b = 0; b <  67; b++)
		{	
			for(int x = Fx; x < (Fx + SizeCells); x++)
				for(int y = Fy; y < (Fy + SizeCells); y++)
				{	
					if(Type == 1)
					{
						//...........Simple.point...........// 
						
						if(LMouseBtn)				
							if(xMFix == x && yMFix == y)  
							{	
								Cells[a][b] += Color;	
								Square(Fx, Fy, ColorAuto);
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
								Square(Fx, Fy, ColorAuto);
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
	ColorButton();
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

/*
#include       "C:\dllBridge\Lego\WinMain.h"  
using namespace Lego;

#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

#define FieldX 25
#define FieldY 25

HPEN pen;
HBRUSH brush;

int ColorTurn;
const int Red   = RGB(255, 51, 51);
const int Blue  = RGB(0, 102, 204);
int ColorAuto;

bool Cells[10][10];

void Turn()
{
	if(ColorTurn % 2 == 0)
		ColorAuto = Red;
	else
		ColorAuto = Blue;
}

void Square(int x, int y, int Color)
{	
	hdc = GetDC(hWnd);

	brush = CreateSolidBrush(Color);	
	SelectObject(hdc, brush);	
	
	Rectangle(hdc, x, y, x + 40, y + 40);	
	
	ReleaseDC(hWnd,hdc);
}

void DrawingBox(int x, int y)
{	
	Turn();
	
	////////////////// Drawing of field //////////////////

	hdc = GetDC(hWnd);
			
	pen = CreatePen(PS_SOLID , 1 , RGB(128, 128, 128));	
	SelectObject (hdc, pen);								
	
	for(int i = 0; i < 11; i++)
	{		

		MoveToEx(hdc, x, y + (i * 40), NULL);  // horizontal	
		LineTo(hdc, x + 400, y + (i * 40));
		
		MoveToEx(hdc, x  + (i * 40), y, NULL); // vertical 
		LineTo(hdc, x + (i * 40), y + 400);
	}
	
	ReleaseDC(hWnd,hdc);
	
	////////////////// Drawing of field //////////////////
	
	
	////////////////// Cell survey //////////////////
	
	int Fx = FieldX, 
		Fy = FieldY;
	
	for(int a = 0; a < 10; a++)
	{	
		for(int b = 0; b < 10; b++)
		{	
			for(int x = Fx; x < (Fx + 40); x++)
				for(int y = Fy; y < (Fy + 40); y++)
					if(xMFix == x && yMFix == y)
					{	
						if(LMouseBtn)
						{	
							Cells[a][b]++;
							Square(Fx, Fy, ColorAuto);
							LMouseBtn = 0;
						}
						
					}
			Fx += 40;
		}	
		Fy += 40;
		Fx = FieldX;
	}
	////////////////// Cell survey //////////////////
		
}	

void INIT()
{	
	DrawingBox(FieldX, FieldY);
}

void START()
{ 	
	if(LMouseBtn)
		DrawingBox(FieldX, FieldY);
}	

*/




