#include "polynomial.h"
#include "bisection.h"

wxBEGIN_EVENT_TABLE(Polynomial, wxPanel)
    EVT_BUTTON(wxID_ANY, Polynomial::OnAddButtonClick)
    EVT_BUTTON(wxID_ANY, Polynomial::OnRemoveButtonClick)
    EVT_BUTTON(wxID_ANY, Polynomial::OnSaveButtonClick)
    EVT_BUTTON(wxID_ANY, Polynomial::OnCalculateButtonClick)
wxEND_EVENT_TABLE()

Polynomial::Polynomial(wxWindow* parent) : wxPanel(parent, wxID_ANY)
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
    wxBoxSizer* coefficientButtons = new wxBoxSizer(wxHORIZONTAL);

    addButton = new wxButton(this, wxID_ANY, "Add");
    removeButton = new wxButton(this, wxID_ANY, "Remove");
    saveButton = new wxButton(this, wxID_ANY, "Save");

    coefficientButtons->Add(addButton, 0, wxALL, 10);
    coefficientButtons->Add(removeButton, 0, wxALL, 10);
    coefficientButtons->Add(saveButton, 0, wxALL, 10);


    mainSizer->Add(coefficientButtons, 0, wxALIGN_CENTER);

    SetSizerAndFit(mainSizer);

    // Bind button events
    addButton->Bind(wxEVT_BUTTON, &Polynomial::OnAddButtonClick, this);
    removeButton->Bind(wxEVT_BUTTON, &Polynomial::OnRemoveButtonClick, this);
    saveButton->Bind(wxEVT_BUTTON, &Polynomial::OnSaveButtonClick, this);

    // Create initial input fields
    for (int i = 0; i < 3; ++i)
    {
        AddInputField();
    }

    // Set the fixed height for the scrollable container
    scrollWindow->SetScrollRate(10, 10);

    // Create the output panel
    functionPanel = new wxPanel(this);
    functionPanel->SetBackgroundColour(wxColour(240, 240, 240));

    functionText = new wxStaticText(functionPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    wxBoxSizer* functionPreviewSizer = new wxBoxSizer(wxVERTICAL);
    functionPreviewSizer->Add(functionText, 0, wxALL, 10);
    functionPanel->SetSizer(functionPreviewSizer);

    mainSizer->Add(functionPanel, 0, wxEXPAND | wxALL, 10);
    
    wxBoxSizer* paramInput = new wxBoxSizer(wxVERTICAL);
    calculateButton = new wxButton(this, wxID_ANY, "Calculate");
    calculateButton->Bind(wxEVT_BUTTON, &Polynomial::OnCalculateButtonClick, this);
    //input for a,b, epsilon
    wxStaticText* aLabel = new wxStaticText(this, wxID_ANY, "a = ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    wxStaticText* bLabel = new wxStaticText(this, wxID_ANY, "b = ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    wxStaticText* epsilonLabel = new wxStaticText(this, wxID_ANY, "epsilon = ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    aInput = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    bInput = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    epsilonInput = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    wxBoxSizer* aSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* epsilonSizer = new wxBoxSizer(wxHORIZONTAL);
    aSizer->Add(aLabel, 0, wxALL | wxALIGN_CENTER, 5);
    aSizer->Add(aInput, 0, wxALL | wxALIGN_CENTER, 5);
    bSizer->Add(bLabel, 0, wxALL | wxALIGN_CENTER, 5);
    bSizer->Add(bInput, 0, wxALL | wxALIGN_CENTER, 5);
    epsilonSizer->Add(epsilonLabel, 0, wxALL | wxALIGN_CENTER, 5);
    epsilonSizer->Add(epsilonInput, 0, wxALL | wxALIGN_CENTER, 5);
    
    paramInput->Add(aSizer, 0, wxALL | wxALIGN_CENTER, 1);
    paramInput->Add(bSizer, 0, wxALL | wxALIGN_CENTER, 1);
    paramInput->Add(epsilonSizer, 0, wxALL | wxALIGN_CENTER, 1);
    paramInput->Add(calculateButton, 0, wxALL | wxALIGN_CENTER, 3);

    //output
    wxStaticText* outputLabel = new wxStaticText(this, wxID_ANY, "Output: ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    outputText = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    wxBoxSizer* outputSizer = new wxBoxSizer(wxHORIZONTAL);
    outputSizer->Add(outputLabel, 0, wxALL | wxALIGN_CENTER, 5);
    outputSizer->Add(outputText, 0, wxALL | wxALIGN_CENTER, 5);
    paramInput->Add(outputSizer, 0, wxALL | wxALIGN_CENTER, 10);
    
    mainSizer->Add(paramInput, 0, wxALIGN_CENTER);

    Layout();
}

//destructor
Polynomial::~Polynomial()
{
    delete aInput;
    delete bInput;
    delete epsilonInput;
    delete calculateButton;
    delete functionText;
    delete functionPanel;
    delete scrollSizer;
    delete scrollWindow;
    delete addButton;
    delete removeButton;
    delete saveButton;

}

void Polynomial::OnAddButtonClick(wxCommandEvent& event)
{
    AddInputField();
}


void Polynomial::OnSaveButtonClick(wxCommandEvent& event)
{
    Save();
}
void Polynomial::OnCalculateButtonClick(wxCommandEvent& event)
{
    Save();
    //check if a,b,epsilon are numbers
    if (aInput->GetValue().ToDouble(&a) == false || bInput->GetValue().ToDouble(&b) == false || epsilonInput->GetValue().ToDouble(&epsilon) == false)
    {
        wxMessageBox("Please enter numbers for a, b and epsilon", "Error", wxICON_ERROR);
        return;
    }
     //if not set set a,b,epsilon
    if (epsilon == 0)
    {
        wxMessageBox("Please set epsilon to != 0", "Error", wxICON_ERROR);
        return;
    }

    Calculate();
}

void Polynomial::AddInputField()
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

void Polynomial::RemoveInputField()
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

void Polynomial::OnRemoveButtonClick(wxCommandEvent& event)
{
    RemoveInputField();   
}

void Polynomial::InputToVector()
{


    coefficients.clear();
    for (int i = 0; i <= textCtrls.size() - 1; ++i)
    {
        wxString coefficient = textCtrls[i]->GetValue();
        //transform coefficient to double
        double coefficientDouble;
        coefficient.ToDouble(&coefficientDouble);
        coefficients.push_back(coefficientDouble);

    }

}

void Polynomial::ShowEquation()
{
    wxString equation = "f(x) = ";
    
    for (int i = 0; i <= coefficients.size() - 1; ++i)
    {
        bool isZero = false;
        if (coefficients[i] == 0)
            isZero = true;

        wxString coefficient = wxString::Format(wxT("%.2f"), coefficients[i]);
        //trim trailing zeros
        coefficient.Trim().Trim(false);

        //If coefficient is 0, dont add it to equation
        if (isZero)
            coefficient = "";
        
        int power = textCtrls.size() - i - 1;
        
        equation << coefficient;

        if (power > 0){

            if (!isZero)
                equation << "x^" << power ;

            //If next coefficient is negative, dont add + sign
            if (i < textCtrls.size() - 1 && textCtrls[i + 1]->GetValue()[0] == '-')
                equation << " ";
            else
                //If next coefficient is not zero, add + sign
                if (i < textCtrls.size() - 1 && textCtrls[i + 1]->GetValue()[0] != '0')
                    equation << " + ";
        }
    }
        
    functionText->SetLabel(equation);
    Layout();
}

void Polynomial::Save()
{
    
    //fill all textCtrls with 0 if empty
    for (int i = 0; i <= textCtrls.size() - 1; ++i)
    {
        if (textCtrls[i]->GetValue().IsEmpty())
            textCtrls[i]->SetValue("0");
    }
    if (CheckInput())
        return;   
  
    InputToVector();
    ShowEquation();

   
}

void Polynomial::Calculate(){
    if (CheckInput())
        return;
    
    Bisection bisection(coefficients, a, b, epsilon);
    //solve equation for root
    short * errorCode = new short;
    //wxMessageBox("a = " + wxString::Format(wxT("%.2f"), a) + "\nb = " + wxString::Format(wxT("%.2f"), b) + "\nepsilon = " + wxString::Format(wxT("%.2f"), epsilon), "Info", wxICON_INFORMATION);
    double root = bisection.solve(errorCode);
    //f(a) and f(b) must have opposite signs
    double fx1 = bisection.f(a);
    double fx2 = bisection.f(b);
    switch (*errorCode)
    {
    case 0:
        wxMessageBox("Root = " + wxString::Format(wxT("%.15f"), root), "Info", wxICON_INFORMATION);
        //set outputText
        outputText->SetLabel("Root Found\n "+ wxString::Format(wxT("f( %.2f ) = 0") , root));
        break;
    case 1:
    //coefficients are empty
        wxMessageBox("Root not found! Invalid polynomial!", "Error", wxICON_ERROR);
        outputText->SetLabel("Root not found! Invalid polynomial!");
        break;
    case 2:
    //epsilon is empty
        wxMessageBox("Root not found! Invalid epsilon!", "Error", wxICON_ERROR);
        outputText->SetLabel("Root not found! Invalid epsilon!");
        break;
    case 3:
    //polynomial_degree must be non-negative
        wxMessageBox("Root not found! Invalid polynomial degree!", "Error", wxICON_ERROR);
        outputText->SetLabel("Root not found! Invalid polynomial degree!");
        break;
    case 4:
        
        wxMessageBox("Root not found! f(a) and f(b) must have opposite signs! \n f(a) = " + wxString::Format(wxT("%.2f"), fx1) + " f(b) = " + wxString::Format(wxT("%.2f"), fx2), "Error", wxICON_ERROR);
        outputText->SetLabel("Root not found! f(a) and f(b) must have opposite signs! \n f(a) = " + wxString::Format(wxT("%.2f"), fx1) + " f(b) = " + wxString::Format(wxT("%.2f"), fx2));
        break;
    default:
        wxMessageBox("Unknown error!", "Error", wxICON_ERROR);
        outputText->SetLabel("Unknown error!");
        break;
    }
    Layout();

}

bool Polynomial::CheckInput(){
  //Check if all coefficients are valid numbers
    for (int i = 0; i <= textCtrls.size() - 1; ++i)
    {
        wxString coefficient = textCtrls[i]->GetValue();
        //transform coefficient to double
        double coefficientDouble;
        if (!coefficient.ToDouble(&coefficientDouble))
        {
            wxMessageBox("Invalid coefficient!", "Error", wxICON_ERROR);
            return 1;
        }
    }
    return 0;
}