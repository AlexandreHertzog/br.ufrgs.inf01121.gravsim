#include "window.h"

GravSimGui::Window::Window(const wxString &title)
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

void GravSimGui::Window::OnNew(wxCommandEvent &WXUNUSED(event)) {
  
}

void GravSimGui::Window::OnOpen(wxCommandEvent &WXUNUSED(event)) {
  
}

void GravSimGui::Window::OnQuit(wxCommandEvent & WXUNUSED(event)) {
  Close(true);
}
