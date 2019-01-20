#include "PassItem.h"

PassItem::PassItem()
{
    //ctor
    m_bDeleted = false;
}

PassItem::~PassItem()
{
    //dtor
}

void PassItem::UpdatePassItem(
wxString sGroupName,
wxString sItemName,
wxString sLink,
wxString sUser,
wxString sPassword,
wxString sNotes)
{
    m_sGroupName = sGroupName;
    m_sItemName = sItemName;
    m_sLink = sLink;
    m_sUser = sUser;
    m_sPassword = sPassword;
    m_sNotes = sNotes;

}

