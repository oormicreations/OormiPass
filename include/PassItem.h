#ifndef PASSITEM_H
#define PASSITEM_H
#include<string>
#include <wx/string.h>

class PassItem
{
    public:
        PassItem();
        virtual ~PassItem();

        wxString m_sGroupName;
        wxString m_sItemName;
        wxString m_sLink;
        wxString m_sUser;
        wxString m_sPassword;
        wxString m_sNotes;
        bool m_bDeleted;

        void UpdatePassItem(
        wxString sGroupName,
        wxString sItemName,
        wxString sLink,
        wxString sUser,
        wxString sPassword,
        wxString sNotes);


    protected:

    private:
};

#endif // PASSITEM_H
