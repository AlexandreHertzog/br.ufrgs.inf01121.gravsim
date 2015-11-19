#include <wx/wx.h>
#include <wx/textctrl.h>
#include <vector>


namespace GravSim {
namespace Gui {

enum class FieldType {
  INTEGER, DOUBLE
};

class Dialog : public wxDialog {
public:
  Dialog(
    wxWindow *parent, const wxString &title, const std::vector<wxString> fieldnames,
    const std::vector<FieldType> fieldtypes
  );

  int GetValue(void);

private:
  enum {
    ID_OK, ID_CANCEL, ID_INPUT, ID_UNUSED
  };
  void OnOk(wxCommandEvent &event);
  void OnCancel(wxCommandEvent &event);

  wxTextCtrl *_input;
  int _dialogreturn;
};

} // namespace Gui
} // namespace GravSim
