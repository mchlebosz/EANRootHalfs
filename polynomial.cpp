#include "polynomial.h"

#include <iomanip>
#include <sstream>

#include "bisection.h"

wxBEGIN_EVENT_TABLE(Polynomial,
					wxPanel) EVT_BUTTON(wxID_ANY, Polynomial::OnAddButtonClick)
	EVT_BUTTON(wxID_ANY, Polynomial::OnRemoveButtonClick)
		EVT_BUTTON(wxID_ANY, Polynomial::OnSaveButtonClick)
			EVT_BUTTON(wxID_ANY, Polynomial::OnCalculateButtonClick)
				wxEND_EVENT_TABLE()

					Polynomial::Polynomial(wxWindow *parent, bool isInterval) :
	wxPanel(parent, wxID_ANY), isInterval(isInterval) {
	wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

	// Create the upper part with a horizontal scroll window
	scrollWindow = new wxScrolledWindow(this, wxID_ANY);

	scrollSizer = new wxBoxSizer(wxHORIZONTAL);
	scrollSizer->SetMinSize(wxSize(1000, 100));

	scrollWindow->SetSizer(scrollSizer);
	scrollWindow->SetScrollRate(10, 10);
	scrollWindow->SetMinSize(wxSize(1000, 100));

	mainSizer->Add(scrollWindow, 0, wxEXPAND | wxALL, 5);

	// Create the bottom part (static part) with buttons
	wxBoxSizer *coefficientButtons = new wxBoxSizer(wxHORIZONTAL);

	addButton    = new wxButton(this, wxID_ANY, "Add");
	removeButton = new wxButton(this, wxID_ANY, "Remove");
	saveButton   = new wxButton(this, wxID_ANY, "Save");

	coefficientButtons->Add(addButton, 0, wxALL, 10);
	coefficientButtons->Add(removeButton, 0, wxALL, 10);
	coefficientButtons->Add(saveButton, 0, wxALL, 10);

	mainSizer->Add(isInterval, 0, wxALL | wxALIGN_CENTER, 3);

	mainSizer->Add(coefficientButtons, 0, wxALIGN_CENTER);

	SetSizerAndFit(mainSizer);

	// Bind button events
	addButton->Bind(wxEVT_BUTTON, &Polynomial::OnAddButtonClick, this);
	removeButton->Bind(wxEVT_BUTTON, &Polynomial::OnRemoveButtonClick, this);
	saveButton->Bind(wxEVT_BUTTON, &Polynomial::OnSaveButtonClick, this);

	// Create initial input fields
	for (int i = 0; i < 3; ++i) {
		AddInputField();
	}

	// Set the fixed height for the scrollable container
	scrollWindow->SetScrollRate(10, 10);

	// Create the output panel
	functionPanel = new wxPanel(this);
	functionPanel->SetBackgroundColour(wxColour(240, 240, 240));

	functionText =
		new wxStaticText(functionPanel, wxID_ANY, "", wxDefaultPosition,
						 wxDefaultSize, wxALIGN_LEFT);
	wxBoxSizer *functionPreviewSizer = new wxBoxSizer(wxVERTICAL);
	functionPreviewSizer->Add(functionText, 0, wxALL, 10);
	functionPanel->SetSizer(functionPreviewSizer);

	mainSizer->Add(functionPanel, 0, wxEXPAND | wxALL, 10);

	wxBoxSizer *paramInput = new wxBoxSizer(wxVERTICAL);
	calculateButton        = new wxButton(this, wxID_ANY, "Calculate");
	calculateButton->Bind(wxEVT_BUTTON, &Polynomial::OnCalculateButtonClick,
						  this);

	wxBoxSizer *approxSizer = new wxBoxSizer(wxVERTICAL);
	const wxSize approxSize = wxSize(200, 50);

	approximationSlider =
		new wxSlider(this, wxID_ANY, 4, 1, 64, wxDefaultPosition, approxSize,
					 wxSL_HORIZONTAL | wxSL_LABELS);
	approximationSlider->SetTickFreq(1);
	wxStaticText *approximationLabel =
		new wxStaticText(this, wxID_ANY, "Precision:", wxDefaultPosition,
						 wxDefaultSize, wxALIGN_LEFT);

	approxSizer->Add(approximationLabel, 0, wxTOP | wxALIGN_CENTER, 20);
	approxSizer->Add(approximationSlider, 0, wxALL | wxALIGN_CENTER, 3);

	if (isInterval) {
		approximationSlider->Hide();
		approximationLabel->Hide();
	}

	// input for a,b, epsilon
	wxStaticText *aLabel = new wxStaticText(
		this, wxID_ANY, "a = ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxStaticText *bLabel = new wxStaticText(
		this, wxID_ANY, "b = ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxStaticText *epsilonLabel =
		new wxStaticText(this, wxID_ANY, "epsilon = ", wxDefaultPosition,
						 wxDefaultSize, wxALIGN_LEFT);
	aInput             = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition,
										wxDefaultSize, wxTE_PROCESS_ENTER);
	bInput             = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition,
										wxDefaultSize, wxTE_PROCESS_ENTER);
	epsilonInput       = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition,
										wxDefaultSize, wxTE_PROCESS_ENTER);
	wxBoxSizer *aSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *bSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *epsilonSizer = new wxBoxSizer(wxHORIZONTAL);
	aSizer->Add(aLabel, 0, wxALL | wxALIGN_CENTER, 5);
	aSizer->Add(aInput, 0, wxALL | wxALIGN_CENTER, 5);
	if (isInterval) {
		aInput2 =
			new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
						   wxDefaultSize, wxTE_PROCESS_ENTER);
		aSizer->Add(aInput2, 0, wxALL | wxALIGN_CENTER, 5);
	}
	bSizer->Add(bLabel, 0, wxALL | wxALIGN_CENTER, 5);
	bSizer->Add(bInput, 0, wxALL | wxALIGN_CENTER, 5);
	if (isInterval) {
		bInput2 =
			new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
						   wxDefaultSize, wxTE_PROCESS_ENTER);
		bSizer->Add(bInput2, 0, wxALL | wxALIGN_CENTER, 5);
	}
	epsilonSizer->Add(epsilonLabel, 0, wxALL | wxALIGN_CENTER, 5);
	epsilonSizer->Add(epsilonInput, 0, wxALL | wxALIGN_CENTER, 5);

	paramInput->Add(aSizer, 0, wxALL | wxALIGN_CENTER, 1);
	paramInput->Add(bSizer, 0, wxALL | wxALIGN_CENTER, 1);
	paramInput->Add(epsilonSizer, 0, wxALL | wxALIGN_CENTER, 1);
	if (!isInterval) {
		paramInput->Add(approxSizer, 0, wxALL | wxALIGN_CENTER, 3);
	}

	paramInput->Add(calculateButton, 0, wxALL | wxALIGN_CENTER, 3);

	// output
	wxStaticText *outputLabel =
		new wxStaticText(this, wxID_ANY, "Output: ", wxDefaultPosition,
						 wxDefaultSize, wxALIGN_LEFT);
	outputText = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition,
								  wxDefaultSize, wxALIGN_LEFT);
	wxBoxSizer *outputSizer = new wxBoxSizer(wxHORIZONTAL);
	outputSizer->Add(outputLabel, 0, wxALL | wxALIGN_CENTER, 5);
	outputSizer->Add(outputText, 0, wxALL | wxALIGN_CENTER, 5);
	paramInput->Add(outputSizer, 0, wxALL | wxALIGN_CENTER, 10);

	mainSizer->Add(paramInput, 0, wxALIGN_CENTER);

	coefficientButtons->Layout();
	mainSizer->Layout();
	Layout();
}

