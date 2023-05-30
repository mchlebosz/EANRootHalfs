#ifndef BISECTION_POLYNOMIAL_H
#define BISECTION_POLYNOMIAL_H

#include <wx/wx.h>
#include <wx/scrolwin.h>
#include <vector>

class Polynomial : public wxPanel
{
private:
    wxScrolledWindow* scrollWindow;
    wxBoxSizer* scrollSizer;
    std::vector<wxTextCtrl*> textCtrls;
    std::vector<wxStaticText*> labels;
    wxStaticText* fxLabel;
    wxStaticText* outputText;

    wxTextCtrl* aInput;
    wxTextCtrl* bInput;
    wxTextCtrl* epsilonInput;

    wxButton* addButton;
    wxButton* removeButton;
    wxButton* saveButton;
    wxButton* calculateButton;


    wxPanel* functionPanel;
    wxStaticText* functionText;

    void OnAddButtonClick(wxCommandEvent& event);
    void OnCalculateButtonClick(wxCommandEvent& event);
    void OnSaveButtonClick(wxCommandEvent& event);
    void OnRemoveButtonClick(wxCommandEvent& event);


    void InputToVector();
    void ShowEquation();
    bool CheckInput();

    wxDECLARE_EVENT_TABLE();

    std::vector<double> coefficients;
    double a, b, epsilon;

public:
    void AddInputField();
    void RemoveInputField();
    void Save();
    void Calculate();
    Polynomial(wxWindow* parent);

    ~Polynomial();

};

#endif // BISECTION_POLYNOMIAL_H
