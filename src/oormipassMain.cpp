/***************************************************************
 * Name:      oormipassMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    oormi creations (oormicreations@gmail.com)
 * Created:   2018-12-22
 * Copyright: oormi creations (https://oormi.in)
 * License:
 **************************************************************/

#include "oormipassMain.h"
#include <wx/msgdlg.h>
#include <wx/clipbrd.h>
#include "GenPassDialog.h"
#include "CryptHelper.h"
#include <wx/dcclient.h>
#include <wx/tokenzr.h>
#include "LoginDialog.h"
#include "GenPassDialog.h"


//(*InternalHeaders(oormipassFrame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

std::string oormipassFrame::m_sMaster = "";
std::string oormipassFrame::m_sIV = "";


//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(oormipassFrame)
const long oormipassFrame::ID_STATICBOX1 = wxNewId();
const long oormipassFrame::ID_LISTBOX_GROUP = wxNewId();
const long oormipassFrame::ID_BUTTON_ADDGROUP = wxNewId();
const long oormipassFrame::ID_STATICBOX2 = wxNewId();
const long oormipassFrame::ID_LISTBOXITEMS = wxNewId();
const long oormipassFrame::ID_BUTTON_ADDITEM = wxNewId();
const long oormipassFrame::ID_STATICBOX3 = wxNewId();
const long oormipassFrame::ID_STATICTEXT1 = wxNewId();
const long oormipassFrame::ID_TEXTCTRL_LINK = wxNewId();
const long oormipassFrame::ID_BUTTON_LAUNCH = wxNewId();
const long oormipassFrame::ID_BUTTON_COPYLINK = wxNewId();
const long oormipassFrame::ID_STATICTEXT2 = wxNewId();
const long oormipassFrame::ID_TEXTCTRL_USER = wxNewId();
const long oormipassFrame::ID_BUTTON_COPYUSER = wxNewId();
const long oormipassFrame::ID_STATICTEXT3 = wxNewId();
const long oormipassFrame::ID_TEXTCTRL_NOTES = wxNewId();
const long oormipassFrame::ID_STATICTEXT4 = wxNewId();
const long oormipassFrame::ID_TEXTCTRL_PASS = wxNewId();
const long oormipassFrame::ID_BUTTON_COPYPASS = wxNewId();
const long oormipassFrame::ID_BUTTON_NEWPASS = wxNewId();
const long oormipassFrame::ID_BUTTON_REMGROUP = wxNewId();
const long oormipassFrame::ID_BUTTON_REMITEM = wxNewId();
const long oormipassFrame::ID_TEXTCTRL_GROUPNAME = wxNewId();
const long oormipassFrame::ID_BUTTON_EDITGROUP = wxNewId();
const long oormipassFrame::ID_TEXTCTRL_ITEMNAME = wxNewId();
const long oormipassFrame::ID_BUTTON_EDITITEM = wxNewId();
const long oormipassFrame::ID_BUTTON_SAVEFORM = wxNewId();
const long oormipassFrame::ID_BUTTON_SHOWPASS = wxNewId();
const long oormipassFrame::ID_BUTTON_CLEAR = wxNewId();
const long oormipassFrame::ID_BUTTON_DEL = wxNewId();
const long oormipassFrame::idMenuLogOut = wxNewId();
const long oormipassFrame::ID_MENUITEM1 = wxNewId();
const long oormipassFrame::idMenuAuto = wxNewId();
const long oormipassFrame::idMenuLog = wxNewId();
const long oormipassFrame::idMenuChangeMaster = wxNewId();
const long oormipassFrame::idMenuHelp = wxNewId();
const long oormipassFrame::idMenuUpdate = wxNewId();
const long oormipassFrame::idMenuMore = wxNewId();
const long oormipassFrame::idMenuAbout = wxNewId();
const long oormipassFrame::ID_STATUSBAR1 = wxNewId();
const long oormipassFrame::ID_TIMER_HIGHLIGHT = wxNewId();
const long oormipassFrame::ID_TIMER_LOGOFF = wxNewId();
//*)

BEGIN_EVENT_TABLE(oormipassFrame,wxFrame)
    //(*EventTable(oormipassFrame)
    //*)
END_EVENT_TABLE()