void Polynomial::OnAddButtonClick(wxCommandEvent &event) {
	AddInputField();
}

void Polynomial::OnSaveButtonClick(wxCommandEvent &event) {
	Save();
}
void Polynomial::OnCalculateButtonClick(wxCommandEvent &event) {
	Save();

	// check if a,b,epsilon are numbers
	if (aInput->GetValue().ToDouble(&a) == false ||
		bInput->GetValue().ToDouble(&b) == false ||
		epsilonInput->GetValue().ToDouble(&epsilon) == false) {
		wxMessageBox("Please enter numbers for a, b and epsilon", "Error",
					 wxICON_ERROR);
		return;
	}
	if (isInterval) {
		if (aInput2->GetValue().ToDouble(&a2) == false ||
			bInput2->GetValue().ToDouble(&b2) == false) {
			wxMessageBox("Please enter numbers for a2 and b2", "Error",
						 wxICON_ERROR);
			return;
		}
	}
	if (epsilon == 0) {
		wxMessageBox("Please set epsilon to != 0", "Error", wxICON_ERROR);
		return;
	}

	Calculate();
}

void Polynomial::AddInputField() {
	int power = textCtrls.size();

	wxString labelText;
	if (power > 0)
		labelText << "x^" << power << " + ";
	else
		labelText << "";

	// Create the static text for the coefficient label
	wxStaticText *label =
		new wxStaticText(scrollWindow, wxID_ANY, labelText, wxDefaultPosition,
						 wxDefaultSize, wxALIGN_CENTER);
	scrollSizer->Insert(0, label, 0, wxALL, 5);

	wxTextCtrl *textCtrl =
		new wxTextCtrl(scrollWindow, wxID_ANY, wxEmptyString, wxDefaultPosition,
					   wxDefaultSize, wxTE_PROCESS_ENTER);
	scrollSizer->Insert(0, textCtrl, 0, wxALL, 5);

	textCtrls.insert(textCtrls.begin(), textCtrl);

	if (isInterval) {
		wxTextCtrl *textCtrl2 = new wxTextCtrl(
			scrollWindow, wxID_ANY, wxEmptyString, wxDefaultPosition,
			wxDefaultSize, wxTE_PROCESS_ENTER);
		scrollSizer->Insert(0, textCtrl2, 0, wxALL, 5);
		textCtrls2.insert(textCtrls2.begin(), textCtrl2);
	}

	labels.insert(labels.begin(), label);

	scrollSizer->Layout();
	scrollWindow->Scroll(0, 0);

	Layout();
}

