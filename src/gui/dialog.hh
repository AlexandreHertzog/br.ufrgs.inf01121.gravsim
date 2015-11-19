#include <wx/wx.h>
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

private:
};

} // namespace Gui
} // namespace GravSim
