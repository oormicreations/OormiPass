/***************************************************************
 * Name:      oormipassMain.h
 * Purpose:   Defines Application Frame
 * Author:    oormi creations (oormicreations@gmail.com)
 * Created:   2018-12-22
 * Copyright: oormi creations (https://oormi.in)
 * License:
 **************************************************************/

#ifndef OORMIPASSMAIN_H
#define OORMIPASSMAIN_H

//(*Headers(oormipassFrame)
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/listbox.h>
#include <wx/menu.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
//*)

#include "PassItem.h"
#include "FileHelper.h"
#include <wx/log.h>

#define AUTO_LOGOUT_TIME 10 //minutes
#define SAVE_TEXT_COLOR 220,0,0

class oormipassFrame: public wxFrame
{
    public:

        oormipassFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~oormipassFrame();

        unsigned m_uGroupCount;
        int m_iSelGroup;
        std::vector <PassItem> m_vItems;
        FileHelper m_FileHelper;
        bool m_bShowPass;
        bool m_bIsUserActive;
        wxLogWindow* m_wLog;

        static std::string m_sMaster;
        static std::string m_sIV;


        void PopulateGroups();
        void PopulateItems(wxString sGroupName);
        void PopulateDetails(wxString sItemName);
        wxString Truncate(wxString str, size_t width, bool show_ellipsis=true);
        void ClearDetails();
        void CopyToClipboard(wxString text);
        void ShowPassToggle(bool bShow);
        wxString GetPassword();
        void SaveData();




    private:
        void OnHelp(wxCommandEvent& event);
        void OnUpdate(wxCommandEvent& event);
        void OnAutoLogoff(wxCommandEvent& event);
        void OnLog(wxCommandEvent& event);
        void OnLogOut(wxCommandEvent& event);
        void OnChangeMaster(wxCommandEvent& event);
        void OnMore(wxCommandEvent& event);

        //(*Handlers(oormipassFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButtonAddGroupClick(wxCommandEvent& event);
        void OnListBoxGroupSelect(wxCommandEvent& event);
        void OnListBoxItemsSelect(wxCommandEvent& event);
        void OnButtonEditGroupClick(wxCommandEvent& event);
        void OnButtonRemoveGroupClick(wxCommandEvent& event);
        void OnButtonAddItemClick(wxCommandEvent& event);
        void OnButtonEditItemClick(wxCommandEvent& event);
        void OnButtonRemoveItemClick(wxCommandEvent& event);
        void OnTimerHighlightTrigger(wxTimerEvent& event);
        void OnButtonClearClick(wxCommandEvent& event);
        void OnButtonSaveFormClick(wxCommandEvent& event);
        void OnButtonCopyLinkClick(wxCommandEvent& event);
        void OnButtonCopyUserClick(wxCommandEvent& event);
        void OnButtonCopyPassClick(wxCommandEvent& event);
        void OnButtonShowPassClick(wxCommandEvent& event);
        void OnButtonNewPassClick(wxCommandEvent& event);
        void OnButtonLaunchClick(wxCommandEvent& event);
        void OnButtonDelClick(wxCommandEvent& event);
        void OnTimer1Trigger(wxTimerEvent& event);
        void OnMouseMove(wxMouseEvent& event);
        void OnTextCtrlLinkText(wxCommandEvent& event);
        void OnTextCtrlUSerText(wxCommandEvent& event);
        void OnTextCtrlPassText(wxCommandEvent& event);
        void OnTextCtrlNotesText(wxCommandEvent& event);
        void OnTextCtrlGroupNameText(wxCommandEvent& event);
        void OnTextCtrlItemNameText(wxCommandEvent& event);
        //*)

        //(*Identifiers(oormipassFrame)
        static const long ID_STATICBOX1;
        static const long ID_LISTBOX_GROUP;
        static const long ID_BUTTON_ADDGROUP;
        static const long ID_STATICBOX2;
        static const long ID_LISTBOXITEMS;
        static const long ID_BUTTON_ADDITEM;
        static const long ID_STATICBOX3;
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL_LINK;
        static const long ID_BUTTON_LAUNCH;
        static const long ID_BUTTON_COPYLINK;
        static const long ID_STATICTEXT2;
        static const long ID_TEXTCTRL_USER;
        static const long ID_BUTTON_COPYUSER;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL_NOTES;
        static const long ID_STATICTEXT4;
        static const long ID_TEXTCTRL_PASS;
        static const long ID_BUTTON_COPYPASS;
        static const long ID_BUTTON_NEWPASS;
        static const long ID_BUTTON_REMGROUP;
        static const long ID_BUTTON_REMITEM;
        static const long ID_TEXTCTRL_GROUPNAME;
        static const long ID_BUTTON_EDITGROUP;
        static const long ID_TEXTCTRL_ITEMNAME;
        static const long ID_BUTTON_EDITITEM;
        static const long ID_BUTTON_SAVEFORM;
        static const long ID_BUTTON_SHOWPASS;
        static const long ID_BUTTON_CLEAR;
        static const long ID_BUTTON_DEL;
        static const long idMenuLogOut;
        static const long ID_MENUITEM1;
        static const long idMenuAuto;
        static const long idMenuLog;
        static const long idMenuChangeMaster;
        static const long idMenuHelp;
        static const long idMenuUpdate;
        static const long idMenuMore;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long ID_TIMER_HIGHLIGHT;
        static const long ID_TIMER_LOGOFF;
        //*)

        //(*Declarations(oormipassFrame)
        wxButton* ButtonAddGroup;
        wxButton* ButtonAddItem;
        wxButton* ButtonClear;
        wxButton* ButtonCopyLink;
        wxButton* ButtonCopyPass;
        wxButton* ButtonCopyUser;
        wxButton* ButtonDel;
        wxButton* ButtonEditGroup;
        wxButton* ButtonEditItem;
        wxButton* ButtonLaunch;
        wxButton* ButtonNewPass;
        wxButton* ButtonRemoveGroup;
        wxButton* ButtonRemoveItem;
        wxButton* ButtonSaveForm;
        wxButton* ButtonShowPass;
        wxListBox* ListBoxGroup;
        wxListBox* ListBoxItems;
        wxMenu* Menu3;
        wxMenuItem* MenuItem3;
        wxMenuItem* MenuItem4;
        wxMenuItem* MenuItem5;
        wxMenuItem* MenuItem6;
        wxMenuItem* MenuItem7;
        wxMenuItem* MenuItem8;
        wxMenuItem* MenuItem9;
        wxStaticBox* StaticBox1;
        wxStaticBox* StaticBox2;
        wxStaticBox* StaticBox3;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxStatusBar* StatusBar1;
        wxTextCtrl* TextCtrlGroupName;
        wxTextCtrl* TextCtrlItemName;
        wxTextCtrl* TextCtrlLink;
        wxTextCtrl* TextCtrlNotes;
        wxTextCtrl* TextCtrlPass;
        wxTextCtrl* TextCtrlUSer;
        wxTimer TimerHighlight;
        wxTimer TimerLogOff;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // OORMIPASSMAIN_H
