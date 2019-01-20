#ifndef FILEHELPER_H
#define FILEHELPER_H
#include <string>
#include <fstream>
#include <wx/string.h>

class FileHelper
{
    public:
        FileHelper();
        virtual ~FileHelper();

        bool SetUserPath();
        bool FHSaveFile(std::string sFileName, std::string sData);
        std::string FHReadFile(std::string sFileName);
        std::string GetTimeStamp();
        inline bool exist(const std::string& name)
        {
            std::ifstream file(name);
            return (bool)file;
        }

        static wxString m_sUserPath;


    protected:

    private:



};

#endif // FILEHELPER_H
