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

	unsigned int localMaxColourValue = 255; // = getSliderValue();

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


	m_bitmap = wxBitmap(m_bgImage);
	memoryDC.SelectObject(m_bitmap);
	memoryDC.DrawBitmap(wxBitmap(redSquare), 0, 0, true);
	memoryDC.DrawBitmap(wxBitmap(greenSquare), 49, 27, true);
	memoryDC.DrawBitmap(wxBitmap(blueSquare), -49, 27, true);
	wxGraphicsContext* gCon = wxGraphicsContext::Create(memoryDC);
	gCon->SetPen(*wxBLACK_PEN);
	gCon->SetBrush(*wxBLACK_BRUSH);
	wxGraphicsPath path = gCon->CreatePath();
	path.AddCircle(m_ptrPosition_x, m_ptrPosition_y, 2);
	path.AddCircle(m_ptrPosition_x, m_ptrPosition_y, 1);
	gCon->FillPath(path);
	delete gCon;
	paintDC.Blit(0, 0, m_width, m_height, &memoryDC, 0, 0, wxCOPY, true);
}

void Hexagon::leftClick(wxMouseEvent& event) { //do poprawy
	//poprawiæ, ¿eby nie mruga³
	int panelX = this->GetScreenPosition().x;
	int panelY = this->GetScreenPosition().y;

	int mouseX = wxGetMousePosition().x - panelX;
	int mouseY = wxGetMousePosition().y - panelY;

	int panelEndX = panelX + m_width;
	int panelEndY = panelY + m_height;

	wxColour colour;
	m_windowDC->GetPixel(mouseX, mouseY, &colour);

	//if jest do poprawy, ¿eby nie ³apaæ t³a
	if ((mouseX < panelEndX && mouseY < panelEndY && mouseX != m_ptrPosition_x && mouseY != m_ptrPosition_y)
		&& (colour != wxColour(BACKGROUND_COLOUR, BACKGROUND_COLOUR, BACKGROUND_COLOUR) || (mouseY > 60 && mouseY < 160))) {
		setPointerPosition(mouseX, mouseY);
		m_selectedColour = colour;
		ChangeColour(&m_image);
		m_ChosenColour = m_selectedColour;


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
	auto data = Image->GetData();
	int w = Image->GetWidth();
	int h = Image->GetHeight();

	for (int i = 0; i < 3 * w * h; i += 3)
	{
		if (m_ChosenColour.Red() == data[i] && m_ChosenColour.Green() == data[i + 1] && m_ChosenColour.Blue() == data[i + 2])
		{
			data[i] = getSelectedColour().Red();
			data[i + 1] = getSelectedColour().Green();
			data[i + 2] = getSelectedColour().Blue();
		}
	}
}

void Hexagon::erase(wxEraseEvent& event) {
	//event.Skip();
}

wxColour Hexagon::getSelectedColour() { //skoñczone
	return m_selectedColour;
}

void Hexagon::setSelectedColour(const wxColour& sear_colour) { //skoñczone
	wxImage image = m_bitmap.ConvertToImage();
	wxColour curr_colour;
	unsigned int hexagonNumber = max(sear_colour.Red(), sear_colour.Green(), sear_colour.Blue());
	// this->setSliderValue(hexagonNumber);
	if (this->getSelectedColour() != sear_colour) {
		for (int multi = 1; multi < 11; multi++) { // skoro nie ma skalowania to byæ mo¿e ten for nie bêdzie potrzeby
			for (int i = 0; i < m_width; i++) {
				for (int j = 0; j < m_height; j++) {
					curr_colour.Set(image.GetRed(i, j), image.GetGreen(i, j), image.GetBlue(i, j));
					if (curr_colour == sear_colour
						|| (abs(curr_colour.Red() - sear_colour.Red()) < (10 * multi)
							&& (abs(curr_colour.Green() - sear_colour.Green())) < (10 * multi)
							&& (abs(curr_colour.Blue() - sear_colour.Blue())) < (10 * multi))) {
						setPointerPosition(i, j);
						m_selectedColour = sear_colour;
						this->Refresh();
						break;
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