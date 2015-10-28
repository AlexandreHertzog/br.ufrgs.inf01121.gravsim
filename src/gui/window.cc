#include "window.hh"

/* Unfortunately, this is necessary. g++ points out many warning about internal
 * wxGLCanvas functions that are never used in our program, which causes a lot
 * of clutter in the terminal. This fixes the problem, though we may not know if
 * or when we'll use a deprecated function. */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

using namespace GravSim;

Gui::Window::Window(const wxString &title)
  : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(280, 180))
{
  // Alloc everything.
  menubar  = new wxMenuBar;
  filemenu = new wxMenu;
  canvas   = new Canvas(this);
  
  // Append the commands to the "File" menu.
  filemenu->Append(wxID_NEW, wxT("&Novo"));
  filemenu->Append(wxID_OPEN, wxT("&Abrir"));
  filemenu->Append(wxID_EXIT, wxT("&Sair"));
  
  // Append the menus to the 'menubar'.
  menubar->Append(filemenu, wxT("&Arquivo"));
  SetMenuBar(menubar);
  
  // Connect everything.
  Connect(wxID_NEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(
    Window::OnNew
  ));
  Connect(wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(
    Window::OnOpen
  ));
  Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(
    Window::OnQuit
  ));
  Centre();
}

void Gui::Window::OnNew(wxCommandEvent &WXUNUSED(event)) {
  
}

void Gui::Window::OnOpen(wxCommandEvent &WXUNUSED(event)) {
  
}

void Gui::Window::OnQuit(wxCommandEvent & WXUNUSED(event)) {
  Close(true);
}
