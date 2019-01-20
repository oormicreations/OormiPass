#ifndef DISCLAIMERDIALOG_H
#define DISCLAIMERDIALOG_H

//(*Headers(DisclaimerDialog)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
//*)

class DisclaimerDialog: public wxDialog
{
	public:

		DisclaimerDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~DisclaimerDialog();

		//(*Declarations(DisclaimerDialog)
		wxButton* ButtonAccept;
		wxButton* ButtonExit;
		wxTextCtrl* TextCtrlDis;
		//*)

	protected:

		//(*Identifiers(DisclaimerDialog)
		static const long ID_TEXTCTRL_DIS;
		static const long ID_BUTTON_ACC;
		static const long ID_BUTTON_EXIT;
		//*)

	private:

		//(*Handlers(DisclaimerDialog)
		void OnInit(wxInitDialogEvent& event);
		void OnButtonExitClick(wxCommandEvent& event);
		void OnButtonAcceptClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
