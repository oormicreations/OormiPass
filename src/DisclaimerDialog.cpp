#include "DisclaimerDialog.h"

//(*InternalHeaders(DisclaimerDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(DisclaimerDialog)
const long DisclaimerDialog::ID_TEXTCTRL_DIS = wxNewId();
const long DisclaimerDialog::ID_BUTTON_ACC = wxNewId();
const long DisclaimerDialog::ID_BUTTON_EXIT = wxNewId();
//*)

BEGIN_EVENT_TABLE(DisclaimerDialog,wxDialog)
	//(*EventTable(DisclaimerDialog)
	//*)
END_EVENT_TABLE()

DisclaimerDialog::DisclaimerDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(DisclaimerDialog)
	Create(parent, id, _("Oormi Pass License and Disclaimer"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(400,318));
	Move(wxDefaultPosition);
	TextCtrlDis = new wxTextCtrl(this, ID_TEXTCTRL_DIS, _("Text"), wxPoint(16,16), wxSize(368,240), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_DIS"));
	ButtonAccept = new wxButton(this, ID_BUTTON_ACC, _("Accept and Continue"), wxPoint(256,272), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_ACC"));
	ButtonExit = new wxButton(this, ID_BUTTON_EXIT, _("Exit"), wxPoint(32,272), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_EXIT"));
	Center();

	Connect(ID_BUTTON_ACC,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DisclaimerDialog::OnButtonAcceptClick);
	Connect(ID_BUTTON_EXIT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DisclaimerDialog::OnButtonExitClick);
	Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&DisclaimerDialog::OnInit);
	//*)
}

DisclaimerDialog::~DisclaimerDialog()
{
	//(*Destroy(DisclaimerDialog)
	//*)
}


void DisclaimerDialog::OnInit(wxInitDialogEvent& event)
{
    TextCtrlDis->SetValue(_("The MIT License (MIT)\n\n\
Copyright (c) Oormi Creations and Contributors\n\n\
All rights reserved.\n\n\
Permission is hereby granted, free of charge, to any person obtaining a copy \
of this software and associated documentation files (the \"Software\"), to deal \
in the Software without restriction, including without limitation the rights \
to use, copy, modify, merge, publish, distribute, sublicense, and\\or sell \
copies of the Software, and to permit persons to whom the Software is \
furnished to do so, subject to the following conditions:\n\n\
The above copyright notice and this permission notice shall be included in all \
copies or substantial portions of the Software.\n\n\
THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR \
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE \
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER \
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE \
SOFTWARE."));
}

void DisclaimerDialog::OnButtonExitClick(wxCommandEvent& event)
{
    EndModal(1);
}

void DisclaimerDialog::OnButtonAcceptClick(wxCommandEvent& event)
{
    EndModal(0);
}
