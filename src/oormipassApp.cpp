/***************************************************************
 * Name:      oormipassApp.cpp
 * Purpose:   Code for Application Class
 * Author:    oormi creations (oormicreations@gmail.com)
 * Created:   2018-12-22
 * Copyright: oormi creations (https://oormi.in)
 * License:
 **************************************************************/

#include "oormipassApp.h"
#include "LoginDialog.h"
#include "FileHelper.h"
#include "DisclaimerDialog.h"
#include "GenPassDialog.h"
#include <wx/msgdlg.h>
#include <wx/string.h>

//(*AppHeaders
#include "oormipassMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(oormipassApp);

bool oormipassApp::OnInit()
{
    FileHelper fileHelper;
    if(!fileHelper.SetUserPath()) return false;

    if(!fileHelper.exist(fileHelper.m_sUserPath.ToStdString() + "\\masterhash"))
    {
        DisclaimerDialog disDlg(0);
        if(disDlg.ShowModal()) return false; //close button returns true
        else
        {
            GenPassDialog genPassDlg(0);
            genPassDlg.m_bIsMaster = true;
            if(!genPassDlg.ShowModal()) return false;
        }
    }

    LoginDialog loginDlg(0);
    if(loginDlg.ShowModal()) return false; //close button returns true

    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	oormipassFrame* Frame = new oormipassFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
