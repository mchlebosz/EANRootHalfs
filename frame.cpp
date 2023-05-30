#include "frame.h"

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_OPEN, MyFrame::OnOpen)
    EVT_MENU(wxID_SAVE, MyFrame::OnSave)
    EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
    EVT_MENU(wxID_INFO, MyFrame::OnInfo)
    EVT_MENU(wxID_HELP, MyFrame::OnHelp)
wxEND_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title)
{
        // create a menu bar
    wxMenuBar* menuBar = new wxMenuBar();

    // create a file menu
    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(wxID_OPEN, wxT("&Open"));
    fileMenu->Append(wxID_SAVE, wxT("&Save"));
    fileMenu->Append(wxID_EXIT, wxT("&Quit"));

    // add the file menu to the menu bar
    menuBar->Append(fileMenu, wxT("&File"));

    wxMenu* aboutMenu = new wxMenu();
    aboutMenu->Append(wxID_INFO, wxT("&Info"));
    aboutMenu->Append(wxID_HELP, wxT("&Help"));
    menuBar->Append(aboutMenu, wxT("&About"));

    // set the menu bar for the frame
    SetMenuBar(menuBar);
    // Create the main panel
    wxPanel* mainPanel = new wxPanel(this);

    // Create the main sizer for the frame
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Add the scrollable panel to the main sizer
    mainSizer->Add(new Polynomial(mainPanel), 1, wxEXPAND);

    mainPanel->SetSizerAndFit(mainSizer);
    Layout();
}

void MyFrame::OnOpen(wxCommandEvent& event){
    //Do something
}

void MyFrame::OnSave(wxCommandEvent& event){
    //Do something
}

void MyFrame::OnQuit(wxCommandEvent& event){
    //Close app
    Close();
}

void MyFrame::OnHelp(wxCommandEvent &event)
{
    //Open webpage with docs
    // open a URL in the default browser or web view
    wxLaunchDefaultBrowser(wxT("https://www.example.com"));
  
}

void MyFrame::OnInfo(wxCommandEvent &event)
{
    //Show popup with my data
}

