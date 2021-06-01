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


/*BEGIN_EVENT_TABLE(ColorsHexagon, wxPanel)
	EVT_LEFT_DOWN(ColorsHexagon::leftClick)
	EVT_PAINT(ColorsHexagon::paintEvent)
END_EVENT_TABLE()*/

Hexagon::Hexagon(wxPanel* parent) : //skoñczone
wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(m_width, m_height)),
m_parent(parent),
m_windowDC(new wxWindowDC(this)){

	this->m_image.Create(m_width, m_height);

	for (int i = 0; i < m_width; i++)
		for (int j = 0; j < m_height; j++)
			this->m_image.SetRGB(i, j, MAX_COLOUR_VALUE, MAX_COLOUR_VALUE, MAX_COLOUR_VALUE);
}

Hexagon::Hexagon(wxPanel* parent, wxControl* control, wxColour* colour) : //skoñczone
wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(m_width, m_height)),
m_parent(parent),
m_reactControl(control),
m_colour(colour),
m_windowDC(new wxWindowDC(this)){
	this->m_image.Create(m_width, m_height);

	for (int i = 0; i < m_width; i++)
		for (int j = 0; j < m_height; j++)
			this->m_image.SetRGB(i, j, MAX_COLOUR_VALUE, MAX_COLOUR_VALUE, MAX_COLOUR_VALUE);
}

/*Hexagon::~Hexagon() { //chyba skoñczone

}*/ //jeœli dobrze rozumiem to u¿ytkownik nie musi deklarowaæ destruktora

void Hexagon::paintEvent(wxPaintEvent& event) { //do poprawy
	wxPaintDC paintDC(this);
	wxMemoryDC memoryDC;

	double step_x = MAX_COLOUR_VALUE / 110;
	double step_y = MAX_COLOUR_VALUE / 70;

	//red square
	wxImage redSquare;
	redSquare.Create(200, 200);
	redSquare.SetMask(true); //obiekt nie jest widoczny

	for (int i = 0; i < 70; i++)
		for (int j = 0; j < 110; j++)
			redSquare.SetRGB(j, i + j / 2, MAX_COLOUR_VALUE, 255 - step_x * i, step_y * j);

	//green square
	wxImage greenSquare;
	greenSquare.Create(200, 400);
	greenSquare.SetMask(true);

	for (int i = 0; i < 70; i++)
		for (int j = 0; j < 110; j++)
			redSquare.SetRGB(j, i + j / 2, 255 - step_x * i, MAX_COLOUR_VALUE, step_y * j);

	//blue square
	wxImage blueSquare;
	blueSquare.Create(100, 100);
	blueSquare.SetMask(true);

	for (int i = 0; i < 70; i++)
		for (int j = 0; j < 110; j++)
			redSquare.SetRGB(j, i + j / 2, 255 - step_x * i, MAX_COLOUR_VALUE, step_y * j);

	redSquare = redSquare.Rotate(45 * 2 * M_PI / 360, wxPoint(50, 50)); //obrót w radianach
	redSquare = redSquare.Scale(145, 85);

	greenSquare = greenSquare.Rotate(45 * 2 * M_PI / 360, wxPoint(50, 50)); //obrót w radianach
	greenSquare = greenSquare.Scale(145, 85);

	blueSquare = blueSquare.Rotate(45 * 2 * M_PI / 360, wxPoint(50, 50)); //obrót w radianach
	blueSquare = blueSquare.Scale(145, 85);

	m_bitmap = wxBitmap(this->m_image);
	memoryDC.SelectObject(m_bitmap);
	memoryDC.DrawBitmap(wxBitmap(redSquare), 28, 7, true);
	memoryDC.DrawBitmap(wxBitmap(greenSquare), 100, 20, true);
	memoryDC.DrawBitmap(wxBitmap(blueSquare), 30, 50, true);

}

void Hexagon::leftClick(wxMouseEvent& event) { //do zrobienia

}

wxColor Hexagon::getSelectedColour() { //skoñczone
	return this->m_selectedColour;
}

void Hexagon::setSelectedColour(const wxColour& colour) { //do zrobienia

}

void Hexagon::setPointerPosition(int pos_x, int pos_y) { //skoñczone
	this->m_ptrPosition_x = pos_x;
	this->m_ptrPosition_y = pos_y;
}