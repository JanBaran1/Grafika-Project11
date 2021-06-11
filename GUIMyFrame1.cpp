#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
    //Bind(wxEVT_PAINT, &GUIMyFrame1::DrawPicture, this);
    //SetBackgroundStyle(wxBG_STYLE_PAINT);
    MyImage.AddHandler(new wxJPEGHandler);
    MyImage.AddHandler(new wxPNGHandler);

    this->hexagon = new Hexagon(m_panel4);
    //m_panel4->Add(this->hexagon);
}

void GUIMyFrame1::m_panel3OnLeft( wxMouseEvent& event )
{
    if (ImageCpy.IsOk()){
        unsigned int x_position = event.GetPosition().x;
        unsigned int y_position = event.GetPosition().y;
        auto data = ImageCpy.GetData();
        unsigned int width = ImageCpy.GetWidth();
        unsigned int c1 = data[3 * y_position * width + 3 * x_position];
        unsigned int c2 = data[3 * y_position * width + 3 * x_position + 1];
        unsigned int c3 = data[3 * y_position * width + 3 * x_position + 2];
        ChosenColour = wxColour(c1, c2, c3);
        hexagon->setChosenColour(ChosenColour);

        wxColour selectedColour = wxColour(ImageCpy.GetRed(x_position, y_position), ImageCpy.GetGreen(x_position, y_position), ImageCpy.GetBlue(x_position, y_position));
        hexagon->setSelectedColour(selectedColour);
        DrawColour();
        m_slider5->SetValue(hexagon->getSliderValue());

    }
}

void GUIMyFrame1::m_panel3OnUpdateUI( wxUpdateUIEvent& event )
{
    DrawPicture(bright,sat,zmiana);
    //Repaint();
}

void GUIMyFrame1::m_panel4OnClick( wxMouseEvent& event )
{
    ChangeColour(&MyImage);
    DrawPicture(bright, sat,zmiana);

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
if (!ImageOrg.LoadFile(WxOpenFileDialog1->GetPath(), wxBITMAP_TYPE_JPEG))
wxLogError(_("Nie można załadować obrazka"));
else
{
wxImage TempImg(ImageOrg);
//TempImg.Rescale(120, 80);
//MyImage.Paste(TempImg, MyImage.GetWidth() - 120, 0);
//MyBitmap = wxBitmap(MyImage);
MyImage = TempImg;
hexagon->setImage(MyImage);
//ImageCpy = TempImg;
//ImageCpy.Rescale(m_panel3->GetSize().x, m_panel3->GetSize().y);
//MyBitmap = wxBitmap(ImageCpy);
ChosenColour = wxColor(255, 255, 255);
hexagon->setChosenColour(ChosenColour);
DrawColour();
DrawPicture(bright,sat,zmiana);
}
//if (MyBitmap.Ok()) this->SetTitle(WxOpenFileDialog1->GetFilename());
//Refresh();
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
    //hexagon->setSuwak(m_slider1->GetValue()/100. );
    
}

void GUIMyFrame1::m_slider2OnScroll( wxScrollEvent& event )
{
// TODO: Implement m_slider2OnScroll
    zmiana = m_slider2->GetValue();
    DrawPicture(bright, sat, zmiana);
}

void GUIMyFrame1::m_slider3OnScroll( wxScrollEvent& event )
{
// TODO: Implement m_slider3OnScroll
//Brightness((m_slider3->GetValue() -50)/50. * 200 );
bright = (m_slider3->GetValue() - 50) / 50. * 150;
//Repaint();
DrawPicture(bright,sat,zmiana);
}

void GUIMyFrame1::m_slider4OnScroll( wxScrollEvent& event )
{
// TODO: Implement m_slider4OnScroll
sat = ((m_slider4->GetValue()-50)*2) ;
//Repaint();
DrawPicture(bright,sat,zmiana);
}

