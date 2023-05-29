#include <wx/wx.h>
#include <wx/scrolwin.h>
#include <vector>

class MyScrollablePanel : public wxPanel
{
    private:
    wxScrolledWindow* scrollWindow;
    wxBoxSizer* scrollSizer;
    std::vector<wxTextCtrl*> textCtrls;
    std::vector<wxStaticText*> labels;
    wxStaticText* fxLabel;
    
    wxButton* addButton;
    wxButton* removeButton;

public:
    MyScrollablePanel(wxWindow* parent) : wxPanel(parent, wxID_ANY)
    {
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
        // Create the section title for "f(x) = "
        wxStaticText* sectionTitle = new wxStaticText(this, wxID_ANY, "f(x) =", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
        mainSizer->Add(sectionTitle, 0, wxALL, 10);

        // Create the upper part with a horizontal scroll window
        scrollWindow = new wxScrolledWindow(this, wxID_ANY);
        

        scrollSizer = new wxBoxSizer(wxHORIZONTAL);
        scrollWindow->SetSizer(scrollSizer);

        mainSizer->Add(scrollWindow, 1, wxEXPAND | wxALL, 10);

        // Create the bottom part (static part) with buttons
        wxBoxSizer* bottomSizer = new wxBoxSizer(wxHORIZONTAL);

        addButton = new wxButton(this, wxID_ANY, "Add");
        removeButton = new wxButton(this, wxID_ANY, "Remove");

        bottomSizer->Add(addButton, 0, wxALL, 10);
        bottomSizer->Add(removeButton, 0, wxALL, 10);

        mainSizer->Add(bottomSizer, 0, wxALIGN_CENTER);

        SetSizerAndFit(mainSizer);

        // Bind button events
        addButton->Bind(wxEVT_BUTTON, &MyScrollablePanel::OnAddButtonClick, this);
        removeButton->Bind(wxEVT_BUTTON, &MyScrollablePanel::OnRemoveButtonClick, this);

        // Create initial input fields
        for (int i = 0; i < 3; ++i)
        {
            AddInputField();
        }

        // Set the fixed height for the scrollable container
        scrollWindow->SetScrollRate(10, 10);

        Layout();
    }

    void OnAddButtonClick(wxCommandEvent& event)
    {
        AddInputField();
    }


private:
    void AddInputField()
    {
        int power = textCtrls.size();

        wxString labelText;
        if (power > 0)
            labelText << "x^" << power << " + ";
        else
            labelText << "";


        // Create the static text for the coefficient label
        wxStaticText* label = new wxStaticText(scrollWindow, wxID_ANY, labelText, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        scrollSizer->Insert(0, label, 0, wxALL, 5);

        wxTextCtrl* textCtrl = new wxTextCtrl(scrollWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
        scrollSizer->Insert(0, textCtrl, 0, wxALL, 5);

        textCtrls.insert(textCtrls.begin(), textCtrl);
        labels.insert(labels.begin(), label);

        scrollSizer->Layout();
        scrollWindow->Scroll(0, 0);

        Layout();

    }

    void OnRemoveButtonClick(wxCommandEvent& event)
    {
        if (textCtrls.size() > 1)
        {
            wxTextCtrl* firstTextCtrl = textCtrls.front();
            scrollSizer->Detach(firstTextCtrl);
            firstTextCtrl->Destroy();
            textCtrls.erase(textCtrls.begin());

            wxStaticText* firstLabel = labels.front();
            scrollSizer->Detach(firstLabel);
            firstLabel->Destroy();
            labels.erase(labels.begin());

            scrollSizer->Layout();
        }
        Layout();

    }
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title)
    {
        // Create the main panel
        wxPanel* mainPanel = new wxPanel(this);

        // Create the main sizer for the frame
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        // Add the scrollable panel to the main sizer
        mainSizer->Add(new MyScrollablePanel(mainPanel), 1, wxEXPAND);

        mainPanel->SetSizerAndFit(mainSizer);
        Layout();

    }
};

class MyApp : public wxApp
{
public:
    bool OnInit() override
    {
        MyFrame* frame = new MyFrame("Bisection Method");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