void Polynomial::RemoveInputField() {
	if (textCtrls.size() > 1) {
		wxTextCtrl *firstTextCtrl = textCtrls.front();
		scrollSizer->Detach(firstTextCtrl);
		firstTextCtrl->Destroy();
		textCtrls.erase(textCtrls.begin());

		if (isInterval) {
			wxTextCtrl *firstTextCtrl2 = textCtrls2.front();
			scrollSizer->Detach(firstTextCtrl2);
			firstTextCtrl2->Destroy();
			textCtrls2.erase(textCtrls2.begin());
		}

		wxStaticText *firstLabel = labels.front();
		scrollSizer->Detach(firstLabel);
		firstLabel->Destroy();
		labels.erase(labels.begin());

		scrollSizer->Layout();
	}
	Layout();
}

void Polynomial::OnRemoveButtonClick(wxCommandEvent &event) {
	RemoveInputField();
}

void Polynomial::InputToVector() {
	coefficients.clear();
	for (int i = 0; i <= textCtrls.size() - 1; ++i) {
		wxString coefficient = textCtrls[i]->GetValue();
		// transform coefficient to double
		double coefficientDouble;
		coefficient.ToDouble(&coefficientDouble);
		coefficients.push_back(coefficientDouble);
	}

	if (isInterval) {
		coefficients2.clear();
		for (int i = 0; i <= textCtrls2.size() - 1; ++i) {
			wxString coefficient = textCtrls2[i]->GetValue();
			// transform coefficient to double
			double coefficientDouble;
			coefficient.ToDouble(&coefficientDouble);
			coefficients2.push_back(coefficientDouble);
		}
	}
}

