#ifndef GENPASSDIALOG_H
#define GENPASSDIALOG_H

//(*Headers(GenPassDialog)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class GenPassDialog: public wxDialog
{
	public:

		GenPassDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~GenPassDialog();

		//(*Declarations(GenPassDialog)
		wxButton* ButtonApplyPass;
		wxButton* ButtonGenPass;
		wxCheckBox* CheckBoxRnd;
		wxCheckBox* CheckBox_Mne;
		wxStaticBox* StaticBox1;
		wxStaticBox* StaticBox2;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticText* StaticText4;
		wxStaticText* StaticTextMaster1;
		wxStaticText* StaticTextMaster2;
		wxStaticText* StaticTextMasterWarn;
		wxTextCtrl* TextCtrlMaster1;
		wxTextCtrl* TextCtrlMaster2;
		wxTextCtrl* TextCtrlMnemonic;
		//*)

		bool m_bIsMaster;
		wxString m_sMaster, m_sIV;

	protected:

		//(*Identifiers(GenPassDialog)
		static const long ID_STATICBOX2;
		static const long ID_STATICBOX1;
		static const long ID_CHECKBOX_MNE;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL_MNEMO;
		static const long ID_STATICTEXT_MASTERWARN;
		static const long ID_STATICTEXT3;
		static const long ID_CHECKBOX_RND;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT_MASTER1;
		static const long ID_STATICTEXT_MASTER2;
		static const long ID_TEXTCTRL_MASTER1;
		static const long ID_TEXTCTRL_MASTER2;
		static const long ID_BUTTON_GENPASS;
		static const long ID_BUTTON_APPLYPASS;
		//*)

	private:

		//(*Handlers(GenPassDialog)
		void OnClose(wxCloseEvent& event);
		void OnCheckBox_MneClick(wxCommandEvent& event);
		void OnCheckBoxRndClick(wxCommandEvent& event);
		void OnButtonGenPassClick(wxCommandEvent& event);
		void OnButtonApplyPassClick(wxCommandEvent& event);
		void OnInit(wxInitDialogEvent& event);
		//*)

		void GenMnemonic(wxString str);
		void GenRandom();
		wxString GenRandomString();

		bool m_bIsMnemonic;
		bool m_bIsRandom;

		DECLARE_EVENT_TABLE()
};

#endif
