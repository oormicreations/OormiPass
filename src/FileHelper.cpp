#include "FileHelper.h"
#include <wx/wx.h>
#include <wx/filedlg.h>
#include <wx/stdpaths.h>
#include <wx/msgdlg.h>
#include <wx/filefn.h>
#include <chrono>
#include <sstream>

wxString FileHelper::m_sUserPath = "nil";

FileHelper::FileHelper()
{
    //ctor
}

FileHelper::~FileHelper()
{
    //dtor
}

bool FileHelper::SetUserPath()
{
    wxString sDir = wxStandardPaths::Get().GetUserLocalDataDir() + _("dev"); //remove dev for release versions
    if(!wxDirExists(sDir))
    {
        if(!wxMkdir(sDir))
        {
            wxMessageBox(_("Error: User Directory creation failed!"));
            return false;
        }
    }
    m_sUserPath = sDir.ToStdString();
    //wxMessageBox(m_sUserPath);
    return true;
}

bool FileHelper::FHSaveFile(std::string sFileName, std::string sData)
{
    if(m_sUserPath.empty())
    {
        wxMessageBox(_("Error: No User Path. Failed to write data to ") + sFileName);
        return false;
    }
    if(sFileName.empty())
    {
        wxMessageBox(_("Error: No File Name. Failed to write data to ") + sFileName);
        return false;
    }

    std::fstream fs;
    fs.open (m_sUserPath + "\\" + sFileName, std::fstream::in | std::fstream::out | std::fstream::trunc);
    if(fs.fail())
    {
        wxMessageBox(_("Error: File Open Failed. Failed to write data to ") + sFileName);
        return false;
    }

    fs << sData;
    fs.close();

    return true;

}

std::string FileHelper::FHReadFile(std::string sFileName)
{
    std::string sData;

    //wxString sPath(m_sUserPath);
    if(m_sUserPath.empty()) return sData;
    if(sFileName.empty()) return sData;


    std::fstream fs;
    fs.open ((m_sUserPath + "\\" + sFileName), std::fstream::in | std::fstream::out);
    if(fs.fail())
    {
        //wxMessageBox(_("Error: Failed to read data from ") + sFileName);
        return sData;
    }

    std::stringstream buffer;
    buffer << fs.rdbuf();
    fs.close();
    sData = buffer.str();

    return sData;

}
std::string FileHelper::GetTimeStamp()
{
    std::chrono::system_clock::time_point tpToday = std::chrono::system_clock::now();
    time_t ttToday;
    ttToday = std::chrono::system_clock::to_time_t ( tpToday );
    char ch[30];
    std::strftime(ch, sizeof(ch), "%Y-%m-%d %H:%M:%S", std::localtime(&ttToday));
    std::string s(ch);
    return s;
}
