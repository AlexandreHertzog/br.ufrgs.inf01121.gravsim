#include "dialog.hh"

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/textctrl.h>

/* Unfortunately, this is necessary. g++ points out many warnings about internal
 * wxWidgets functions that are never used in our program, which causes a lot
 * of clutter in the terminal. This fixes the problem, though we may not know if
 * or when we'll use a deprecated function. */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

using namespace GravSim::Gui;
using std::string;
using std::vector;

Dialog::Dialog(
  wxWindow *parent, const wxString &title, const vector<wxString> fieldnames
)
  : wxDialog(parent, -1, title)
{
  wxButton *okbutton = new wxButton(this, wxID_OK, wxT("Ok"), wxDefaultPosition, wxSize(70, 30));
  wxButton *cancelbutton = new wxButton(this, wxID_CANCEL, wxT("Cancelar"), wxDefaultPosition, wxSize(70, 30));
  vector<wxStaticText*> texts;
    for (int i = 0; i < fieldnames.size(); i++) {
      texts.push_back(new wxStaticText(this, ID_UNUSED, fieldnames[i]));
      _inputfields.push_back(new wxTextCtrl(
          this, ID_INPUT, _("50"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER
      ));
    }

  wxSizerFlags flags;
    flags.Expand().Border(wxALL, 5);
 
  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);   
    for (int i = 0; i < fieldnames.size(); i++) {
      vbox->Add(texts[i], flags);
      vbox->Add(_inputfields[i], flags);
    }
    vbox->Add(okbutton, flags);
    vbox->Add(cancelbutton, flags);
        
  SetSizer(vbox);
  SetSize(wxSize(300, 70*fieldnames.size() + 90));
}

int Dialog::ShowModal(void) {
  if (wxDialog::ShowModal() == wxID_CANCEL) {
    OnCancel();
    return wxID_CANCEL;
  }
  OnOk();
  return wxID_OK;
}

vector<int> Dialog::GetIntInputs(void) {
  return _convertedints;
}

vector<double> Dialog::GetDoubleInputs(void) {
  return _converteddoubles;
}

void Dialog::OnOk(void) {
  _convertedints.clear();
  _converteddoubles.clear();
  for (int i = 0; i < _inputfields.size(); i++) {
    string line = static_cast<const char*>(_inputfields[i]->GetLineText(0).mb_str());
    int convertedint = 0;
    try {
      convertedint = std::atoi(line.c_str());
    } catch (const std::invalid_argument &e) {
    }
    _convertedints.push_back(convertedint);

    double converteddouble = 0.0;
    try {
      converteddouble = std::atof(line.c_str());
    } catch (const std::invalid_argument &e) {
    }
    _converteddoubles.push_back(converteddouble);
  }

  Close();
}

void Dialog::OnCancel(void) {
  _dialogreturn = 0;
  Close();
}
