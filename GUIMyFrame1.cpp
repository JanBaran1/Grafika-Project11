#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
    //Bind(wxEVT_PAINT, &GUIMyFrame1::DrawPicture, this);
    //SetBackgroundStyle(wxBG_STYLE_PAINT);
    MyImage.AddHandler(new wxJPEGHandler);
    MyImage.AddHandler(new wxPNGHandler);
}


void GUIMyFrame1::m_panel3OnLeft( wxMouseEvent& event )
{
    unsigned int x_position = event.GetPosition().x;
    unsigned int y_position = event.GetPosition().y;
    auto data = ImageCpy.GetData();
    unsigned int width = ImageCpy.GetWidth();
    unsigned int c1 = data[3 * y_position * width + 3 * x_position];
    unsigned int c2 = data[3 * y_position * width + 3 * x_position + 1];
    unsigned int c3 = data[3 * y_position * width + 3 * x_position + 2];
    ChosenColour = wxColour(c1, c2, c3);
    DrawColour();
}

void GUIMyFrame1::m_panel3OnUpdateUI( wxUpdateUIEvent& event )
{
    DrawPicture(bright);
    //Repaint();
}

void GUIMyFrame1::m_panel4OnUpdateUI( wxUpdateUIEvent& event )
{
// TODO: Implement m_panel4OnUpdateUI
}

void GUIMyFrame1::m_panel5OnUpdateUI( wxUpdateUIEvent& event )
{
   
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
//TempImg.Rescale(120, 80);
//MyImage.Paste(TempImg, MyImage.GetWidth() - 120, 0);
//MyBitmap = wxBitmap(MyImage);
ImageCpy = TempImg;
ImageCpy.Rescale(m_panel3->GetSize().x, m_panel3->GetSize().y);
MyBitmap = wxBitmap(ImageCpy);
DrawPicture(bright);
}
if (MyBitmap.Ok()) this->SetTitle(WxOpenFileDialog1->GetFilename());
Refresh();
}
}

void GUIMyFrame1::m_button2OnButtonClick( wxCommandEvent& event )
{
std::shared_ptr<wxFileDialog> wxSaveFileDialog1(new wxFileDialog(this, _("Save file"), "", "",
"JPEG files (*.jpg)|*.jpg", wxFD_SAVE | wxFD_OVERWRITE_PROMPT));

if (wxSaveFileDialog1->ShowModal() == wxID_CANCEL)
return;
wxFileOutputStream output_stream(wxSaveFileDialog1->GetPath());
if (!output_stream.IsOk())
{
wxLogError("Cannot save current contents in file '%s'.", wxSaveFileDialog1->GetPath());
return;
}
else
ImageCpy.SaveFile(output_stream, "image/jpeg");
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
    //Brightness((m_slider3->GetValue() -50)/50. * 200 );
    bright = (m_slider3->GetValue() - 50) / 50. * 150;
    //Repaint();
    DrawPicture(bright);
}

void GUIMyFrame1::m_slider4OnScroll( wxScrollEvent& event )
{
// TODO: Implement m_slider4OnScroll
}


void GUIMyFrame1::DrawColour()
{
   
    if (ChosenColour.IsOk())
    {
        m_panel5->SetBackgroundColour(ChosenColour);
        m_panel5->Refresh();
    }
}

/*void GUIMyFrame1::DrawPicture(wxPaintEvent& e)
{
    //wxAutoBufferedPaintDC MyDC(m_panel3);
    wxClientDC MyDC(m_panel3);
    wxBufferedDC buffDC(&MyDC);
    buffDC.Clear();
    m_panel3->PrepareDC(buffDC);
    
    
    if (MyBitmap.Ok()) buffDC.DrawBitmap(MyBitmap, 0, 0);
}
      */
void GUIMyFrame1::DrawPicture(int bright)
{
    //wxAutoBufferedPaintDC MyDC(m_panel3);
    wxClientDC MyDC(m_panel3);
    wxBufferedDC buffDC(&MyDC);
    if (MyImage.IsOk())
    {
        ImageCpy = MyImage;
        ImageCpy.Rescale(m_panel3->GetSize().x, m_panel3->GetSize().y);
        Brightness(bright);
        MyBitmap = wxBitmap(ImageCpy);
    }
    buffDC.Clear();
    m_panel3->PrepareDC(buffDC);
    

    if (MyBitmap.Ok()) buffDC.DrawBitmap(MyBitmap, 0, 0,true);
}


void GUIMyFrame1::Brightness(int value)
{
    // TO DO: Zmiana jasnosci obrazu. value moze przyjmowac wartosci od -100 do 100
    //ImageCpy = MyImage.Copy();
    unsigned char* piks = ImageCpy.GetData();

    int rozmiar = 3* ImageCpy.GetWidth() * ImageCpy.GetHeight();
    int k = 0;

    while (k < rozmiar) {

        int tmp = piks[k] + value;

        if (tmp > 255)
            tmp = 255;
        else if (tmp < 0)
            tmp = 0;

        piks[k++] = tmp;
    }
}

void GUIMyFrame1::Repaint()
{
    //ImageCpy = MyImage;
    //ImageCpy.Rescale(m_panel3->GetSize().x, m_panel3->GetSize().y);
   if (MyImage.IsOk())
   {
    ImageCpy.Rescale(m_panel3->GetSize().x, m_panel3->GetSize().y);
        MyBitmap = wxBitmap(ImageCpy);
    }
    // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
    wxClientDC dc(m_panel3);   // Pobieramy kontekst okna
   // wxBufferedDC buffDC(&dc);
    m_panel3->PrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
    if (MyBitmap.Ok()) dc.DrawBitmap(MyBitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}

