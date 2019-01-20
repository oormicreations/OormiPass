#include "GenPassDialog.h"
#include <wx/msgdlg.h>
#include <wx/tokenzr.h>
#include <cstdlib>
#include "CryptHelper.h"
#include "FileHelper.h"

//(*InternalHeaders(GenPassDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(GenPassDialog)
const long GenPassDialog::ID_STATICBOX2 = wxNewId();
const long GenPassDialog::ID_STATICBOX1 = wxNewId();
const long GenPassDialog::ID_CHECKBOX_MNE = wxNewId();
const long GenPassDialog::ID_STATICTEXT1 = wxNewId();
const long GenPassDialog::ID_TEXTCTRL_MNEMO = wxNewId();
const long GenPassDialog::ID_STATICTEXT_MASTERWARN = wxNewId();
const long GenPassDialog::ID_STATICTEXT3 = wxNewId();
const long GenPassDialog::ID_CHECKBOX_RND = wxNewId();
const long GenPassDialog::ID_STATICTEXT4 = wxNewId();
const long GenPassDialog::ID_STATICTEXT_MASTER1 = wxNewId();
const long GenPassDialog::ID_STATICTEXT_MASTER2 = wxNewId();
const long GenPassDialog::ID_TEXTCTRL_MASTER1 = wxNewId();
const long GenPassDialog::ID_TEXTCTRL_MASTER2 = wxNewId();
const long GenPassDialog::ID_BUTTON_GENPASS = wxNewId();
const long GenPassDialog::ID_BUTTON_APPLYPASS = wxNewId();
//*)

BEGIN_EVENT_TABLE(GenPassDialog,wxDialog)
	//(*EventTable(GenPassDialog)
	//*)
END_EVENT_TABLE()

