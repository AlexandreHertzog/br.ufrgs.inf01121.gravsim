/* Unfortunately, this is necessary. g++ points out many warnings about internal
 * wxWidgets functions that are never used in our program, which causes a lot
 * of clutter in the terminal. This fixes the problem, though we may not know if
 * or when we'll use a deprecated function. */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "window.hh"

#include <wx/filedlg.h>
#include <wx/string.h>

#include "dialog.hh"

using namespace GravSim;
using GravSim::Gui::Dialog;

Gui::Window::Window(const wxString &title)
  : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 600))
{
  // Alloc everything.
  _menubar   = new wxMenuBar;
  _filemenu  = new wxMenu;
  _editmenu  = new wxMenu;
  _simmenu   = new wxMenu;
  //_statusbar = new wxStatusBar(this, wxID_ANY, wxST_SIZEGRIP, wxT("statusbar"));
  
  // Append the commands to the "File" menu.
  _filemenu->Append(wxID_NEW, wxT("&Novo"));
  _filemenu->Append(wxID_OPEN, wxT("Abrir (&O)"));
  _filemenu->Append(wxID_SAVE, wxT("&Salvar"));
  _filemenu->Append(ID_SAVE_AS, wxT("Salvar como"));
  _filemenu->Append(wxID_EXIT, wxT("Sair(&Q)"));
  
  // Append the commands to the "Edit" menu
  _editmenu->Append(ID_ADD_PART, wxT("&Adicionar partícula"));
  
  // Append the commands to the "Simulation" menu
  _simmenu->Append(ID_PAUSE, wxT("&Pausar"));
  _simmenu->Append(ID_RESUME, wxT("&Continuar"));
  _simmenu->Append(ID_STOP, wxT("Pa&rar"));
  _simmenu->Append(ID_STEP, wxT("Pa&sso"));
  
  // Append the menus to the 'menubar'.
  _menubar->Append(_filemenu, wxT("&Arquivo"));
  _menubar->Append(_editmenu, wxT("&Editar"));
  _menubar->Append(_simmenu, wxT("&Simulação"));
  SetMenuBar(_menubar);
  
  // Connect everything.
  Connect(wxID_NEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(
    Window::OnNew
  ));
  Connect(wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(
    Window::OnOpen
  ));
  Connect(wxID_SAVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(
    Window::OnSave
  ));
  Connect(ID_SAVE_AS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(
    Window::OnSaveAs
  ));
  Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(
    Window::OnQuit
  ));
  
  Connect(ID_ADD_PART, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(
    Window::OnAddParticle
  ));

  Connect(ID_PAUSE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(
    Window::OnPause
  ));
  Connect(ID_RESUME, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(
    Window::OnResume
  ));
  Connect(ID_STOP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(
    Window::OnStop
  ));
  Connect(ID_STEP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(
    Window::OnStep
  ));

  Centre();
}

Gui::Window::~Window(void) {
  // Well, we can't really delete anything from wx unless we want segfaults.
  //delete _simmenu;
  //delete _editmenu;
  //delete _filemenu;
  //delete _menubar;
}

void Gui::Window::SetCanvas(std::unique_ptr<Canvas> canvas) {
  _canvas = std::move(canvas);
}

void Gui::Window::UpdateCanvas(void) {
  if (_canvas) {
    _canvas->Refresh();
  }
}

void Gui::Window::OnNew(wxCommandEvent &WXUNUSED(event)) {
  Dialog numparticlesdialog(
    this, _("Nova simulação"), {_("Quantidade de partículas: ")}
  );
  if (numparticlesdialog.ShowModal() == wxID_OK) {
    const int numparts = numparticlesdialog.GetIntInputs()[0];
    if (numparts > 0) {
      GenerateRandom(numparts);
    }
  }
  if (_canvas) {
    _canvas->Refresh();
  }
}

void Gui::Window::OnOpen(wxCommandEvent &WXUNUSED(event)) {
  wxFileDialog opendialog(
    this, wxT("Abrir arquivo"), wxT(""), wxT(""),
    wxT("arquivos gsim (*.gsim)|*.gsim"), wxFD_OPEN | wxFD_FILE_MUST_EXIST
  );

  if (opendialog.ShowModal() == wxID_CANCEL) {
    return;
  }

  const std::string filename = static_cast<const char*>(opendialog.GetPath().mb_str());
  LoadParticlesFromFile(filename);
  if (_canvas) {
    _canvas->Refresh();
  }
}

void Gui::Window::OnSave(wxCommandEvent &event) {
  if (GetFilename() == "default.gsim") {
    OnSaveAs(event);
    return;
  }
  SaveParticlesToFile();
}

void Gui::Window::OnSaveAs(wxCommandEvent &WXUNUSED(event)) {
  wxFileDialog savedialog(
    this, wxT("Salvar arquivo"), wxT(""), wxT(""),
    wxT("arquivos gsim (*.gsim)|*.gsim"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT
  );

  if (savedialog.ShowModal() == wxID_CANCEL) {
    return;
  }

  std::string filename = static_cast<const char*>(savedialog.GetPath().mb_str());
  std::string extension = filename.substr(filename.length() - 5);
  if (extension != ".gsim") {
    filename.append(".gsim");
  }
  SaveParticlesToFile(filename);
}

void Gui::Window::OnQuit(wxCommandEvent & WXUNUSED(event)) {
  Close(true);
}

void Gui::Window::OnAddParticle(wxCommandEvent &WXUNUSED(event)) {
  Dialog addpartdialog(
    this, _("Adicionar partícula"), {_("Massa: "), _("Posição x:"), _("Posição y: ")}
  );
  if (addpartdialog.ShowModal() == wxID_OK) {
    vector<double> params = addpartdialog.GetDoubleInputs();
    AddParticle(params);
  }
}

