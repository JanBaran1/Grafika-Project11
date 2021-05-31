#pragma once
#include <wx/colour.h>
#include <wx/control.h>
#include <wx/dcscreen.h>
#include <wx/dcclient.h>
#include <wx/panel.h>

class Hexagon : public wxPanel {
	public:
		Hexagon(wxPanel* parent);
		Hexagon(wxPanel* parent, wxControl* control, wxColour* colour);
		//~Hexagon(); jeœli dobrze rozumiem to u¿ytkownik nie musi deklarowaæ destruktora

		void paintEvent(wxPaintEvent& event);
		void leftClick(wxMouseEvent& event);

		wxColour getSelectedColour();
		void setSelectedColour(const wxColour& colour);
		void setPointerPosition(int pos_x, int pos_y);

		//DECLARE_EVENT_TABLE()

	private:
		static const int m_width = 200;
		static const int m_height = 200;

		wxColour m_selectedColour;
		wxWindow* m_parent;
		wxWindowDC* m_windowDC;
		wxImage m_image;
		wxBitmap m_bitmap;

		//small hack
		wxControl* m_reactControl;
		wxColour* m_colour;

		int m_ptrPosition_x = m_width / 2;
		int m_ptrPosition_y = m_height / 2;


};