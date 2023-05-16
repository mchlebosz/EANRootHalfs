#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/utils.h>
#include <wx/wx.h>

#include "bisection.h"

class Simple : public wxFrame {
public:
	Simple(const wxString & title) :
		wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150)) {
		Centre();

		// create input fields
		wxStaticText * staticText1 =
			new wxStaticText(this, wxID_ANY, wxT("f(x) = "));
		wxTextCtrl * textCtrl1 =
			new wxTextCtrl(this, wxID_ANY, wxT("1 0 -2"), wxDefaultPosition,
						   wxDefaultSize, wxTE_MULTILINE);
		wxStaticText * staticText2 =
			new wxStaticText(this, wxID_ANY, wxT("a = "));
		wxTextCtrl * textCtrl2 =
			new wxTextCtrl(this, wxID_ANY, wxT("-2"), wxDefaultPosition,
						   wxDefaultSize, wxTE_MULTILINE);
		wxStaticText * staticText3 =
			new wxStaticText(this, wxID_ANY, wxT("b = "));
		wxTextCtrl * textCtrl3 =
			new wxTextCtrl(this, wxID_ANY, wxT("2"), wxDefaultPosition,
						   wxDefaultSize, wxTE_MULTILINE);

		// create button
		wxButton * button = new wxButton(this, wxID_ANY, wxT("Calculate"));

		// create output field
		wxStaticText * staticText4 =
			new wxStaticText(this, wxID_ANY, wxT("x = "));
		wxTextCtrl * textCtrl4 =
			new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition,
						   wxDefaultSize, wxTE_MULTILINE);

		// create sizer
		wxBoxSizer * boxSizer = new wxBoxSizer(wxVERTICAL);
		boxSizer->Add(staticText1, 0, wxEXPAND | wxALL, 5);
		boxSizer->Add(textCtrl1, 0, wxEXPAND | wxALL, 5);
		boxSizer->Add(staticText2, 0, wxEXPAND | wxALL, 5);
		boxSizer->Add(textCtrl2, 0, wxEXPAND | wxALL, 5);

		boxSizer->Add(staticText3, 0, wxEXPAND | wxALL, 5);
		boxSizer->Add(textCtrl3, 0, wxEXPAND | wxALL, 5);
		boxSizer->Add(button, 0, wxEXPAND | wxALL, 5);
		boxSizer->Add(staticText4, 0, wxEXPAND | wxALL, 5);
		boxSizer->Add(textCtrl4, 0, wxEXPAND | wxALL, 5);

		SetSizer(boxSizer);

		// bind button
		Bind(wxEVT_BUTTON, &Simple::OnCalculate, this, button->GetId());

		wxMenu * menuFile = new wxMenu;
		menuFile->Append(wxID_EXIT);

		wxMenu * menuHelp = new wxMenu;
		menuHelp->Append(wxID_ABOUT);
		menuHelp->Append(wxID_HELP);

		wxMenuBar * menuBar = new wxMenuBar;
		menuBar->Append(menuFile, wxT("&File"));
		menuBar->Append(menuHelp, wxT("&Help"));

		SetMenuBar(menuBar);

		CreateStatusBar();
		SetStatusText(wxT("Welcome to wxWidgets!"));

		Bind(wxEVT_MENU, &Simple::OnAbout, this, wxID_ABOUT);
		Bind(wxEVT_MENU, &Simple::OnHelp, this, wxID_HELP);
		Bind(wxEVT_MENU, &Simple::OnExit, this, wxID_EXIT);
	}

private:
	void OnAbout(wxCommandEvent & event) {
		wxMessageBox(wxT("This is a wxWidgets' Hello world sample"),
					 wxT("About Hello World"), wxOK | wxICON_INFORMATION);
	}

	void OnExit(wxCommandEvent & event) {
		Close(true);
	}

	void OnHelp(wxCommandEvent & event) {
		// go to webpage
		wxLaunchDefaultBrowser(wxT("https://www.wxwidgets.org/"));
	}

	void OnCalculate(wxCommandEvent & event) {
		// get input
	}
};

class MyApp : public wxApp {
public:
	bool OnInit() {
		Simple * simple = new Simple(wxT("Simple"));
		simple->Show(true);
		return true;
	}
};

wxIMPLEMENT_APP(MyApp);