#include <iostream>
#include <string>
#include <vector>
#include <wx/wx.h>
#include "frame.h"

class MyApp : public wxApp
{
public:
    bool OnInit() override
    {
        MyFrame* frame = new MyFrame("Bisection Method");
        frame->SetSize(800, 600);
        frame->Show(true);
        return true;

    }
};

wxIMPLEMENT_APP(MyApp);
