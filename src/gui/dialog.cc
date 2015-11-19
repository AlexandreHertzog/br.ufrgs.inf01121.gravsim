#include "dialog.hh"

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/spinbutt.h>
#include <wx/button.h>

using namespace GravSim::Gui;
using std::string;
using std::vector;

Dialog::Dialog(
  wxWindow *parent, const wxString &title, const vector<wxString> fieldnames,
  const vector<FieldType> fieldtypes
)
  : wxDialog(parent, -1, title)
{
  wxPanel *panel = new wxPanel(this, -1);
  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

  wxGridSizer *labelsandfields = new wxGridSizer(fieldnames.size(), 2, 10, 10);
  for (int i = 0; i < fieldnames.size(); i++) {
    labelsandfields->Add(new wxStaticText(this, -1, fieldnames[i]), 0, wxEXPAND);
    if (fieldtypes[i] == FieldType::INTEGER) {
      labelsandfields->Add(new wxSpinButton(this), 0, wxEXPAND);
    }
  }

  wxButton *okButton = new wxButton(this, -1, wxT("Ok"), wxDefaultPosition, wxSize(70, 30));
  wxButton *closeButton = new wxButton(this, -1, wxT("Close"), wxDefaultPosition, wxSize(70, 30));

  hbox->Add(okButton, 1);
  hbox->Add(closeButton, 1, wxLEFT, 5);
    
  vbox->Add(panel, 1);
  vbox->Add(labelsandfields, 2);
  vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
        
  SetSizer(vbox);
}

