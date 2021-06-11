///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/slider.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame 
{
	private:
	
	protected:
		wxPanel* m_panel3;
		wxPanel* m_panel4;
		wxPanel* m_panel5;
		wxButton* m_button1;
		wxButton* m_button2;
		wxStaticText* m_staticText2;
		wxSlider* m_slider1;
		wxStaticText* m_staticText3;
		wxSlider* m_slider2;
		wxStaticText* m_staticText4;
		wxSlider* m_slider3;
		wxStaticText* m_staticText5;
		wxSlider* m_slider4;
		wxStaticText* m_staticText51;
		wxSlider* m_slider5;
		
		// Virtual event handlers, overide them in your derived class
		virtual void m_panel3OnLeft( wxMouseEvent& event ) { event.Skip(); }
		virtual void m_panel3OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_panel4OnClick( wxMouseEvent& event ) { event.Skip(); }
		virtual void m_panel4OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_panel5OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_button1OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button2OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_slider1OnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void m_slider1OnScrollChanged( wxScrollEvent& event ) { event.Skip(); }
		virtual void m_slider2OnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void m_slider2OnScrollChanged( wxScrollEvent& event ) { event.Skip(); }
		virtual void m_slider3OnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void m_slider3OnScrollChanged( wxScrollEvent& event ) { event.Skip(); }
		virtual void m_slider4OnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void m_slider4OnScrollChanged( wxScrollEvent& event ) { event.Skip(); }
		virtual void m_slider5OnScroll( wxScrollEvent& event ) { event.Skip(); }
		
	
	public:
		
		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Korekty barwne"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MyFrame1();
	
};

#endif //__GUI_H__
