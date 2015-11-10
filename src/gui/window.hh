// Copied from https://wiki.wxwidgets.org/WxGLCanvas

#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/statusbr.h>

#include <memory>

#include "canvas.hh"

namespace GravSim {
namespace Gui {

class Window : public wxFrame {
public:
  // Constructor and destructor.
  Window(const wxString &title);
  ~Window(void);
  void SetCanvas(std::unique_ptr<Canvas> canvas);

protected:
  // These functions must come from the Storage class.
  virtual void SavePointsToFile(const std::string filename = "") = 0;
  virtual void LoadPointsFromFile(const std::string filename = "") = 0;
  virtual void GenerateRandom(const size_t numparticles) = 0;
  virtual const std::string GetFilename(void) = 0;

private:
  enum {
    ID_SAVE_AS,
    ID_ADD_PART,
    ID_PAUSE,
    ID_RESUME,
    ID_STOP,
    ID_STEP
  };
  // Connection functions.
  void OnQuit(wxCommandEvent &event);
  void OnNew(wxCommandEvent &event);
  void OnSave(wxCommandEvent &event);
  void OnSaveAs(wxCommandEvent &event);
  void OnOpen(wxCommandEvent &event);
  
  void OnAddParticle(wxCommandEvent &event);
  
  void OnPause(wxCommandEvent &event);
  void OnResume(wxCommandEvent &event);
  void OnStop(wxCommandEvent &event);
  void OnStep(wxCommandEvent &event);
  
  // Internal variables.
  // 'menubar' is the bar below the window title bar.
  wxMenuBar *_menubar;
  // Below, the menus that will be embedded inside the 'menubar'.
  wxMenu    *_filemenu;
  wxMenu    *_editmenu;
  wxMenu    *_simmenu;
  // Canvas is the middle class between the interface and the OpenGL canvas.
  std::unique_ptr<Canvas> _canvas;
}; // class Window
}; // namespace Gui
}; // namespace GravSim
