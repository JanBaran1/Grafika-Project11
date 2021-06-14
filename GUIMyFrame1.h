﻿#ifndef __GUIMyFrame1__
#define __GUIMyFrame1__

/**
@file
Subclass of MyFrame1, which is generated by wxFormBuilder.
*/

#include "GUI.h"

//// end generated include
#include "ColoursHexagon.h"
#include <wx/wxprec.h>
#include <wx/dcbuffer.h>
#include <wx/wfstream.h>
/** Implementing MyFrame1 */
class GUIMyFrame1 : public MyFrame1
{
	protected:
		// Handlers for MyFrame1 events.
		void m_panel3OnLeft( wxMouseEvent& event );
		void m_panel3OnUpdateUI( wxUpdateUIEvent& event );
		void m_panel4OnClick( wxMouseEvent& event );
		void m_panel4OnUpdateUI( wxUpdateUIEvent& event );
		void m_panel5OnUpdateUI( wxUpdateUIEvent& event );
		void m_button1OnButtonClick( wxCommandEvent& event );
		void m_button2OnButtonClick( wxCommandEvent& event );
		void m_checkBox1OnCheckBox( wxCommandEvent& event );
		void m_slider1OnScroll( wxScrollEvent& event );
		void m_slider1OnScrollChanged( wxScrollEvent& event );
		void m_slider6OnScroll( wxScrollEvent& event );
		void m_slider6OnScrollChanged( wxScrollEvent& event );
		void m_slider2OnScroll( wxScrollEvent& event );
		void m_slider2OnScrollChanged( wxScrollEvent& event );
		void m_slider3OnScroll( wxScrollEvent& event );
		void m_slider3OnScrollChanged( wxScrollEvent& event );
		void m_slider4OnScroll( wxScrollEvent& event );
		void m_slider4OnScrollChanged( wxScrollEvent& event );
		void m_slider5OnScroll( wxScrollEvent& event );
	public:
		/** Constructor */
		GUIMyFrame1( wxWindow* parent );
	//// end generated class members
		wxImage ImageOrg;
		wxImage MyImage;
		wxImage ImageCpy;
		wxBitmap MyBitmap;
		wxColour ChosenColour;
		Hexagon* hexagon;
		int bright = 0;
		bool bright_flag = false;
		bool sat_flag = false;
		bool zmiana_flag = false;
		double sat = 0;
		bool CC = 0;
		double zmiana = 0;

		void Brightness(int value); // funkcja zmieniajaca jasnosc obrazka
		void Repaint();
		void Saturation(double value);
		void SilaZmian(double value);
		//void DrawPicture(wxPaintEvent& e);
		void DrawPicture(int bright,double sat);
		void DrawColour();
		void ChangeColour(wxImage *Image);



		//moje zmiany:
		//Hexagon* hexagon;



















};

#endif // __GUIMyFrame1__
