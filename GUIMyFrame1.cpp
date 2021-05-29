#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
    Bind(wxEVT_PAINT, &GUIMyFrame1::DrawPicture, this);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    MyImage.AddHandler(new wxJPEGHandler);
    MyImage.AddHandler(new wxPNGHandler);
}

void GUIMyFrame1::m_panel3OnUpdateUI( wxUpdateUIEvent& event )
{
// TODO: Implement m_panel3OnUpdateUI
}

void GUIMyFrame1::m_panel4OnUpdateUI( wxUpdateUIEvent& event )
{
// TODO: Implement m_panel4OnUpdateUI
}

void GUIMyFrame1::m_panel5OnUpdateUI( wxUpdateUIEvent& event )
{
// TODO: Implement m_panel5OnUpdateUI
}

void GUIMyFrame1::m_button1OnButtonClick( wxCommandEvent& event )
{
    std::shared_ptr<wxFileDialog> WxOpenFileDialog1(new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("JPEG files (*.jpg)|*.jpg"), wxFD_OPEN));
    if (WxOpenFileDialog1->ShowModal() == wxID_OK)
    {
        if (!MyImage.LoadFile(WxOpenFileDialog1->GetPath(), wxBITMAP_TYPE_JPEG))
            wxLogError(_("Nie można załadować obrazka"));
        else
        {
            wxImage TempImg(MyImage);
            TempImg.Rescale(120, 80);
            MyImage.Paste(TempImg, MyImage.GetWidth() - 120, 0);
            MyBitmap = wxBitmap(MyImage);
        }
        if (MyBitmap.Ok()) this->SetTitle(WxOpenFileDialog1->GetPath());
        Refresh();
    }
}

void GUIMyFrame1::m_slider1OnScroll( wxScrollEvent& event )
{
// TODO: Implement m_slider1OnScroll
}

void GUIMyFrame1::m_slider2OnScroll( wxScrollEvent& event )
{
// TODO: Implement m_slider2OnScroll
}

void GUIMyFrame1::m_slider3OnScroll( wxScrollEvent& event )
{
// TODO: Implement m_slider3OnScroll
}

void GUIMyFrame1::m_slider4OnScroll( wxScrollEvent& event )
{
// TODO: Implement m_slider4OnScroll
}

void GUIMyFrame1::DrawPicture(wxPaintEvent& e)
{
    wxAutoBufferedPaintDC MyDC(this);
    if (MyBitmap.Ok()) MyDC.DrawBitmap(MyBitmap, 20, 20);
}
