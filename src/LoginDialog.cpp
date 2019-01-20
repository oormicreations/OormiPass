#include "LoginDialog.h"
#include <wx/msgdlg.h>
#include "GenPassDialog.h"
#include "CryptHelper.h"
#include "FileHelper.h"
#include "oormipassMain.h"

//(*InternalHeaders(LoginDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(LoginDialog)
const long LoginDialog::ID_STATICBOX1 = wxNewId();
const long LoginDialog::ID_TEXTCTRL_MASTERPASS = wxNewId();
const long LoginDialog::ID_BUTTON_SUBMASTER = wxNewId();
const long LoginDialog::ID_BUTTON_NEWMASTER = wxNewId();
//*)

BEGIN_EVENT_TABLE(LoginDialog,wxDialog)
	//(*EventTable(LoginDialog)
	//*)
END_EVENT_TABLE()

LoginDialog::LoginDialog(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(LoginDialog)
	Create(parent, wxID_ANY, _("Oormi Pass :: Password Manager"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxMINIMIZE_BOX, _T("wxID_ANY"));
	SetClientSize(wxSize(358,96));
	wxFont thisFont(8,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
	SetFont(thisFont);
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("Enter Master Password"), wxPoint(16,8), wxSize(320,72), 0, _T("ID_STATICBOX1"));
	TextCtrlMasterPass = new wxTextCtrl(this, ID_TEXTCTRL_MASTERPASS, wxEmptyString, wxPoint(32,32), wxSize(208,23), wxTE_PASSWORD, wxDefaultValidator, _T("ID_TEXTCTRL_MASTERPASS"));
	ButtonSubmitMaster = new wxButton(this, ID_BUTTON_SUBMASTER, _("Go"), wxPoint(248,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SUBMASTER"));
	ButtonSubmitMaster->SetDefault();
	ButtonNewMaster = new wxButton(this, ID_BUTTON_NEWMASTER, _("New Master Password"), wxPoint(32,64), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_NEWMASTER"));
	ButtonNewMaster->Hide();
	Center();

	Connect(ID_BUTTON_SUBMASTER,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LoginDialog::OnButtonSubmitMasterClick);
	Connect(ID_BUTTON_NEWMASTER,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LoginDialog::OnButtonNewMasterClick);
	//*)

    m_iFailedAttempts = 0;
}

LoginDialog::~LoginDialog()
{
	//(*Destroy(LoginDialog)
	//*)
}


void LoginDialog::OnButtonSubmitMasterClick(wxCommandEvent& event)
{
    if(TextCtrlMasterPass->GetValue().IsEmpty()) return;

    FileHelper fileHelper;
    std::string sStoredHash = fileHelper.FHReadFile("masterhash");
    std::string sStoredSalt = fileHelper.FHReadFile("salt");
    std::string m_sIV = fileHelper.FHReadFile("iv");
    std::string sPass = TextCtrlMasterPass->GetValue().ToStdString();

    if(sStoredHash.empty() || sStoredSalt.empty() || m_sIV.empty())
    {
         wxMessageBox(_("Error: Could not read master data!"));
         return;
    }

    std::string sMaster = sPass + sStoredSalt;

    CryptHelper cryptHelper;
    std::string sHexHash = cryptHelper.HexHash(sMaster);

    if(sHexHash!=sStoredHash)
    {
        wxMessageBox(_("Password is incorrect!"));
        m_iFailedAttempts++;
        if(m_iFailedAttempts>2)
        {
            wxMessageBox(_("Three failed attempts. Oormi Pass will close. Please launch it again and try."));
            EndModal(1);
        }
        return;
    }

    //everything is ok
    oormipassFrame::m_sMaster = sPass;
    oormipassFrame::m_sIV = m_sIV;
    EndModal(0);
}
/*
void LoginDialog::OnClose(wxCloseEvent& event)
{
   //this->Destroy();
   wxDialog::OnCloseWindow(event);
}
*/
void LoginDialog::OnButtonNewMasterClick(wxCommandEvent& event)
{
    GenPassDialog genPassDlg(0);
    genPassDlg.m_bIsMaster = true;
    genPassDlg.ShowModal();
}