void Polynomial::ShowEquation() {
	wxString equation = "f(x) = ";

	if (!isInterval) {
		for (int i = 0; i <= coefficients.size() - 1; ++i) {
			bool isZero = (coefficients[i] == 0);

			wxString coefficient =
				wxString::Format(wxT("%.2f"), coefficients[i]);
			// trim trailing zeros
			coefficient.Trim().Trim(false);

			// If coefficient is 0, dont add it to equation
			if (isZero) coefficient = "";

			int power = textCtrls.size() - i - 1;

			equation << coefficient;

			if (power > 0) {
				if (!isZero) equation << "x^" << power;

				// If next coefficient is negative, dont add + sign
				if (i < textCtrls.size() - 1 &&
					textCtrls[i + 1]->GetValue()[0] == '-')
					equation << " ";
				else
					// If next coefficient is not zero, add + sign
					if (i < textCtrls.size() - 1 &&
						textCtrls[i + 1]->GetValue()[0] != '0')
						equation << " + ";
			}
		}
	} else {
		for (size_t i = 0; i <= coefficients.size() - 1; ++i) {
			bool isZero = (coefficients[i] == 0 && coefficients2[i] == 0);
			wxString leftCoefficient =
				wxString::Format(wxT("%.2f"), coefficients2[i]);
			wxString rightCoefficient =
				wxString::Format(wxT("%.2f"), coefficients[i]);
			// trim trailing zeros
			leftCoefficient.Trim().Trim(false);
			rightCoefficient.Trim().Trim(false);

			// If coefficient is 0, dont add it to equation
			if (isZero)
				leftCoefficient = rightCoefficient = "";
			else {
				leftCoefficient  = "[" + leftCoefficient + ",";
				rightCoefficient = rightCoefficient + "]";
			}

			int power = textCtrls.size() - i - 1;

			equation << leftCoefficient << rightCoefficient;
			if (power > 0) {
				if (!isZero) equation << "x^" << power;

				// If next coefficient is not zero, add + sign
				if (i < textCtrls.size() - 1 &&
					textCtrls[i + 1]->GetValue()[0] != '0' &&
					textCtrls2[i + 1]->GetValue()[0] != '0')
					equation << " + ";
			}
		}
	}

	functionText->SetLabel(equation);
	Layout();
}

void Polynomial::Save() {
	// fill all empty textCtrls2 with textCtrls values if empty
	if (isInterval) {
		for (int i = 0; i <= textCtrls.size() - 1; ++i) {
			if (textCtrls[i]->GetValue().IsEmpty() &&
				textCtrls2[i]->GetValue().IsEmpty())
				textCtrls[i]->SetValue("0");
			if (textCtrls[i]->GetValue().IsEmpty())
				textCtrls[i]->SetValue(textCtrls2[i]->GetValue());
			if (textCtrls2[i]->GetValue().IsEmpty())
				textCtrls2[i]->SetValue(textCtrls[i]->GetValue());
		}

		// set a2 and b2 to a and b if are empty (for interval)

		if (aInput2->GetValue().IsEmpty()) {
			aInput2->SetValue(aInput->GetValue());
		}
		if (bInput2->GetValue().IsEmpty()) {
			bInput2->SetValue(bInput->GetValue());
		}
	} else {
		// fill all textCtrls with 0 if empty
		for (int i = 0; i <= textCtrls.size() - 1; ++i) {
			if (textCtrls[i]->GetValue().IsEmpty()) textCtrls[i]->SetValue("0");
		}
	}
	if (CheckInput()) return;

	InputToVector();
	ShowEquation();
}

