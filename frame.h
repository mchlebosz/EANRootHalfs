#ifndef MY_FRAME_H
#define MY_FRAME_H

#include <wx/wx.h>
#include "polynomial.h"

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
    
     // Event handler declarations
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnInfo(wxCommandEvent& event);
    void OnHelp(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
private:
    void OnClose(wxCloseEvent& event)
    {
        // delete the frame object
        Destroy();
    }
};

#endif // MY_FRAME_H
