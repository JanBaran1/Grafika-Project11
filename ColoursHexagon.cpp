#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <wx/colour.h>
#include <wx/control.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/frame.h>
#include <wx/graphics.h>
#include <wx/msgdlg.h>
#include "ColoursHexagon.h"

#define MAX_COLOUR_VALUE 255
#define BACKGROUND_COLOUR 171
#define DEGREE (2 * M_PI / 360)

unsigned int max(unsigned int x, unsigned int y, unsigned int z);

wxBEGIN_EVENT_TABLE(Hexagon, wxPanel)
	EVT_LEFT_DOWN(Hexagon::leftClick)
	EVT_PAINT(Hexagon::drawHexagon)
	EVT_ERASE_BACKGROUND(Hexagon::erase)
wxEND_EVENT_TABLE()

Hexagon::Hexagon(wxPanel* parent) :
wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(m_width, m_height)),
m_parent(parent),
m_windowDC(new wxWindowDC(this)),
m_selectedColour(wxColour(MAX_COLOUR_VALUE, MAX_COLOUR_VALUE, MAX_COLOUR_VALUE))
{
	m_bgImage.Create(m_width, m_height);

	for (int i = 0; i < m_width; i++)
		for (int j = 0; j < m_height; j++)
			m_bgImage.SetRGB(i, j, BACKGROUND_COLOUR, BACKGROUND_COLOUR, BACKGROUND_COLOUR);

}

Hexagon::Hexagon(wxPanel* parent, wxControl* control, wxColour* colour) :
wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(m_width, m_height)),
m_parent(parent),
m_reactControl(control),
m_colour(colour),
m_windowDC(new wxWindowDC(this)){
	m_bgImage.Create(m_width, m_height);

	for (int i = 0; i < m_width; i++)
		for (int j = 0; j < m_height; j++)
			m_bgImage.SetRGB(i, j, BACKGROUND_COLOUR, BACKGROUND_COLOUR, BACKGROUND_COLOUR);
}

void Hexagon::drawHexagon(wxPaintEvent& event) { //do poprawy, ale dopiero, gdy bêdziemy wyœwietlaæ
	wxPaintDC paintDC(this);
	wxMemoryDC memoryDC;

	unsigned int localMaxColourValue = this->getSliderValue();

	double step = (double) localMaxColourValue / 200;

	//red square
	wxImage redSquare;
	redSquare.Create(200, 200);
	redSquare.SetMask(true);

	for (int i = 0; i < 200; i++)
		for (int j = 0; j < 200; j++)
			redSquare.SetRGB(i, j, localMaxColourValue, step * i, step * j);

	redSquare = redSquare.Rotate(-45 * DEGREE, wxPoint(50, 50));
	redSquare = redSquare.Scale(200, 115);

	//green square
	wxImage greenSquare;
	greenSquare.Create(200, 200);
	greenSquare.SetMask(true);

	for (int i = 0; i < 200; i++)
		for (int j = 0; j < 200; j++)
			greenSquare.SetRGB(i, j, step * j, localMaxColourValue, step * i);

	greenSquare = greenSquare.Rotate(-45 * DEGREE, wxPoint(50, 50));
	greenSquare = greenSquare.Scale(200, 115);
	greenSquare = greenSquare.Rotate(-120 * DEGREE, wxPoint(50, 50));

	//blue square
	wxImage blueSquare;
	blueSquare.Create(200, 200);
	blueSquare.SetMask(true);

	for (int i = 0; i < 200; i++)
		for (int j = 0; j < 200; j++)
			blueSquare.SetRGB(i, j, step * i, step * j, localMaxColourValue);

	blueSquare = blueSquare.Rotate(-45 * DEGREE, wxPoint(50, 50));
	blueSquare = blueSquare.Scale(200, 115);
	blueSquare = blueSquare.Rotate(120 * DEGREE, wxPoint(50, 50));

	wxImage cyanLine;
	cyanLine.Create(200, 200);
	cyanLine.SetMask(true);
	double stepLine = (double)localMaxColourValue / 114;
	for (int i = 0; i < 113; i++) {
		cyanLine.SetRGB(99, i, localMaxColourValue - stepLine * i, localMaxColourValue - stepLine, localMaxColourValue);
		cyanLine.SetRGB(100, i, localMaxColourValue - stepLine * i, localMaxColourValue, localMaxColourValue);
		cyanLine.SetRGB(101, i, localMaxColourValue - stepLine * i, localMaxColourValue, localMaxColourValue - stepLine);
		
	}
	//cyanLine.SetRGB(100, 113, 0, localMaxColourValue, localMaxColourValue);

	m_bitmap = wxBitmap(m_bgImage);
	memoryDC.SelectObject(m_bitmap);
	memoryDC.DrawBitmap(wxBitmap(greenSquare), 48, 27, true);
	memoryDC.DrawBitmap(wxBitmap(blueSquare), -49, 27, true);
	memoryDC.DrawBitmap(wxBitmap(redSquare), 0, 1, true);
	memoryDC.DrawBitmap(wxBitmap(cyanLine), 0, 115, true);
	wxGraphicsContext* gCon = wxGraphicsContext::Create(memoryDC);
	if (localMaxColourValue > 75) {
		gCon->SetPen(*wxBLACK_PEN);
		gCon->SetBrush(*wxBLACK_BRUSH);
	}
	else {
		gCon->SetPen(*wxWHITE_PEN);
		gCon->SetBrush(*wxWHITE_BRUSH);
	}
	wxGraphicsPath path = gCon->CreatePath();
	path.AddCircle(m_ptrPosition_x, m_ptrPosition_y, 2);
	path.AddCircle(m_ptrPosition_x, m_ptrPosition_y, 1);
	gCon->FillPath(path);
	delete gCon;
	paintDC.Blit(0, 0, m_width, m_height, &memoryDC, 0, 0, wxCOPY, true);
}