void Polynomial::Calculate() {
	if (CheckInput(true)) return;

	short *errorCode             = new short;
	int approximationSliderValue = approximationSlider->GetValue();
	std::ostringstream ostream;
	std::string stringRoot;
	wxString fx1;
	wxString fx2;
	interval_arithmetic::Interval<double> rootInv;
	double root;

	if (isInterval) {
		double *intervalWidth = new double;
		BisectionInterval bisectIntv(coefficients2, coefficients, a2, b2, a, b,
									 epsilon, 10);
		// solve equation for root
		wxString fx1 = wxString::Format(
			wxT("%.4f , %.4f"),
			bisectIntv.f(interval_arithmetic::Interval<double>(a2, a)).a,
			bisectIntv.f(interval_arithmetic::Interval<double>(a2, a)).b);
		wxString fx2 = wxString::Format(
			wxT("%.4f , %.4f"),
			bisectIntv.f(interval_arithmetic::Interval<double>(b2, b)).a,
			bisectIntv.f(interval_arithmetic::Interval<double>(b2, b)).b);

		rootInv = bisectIntv.solve(errorCode);
	} else {
		Bisection bisection(coefficients, a, b, epsilon);
		// solve equation for root
		// wxMessageBox("a = " + wxString::Format(wxT("%.2f"), a) + "\nb = " +
		// wxString::Format(wxT("%.2f"), b) + "\nepsilon = " +
		// wxString::Format(wxT("%.2f"), epsilon), "Info", wxICON_INFORMATION);
		root = bisection.solve(errorCode);
		// f(a) and f(b) must have opposite signs
		wxString fx1 = wxString::Format(wxT("%.2f"), bisection.f(a));
		wxString fx2 = wxString::Format(wxT("%.2f"), bisection.f(b));
	}

	switch (*errorCode) {
		case 0:
			if (isInterval) {
				std::string leftInv;
				std::string rightInv;
				std::ostringstream ostream;
				rootInv.IEndsToStrings(leftInv, rightInv);
				ostream << "[" << leftInv << " , " << rightInv << "]"
						<< "\nWidth: " << rootInv.GetWidth();
				stringRoot = ostream.str();
				wxMessageBox("Root = " + stringRoot, "Info",
							 wxICON_INFORMATION);

				// set outputText
				outputText->SetLabel("Root Found\n " + stringRoot);
				break;
			} else {
				ostream << std::scientific
						<< std::setprecision(approximationSliderValue) << root;
				stringRoot = ostream.str();
				wxMessageBox(("Root = " + stringRoot), "Info",
							 wxICON_INFORMATION);

				// set outputText
				outputText->SetLabel("Root Found\n " + stringRoot);
				break;
			}

		case 1:
			// coefficients are empty
			wxMessageBox("Root not found! Invalid polynomial!", "Error",
						 wxICON_ERROR);
			outputText->SetLabel("Root not found! Invalid polynomial!");
			break;
		case 2:
			// epsilon is empty
			wxMessageBox("Root not found! Invalid epsilon!", "Error",
						 wxICON_ERROR);
			outputText->SetLabel("Root not found! Invalid epsilon!");
			break;
		case 3:
			// polynomial_degree must be non-negative
			wxMessageBox("Root not found! Invalid polynomial degree!", "Error",
						 wxICON_ERROR);
			outputText->SetLabel("Root not found! Invalid polynomial degree!");
			break;
		case 4:

			wxMessageBox(
				"Root not found! f(a) and f(b) must have opposite signs! \n f(a) = " +
					fx1 + " f(b) = " + fx2,
				"Error", wxICON_ERROR);
			outputText->SetLabel(
				"Root not found! f(a) and f(b) must have opposite signs! \n f(a) = " +
				fx1 + " f(b) = " + fx2);
			break;
		case 55:
			if (isInterval) {
				std::string leftInv;
				std::string rightInv;
				std::ostringstream ostream;
				rootInv.IEndsToStrings(leftInv, rightInv);
				ostream << "[" << leftInv << " , " << rightInv << "]";
				stringRoot = ostream.str();

				wxMessageBox(
					"Root not found! Too many iterations!\nClosest calculated root:" +
						stringRoot,
					"Error", wxICON_ERROR);
				outputText->SetLabel(
					"Root not found! Too many iterations!\nClosest calculated root:" +
					stringRoot);
				break;
			} else {
				ostream << std::scientific
						<< std::setprecision(approximationSliderValue) << root;
				stringRoot = ostream.str();

				wxMessageBox(
					"Root not found! Too many iterations!\nClosest calculated root:" +
						stringRoot,
					"Error", wxICON_ERROR);
				outputText->SetLabel(
					"Root not found! Too many iterations!\nClosest calculated root:" +
					stringRoot);
				break;
			}
		default:
			wxMessageBox("Unknown error!", "Error", wxICON_ERROR);
			outputText->SetLabel("Unknown error!");
			break;
	}
	Layout();
}

