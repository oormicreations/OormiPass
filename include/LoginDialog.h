#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

//(*Headers(LoginDialog)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/statbox.h>
#include <wx/textctrl.h>
//*)


class LoginDialog: public wxDialog
{
	public:

		LoginDialog(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~LoginDialog();

		int m_iFailedAttempts;
		std::string m_sMaster;
		std::string m_sIV;

		//(*Declarations(LoginDialog)
		wxButton* ButtonNewMaster;
		wxButton* ButtonSubmitMaster;
		wxStaticBox* StaticBox1;
		wxTextCtrl* TextCtrlMasterPass;
		//*)

	protected:

		//(*Identifiers(LoginDialog)
		static const long ID_STATICBOX1;
		static const long ID_TEXTCTRL_MASTERPASS;
		static const long ID_BUTTON_SUBMASTER;
		static const long ID_BUTTON_NEWMASTER;
		//*)

	private:

		//(*Handlers(LoginDialog)
		void OnButtonSubmitMasterClick(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnButtonNewMasterClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
