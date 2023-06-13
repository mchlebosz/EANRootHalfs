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

    wxMenu* editMenu = new wxMenu();
    //add
    // Add a menu item with a check mark
    wxMenuItem* checkItem = new wxMenuItem(editMenu, wxID_ANY, wxT("&Interval Mode"), wxT("Check this item to switch between interval and non-interval modes"), wxITEM_CHECK);
    editMenu->Append(checkItem);
    // Bind the menu item to a handler function
    Bind(wxEVT_MENU, &MyFrame::OnCheckItem, this, checkItem->GetId());

    menuBar->Append(editMenu, wxT("&Edit"));

    // set the menu bar for the frame
    SetMenuBar(menuBar);
    // Create the main panel
    mainPanel = new wxPanel(this);

    // Create the main sizer for the frame
    mainSizer = new wxBoxSizer(wxVERTICAL);

    // Add the scrollable panel to the main sizer
    polynomial = new Polynomial(mainPanel, false);
    intervalPolynomial = new Polynomial(mainPanel, true);
    mainSizer->Add(polynomial, 1, wxEXPAND);
    mainSizer->Add(intervalPolynomial, 1, wxEXPAND);
    intervalPolynomial->Hide();

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
    wxLaunchDefaultBrowser(wxT("https://mchlebosz.github.io/EANRootHalfs/"));
  
}

void MyFrame::OnInfo(wxCommandEvent &event)
{
    //Show popup with my data
    wxMessageBox(wxT("Bisection Method Calc\n\nAuthor: Mateusz Chlebosz\n\nVersion: 1.0.0\n\nPrepared for EAN"), wxT("Info"), wxOK | wxICON_INFORMATION);
}

// Define the handler function
void MyFrame::OnCheckItem(wxCommandEvent& event)
{
    // Get the menu item that triggered the event
    wxMenuItem* item = GetMenuBar()->FindItem(event.GetId());

    // Check the state of the menu item
    if (item->IsChecked())
    {
        // Checkbox is checked, perform action
        // ...
        polynomial->Hide();
        intervalPolynomial->Show();
        intervalPolynomial->Layout();
        wxMessageBox(wxT("Interval mode enabled"), wxT("Info"), wxOK | wxICON_INFORMATION);
    }
    else
    {
        // Checkbox is unchecked, perform action
        // ...
        polynomial->Show();
        intervalPolynomial->Hide();
        polynomial->Layout();
        wxMessageBox(wxT("Interval mode disabled"), wxT("Info"), wxOK | wxICON_INFORMATION);

        // Update the layout of the main panel to reflect the changes
        mainSizer->Layout();
        mainPanel->Layout();
        Layout();
    }
}