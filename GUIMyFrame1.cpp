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
hexagon->wsp_x = x_position;
hexagon->wsp_y = y_position;
auto data = ImageCpy.GetData();
unsigned int width = ImageCpy.GetWidth();
unsigned int c1 = data[3 * y_position * width + 3 * x_position];
unsigned int c2 = data[3 * y_position * width + 3 * x_position + 1];
unsigned int c3 = data[3 * y_position * width + 3 * x_position + 2];
ChosenColour = wxColour(c1, c2, c3);
hexagon->setChosenColour(ChosenColour);

wxColour selectedColour = wxColour(ImageCpy.GetRed(x_position, y_position), ImageCpy.GetGreen(x_position, y_position), ImageCpy.GetBlue(x_position, y_position));
hexagon->setSelectedColour(selectedColour);
m_slider5->SetValue(hexagon->getSliderValue());
DrawColour();

}


}

void GUIMyFrame1::m_panel3OnUpdateUI( wxUpdateUIEvent& event )
{
DrawPicture(bright,sat);
//Repaint();
}

void GUIMyFrame1::m_panel4OnClick( wxMouseEvent& event )
{
//nie dziala

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

MyImage = TempImg;
hexagon->m_image = MyImage.Copy();
hexagon->m_imageSuwak = MyImage.Copy();

ChosenColour = wxColor(255, 255, 255);
hexagon->setChosenColour(ChosenColour);
DrawColour();
DrawPicture(bright,sat);
}

}
}