void Hexagon::leftClick(wxMouseEvent& event) { //skoñczone
	int panelX = this->GetScreenPosition().x;
	int panelY = this->GetScreenPosition().y;

	int mouseX = wxGetMousePosition().x - panelX;
	int mouseY = wxGetMousePosition().y - panelY;

	int panelEndX = panelX + m_width;
	int panelEndY = panelY + m_height;

	wxColour colour;
	m_windowDC->GetPixel(mouseX, mouseY, &colour);

	if ((mouseX < panelEndX && mouseY < panelEndY && mouseX != m_ptrPosition_x && mouseY != m_ptrPosition_y)
		&& (colour != wxColour(BACKGROUND_COLOUR, BACKGROUND_COLOUR, BACKGROUND_COLOUR) || (mouseY > 60 && mouseY < 160))) {
		setPointerPosition(mouseX, mouseY);
		m_selectedColour = colour;
		if (m_image.IsOk())
		{
			//m_imageSuwak = wxImage(m_image);
			m_imageSuwak = m_image.Copy();
			ChangeColour(&m_image);
			//m_imageSuwak = m_image.Copy();
			
			
		}
		//m_ChosenColour = m_selectedColour;


		/*if (m_reactControl != nullptr) {
			m_colour->SetRGB(colour.GetRGB());
			m_reactControl->SetForegroundColour(colour);
			m_reactControl->Refresh();
		}*/

		//m_parent->Refresh();
		this->Refresh();
	}
}