GenPassDialog::GenPassDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(GenPassDialog)
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(474,455));
	wxFont thisFont(8,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
	SetFont(thisFont);
	StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, _("Master Password"), wxPoint(8,256), wxSize(456,152), 0, _T("ID_STATICBOX2"));
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("Password Generator"), wxPoint(8,8), wxSize(456,240), 0, _T("ID_STATICBOX1"));
	CheckBox_Mne = new wxCheckBox(this, ID_CHECKBOX_MNE, _("Use Mnemonic Password Generator"), wxPoint(24,88), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_MNE"));
	CheckBox_Mne->SetValue(false);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Type at least 10 words from a song or a book or any movie dialogue which you remember precisely and of which you are certain that you will never forget them. Your password is first letters of each word. Case sensitive."), wxPoint(24,168), wxSize(432,40), wxST_NO_AUTORESIZE, _T("ID_STATICTEXT1"));
	TextCtrlMnemonic = new wxTextCtrl(this, ID_TEXTCTRL_MNEMO, wxEmptyString, wxPoint(24,144), wxSize(432,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL_MNEMO"));
	TextCtrlMnemonic->Disable();
	StaticTextMasterWarn = new wxStaticText(this, ID_STATICTEXT_MASTERWARN, _("Warning: This is the master password. If you lose it, there is no way to get it back. If you forget it, you will lose access to all saved passwords !"), wxPoint(24,352), wxSize(432,40), wxST_NO_AUTORESIZE, _T("ID_STATICTEXT_MASTERWARN"));
	StaticTextMasterWarn->SetForegroundColour(wxColour(255,0,0));
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Warning: This is easy to remember but is also easy to hack or guess !"), wxPoint(24,112), wxSize(432,24), 0, _T("ID_STATICTEXT3"));
	StaticText3->SetForegroundColour(wxColour(128,0,0));
	CheckBoxRnd = new wxCheckBox(this, ID_CHECKBOX_RND, _("Use Random Password Generator"), wxPoint(24,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_RND"));
	CheckBoxRnd->SetValue(false);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Warning: This is very secure but very difficult to remember !"), wxPoint(24,56), wxSize(432,24), 0, _T("ID_STATICTEXT4"));
	StaticText4->SetForegroundColour(wxColour(128,0,0));
	StaticTextMaster1 = new wxStaticText(this, ID_STATICTEXT_MASTER1, _("Password:"), wxPoint(40,288), wxSize(123,13), wxALIGN_RIGHT, _T("ID_STATICTEXT_MASTER1"));
	StaticTextMaster2 = new wxStaticText(this, ID_STATICTEXT_MASTER2, _("Confirm Password:"), wxPoint(40,320), wxSize(128,13), wxALIGN_RIGHT, _T("ID_STATICTEXT_MASTER2"));
	TextCtrlMaster1 = new wxTextCtrl(this, ID_TEXTCTRL_MASTER1, wxEmptyString, wxPoint(192,280), wxSize(224,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL_MASTER1"));
	TextCtrlMaster2 = new wxTextCtrl(this, ID_TEXTCTRL_MASTER2, wxEmptyString, wxPoint(192,312), wxSize(224,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL_MASTER2"));
	ButtonGenPass = new wxButton(this, ID_BUTTON_GENPASS, _("Generate"), wxPoint(192,216), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_GENPASS"));
	ButtonGenPass->Disable();
	ButtonApplyPass = new wxButton(this, ID_BUTTON_APPLYPASS, _("Apply"), wxPoint(192,416), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_APPLYPASS"));
	Center();

	Connect(ID_CHECKBOX_MNE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&GenPassDialog::OnCheckBox_MneClick);
	Connect(ID_CHECKBOX_RND,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&GenPassDialog::OnCheckBoxRndClick);
	Connect(ID_BUTTON_GENPASS,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GenPassDialog::OnButtonGenPassClick);
	Connect(ID_BUTTON_APPLYPASS,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GenPassDialog::OnButtonApplyPassClick);
	Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&GenPassDialog::OnInit);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&GenPassDialog::OnClose);
	//*)

	m_bIsMnemonic = false;
	m_bIsRandom = false;
	m_bIsMaster = false;
    std::srand(time(NULL));

}

GenPassDialog::~GenPassDialog()
{
	//(*Destroy(GenPassDialog)
	//*)
}


void GenPassDialog::OnClose(wxCloseEvent& event)
{
    //this->Destroy();
    EndDialog(0);
}

void GenPassDialog::OnCheckBox_MneClick(wxCommandEvent& event)
{
    m_bIsMnemonic = CheckBox_Mne->GetValue();

    if(m_bIsMnemonic)
    {
        m_bIsRandom = !m_bIsMnemonic;
        CheckBoxRnd->SetValue(m_bIsRandom);
    }

    ButtonGenPass->Enable(m_bIsMnemonic);
    TextCtrlMnemonic->Enable(m_bIsMnemonic);

}

void GenPassDialog::OnCheckBoxRndClick(wxCommandEvent& event)
{
    m_bIsRandom = CheckBoxRnd->GetValue();

    if(m_bIsRandom)
    {
        m_bIsMnemonic = !m_bIsRandom;
        CheckBox_Mne->SetValue(m_bIsMnemonic);
    }

    ButtonGenPass->Enable(m_bIsRandom);
    TextCtrlMnemonic->Enable(m_bIsMnemonic);

}

void GenPassDialog::OnButtonGenPassClick(wxCommandEvent& event)
{
    wxString sMneStr = TextCtrlMnemonic->GetValue();
    if(m_bIsMnemonic) GenMnemonic(sMneStr);
    if(m_bIsRandom) GenRandom();


}

void GenPassDialog::GenMnemonic(wxString str)
{
    int iCount = 0;
    int iMaxWords = 10;
    wxString sMnePass;

    wxStringTokenizer tokenizer(str, " ");
    while ( tokenizer.HasMoreTokens() )
    {
        wxString token = tokenizer.GetNextToken();
        sMnePass.Append(token.GetChar(0));
        iCount++;
    }

    if(iCount<iMaxWords)
    {
        wxMessageBox(_("Mnemonic password generation requires at least 10 words!"));
        return;
    }

    TextCtrlMaster1->SetValue(sMnePass);
}

void GenPassDialog::GenRandom()
{
    CryptHelper cryptHelper;
    TextCtrlMaster1->SetValue(cryptHelper.GenRandomString());
}

void GenPassDialog::OnButtonApplyPassClick(wxCommandEvent& event)
{
    if(TextCtrlMaster1->GetValue().IsEmpty()) return;

    if(TextCtrlMaster1->GetValue()!=TextCtrlMaster2->GetValue())
    {
        wxMessageBox(_("Passwords do not match. Please enter exactly the same password in both boxes."));
        return;
    }
    else
    {
        CryptHelper cryptHelper;
        std::string sPass = TextCtrlMaster1->GetValue().ToStdString();
        std::string sSalt = cryptHelper.GenRandomString();
        std::string sHexHash = cryptHelper.HexHash(sPass + sSalt);
        std::string sIV = cryptHelper.GenRandomString(16);

        FileHelper fileHelper;
        bool bRes1 = fileHelper.FHSaveFile("masterhash", sHexHash);
        bool bRes2 = fileHelper.FHSaveFile("salt", sSalt);
        bool bRes3 = fileHelper.FHSaveFile("iv", sIV);

        int res = 1;

        if(!(bRes1 && bRes2 && bRes3))
        {
            wxMessageBox(_("Error: Failed to save password data."));
            res = 0;
        }

        m_sMaster = sPass;
        m_sIV = sIV;

        EndModal(res);
    }
}

void GenPassDialog::OnInit(wxInitDialogEvent& event)
{
    StaticTextMasterWarn->Show(m_bIsMaster);
    if(m_bIsMaster)
    {
        StaticTextMaster1->SetLabelText(_("Master Password"));
        StaticTextMaster2->SetLabelText(_("Confirm Master Password"));

    }
}