oormipassFrame::oormipassFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(oormipassFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, wxID_ANY, _("Oormi Pass :: Password Manager"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(770,450));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));
    wxFont thisFont(8,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("Groups"), wxPoint(8,8), wxSize(184,400), 0, _T("ID_STATICBOX1"));
    ListBoxGroup = new wxListBox(this, ID_LISTBOX_GROUP, wxPoint(16,32), wxSize(168,300), 0, 0, wxLB_SORT, wxDefaultValidator, _T("ID_LISTBOX_GROUP"));
    ButtonAddGroup = new wxButton(this, ID_BUTTON_ADDGROUP, _("Add"), wxPoint(16,376), wxSize(50,23), 0, wxDefaultValidator, _T("ID_BUTTON_ADDGROUP"));
    ButtonAddGroup->SetToolTip(_("Add a new password group"));
    ButtonAddGroup->SetHelpText(_("Add a new password group"));
    StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, _("Items"), wxPoint(200,8), wxSize(184,400), 0, _T("ID_STATICBOX2"));
    ListBoxItems = new wxListBox(this, ID_LISTBOXITEMS, wxPoint(208,32), wxSize(168,300), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOXITEMS"));
    ButtonAddItem = new wxButton(this, ID_BUTTON_ADDITEM, _("Add"), wxPoint(208,376), wxSize(50,23), 0, wxDefaultValidator, _T("ID_BUTTON_ADDITEM"));
    ButtonAddItem->SetToolTip(_("Add items to this group"));
    ButtonAddItem->SetHelpText(_("Add items to this group"));
    StaticBox3 = new wxStaticBox(this, ID_STATICBOX3, _("Details"), wxPoint(392,8), wxSize(368,400), 0, _T("ID_STATICBOX3"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Link"), wxPoint(410,34), wxSize(48,16), wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
    TextCtrlLink = new wxTextCtrl(this, ID_TEXTCTRL_LINK, wxEmptyString, wxPoint(464,32), wxSize(270,23), 0, wxDefaultValidator, _T("ID_TEXTCTRL_LINK"));
    ButtonLaunch = new wxButton(this, ID_BUTTON_LAUNCH, _("Launch"), wxPoint(560,64), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_LAUNCH"));
    ButtonLaunch->SetToolTip(_("Open this link or file"));
    ButtonLaunch->SetHelpText(_("Open this link or file"));
    ButtonCopyLink = new wxButton(this, ID_BUTTON_COPYLINK, _("Copy"), wxPoint(464,64), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_COPYLINK"));
    ButtonCopyLink->SetToolTip(_("Copy the link to clipboard"));
    ButtonCopyLink->SetHelpText(_("Copy the link to clipboard"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("User Name"), wxPoint(410,106), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    TextCtrlUSer = new wxTextCtrl(this, ID_TEXTCTRL_USER, wxEmptyString, wxPoint(464,104), wxSize(270,23), 0, wxDefaultValidator, _T("ID_TEXTCTRL_USER"));
    ButtonCopyUser = new wxButton(this, ID_BUTTON_COPYUSER, _("Copy"), wxPoint(464,136), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_COPYUSER"));
    ButtonCopyUser->SetToolTip(_("Copy the username to clipboard"));
    ButtonCopyUser->SetHelpText(_("Copy the username to clipboard"));
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Notes"), wxPoint(424,272), wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT3"));
    TextCtrlNotes = new wxTextCtrl(this, ID_TEXTCTRL_NOTES, wxEmptyString, wxPoint(464,264), wxSize(270,64), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL_NOTES"));
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Password"), wxPoint(410,178), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    TextCtrlPass = new wxTextCtrl(this, ID_TEXTCTRL_PASS, wxEmptyString, wxPoint(464,176), wxSize(270,23), wxTE_PASSWORD, wxDefaultValidator, _T("ID_TEXTCTRL_PASS"));
    ButtonCopyPass = new wxButton(this, ID_BUTTON_COPYPASS, _("Copy"), wxPoint(464,216), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_COPYPASS"));
    ButtonCopyPass->SetToolTip(_("Copy the password to clipboard"));
    ButtonCopyPass->SetHelpText(_("Copy the password to clipboard"));
    ButtonNewPass = new wxButton(this, ID_BUTTON_NEWPASS, _("Generate"), wxPoint(656,216), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_NEWPASS"));
    ButtonNewPass->SetToolTip(_("Generate a new password"));
    ButtonNewPass->SetHelpText(_("Generate a new password"));
    ButtonRemoveGroup = new wxButton(this, ID_BUTTON_REMGROUP, _("Remove"), wxPoint(72,376), wxSize(56,23), 0, wxDefaultValidator, _T("ID_BUTTON_REMGROUP"));
    ButtonRemoveGroup->SetToolTip(_("Remove selected group"));
    ButtonRemoveGroup->SetHelpText(_("Remove selected group"));
    ButtonRemoveItem = new wxButton(this, ID_BUTTON_REMITEM, _("Remove"), wxPoint(264,376), wxSize(56,23), 0, wxDefaultValidator, _T("ID_BUTTON_REMITEM"));
    ButtonRemoveItem->SetToolTip(_("Remove selected item"));
    ButtonRemoveItem->SetHelpText(_("Remove selected item"));
    TextCtrlGroupName = new wxTextCtrl(this, ID_TEXTCTRL_GROUPNAME, wxEmptyString, wxPoint(16,344), wxSize(168,23), 0, wxDefaultValidator, _T("ID_TEXTCTRL_GROUPNAME"));
    ButtonEditGroup = new wxButton(this, ID_BUTTON_EDITGROUP, _("Edit"), wxPoint(136,376), wxSize(50,23), 0, wxDefaultValidator, _T("ID_BUTTON_EDITGROUP"));
    ButtonEditGroup->SetToolTip(_("Edit selected group name"));
    ButtonEditGroup->SetHelpText(_("Edit selected group name"));
    TextCtrlItemName = new wxTextCtrl(this, ID_TEXTCTRL_ITEMNAME, wxEmptyString, wxPoint(208,344), wxSize(168,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL_ITEMNAME"));
    ButtonEditItem = new wxButton(this, ID_BUTTON_EDITITEM, _("Edit"), wxPoint(328,376), wxSize(50,23), 0, wxDefaultValidator, _T("ID_BUTTON_EDITITEM"));
    ButtonEditItem->SetToolTip(_("Edit selected item name"));
    ButtonEditItem->SetHelpText(_("Edit selected item name"));
    ButtonSaveForm = new wxButton(this, ID_BUTTON_SAVEFORM, _("Save"), wxPoint(656,360), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SAVEFORM"));
    ButtonSaveForm->SetToolTip(_("Save all details"));
    ButtonSaveForm->SetHelpText(_("Save all details"));
    ButtonShowPass = new wxButton(this, ID_BUTTON_SHOWPASS, _("Show"), wxPoint(560,216), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SHOWPASS"));
    ButtonShowPass->SetToolTip(_("Show the password"));
    ButtonShowPass->SetHelpText(_("Show the password"));
    ButtonClear = new wxButton(this, ID_BUTTON_CLEAR, _("Clear"), wxPoint(560,360), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_CLEAR"));
    ButtonClear->SetToolTip(_("Clear all details"));
    ButtonClear->SetHelpText(_("Clear all details"));
    ButtonDel = new wxButton(this, ID_BUTTON_DEL, _("Delete"), wxPoint(464,360), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_DEL"));
    ButtonDel->SetToolTip(_("Delete details"));
    ButtonDel->SetHelpText(_("Delete details"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem7 = new wxMenuItem(Menu1, idMenuLogOut, _("&Log Out\tF8"), _("Log Out"), wxITEM_NORMAL);
    Menu1->Append(MenuItem7);
    MenuItem1 = new wxMenuItem(Menu1, ID_MENUITEM1, _("&Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItem5 = new wxMenuItem(Menu3, idMenuAuto, _("&Auto LogOff\tF10"), _("Log Off automatically after 10 mins of no activity"), wxITEM_CHECK);
    Menu3->Append(MenuItem5);
    MenuItem5->Check(true);
    MenuItem6 = new wxMenuItem(Menu3, idMenuLog, _("Show &Log\tF5"), _("Show log window"), wxITEM_CHECK);
    Menu3->Append(MenuItem6);
    MenuItem8 = new wxMenuItem(Menu3, idMenuChangeMaster, _("Change &Master Password\tF6"), _("Change Master Password"), wxITEM_NORMAL);
    Menu3->Append(MenuItem8);
    MenuBar1->Append(Menu3, _("&Options"));
    Menu2 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu2, idMenuHelp, _("Online &Help\tF1"), _("Online Help"), wxITEM_NORMAL);
    Menu2->Append(MenuItem3);
    MenuItem4 = new wxMenuItem(Menu2, idMenuUpdate, _("Check for &Updates\tF3"), _("Check for updates"), wxITEM_NORMAL);
    Menu2->Append(MenuItem4);
    MenuItem9 = new wxMenuItem(Menu2, idMenuMore, _("&Get More Free Apps\tF9"), _("Get more free open source Apps from Oormi Creations"), wxITEM_NORMAL);
    Menu2->Append(MenuItem9);
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("&About\tF2"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("&Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_FLAT };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    TimerHighlight.SetOwner(this, ID_TIMER_HIGHLIGHT);
    TimerLogOff.SetOwner(this, ID_TIMER_LOGOFF);
    Center();

    Connect(ID_LISTBOX_GROUP,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&oormipassFrame::OnListBoxGroupSelect);
    Connect(ID_BUTTON_ADDGROUP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&oormipassFrame::OnButtonAddGroupClick);
    Connect(ID_LISTBOXITEMS,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&oormipassFrame::OnListBoxItemsSelect);
    Connect(ID_BUTTON_ADDITEM,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&oormipassFrame::OnButtonAddItemClick);
    Connect(ID_TEXTCTRL_LINK,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&oormipassFrame::OnTextCtrlLinkText);
    Connect(ID_BUTTON_LAUNCH,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&oormipassFrame::OnButtonLaunchClick);
    Connect(ID_BUTTON_COPYLINK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&oormipassFrame::OnButtonCopyLinkClick);
    Connect(ID_TEXTCTRL_USER,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&oormipassFrame::OnTextCtrlUSerText);
    Connect(ID_BUTTON_COPYUSER,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&oormipassFrame::OnButtonCopyUserClick);
    Connect(ID_TEXTCTRL_NOTES,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&oormipassFrame::OnTextCtrlNotesText);
    Connect(ID_TEXTCTRL_PASS,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&oormipassFrame::OnTextCtrlPassText);
    Connect(ID_BUTTON_COPYPASS,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&oormipassFrame::OnButtonCopyPassClick);
    Connect(ID_BUTTON_NEWPASS,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&oormipassFrame::OnButtonNewPassClick);
    Connect(ID_BUTTON_REMGROUP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&oormipassFrame::OnButtonRemoveGroupClick);
    Connect(ID_BUTTON_REMITEM,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&oormipassFrame::OnButtonRemoveItemClick);
    Connect(ID_TEXTCTRL_GROUPNAME,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&oormipassFrame::OnTextCtrlGroupNameText);
    Connect(ID_BUTTON_EDITGROUP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&oormipassFrame::OnButtonEditGroupClick);
    Connect(ID_TEXTCTRL_ITEMNAME,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&oormipassFrame::OnTextCtrlItemNameText);
    Connect(ID_BUTTON_EDITITEM,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&oormipassFrame::OnButtonEditItemClick);
    Connect(ID_BUTTON_SAVEFORM,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&oormipassFrame::OnButtonSaveFormClick);
    Connect(ID_BUTTON_SHOWPASS,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&oormipassFrame::OnButtonShowPassClick);
    Connect(ID_BUTTON_CLEAR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&oormipassFrame::OnButtonClearClick);
    Connect(ID_BUTTON_DEL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&oormipassFrame::OnButtonDelClick);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&oormipassFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&oormipassFrame::OnAbout);
    Connect(ID_TIMER_HIGHLIGHT,wxEVT_TIMER,(wxObjectEventFunction)&oormipassFrame::OnTimerHighlightTrigger);
    Connect(ID_TIMER_LOGOFF,wxEVT_TIMER,(wxObjectEventFunction)&oormipassFrame::OnTimer1Trigger);
    Connect(wxEVT_MOTION,(wxObjectEventFunction)&oormipassFrame::OnMouseMove);
    //*)

    Connect(idMenuHelp,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&oormipassFrame::OnHelp);
    Connect(idMenuUpdate,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&oormipassFrame::OnUpdate);
    Connect(idMenuAuto,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&oormipassFrame::OnAutoLogoff);
    Connect(idMenuLog,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&oormipassFrame::OnLog);
    Connect(idMenuLogOut,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&oormipassFrame::OnLogOut);
    Connect(idMenuChangeMaster,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&oormipassFrame::OnChangeMaster);
    Connect(idMenuMore,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&oormipassFrame::OnMore);


    m_bShowPass = false;
    SetWindowStyle(wxDEFAULT_FRAME_STYLE &  ~(wxMAXIMIZE_BOX | wxRESIZE_BORDER)); //avoid reset via wxsmith
    PopulateGroups();
    m_uGroupCount = ListBoxGroup->GetCount();
    if(m_uGroupCount>0)
    {
        ListBoxGroup->SetSelection(0);
        m_iSelGroup = 0;
        PopulateItems(ListBoxGroup->GetString(0));
    }

    /*
    std::string str = "plaintext";
    std::string key = "userpass";
    std::string IV = "0123456789123456";
    wxMessageBox(m_sMaster);
    wxMessageBox(m_sIV);

    CryptHelper cryptHelper;
    std::string strout = cryptHelper.encrypt(str, m_sMaster, m_sIV);
    wxMessageBox(strout);
    str = cryptHelper.decrypt(strout, m_sMaster, m_sIV);
    wxMessageBox(str);
    */

    m_wLog = new wxLogWindow(this, _("Log"), false);
    wxLog::SetTimestamp(_("%Y-%m-%dT%H:%M:%S.%l"));
    wxLog::SetActiveTarget(m_wLog);
    m_bIsUserActive = true;
    TimerLogOff.Start(AUTO_LOGOUT_TIME*1000, true);

}

oormipassFrame::~oormipassFrame()
{
    //(*Destroy(oormipassFrame)
    //*)
}

void oormipassFrame::OnHelp(wxCommandEvent& event)
{
    ShellExecuteA(NULL, "open", "https://oormi.in/software/oormipass/help.html", NULL, NULL, SW_SHOWNORMAL);
}

void oormipassFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void oormipassFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = _("Oormi Pass Version 1.0.0\nJan 2019\n\nBy\nOormi Creations\n\nCode::Blocks | MinGW | Crypto++\n\n") + wxbuildinfo(long_f);
    wxMessageBox(msg, _("Oormi Pass"));

}

void oormipassFrame::OnUpdate(wxCommandEvent& event)
{
    ShellExecuteA(NULL, "open", "https://oormi.in/checkupdate.php?app=OP&ver=100", NULL, NULL, SW_SHOWNORMAL);
}

void oormipassFrame::OnMore(wxCommandEvent& event)
{
    ShellExecuteA(NULL, "open", "https://github.com/oormicreations?tab=repositories", NULL, NULL, SW_SHOWNORMAL);
}

void oormipassFrame::OnAutoLogoff(wxCommandEvent& event)
{
}

void oormipassFrame::OnLog(wxCommandEvent& event)
{
    m_wLog->Show(event.IsChecked());
}

void oormipassFrame::OnLogOut(wxCommandEvent& event)
{
    this->Hide();
    TimerLogOff.Stop();

    LoginDialog loginDlg(0);
    if(loginDlg.ShowModal()) this->Close();
    else
    {
        this->Show();
        m_bIsUserActive = true;
        wxLogDebug("Login OK");
        StatusBar1->SetStatusText(_("Welcome back!"));
        TimerLogOff.Start(AUTO_LOGOUT_TIME*60000, true);
    }
}

void oormipassFrame::OnChangeMaster(wxCommandEvent& event)
{
    GenPassDialog genPassDlg(0);
    genPassDlg.m_bIsMaster = true;
    int res = genPassDlg.ShowModal();
    wxLogDebug("Gen pass returned %d", res);

    if(res)//encrypt all passwords again
    {
        //wxLogDebug(genPassDlg.m_sMaster);
        std::string sOldMaster = m_sMaster;
        std::string sOldIV = m_sIV;
        m_sMaster = genPassDlg.m_sMaster.ToStdString();
        m_sIV = genPassDlg.m_sIV.ToStdString();

        CryptHelper cryptHelper;
        for(unsigned int i = 0; i < m_vItems.size(); i++)
        {
            std::string sOldPass = cryptHelper.decrypt(m_vItems[i].m_sPassword.ToStdString(), sOldMaster, sOldIV);
            m_vItems[i].m_sPassword = cryptHelper.encrypt(sOldPass, m_sMaster, m_sIV);
        }

        SaveData();

        StatusBar1->SetStatusText(_("Master password changed successfully"));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void oormipassFrame::PopulateGroups()
{
    wxString sData = m_FileHelper.FHReadFile("data");
    if(sData.IsEmpty())
    {
        std::vector <wxString> sDefaultGroups = {"Web Hosts", "Zip Files", "PDF Files", "Office", "Work", "Gaming", "Forums", "Sites", "Misc"};
        PassItem piItem;

        for(int n=0; n<(int)sDefaultGroups.size(); n++)
        {
            piItem.m_sGroupName = sDefaultGroups[n];
            m_vItems.push_back(piItem);

        }

        FileHelper fHelper;
        std::string sTS = "\nCreated on: " + fHelper.GetTimeStamp();

       piItem.UpdatePassItem("Email", "Gmail Home", "https://gmail.com", "username@gmail.com", "", "Home Email"+sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Email", "Gmail Work", "https://gmail.com", "username@gmail.com", "", "Work Email"+sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Online Storage", "DropBox", "https://www.dropbox.com", "username@email.com", "", "Backups"+sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Online Storage", "Google Drive", "https://drive.google.com", "username@email.com", "", "Songs"+sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Code Repositories", "Github", "https://github.com/oormicreations", "username@gmail.com", "", "Projects"+sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Code Repositories", "GitLab", "https://gitlab.com/oormicreations", "username@gmail.com", "", "Projects"+sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Social", "Twitter", "https://twitter.com", "username", "", sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Social", "Mastodon", "https://mastodon.social/web/timelines/public/local", "username", "", sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Banks", "HDFC", "http://www.hdfcbank.com/", "username", "", sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Banks", "HSBC", "https://www.hsbc.co.in", "username", "", sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Banks", "Paypal", "https://www.paypal.com/signin?country.x=IN&locale.x=en_IN", "username", "", sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Taxes", "IT", "https://incometaxindiaefiling.gov.in", "username", "", sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Taxes", "GST", "https://services.gst.gov.in/services/login", "username", "", sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Services", "HP Gas", "https://myhpgas.in/myHPGas/Index.aspx", "username", "", sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Services", "MSEB", "http://wss.mahadiscom.in/wss/wss", "username", "", sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Services", "Idea", "https://care.ideacellular.com/wps/portal/account/account-login", "username", "", sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Videos", "YouTube", "https://youtube.com", "username", "", sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Videos", "YouTube", "https://youtube.com", "username", "", sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Shopping", "Amazon", "https://www.amazon.in", "username", "", sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Shopping", "Ebay", "https://www.ebay.in", "username", "", sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Movies", "Amazon Prime", "https://www.primevideo.com/", "username", "", sTS);
       m_vItems.push_back(piItem);
       piItem.UpdatePassItem("Movies", "Netflix", "https://www.netflix.com/browse/my-list", "username", "", sTS);
       m_vItems.push_back(piItem);

    }
    else
    {
        //parse it
        PassItem piItem;
        wxArrayString sLines, sDet;
        wxStringTokenizer tokens(sData, _("\r\n"));
        while ( tokens.HasMoreTokens() )
        {
            sLines.Add(tokens.GetNextToken());
        }
        for(unsigned int i = 0; i < sLines.GetCount(); i++)
        {
            sDet.Empty();
            wxStringTokenizer details(sLines[i], _("|"), wxTOKEN_RET_EMPTY_ALL);
            while ( details.HasMoreTokens() )
            {
                sDet.Add(details.GetNextToken());
                //wxLogMessage(details.GetNextToken());
            }
            if(sDet.GetCount()>5)
            {
                //wxLogMessage(sDet[0]+sDet[1]+sDet[2]+sDet[3]+sDet[4]+sDet[5]);
                sDet[5].Replace(_("!@!"), _("\n"));
                piItem.UpdatePassItem(sDet[0],sDet[1],sDet[2],sDet[3],sDet[4],sDet[5]);
                m_vItems.push_back(piItem);
            }
        }

    }

    //extract group names
    for(int n=0; n<(int)m_vItems.size(); n++)
    {
        //wxLogMessage(m_vItems[n].m_sGroupName);
        if(ListBoxGroup->FindString(m_vItems[n].m_sGroupName) == wxNOT_FOUND)
        {
             ListBoxGroup->Append(m_vItems[n].m_sGroupName);
        }
    }
}

void oormipassFrame::PopulateItems(wxString sGroupName)
{
    //for(int i=ListBoxItems->GetCount(); i>=0 ;i--)
    ListBoxItems->Clear();
    for(PassItem p : m_vItems)
    {
       if(p.m_sGroupName == sGroupName)
       {
           if(!p.m_sItemName.empty())
           {
               if(!p.m_bDeleted) ListBoxItems->AppendAndEnsureVisible(p.m_sItemName);
           }
       }
    }

    if(ListBoxItems->GetCount()>0)
    {
        ListBoxItems->SetSelection(0);
        PopulateDetails(ListBoxItems->GetString(0));
    }
    else ClearDetails();

}

void oormipassFrame::PopulateDetails(wxString sItemName)
{
    ClearDetails();
    wxString sGroup = ListBoxGroup->GetString(ListBoxGroup->GetSelection());
    //bool bPlaceholder = false;

    for(int n=0; n<(int)m_vItems.size(); n++)
    {
        if((m_vItems[n].m_sGroupName==sGroup)&&(m_vItems[n].m_sItemName==sItemName))
        {
            m_vItems[n].m_sNotes.Replace(_("!@!"), _("\n"));
            TextCtrlLink->SetValue(m_vItems[n].m_sLink);
            TextCtrlNotes->SetValue(m_vItems[n].m_sNotes);
            TextCtrlUSer->SetValue(m_vItems[n].m_sUser);
            if(!m_vItems[n].m_sPassword.IsEmpty())
            {
                TextCtrlPass->SetValue(GetPassword());
                //bPlaceholder = true;
            }
        }
    }

    m_bShowPass = false;
    ShowPassToggle(m_bShowPass);
    ButtonSaveForm->SetForegroundColour(ButtonClear->GetForegroundColour());

}

wxString oormipassFrame::Truncate(wxString str, size_t width, bool show_ellipsis)
{
    if (str.length() > width)
    {
        if (show_ellipsis)
            return str.substr(0, width) + L"...";
        else
            return str.substr(0, width);
    }

    return str;
}

void oormipassFrame::OnButtonAddGroupClick(wxCommandEvent& event)
{
    wxString sNewGroup = TextCtrlGroupName->GetValue();
    if(sNewGroup.IsEmpty())
    {
        TextCtrlGroupName->SetBackgroundColour(wxColor(255,230,200));
        TextCtrlGroupName->SetFocus();
        TimerHighlight.Start(5000, true);
        wxMessageBox(_("Please enter a name in the box"));
        return;
    }

    sNewGroup = Truncate(sNewGroup.ToStdWstring(), 25);

    if(ListBoxGroup->FindString(sNewGroup)!=wxNOT_FOUND)
    {
        wxMessageBox(_("Group already exists!"));
        return;
    }

    PassItem piItem;
    piItem.UpdatePassItem(sNewGroup.ToStdString(), "", "", "", "", "");
    m_vItems.push_back(piItem);

    ListBoxGroup->AppendAndEnsureVisible(sNewGroup);
    ListBoxGroup->SetStringSelection(sNewGroup);
    PopulateItems(sNewGroup);
    TextCtrlGroupName->Clear();
    SaveData();
    StatusBar1->SetStatusText(_("Group Added."));

}

void oormipassFrame::OnListBoxGroupSelect(wxCommandEvent& event)
{
    PopulateItems(ListBoxGroup->GetString(event.GetSelection()));
    ButtonSaveForm->SetForegroundColour(ButtonClear->GetForegroundColour());
    StatusBar1->SetStatusText(_("Select any item to view details."));
}

void oormipassFrame::OnListBoxItemsSelect(wxCommandEvent& event)
{
    PopulateDetails(ListBoxItems->GetString(event.GetSelection()));
    ButtonSaveForm->SetForegroundColour(ButtonClear->GetForegroundColour());
    StatusBar1->SetStatusText(_("Use, change or add details."));
}

void oormipassFrame::OnButtonEditGroupClick(wxCommandEvent& event)
{
    int iSel = ListBoxGroup->GetSelection();
    if(iSel<0)
    {
        wxMessageBox(_("Please select a group"));
        return;
    }

    wxString sGroup = ListBoxGroup->GetString(iSel).ToStdString();
    wxString sNewGroup = TextCtrlGroupName->GetValue().ToStdString();

    if(sNewGroup.empty())
    {
        TextCtrlGroupName->SetBackgroundColour(wxColor(255,230,200));
        TextCtrlGroupName->SetFocus();
        TimerHighlight.Start(5000, true);//one shot timer to clear background
        wxMessageBox(_("Please enter a name in the box"));
        return;
    }

//    sNewGroup = Truncate(sNewGroup, 25);

    if(ListBoxGroup->FindString(sNewGroup)!=wxNOT_FOUND)
    {
        wxMessageBox(_("Group already exists!"));
        return;
    }

    for(int n=0; n<(int)m_vItems.size(); n++)
    {
        if(m_vItems[n].m_sGroupName==sGroup)
        {
            m_vItems[n].m_sGroupName = sNewGroup;
        }
    }

    ListBoxGroup->SetString(iSel, sNewGroup);
    TextCtrlGroupName->Clear();

    SaveData();
    StatusBar1->SetStatusText(_("Edit Complete."));

}

void oormipassFrame::OnButtonRemoveGroupClick(wxCommandEvent& event)
{
    int iSel = ListBoxGroup->GetSelection();
    if(iSel<0)
    {
        wxMessageBox(_("Please select a group"));
        return;
    }

    int res = wxMessageBox(_("Delete data?"), _("Confirm deletion"), wxYES_NO | wxCENTRE | wxNO_DEFAULT);
    if(res == wxNO) return;

    wxString sGroup = ListBoxGroup->GetString(iSel).ToStdString();

    for(int n=0; n<(int)m_vItems.size(); n++)
    {
        if(m_vItems[n].m_sGroupName==sGroup)
        {
            m_vItems[n].m_bDeleted = true;
        }
    }

    ListBoxGroup->Delete(iSel);
    ListBoxGroup->DeselectAll();
    ListBoxItems->Clear();
    ClearDetails();
    SaveData();
    StatusBar1->SetStatusText(_("Group Removed."));
}

 void oormipassFrame::ClearDetails()
 {
    TextCtrlLink->SetValue(_(""));
    TextCtrlNotes->SetValue(_(""));
    TextCtrlUSer->SetValue(_(""));
    TextCtrlPass->SetValue(_(""));
    wxLogDebug("Form cleared.");
 }

void oormipassFrame::OnButtonAddItemClick(wxCommandEvent& event)
{
    wxString sNewItem = TextCtrlItemName->GetValue();
    if(sNewItem.IsEmpty())
    {
        TextCtrlItemName->SetBackgroundColour(wxColor(255,230,200));
        TextCtrlItemName->SetFocus();
        TimerHighlight.Start(5000, true);
        wxMessageBox(_("Please enter a name in the box"));
        return;
    }

    int iSel = ListBoxGroup->GetSelection();
    if(iSel<0)
    {
        wxMessageBox(_("Please select a group"));
        return;
    }
    wxString sGroup = ListBoxGroup->GetString(iSel);

    sNewItem = Truncate(sNewItem.ToStdWstring(), 25);

    if(ListBoxItems->FindString(sNewItem)!=wxNOT_FOUND)
    {
        wxMessageBox(_("Item already exists!"));
        return;
    }

    PassItem piItem;
    piItem.UpdatePassItem(sGroup, sNewItem, _(""), _(""), _(""), _("Created on ") + m_FileHelper.GetTimeStamp());
    m_vItems.push_back(piItem);

    ListBoxItems->AppendAndEnsureVisible(sNewItem);
    ListBoxItems->SetStringSelection(sNewItem);
    PopulateDetails(sNewItem);
    TextCtrlItemName->Clear();
    SaveData();
    StatusBar1->SetStatusText(_("New Item Added."));

}

void oormipassFrame::OnButtonEditItemClick(wxCommandEvent& event)
{
    int iSel1 = ListBoxGroup->GetSelection();
    if(iSel1<0)
    {
        wxMessageBox(_("Please select a group"));
        return;
    }
    int iSel2 = ListBoxItems->GetSelection();
    if(iSel2<0)
    {
        wxMessageBox(_("Please select an item"));
        return;
    }


    wxString sGroup = ListBoxGroup->GetString(iSel1).ToStdString();
    wxString sItem = ListBoxItems->GetString(iSel2).ToStdString();
    wxString sNewItem = TextCtrlItemName->GetValue().ToStdString();

    if(sNewItem.empty())
    {
        TextCtrlItemName->SetBackgroundColour(wxColor(255,230,200));
        TextCtrlItemName->SetFocus();
        TimerHighlight.Start(5000, true);
        wxMessageBox(_("Please enter a name in the box"));
        return;
    }
//    sNewItem = Truncate(sNewItem, 25);

    if(ListBoxItems->FindString(sNewItem)!=wxNOT_FOUND)
    {
        wxMessageBox(_("Item already exists!"));
        return;
    }

    for(int n=0; n<(int)m_vItems.size(); n++)
    {
        if(m_vItems[n].m_sGroupName==sGroup)
        {
            if(m_vItems[n].m_sItemName==sItem)
            {
               m_vItems[n].m_sItemName = sNewItem;
            }
        }
    }

    ListBoxItems->SetString(iSel2, sNewItem);
    TextCtrlItemName->Clear();
    SaveData();
    StatusBar1->SetStatusText(_("Item Edited."));

}

void oormipassFrame::OnButtonRemoveItemClick(wxCommandEvent& event)
{
    int iSel1 = ListBoxGroup->GetSelection();
    if(iSel1<0)
    {
        wxMessageBox(_("Please select a group"));
        return;
    }
    int iSel2 = ListBoxItems->GetSelection();
    if(iSel2<0)
    {
        wxMessageBox(_("Please select an item"));
        return;
    }

    int res = wxMessageBox(_("Delete data?"), _("Confirm deletion"), wxYES_NO | wxCENTRE | wxNO_DEFAULT);
    if(res == wxNO) return;

    wxString sGroup = ListBoxGroup->GetString(iSel1).ToStdString();
    wxString sItem = ListBoxItems->GetString(iSel2).ToStdString();

    for(int n=0; n<(int)m_vItems.size(); n++)
    {
        if(m_vItems[n].m_sGroupName==sGroup)
        {
            if(m_vItems[n].m_sItemName==sItem)
            {
               m_vItems[n].m_bDeleted =true;
            }
        }
    }

    ListBoxItems->Delete(iSel2);
    ClearDetails();
    SaveData();
    StatusBar1->SetStatusText(_("Item Removed."));

}

void oormipassFrame::OnTimerHighlightTrigger(wxTimerEvent& event)
{
    TextCtrlGroupName->SetBackgroundColour(wxColor(255,255,255));
    TextCtrlGroupName->Refresh();
    TextCtrlItemName->SetBackgroundColour(wxColor(255,255,255));
    TextCtrlItemName->Refresh();
    TextCtrlPass->SetBackgroundColour(wxColor(255,255,255));
    TextCtrlPass->Refresh();

}

void oormipassFrame::OnButtonClearClick(wxCommandEvent& event)
{
    ClearDetails();
}

void oormipassFrame::OnButtonSaveFormClick(wxCommandEvent& event)
{
    int iSel1 = ListBoxGroup->GetSelection();
    if(iSel1<0)
    {
        wxMessageBox(_("Please select a group"));
        return;
    }
    int iSel2 = ListBoxItems->GetSelection();
    if(iSel2<0)
    {
        wxMessageBox(_("Please select an item"));
        return;
    }


    wxString sGroup = ListBoxGroup->GetString(iSel1);
    wxString sItem = ListBoxItems->GetString(iSel2);

    wxString sPass, sStoredPass;
    sPass = TextCtrlPass->GetValue();
    sStoredPass = GetPassword();
    bool bPassChanged = false;
    if((sPass == _("******")) || (sPass == sStoredPass)) bPassChanged = false;
    else  bPassChanged = true;

    if(sPass.IsEmpty())
    {
        TextCtrlPass->SetBackgroundColour(wxColor(255,230,200));
        TextCtrlPass->SetFocus();
        TimerHighlight.Start(5000, true);
        wxMessageBox(_("Please enter a password"));
        return;
    }


    for(int n=0; n<(int)m_vItems.size(); n++)
    {
        if(m_vItems[n].m_sGroupName==sGroup)
        {
            if(m_vItems[n].m_sItemName==sItem)
            {
                m_vItems[n].m_sLink = TextCtrlLink->GetValue();
                m_vItems[n].m_sUser = TextCtrlUSer->GetValue();
                m_vItems[n].m_sNotes = TextCtrlNotes->GetValue();
                if(bPassChanged)
                {
                    CryptHelper cryptHelper;
                    m_vItems[n].m_sPassword = cryptHelper.encrypt(sPass.ToStdString(), m_sMaster, m_sIV);

                    FileHelper fHelper;
                    m_vItems[n].m_sNotes = m_vItems[n].m_sNotes + _("\nLast Password Change: ") + fHelper.GetTimeStamp();
                    TextCtrlNotes->SetValue(m_vItems[n].m_sNotes);
                }
                SaveData();
                ButtonSaveForm->SetForegroundColour(ButtonClear->GetForegroundColour());
                return;
            }
        }
    }


}

void oormipassFrame::CopyToClipboard(wxString text)
{
   if(text.IsEmpty()) return;

   if(wxTheClipboard->Open())
   {
      wxTheClipboard->Clear();
      wxTheClipboard->SetData( new wxTextDataObject( text ) );
      wxTheClipboard->Flush();
      wxTheClipboard->Close();
      StatusBar1->SetStatusText(_("Copied to clipboard."));
   }
   else
   {
       wxMessageBox(_("Error: Failed to copy!"));
   }
}

void oormipassFrame::OnButtonCopyLinkClick(wxCommandEvent& event)
{
    CopyToClipboard(TextCtrlLink->GetValue());
}

void oormipassFrame::OnButtonCopyUserClick(wxCommandEvent& event)
{
    CopyToClipboard(TextCtrlUSer->GetValue());
}

void oormipassFrame::OnButtonCopyPassClick(wxCommandEvent& event)
{
    if(m_bShowPass) CopyToClipboard(TextCtrlPass->GetValue());
    else CopyToClipboard(GetPassword());
}

void oormipassFrame::ShowPassToggle(bool bShow)
{
    if(bShow)
    {
        ButtonShowPass->SetLabel(_("Hide"));
        //TextCtrlPass->SetValue(GetPassword());
    }
    else
    {
        ButtonShowPass->SetLabel(_("Show"));
        //if(bPlaceholder) TextCtrlPass->SetValue(_("*******"));
    }

#ifdef __WXMSW__
    HWND hwnd = (HWND) TextCtrlPass->GetHandle();
    SendMessage(hwnd, EM_SETPASSWORDCHAR, bShow? 0 : 0x25cf, 0); // 0x25cf is ● character

#else
    //not tested on non-windows platforms
    if(bShow) TextCtrlPass->SetWindowStyle(wxTE_LEFT);
    else TextCtrlPass->SetWindowStyle(wxTE_PASSWORD);
#endif
    TextCtrlPass->Refresh();

}

void oormipassFrame::OnButtonShowPassClick(wxCommandEvent& event)
{
    m_bShowPass = !m_bShowPass;
    ShowPassToggle(m_bShowPass);
    //ButtonSaveForm->SetForegroundColour(ButtonClear->GetForegroundColour());
}

void oormipassFrame::OnButtonNewPassClick(wxCommandEvent& event)
{
    CryptHelper cryptHelper;
    m_bShowPass = true;
    ShowPassToggle(m_bShowPass);
    TextCtrlPass->SetValue(cryptHelper.GenRandomString());
    StatusBar1->SetStatusText(_("Password generated. Please save the new details."));
}

wxString oormipassFrame::GetPassword()
{
    int iSel1 = ListBoxGroup->GetSelection();
    if(iSel1<0)
    {
        wxMessageBox(_("Please select a group"));
        return "";
    }
    int iSel2 = ListBoxItems->GetSelection();
    if(iSel2<0)
    {
        wxMessageBox(_("Please select an item"));
        return "";
    }


    wxString sGroup = ListBoxGroup->GetString(iSel1).ToStdString();
    wxString sItem = ListBoxItems->GetString(iSel2).ToStdString();

    CryptHelper crHelper;

    for(int n=0; n<(int)m_vItems.size(); n++)
    {
        if(m_vItems[n].m_sGroupName==sGroup)
        {
            if(m_vItems[n].m_sItemName==sItem)
            {
                return crHelper.decrypt(m_vItems[n].m_sPassword.ToStdString(), m_sMaster, m_sIV);
            }
        }
    }

    return "";

}


void oormipassFrame::OnButtonLaunchClick(wxCommandEvent& event)
{
    ShellExecuteA(NULL, "open", TextCtrlLink->GetValue().c_str(), NULL, NULL, SW_SHOWNORMAL);
    //wxExecute( TextCtrlLink->GetValue());
    StatusBar1->SetStatusText(_("Link was opened in default browser."));
}

void oormipassFrame::SaveData()
{
    wxString sData;
    for(int n = 0; n < (int)m_vItems.size(); n++)
    {
        m_vItems[n].m_sNotes.Replace(_("\n"), _("!@!"));
        if(!m_vItems[n].m_bDeleted) sData =
          sData + m_vItems[n].m_sGroupName
          + "|" + m_vItems[n].m_sItemName
          + "|" + m_vItems[n].m_sLink
          + "|" + m_vItems[n].m_sUser
          + "|" + m_vItems[n].m_sPassword
          + "|" + m_vItems[n].m_sNotes
          + "\n";
    }

    FileHelper fileHelper;
    fileHelper.FHSaveFile("data", sData.ToStdString());

    //wxLogDebug(sData);
    StatusBar1->SetStatusText(_("Data Saved."));
}

void oormipassFrame::OnButtonDelClick(wxCommandEvent& event)
{
    int iSel1 = ListBoxGroup->GetSelection();
    if(iSel1<0)
    {
        wxMessageBox(_("Please select a group"));
        return;
    }

    if(ListBoxItems->GetCount()<1) return;

    int iSel2 = ListBoxItems->GetSelection();
    if(iSel2<0)
    {
        wxMessageBox(_("Please select an item"));
        return;
    }

    int res = wxMessageBox(_("Delete data?"), _("Confirm deletion"), wxYES_NO | wxCENTRE | wxNO_DEFAULT);
    if(res == wxNO) return;

    wxString sGroup = ListBoxGroup->GetString(iSel1);
    wxString sItem = ListBoxItems->GetString(iSel2);

    for(int n=0; n<(int)m_vItems.size(); n++)
    {
        if(m_vItems[n].m_sGroupName==sGroup)
        {
            if(m_vItems[n].m_sItemName==sItem)
            {
               m_vItems[n].m_sLink.Empty();
               m_vItems[n].m_sNotes.Empty();
               m_vItems[n].m_sPassword.Empty();
               m_vItems[n].m_sUser.Empty();
            }
        }
    }

    SaveData();
    ClearDetails();
    StatusBar1->SetStatusText(_("Entry deleted."));

}

void oormipassFrame::OnTimer1Trigger(wxTimerEvent& event)
{
    TimerLogOff.Start(AUTO_LOGOUT_TIME*60000, true);
//    if(!m_bIsUserActive) wxLogStatus("Auto logout in %d minutes.", TimerLogOff.GetInterval()/1000);

    if(!m_bIsUserActive)
    {
        this->Hide();
        TimerLogOff.Stop();

        LoginDialog loginDlg(0);
        if(loginDlg.ShowModal()) this->Close();
        else
        {
            this->Show();
            m_bIsUserActive = true;
            wxLogDebug("Login OK");
            StatusBar1->SetStatusText(_("Welcome back!"));
            TimerLogOff.Start(AUTO_LOGOUT_TIME*60000, true);
        }
    }

    m_bIsUserActive = false;
}

void oormipassFrame::OnMouseMove(wxMouseEvent& event)
{
    m_bIsUserActive = true;
    //wxLogDebug("Active");
}

void oormipassFrame::OnTextCtrlLinkText(wxCommandEvent& event)
{
    ButtonSaveForm->SetForegroundColour(wxColor(SAVE_TEXT_COLOR));
}

void oormipassFrame::OnTextCtrlUSerText(wxCommandEvent& event)
{
    ButtonSaveForm->SetForegroundColour(wxColor(SAVE_TEXT_COLOR));
}

void oormipassFrame::OnTextCtrlPassText(wxCommandEvent& event)
{
    ButtonSaveForm->SetForegroundColour(wxColor(SAVE_TEXT_COLOR));
}

void oormipassFrame::OnTextCtrlNotesText(wxCommandEvent& event)
{
    ButtonSaveForm->SetForegroundColour(wxColor(SAVE_TEXT_COLOR));
}

void oormipassFrame::OnTextCtrlGroupNameText(wxCommandEvent& event)
{
    wxString sSearch = TextCtrlGroupName->GetValue().Lower();
    if(sSearch.IsEmpty()) return;

    for(int n=0; n<(int)m_vItems.size(); n++)
    {
        if(m_vItems[n].m_sGroupName.Lower().Find(sSearch)>=0)
        {
            wxLogDebug(m_vItems[n].m_sGroupName);
            ListBoxGroup->SetStringSelection(m_vItems[n].m_sGroupName);
            PopulateItems(m_vItems[n].m_sGroupName);
            ButtonSaveForm->SetForegroundColour(ButtonClear->GetForegroundColour());
            StatusBar1->SetStatusText(_("Search complete."));
            return;
        }
    }
}

void oormipassFrame::OnTextCtrlItemNameText(wxCommandEvent& event)
{
    wxString sSearch = TextCtrlItemName->GetValue().Lower();
    if(sSearch.IsEmpty()) return;

    int iSel1 = ListBoxGroup->GetSelection();
    if(iSel1<0)
    {
        wxMessageBox(_("Please select a group"));
        return;
    }
    wxString sGroup = ListBoxGroup->GetString(iSel1);

    for(int n=0; n<(int)m_vItems.size(); n++)
    {
        if(m_vItems[n].m_sGroupName==sGroup)
        {
            if(m_vItems[n].m_sItemName.Lower().Find(sSearch)>=0)
            {
                wxLogDebug(m_vItems[n].m_sItemName);
                ListBoxItems->SetStringSelection(m_vItems[n].m_sItemName);
                PopulateDetails(m_vItems[n].m_sItemName);
                ButtonSaveForm->SetForegroundColour(ButtonClear->GetForegroundColour());
                StatusBar1->SetStatusText(_("Search complete."));
                return;
            }
        }
    }
}
