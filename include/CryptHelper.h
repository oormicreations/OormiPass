#ifndef CRYPTHELPER_H
#define CRYPTHELPER_H

#include <wx/string.h>
#include <wx/msgdlg.h>
#include <wx/intl.h>

#include "cryptlib.h"
#include "sha.h"
#include "config.h"
#include "hex.h"
#include "modes.h"
#include "aes.h"
#include "filters.h"
#include "base64.h"
#include "hkdf.h"

class CryptHelper
{
    public:
        CryptHelper();
        virtual ~CryptHelper();

        std::string GenRandomString(int length=10);
        std::string HexHash(std::string sData);

        std::string encrypt(const std::string& str_in, const std::string& password, const std::string& iv);
        std::string decrypt(const std::string& str_in, const std::string& password, const std::string& iv);


    protected:

    private:
        std::string StringToHex(const std::string& input);
};

#endif // CRYPTHELPER_H
