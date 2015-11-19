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
  wxWindow *parent, const wxString &title, const vector<wxString> fieldnames,
  const vector<FieldType> fieldtypes
)
  : wxDialog(parent, -1, title)
{

  wxButton *okbutton = new wxButton(this, ID_OK, wxT("Ok"), wxDefaultPosition, wxSize(70, 30));
  wxButton *cancelbutton = new wxButton(this, ID_CANCEL, wxT("Cancelar"), wxDefaultPosition, wxSize(70, 30));
  wxStaticText *txt = new wxStaticText(this, ID_UNUSED, fieldnames[0]);

  _input = new wxTextCtrl(this, ID_INPUT, _("50"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
  wxSizerFlags flags;
    flags.Expand().Border(wxALL, 5);
 
  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);   
    vbox->Add(txt, flags);
    vbox->Add(_input, flags);
    vbox->Add(okbutton, flags);
    vbox->Add(cancelbutton, flags);
        
  SetSizer(vbox);

  Connect(ID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(
    Dialog::OnOk 
  ));
  Connect(ID_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(
    Dialog::OnCancel 
  ));
}

int Dialog::GetValue(void) {
  return _dialogreturn;
}

void Dialog::OnOk(wxCommandEvent &event) {
  const string value = static_cast<const char *>(_input->GetLineText(0).mb_str());
  try {
    _dialogreturn = std::stoi(value);
  } catch (const std::invalid_argument &onconverterror) {
    _dialogreturn = 0;
  }
  Close();
}

void Dialog::OnCancel(wxCommandEvent &event) {
  _dialogreturn = 0;
  Close();
}
