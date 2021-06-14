#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <wx/colour.h>
#include <wx/control.h>
#include <wx/dcscreen.h>
#include <wx/dcclient.h>
#include <wx/panel.h>
void RGBtoHSL(double R, double G, double B, double& H, double& S, double& L);
void HSLtoRGB(double &R, double &G, double &B, double H, double S, double L);


class Hexagon : public wxPanel {
	public:
		Hexagon(wxPanel* parent);
		Hexagon(wxPanel* parent, wxControl* control, wxColour* colour);

		void drawHexagon(wxPaintEvent& event);
		void leftClick(wxMouseEvent& event);
		void erase(wxEraseEvent& event);
		unsigned int getSliderValue();
		void setSuwak(double s);
		double getSuwak();
		void setSliderValue(unsigned int sliderValue);
		wxColour getSelectedColour();
		void setSelectedColour(wxColour& sear_colour);
		void setPointerPosition(int pos_x, int pos_y);
		void setImage(wxImage Image) { m_image = Image; }
		wxImage * getImage() { return &m_image; }
		wxImage &getImage2() { return m_image; }
		void ChangeColour(wxImage* Image);
		void setChosenColour(wxColour Colour) { m_ChosenColour = Colour; }
		wxColour getChosenColour() { return m_ChosenColour; }
		wxImage getImageSuwak() { return m_imageSuwak; }
		void setImageSuwak(wxImage img) { m_imageSuwak = img; }
		//int suwak = 0;
		wxImage m_image;
		wxImage m_imageSuwak;
		int wsp_x, wsp_y;
		bool is_checked = false;
		double suwak2 = 10.0;
	private:
		static const int m_width = 200;
		static const int m_height = 260;

		wxColour m_selectedColour = wxColour(127, 127, 127);
		wxWindow* m_parent;
		wxWindowDC* m_windowDC;
		//wxImage m_image;
		//wxImage m_imageSuwak;
		wxImage m_bgImage;
		wxBitmap m_bitmap;
		wxColour m_ChosenColour = wxColour(255,255,255);

		//small hack
		wxControl* m_reactControl;
		wxColour* m_colour;
		double suwak = 0.0;
		unsigned int m_sliderValue = 127;
		int m_ptrPosition_x = m_width / 2;
		int m_ptrPosition_y = m_height / 2 - 18;

		wxDECLARE_EVENT_TABLE();
};