#include "dialog.hh"

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/button.h>

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
  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

  wxButton *okbutton = new wxButton(this, ID_OK, wxT("Ok"), wxDefaultPosition, wxSize(70, 30));
  wxButton *cancelbutton = new wxButton(this, ID_CANCEL, wxT("Cancelar"), wxDefaultPosition, wxSize(70, 30));

  _sb = new wxSpinButton(this);
  _sb->SetRange(1, 100);
  _sb->SetValue(50);
  wxStaticText *txt = new wxStaticText(this, -1, fieldnames[0]);
    
  vbox->Add(txt, 1, wxALIGN_CENTER, wxEXPAND);
  vbox->Add(_sb, 1, wxALIGN_CENTER, wxEXPAND);
  vbox->Add(okbutton, 1, wxALIGN_CENTER, wxEXPAND);
  vbox->Add(cancelbutton, 1, wxALIGN_CENTER, wxEXPAND);
        
  SetSizer(vbox);

  Connect(ID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(
    Dialog::OnOk 
  ));
  Connect(ID_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(
    Dialog::OnCancel 
  ));
}

void Dialog::OnOk(wxCommandEvent &event) {
  _dialogreturn = _sb->GetValue();
  Close();
}

void Dialog::OnCancel(wxCommandEvent &event) {
  _dialogreturn = 0;
  Close();
}
