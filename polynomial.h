#ifndef BISECTION_POLYNOMIAL_H
#define BISECTION_POLYNOMIAL_H

#include <wx/scrolwin.h>
#include <wx/wx.h>

#include <vector>

// Defining a class named `Polynomial` that inherits from the `wxPanel` class.
// This means that the `Polynomial` class will have all the properties and
// methods of the `wxPanel` class, and can also have its own unique properties
// and methods.
class Polynomial : public wxPanel {
private:
	bool isInterval;
	wxScrolledWindow* scrollWindow;
	wxBoxSizer* scrollSizer;
	std::vector<wxTextCtrl*> textCtrls;
	std::vector<wxTextCtrl*> textCtrls2;
	std::vector<wxStaticText*> labels;
	wxStaticText* fxLabel;
	wxStaticText* outputText;

	wxTextCtrl* aInput;
	wxTextCtrl* aInput2;
	wxTextCtrl* bInput;
	wxTextCtrl* bInput2;
	wxTextCtrl* epsilonInput;

	wxButton* addButton;
	wxButton* removeButton;
	wxButton* saveButton;
	wxButton* calculateButton;

	wxSlider* approximationSlider;

	wxPanel* functionPanel;
	wxStaticText* functionText;

	void OnAddButtonClick(wxCommandEvent& event);
	void OnCalculateButtonClick(wxCommandEvent& event);
	void OnSaveButtonClick(wxCommandEvent& event);
	void OnRemoveButtonClick(wxCommandEvent& event);

	void InputToVector();
	void ShowEquation();
	bool CheckInput(bool onCalc = false);

	wxDECLARE_EVENT_TABLE();

	std::vector<double> coefficients;
	std::vector<double> coefficients2;
	double a, b, epsilon;
	double a2, b2, epsilon2;

public:
	void AddInputField();
	void RemoveInputField();
	void Save();
	void Calculate();
	Polynomial(wxWindow* parent, bool isInterval);
};

#endif    // BISECTION_POLYNOMIAL_H