void Hexagon::ChangeColour(wxImage* Image)
{
	if (m_ChosenColour.IsOk())
	{
		auto data = Image->GetData();
		int w = Image->GetWidth();
		int h = Image->GetHeight();
		double x = suwak;
		double red = 0;
		double green = 0;
		double blue = 0;
		int r, g, b;
		double y1;
		double y2;
		double y3;	
		double d1;
		double d2;
		double d3;
		double ch1;
		double ch2;
		double ch3;
		double s1 ;
		double s2 ;
		double s3 ;
		WCHAR buffer[256];
		int flaga = 1;
		RGBtoHSL(m_ChosenColour.Red(), m_ChosenColour.Green(), m_ChosenColour.Blue(), ch1, ch2, ch3);
		RGBtoHSL(m_selectedColour.Red(), m_selectedColour.Green(), m_selectedColour.Blue(), s1, s2, s3);
		
		
		for (int i = 0; i < 3 * w * h; i += 3)
			{
				RGBtoHSL(data[i], data[i + 1], data[i + 2], d1, d2, d3);
				y1 = fabs(ch1 - d1);
				//y2 = fabs(ch2 - d2);
				//y3 = fabs(ch3 - d3);
				flaga = 1;
				if (fabs(d1 - ch1) < 1)
				{
					if (is_checked == true)
					{
						d1 = s1;
						HSLtoRGB(red, green, blue, d1, d2, d3);
						data[i] = red;
						data[i + 1] = green;
						data[i + 2] = blue;
						flaga = 0;
					}
					if (is_checked == false)
					{
						y1 = 2.;
						flaga = 1;
					}
				}  

				
				if(flaga == 1)
				{
					if (fabs(y1 - 1) < 1)
						y1 = 2.;

					if(fabs(d1 - ch1) <  suwak2)
					{
						if (d1 < ch1)
						{

							d1 = (1 - suwak / 100.) * d1 + suwak / 100. * (s1 + fabs(d1 - ch1));
						}
							
						else
						{
							d1 = (1 - suwak / 100.) * d1 + suwak / 100. * (s1 - fabs(d1 - ch1));
						}
							
						if (d1 > 360) d1 -= 360;
					}

					else
					{
						d1 = d1 - fabs(s1 - ch1)   * suwak / 100. * 1. / (y1);
						if (d1 < 0)
							d1 += 360;
					}
					
					HSLtoRGB(red, green, blue, d1, d2, d3);
					data[i] = red;
					data[i + 1] = green;
					data[i + 2] = blue;
					
					/*if (i % 1000 == 0)
						{
							//_swprintf(buffer, L"RGB(%d,%d,%d): y1=%f, y2=%f, y3=%f;  red=%d, green=%d, blue=%d\n", m_ChosenColour.Red(), m_ChosenColour.Green(), m_ChosenColour.Blue(), y1, y2, y3, red, green, blue);
							_swprintf(buffer, L"s=(%d, %d, %d), ch = (%d, %d, %d), pixiel wchodzacy = (%d, %d, %d), pixel wychodzacy = (%d, %d, %d), hsl = (%.1f, %.1f, %.1f)\n", m_selectedColour.Red(), m_selectedColour.Green(), m_selectedColour.Blue(), m_ChosenColour.Red(), m_ChosenColour.Green(), m_ChosenColour.Blue(), r, g, b, data[i], data[i + 1], data[i + 2], d1, d2, d3);
							OutputDebugString(buffer);
						}*/					 
					
				}
		}
	
				
		
	}
}
double maxk(double r, double g, double b)
{
	double m = r;
	if (g > m)
		m = g;
	if (b > m)
		m = b;
	return m;
}
double mink(double r, double g, double b)
{
	double m = r;
	if (g < m)
		m = g;
	if (b < m)
		m = b;
	return m;
}
void RGBtoHSL(double R, double G, double B, double &H, double &S, double &L)
{
	
	double dr = R / 255.;
	double dg = G / 255.;
	double db = B / 255.;
	double Cmax = maxk(dr,dg,db);
	double Cmin = mink(dr, dg, db);
	double delta = Cmax - Cmin;
	L = (Cmax + Cmin) * 50;
	if (fabs(delta) < 1e-6)
	{
		H = 0;
		S = 0;
		return;
	}
	/*else if (L < 50)
	{
		S = 100 * delta / (Cmax + Cmin);
	}
	else
	{
		S = 100 * delta / (2.0 - Cmax - Cmin);
	} */
	else
	{
		S = 100 * delta / (1 - fabs(L / 50. - 1));
	}
	if (Cmax == dr)
		H = 60 * (dg - db) / delta;
	else if(Cmax == dg)
		H = 60 * (db - dr) / delta + 120;
	else
		H = 60 * (dr - dg) / delta + 240;
	if (H < 0)
		H += 360;
	int z;
}

