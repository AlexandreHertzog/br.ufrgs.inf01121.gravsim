#ifndef CUSTOMDIALOG_HH_
#define CUSTOMDIALOG_HH_

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <vector>


namespace GravSim {
namespace Gui {
        
class CustomDialog: public wxDialog {
public:
	CustomDialog(wxWindow* parent, const wxString &title,
                 const std::vector<wxString> fieldnames);
	virtual ~CustomDialog();
	void OnCancel(void);
	void OnOk(void);
	void OnCheckGrav(wxCommandEvent& pEvent);
    void OnCheckElec(wxCommandEvent& pEvent);

      int ShowModal(void);
    
    std::vector<int> GetIntInputs(void);
    std::vector<double> GetDoubleInputs(void);

	// inline bool getProcess()	{
	// 	return process_; }
	inline std::string getName()	{
		return nameTextCtrl_->GetValue().ToStdString();	}


    // Public for now!
    bool isElecCheck = false;
    bool isGravCheck = false;
	
private:
  enum {
    ID_UNUSED, ID_OK, ID_CANCEL, ID_INPUT
  };
	wxTextCtrl* nameTextCtrl_;
    int _dialogreturn;
    std::vector<wxTextCtrl*> _inputfields;
    std::vector<int> _convertedints;
    std::vector<double> _converteddoubles;

};
}
}
#endif
