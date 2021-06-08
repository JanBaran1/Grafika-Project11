#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <wx/colour.h>
#include <wx/control.h>
#include <wx/dcscreen.h>
#include <wx/dcclient.h>
#include <wx/panel.h>



class Hexagon : public wxPanel {
	public:
		Hexagon(wxPanel* parent);
		Hexagon(wxPanel* parent, wxControl* control, wxColour* colour);

		void drawHexagon(wxPaintEvent& event);
		void leftClick(wxMouseEvent& event);
		void erase(wxEraseEvent& event);

		wxColour getSelectedColour();
		void setSelectedColour(const wxColour& colour);
		void setPointerPosition(int pos_x, int pos_y);
		void setImage(wxImage Image) { m_image = Image; }
		wxImage * getImage() { return &m_image; }
		void ChangeColour(wxImage* Image);
		void setChosenColour(wxColour Colour) { m_ChosenColour = Colour; }
		wxColour getChosenColour() { return m_ChosenColour; }

	private:
		static const int m_width = 200;
		static const int m_height = 260;

		wxColour m_selectedColour = wxColour(255,255,255);
		wxWindow* m_parent;
		wxWindowDC* m_windowDC;
		wxImage m_image;
		wxImage m_bgImage;
		wxBitmap m_bitmap;
		wxColour m_ChosenColour = wxColour(255,255,255);

		//small hack
		wxControl* m_reactControl;
		wxColour* m_colour;

		int m_ptrPosition_x = m_width / 2;
		int m_ptrPosition_y = m_height / 2 - 18;

		wxDECLARE_EVENT_TABLE();
};