void GUIMyFrame1::m_slider5OnScroll( wxScrollEvent& event )
{
// TODO: Implement m_slider5OnScroll
    int sliderValue = m_slider5->GetValue();
    if (sliderValue < 1)
        sliderValue = 1;
    hexagon->setSliderValue(255 * sliderValue / 100);
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
void GUIMyFrame1::DrawPicture(int bright,double sat,int zmiana)
{
    //wxAutoBufferedPaintDC MyDC(m_panel3);
    wxClientDC MyDC(m_panel3);
    wxBufferedDC buffDC(&MyDC);
    if (MyImage.IsOk())
    {
        //ImageCpy = MyImage;
        
        ImageCpy = *(hexagon->getImage());
        ImageCpy.Rescale(m_panel3->GetSize().x, m_panel3->GetSize().y);
        
        Brightness(bright);
        Saturation(sat);
        SilaZmian(zmiana);
        
        MyBitmap = wxBitmap(ImageCpy);
        m_panel5->SetBackgroundColour(hexagon->getChosenColour());
        m_panel5->Refresh();
        
    }
    
    buffDC.Clear();
    m_panel3->PrepareDC(buffDC);
    

    if (MyBitmap.Ok()) buffDC.DrawBitmap(MyBitmap, 0, 0,true);
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

void GUIMyFrame1::ChangeColour(wxImage *Image)
{
    if (true)
    {
        auto data = Image->GetData();
        int w = Image->GetWidth();
        int h = Image->GetHeight();

        for (int i = 0; i < 3 * w * h; i += 3)
        {
            if (ChosenColour.Red() == data[i] && ChosenColour.Green() == data[i + 1] && ChosenColour.Blue() == data[i + 2])
            {
                data[i] = hexagon->getSelectedColour().Red();
                data[i + 1] = hexagon->getSelectedColour().Green();
                data[i + 2] = hexagon->getSelectedColour().Blue();
            }
        }
        
    }
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

void GUIMyFrame1::Saturation(double value)
{
    // TO DO: Zmiana jasnosci obrazu. value moze przyjmowac wartosci od -100 do 100
    //ImageCpy = MyImage.Copy();
    unsigned char* piks = ImageCpy.GetData();

    int rozmiar = 3 * ImageCpy.GetWidth() * ImageCpy.GetHeight();
    
    double x = value ;
    for (unsigned k = 0; k < rozmiar;k+=3) {
        int szary = (piks[k] + piks[k + 1] + piks[k + 2]) / 3;
        
        for (int i = 0; i < 3; i++)
        {
           
            int tmp = szary + (piks[k + i] - szary) *( x/100+1.0);

            if (tmp > 255)
                tmp = 255;
            else if (tmp < 0)
                tmp = 0;

            piks[k + i] = tmp;
        }
    }
}

void GUIMyFrame1::SilaZmian(double value)
{
    unsigned char* piks = ImageCpy.GetData();

    int rozmiar = 3 * ImageCpy.GetWidth() * ImageCpy.GetHeight();

    
    for (unsigned k = 0; k < rozmiar; k += 3) {
   
        
        int tmp1 = piks[k] * (100 - value) / 100 + hexagon->getSelectedColour().Red() * value / 100;
        int tmp2 = piks[k+1] * (100 - value) / 100 + hexagon->getSelectedColour().Green() * value / 100;
        int tmp3 = piks[k+2] * (100 - value) / 100 + hexagon->getSelectedColour().Blue() * value / 100;

        

            if (tmp1 > 255)
                tmp1 = 255;
            else if (tmp1 < 0)
                tmp1 = 0;

            piks[k] = tmp1;

            if (tmp2 > 255)
                tmp2 = 255;
            else if (tmp2 < 0)
                tmp2 = 0;

            piks[k+1] = tmp2;

            if (tmp3 > 255)
                tmp3 = 255;
            else if (tmp3 < 0)
                tmp3 = 0;

            piks[k+2] = tmp3;
        
    }


}