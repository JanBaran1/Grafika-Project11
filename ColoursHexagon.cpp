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
		int red = 0;
		int green = 0;
		int blue = 0;

		for (int i = 0; i < 3 * w * h; i += 3)
		{
			if (m_ChosenColour.Red() == data[i] && m_ChosenColour.Green() == data[i + 1] && m_ChosenColour.Blue() == data[i + 2])
			{
				data[i] =	m_selectedColour.Red() ;
				data[i + 1] = m_selectedColour.Green() ;
				data[i + 2] = m_selectedColour.Blue() ;
			}

			else
			{
				
				
				red = data[i] * (1 + x * 1. / (fabs(m_selectedColour.Red() - m_ChosenColour.Red())));
				green = data[i + 1] * (1 + x * 1. / (fabs(m_selectedColour.Green() - m_ChosenColour.Green())));
				blue = data[i + 2] * (1 + x * 1. / (fabs(m_selectedColour.Blue() - m_ChosenColour.Blue())));
				if (red > 255)
					red = 255;
				if (green > 255)
					green = 255;
				if (blue > 255)
					blue = 255;

				//data[i] = data[i] * (1 + x * 1. / (fabs(m_selectedColour.Red() - m_ChosenColour.Red()) ));				
				//data[i + 1] = data[i + 1] * (1 + x * 1. / (fabs(m_selectedColour.Green() - m_ChosenColour.Green()))) ;				
				//data[i + 2] = data[i + 2] * (1 + x * 1. / (fabs(m_selectedColour.Blue() - m_ChosenColour.Blue()))) ;
				data[i] = red;
				data[i + 1] = green;
				data[i + 2] = blue;
			}
		}
	}
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
	unsigned int hexagonNumber = max(sear_colour.Red(), sear_colour.Green(), sear_colour.Blue());
	if (hexagonNumber < 1)
		hexagonNumber = 1;
	this->setSliderValue(hexagonNumber);
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