bool Polynomial::CheckInput(bool onCalc) {
	// Check if all coefficients are valid numbers
	for (int i = 0; i <= textCtrls.size() - 1; ++i) {
		wxString coefficient = textCtrls[i]->GetValue();
		// transform coefficient to double
		double coefficientDouble;
		if (!coefficient.ToDouble(&coefficientDouble)) {
			wxMessageBox("Invalid coefficient!", "Error", wxICON_ERROR);
			return 1;
		}
	}

	if (isInterval) {
		// check if textCtrls2 size is equal to textCtrls size
		if (textCtrls2.size() != textCtrls.size()) {
			wxMessageBox("Invalid interval!\nUnknown Error", "Error",
						 wxICON_ERROR);
			return 1;
		}
		// Check if all coefficients are valid numbers
		for (int i = 0; i <= textCtrls2.size() - 1; ++i) {
			wxString coefficient2 = textCtrls2[i]->GetValue();
			// transform coefficient to double
			double coefficientDouble2;
			if (!coefficient2.ToDouble(&coefficientDouble2)) {
				wxMessageBox("Invalid coefficient!", "Error", wxICON_ERROR);
				return 1;
			}

			wxString coefficient = textCtrls[i]->GetValue();
			// transform coefficient to double
			double coefficientDouble;
			coefficient.ToDouble(&coefficientDouble);

			// Check if coefficient1 is > coefficient2
			if (coefficientDouble2 > coefficientDouble) {
				wxMessageBox(
					"Invalid interval!\nLeft boundary must be <= right boundary!",
					"Error", wxICON_ERROR);
				return 1;
			}
		}

		// Check if a2 is valid number
		wxString a2String = aInput2->GetValue();
		double a2Double;
		if (!a2String.ToDouble(&a2Double)) {
			wxMessageBox("Invalid a!", "Error", wxICON_ERROR);
			return 1;
		}

		// Check if b2 is valid number
		wxString b2String = bInput2->GetValue();
		double b2Double;
		if (!b2String.ToDouble(&b2Double)) {
			wxMessageBox("Invalid b!", "Error", wxICON_ERROR);
			return 1;
		}
	}

	if (!onCalc) return 0;

	// Check if epsilon is valid number
	wxString epsilonString = epsilonInput->GetValue();
	double epsilonDouble;
	if (!epsilonString.ToDouble(&epsilonDouble)) {
		wxMessageBox("Invalid epsilon!", "Error", wxICON_ERROR);
		return 1;
	}

	// Check if a is valid number
	wxString aString = aInput->GetValue();
	double aDouble;
	if (!aString.ToDouble(&aDouble)) {
		wxMessageBox("Invalid a!", "Error", wxICON_ERROR);
		return 1;
	}

	// Check if b is valid number
	wxString bString = bInput->GetValue();
	double bDouble;
	if (!bString.ToDouble(&bDouble)) {
		wxMessageBox("Invalid b!", "Error", wxICON_ERROR);
		return 1;
	}

	// Check if a < b
	std::cout << aDouble << " " << bDouble << std::endl;
	if (aDouble >= bDouble) {
		wxMessageBox("Invalid a and b! a must be less than b!", "Error",
					 wxICON_ERROR);
		return 1;
	}

	return 0;
}
