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
wxEND_EVENT_TABLE()

Hexagon::Hexagon(wxPanel* parent) :
wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(m_width, m_height)),
m_parent(parent),
m_windowDC(new wxWindowDC(this)){

	m_image.Create(m_width, m_height);

	for (int i = 0; i < m_width; i++)
		for (int j = 0; j < m_height; j++)
			m_image.SetRGB(i, j, BACKGROUND_COLOUR, BACKGROUND_COLOUR, BACKGROUND_COLOUR);

}

Hexagon::Hexagon(wxPanel* parent, wxControl* control, wxColour* colour) :
wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(m_width, m_height)),
m_parent(parent),
m_reactControl(control),
m_colour(colour),
m_windowDC(new wxWindowDC(this)){
	m_image.Create(m_width, m_height);

	for (int i = 0; i < m_width; i++)
		for (int j = 0; j < m_height; j++)
			m_image.SetRGB(i, j, BACKGROUND_COLOUR, BACKGROUND_COLOUR, BACKGROUND_COLOUR);
}

void Hexagon::drawHexagon(wxPaintEvent& event) { //do poprawy, ale dopiero, gdy bêdziemy wyœwietlaæ
	wxPaintDC paintDC(this);
	wxMemoryDC memoryDC;

	double step = (double) MAX_COLOUR_VALUE / 200;

	//red square
	wxImage redSquare;
	redSquare.Create(200, 200);
	redSquare.SetMask(true);

	for (int i = 0; i < 200; i++)
		for (int j = 0; j < 200; j++)
			redSquare.SetRGB(i, j, MAX_COLOUR_VALUE, step * i, step * j);

	//green square
	wxImage greenSquare;
	greenSquare.Create(200, 200);
	greenSquare.SetMask(true);

	for (int i = 0; i < 200; i++)
		for (int j = 0; j < 200; j++)
			greenSquare.SetRGB(i, j, step * j, MAX_COLOUR_VALUE, step * i);

	//blue square
	wxImage blueSquare;
	blueSquare.Create(200, 200);
	blueSquare.SetMask(true);

	for (int i = 0; i < 200; i++)
		for (int j = 0; j < 200; j++)
			blueSquare.SetRGB(i, j, step * i, step * j, MAX_COLOUR_VALUE);

	//obroty i skalowanie do poprawy, ¿eby by³y odpowiednie wartoœci
	redSquare = redSquare.Rotate(-45 * DEGREE, wxPoint(50, 50));
	redSquare = redSquare.Scale(200, 115);

	greenSquare = greenSquare.Rotate(-45 * DEGREE, wxPoint(50, 50));
	greenSquare = greenSquare.Scale(200, 115);
	greenSquare = greenSquare.Rotate(-120 * DEGREE, wxPoint(50, 50));

	blueSquare = blueSquare.Rotate(-45 * DEGREE, wxPoint(50, 50));
	blueSquare = blueSquare.Scale(200, 115);
	blueSquare = blueSquare.Rotate(120 * DEGREE, wxPoint(50, 50));

	m_bitmap = wxBitmap(m_image);
	memoryDC.SelectObject(m_bitmap);
	memoryDC.DrawBitmap(wxBitmap(redSquare), 0, 0, true);
	memoryDC.DrawBitmap(wxBitmap(greenSquare), 49, 27, true);
	memoryDC.DrawBitmap(wxBitmap(blueSquare), -49, 27, true);
	paintDC.Blit(0, 0, m_width, m_height, &memoryDC, 0, 0, wxCOPY, true);
}

void Hexagon::leftClick(wxMouseEvent& event) { //do poprawy
	int mouseX = wxGetMousePosition().x - this->GetScreenPosition().x;
	int mouseY = wxGetMousePosition().y - this->GetScreenPosition().y;

	int windowX = this->GetPosition().x;
	int windowY = this->GetPosition().y;

	int hexagonEndX = windowX + m_width;
	int hexagonEndY = windowY + m_height;

	//if jest do poprawy, ¿eby nie ³apaæ t³a
	if (mouseX < hexagonEndX && mouseY < hexagonEndY && mouseX != m_ptrPosition_x && mouseY != m_ptrPosition_y) {
		setPointerPosition(mouseX, mouseY);

		wxColour colour;
		m_windowDC->GetPixel(mouseX, mouseY, &colour);
		m_selectedColour = colour;

		if (m_reactControl != nullptr) {
			m_colour->SetRGB(colour.GetRGB());
			m_reactControl->SetForegroundColour(colour);
			m_reactControl->Refresh();
		}

		//m_parent->Refresh();
	}
}

wxColour Hexagon::getSelectedColour() { //skoñczone
	return m_selectedColour;
}

void Hexagon::setSelectedColour(const wxColour& sear_colour) { //do zrobienia
	wxImage image = m_bitmap.ConvertToImage();
	wxColour curr_colour;
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