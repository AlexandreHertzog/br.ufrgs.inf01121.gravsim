#include <wx/wx.h>
#include <wx/textctrl.h>
#include <vector>


namespace GravSim {
namespace Gui {

class Dialog : public wxDialog {
public:
  Dialog(
    wxWindow *parent, const wxString &title, const std::vector<wxString> names
  );

  int ShowModal(void);

  std::vector<int> GetIntInputs(void);
  std::vector<double> GetDoubleInputs(void);
private:
  enum {
    ID_UNUSED, ID_OK, ID_CANCEL, ID_INPUT
  };
  void OnOk(void);
  void OnCancel(void);
  

  std::vector<wxTextCtrl*> _inputfields;
  std::vector<int> _convertedints;
  std::vector<double> _converteddoubles;
  int _dialogreturn;

};

} // namespace Gui
} // namespace GravSim