void HSLtoRGB(double &R, double &G, double &B, double H, double S, double L)
{
	double C = (1 - fabs(L / 50. - 1)) * S / 100.;
	double X = C * (1 - fabs(std::fmod(H / 60., 2) - 1));
	double m = L / 100. - C / 2.;
	double r, g, b;
	if (H >= 0 && H < 60)
	{
		r = C;
		g = X;
		b = 0;
	}
	else if (H >= 60 && H < 120)
	{
		r = X;
		g = C;
		b = 0;
	}
	else if (H >= 120 && H < 180) 
	{
		r = 0;
		g = C;
		b = X;
	}
	else if (H >= 180 && H < 240) 
	{
		r = 0;
		g = X;
		b = C;
	}
	else if (H >= 240 && H < 300)
	{
		r = X;
		g = 0;
		b = C;
	}
	else
	{
		r = C;
		g = 0;
		b = X;
	}
	R = (r + m) * 255.;
	G = (g + m) * 255.;
	B = (b + m) * 255.;
	
}
 
void Hexagon::erase(wxEraseEvent& event) { //skoñczone
	//event.Skip();
}

inline wxColour Hexagon::getSelectedColour() { //skoñczone
	return m_selectedColour;
}

void Hexagon::setSelectedColour(wxColour& sear_colour) { //skoñczone
	wxImage image = m_bitmap.ConvertToImage();
	wxColour curr_colour;
	/*unsigned int hexagonNumber = max(sear_colour.Red(), sear_colour.Green(), sear_colour.Blue());
	if (hexagonNumber < 1)
		hexagonNumber = 1;
	this->setSliderValue(hexagonNumber);*/
	if (sear_colour == wxColour(BACKGROUND_COLOUR, BACKGROUND_COLOUR, BACKGROUND_COLOUR)) {
		setPointerPosition(m_width / 2, m_height / 2 - 18);
		m_selectedColour = sear_colour;
		this->Refresh();
		return;
	}
	if (this->getSelectedColour() != sear_colour) {
		for (int multi = 0; multi < 4; multi++) {
			for (int i = 0; i < m_width; i++) {
				for (int j = 0; j < m_height; j++) {
					curr_colour.Set(image.GetRed(i, j), image.GetGreen(i, j), image.GetBlue(i, j));
					if (curr_colour == sear_colour
						|| ((abs(curr_colour.Red() - sear_colour.Red()) <= (10 * multi))
							&& (abs(curr_colour.Green() - sear_colour.Green()) <= (10 * multi))
							&& (abs(curr_colour.Blue() - sear_colour.Blue()) <= (10 * multi)))) {
						setPointerPosition(i, j);
						m_selectedColour = sear_colour;
						this->Refresh();
						return;
					}
				}
			}
		}
	}
}

void Hexagon::setPointerPosition(int pos_x, int pos_y) { //skoñczone
	m_ptrPosition_x = pos_x;
	m_ptrPosition_y = pos_y;
}

unsigned int Hexagon::getSliderValue() {
	return m_sliderValue;
}

void Hexagon::setSliderValue(unsigned int sliderValue) {
	if (sliderValue < 1)
		sliderValue = 1;
	m_sliderValue = sliderValue;
	this->Refresh();
}
inline double Hexagon::getSuwak() {
	return suwak;
}

void Hexagon::setSuwak(double s) {
	suwak = s;
	this->Refresh();
}

unsigned int max(unsigned int x, unsigned int y, unsigned int z) {
	if (x > y)
		if (x > z)
			return x;
		else
			return z;
	else
		if (y > z)
			return y;
		else z;
}