void GUIMyFrame1::m_button2OnButtonClick( wxCommandEvent& event )
{
std::shared_ptr<wxFileDialog> wxSaveFileDialog1(new wxFileDialog(this, _("Save file"), "", "", "JPEG files (*.jpg)|*.jpg", wxFD_SAVE | wxFD_OVERWRITE_PROMPT));

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

void GUIMyFrame1::m_checkBox1OnCheckBox( wxCommandEvent& event )
{
    if (event.IsChecked())
        hexagon->is_checked = true;
    else
        hexagon->is_checked = false;
    hexagon->m_image = hexagon->m_imageSuwak.Copy();
    hexagon->ChangeColour(hexagon->getImage());
    DrawPicture(bright, sat);
}

void GUIMyFrame1::m_slider1OnScroll( wxScrollEvent& event )
{
// TODO: Implement m_slider1OnScroll
if (MyImage.IsOk())
{
hexagon->setSuwak(m_slider1->GetValue());
hexagon->m_image = hexagon->m_imageSuwak.Copy();
hexagon->ChangeColour(hexagon->getImage());
DrawPicture(bright, sat);

}
}

void GUIMyFrame1::m_slider1OnScrollChanged( wxScrollEvent& event )
{
    hexagon->m_imageSuwak = hexagon->m_image.Copy();
}

void GUIMyFrame1::m_slider6OnScroll( wxScrollEvent& event )
{
    if (MyImage.IsOk())
    {
        hexagon->suwak2 = (m_slider6->GetValue() + 20)/2.;
        hexagon->m_image = hexagon->m_imageSuwak.Copy();
        hexagon->ChangeColour(hexagon->getImage());
        DrawPicture(bright, sat);

    }
}

void GUIMyFrame1::m_slider6OnScrollChanged( wxScrollEvent& event )
{
// TODO: Implement m_slider6OnScrollChanged
}

void GUIMyFrame1::m_slider2OnScroll( wxScrollEvent& event )
{
zmiana = m_slider2->GetValue();
zmiana_flag = true;
DrawPicture(bright, sat);
}

void GUIMyFrame1::m_slider2OnScrollChanged( wxScrollEvent& event )
{
    hexagon->m_imageSuwak = hexagon->m_image.Copy();
}

void GUIMyFrame1::m_slider3OnScroll( wxScrollEvent& event )
{
bright = (m_slider3->GetValue() - 50) / 50. * 100;
bright_flag = true;
DrawPicture(bright,sat);
}

void GUIMyFrame1::m_slider3OnScrollChanged( wxScrollEvent& event )
{
    hexagon->m_imageSuwak = hexagon->m_image.Copy();
}

void GUIMyFrame1::m_slider4OnScroll( wxScrollEvent& event )
{
sat = ((m_slider4->GetValue()-50)*2);
sat_flag = true;
DrawPicture(bright,sat);
}

void GUIMyFrame1::m_slider4OnScrollChanged( wxScrollEvent& event )
{
    hexagon->m_imageSuwak = hexagon->m_image.Copy();
}

void GUIMyFrame1::m_slider5OnScroll( wxScrollEvent& event )
{
int sliderValue = m_slider5->GetValue();
if (sliderValue < 1)
{
sliderValue = 1;
}
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

     
void GUIMyFrame1::DrawPicture(int bright,double sat)
{
   
    wxClientDC MyDC(m_panel3);
    wxBufferedDC buffDC(&MyDC);

    if (MyImage.IsOk())
    {
        //ImageCpy = MyImage;
        
        ImageCpy = hexagon->m_image;
        ImageCpy.Rescale(m_panel3->GetSize().x, m_panel3->GetSize().y);
        
        if (bright_flag == true)
        {
            Brightness(bright);
            bright_flag = false;
        }
        if (sat_flag == true)
        {
            Saturation(sat);
            sat_flag = false;
        }
        if (zmiana_flag == true)
        {
            SilaZmian(zmiana);
            zmiana_flag = false;
        }
        MyBitmap = wxBitmap(ImageCpy);
       m_panel5->SetBackgroundColour(hexagon->getChosenColour());
        m_panel5->Refresh();
      
        
    }
    
    buffDC.Clear();
    m_panel3->PrepareDC(buffDC);
    

    if (MyBitmap.Ok()) buffDC.DrawBitmap(MyBitmap, 0, 0,true);
   
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

void GUIMyFrame1::Brightness(int value)
{
    // TO DO: Zmiana jasnosci obrazu. value moze przyjmowac wartosci od -100 do 100
    //ImageCpy = MyImage.Copy();
    //unsigned char* piks = ImageCpy.GetData();
    hexagon->m_image = hexagon->m_imageSuwak.Copy();
    unsigned char* piks = hexagon->m_image.GetData();

    int rozmiar = 3* hexagon->m_image.GetWidth() * hexagon->m_image.GetHeight();
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

void GUIMyFrame1::SilaZmian(double value)
{
    //unsigned char* piksorg = ImageCpy.GetData();
    //unsigned char* piks = ImageCpy.GetData();
    // char* piksorg = hexagon->m_image.GetData();
    hexagon->m_image = hexagon->m_imageSuwak.Copy();
    unsigned char* piks = hexagon->m_image.GetData();
    auto dataOrg = ImageOrg.GetData();

    int rozmiar = 3 * hexagon->m_image.GetWidth() * hexagon->m_image.GetHeight();

    
    for (unsigned k = 0; k < rozmiar; k += 3) {
   
        
        int tmp1 =( dataOrg[k] )* (value) / 100 + piks[k] * (100 - value) / 100;
        int tmp2 = (dataOrg[k+1]) * ( value) / 100 + piks[k+1] * (100 - value) / 100;
        int tmp3 = (dataOrg[k+2]) * ( value) / 100 + piks[k+2] * (100 - value) / 100;

        

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

void GUIMyFrame1::Saturation(double value)
{
    // TO DO: Zmiana jasnosci obrazu. value moze przyjmowac wartosci od -100 do 100
    //ImageCpy = MyImage.Copy();
    //unsigned char* piks = ImageCpy.GetData();
    hexagon->m_image = hexagon->m_imageSuwak.Copy();
    unsigned char* piks = hexagon->m_image.GetData();

    int rozmiar = 3 * hexagon->m_image.GetWidth() * hexagon->m_image.GetHeight();
    
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