#include <QGridLayout>

#include "CDrivesTab.h"

CDrivesTab::CDrivesTab(QWidget* parent)
    : QWidget(parent),
      m_is_initialized(false)
{ }

CDrivesTab::~CDrivesTab()
{
    qDebug("DRIVES TAB DELETED");
}

bool CDrivesTab::Initialize(const nlohmann::json& data)
{
    if(m_is_initialized)
    { return false;}

    m_tab_name = QString::fromStdString(
                data["date"].get<std::string>());

    QGridLayout* tab_layout = new QGridLayout(this);
    CDrivesTable* drives_table = new CDrivesTable(this);
    tab_layout->addWidget(drives_table, 0, 0, 1, 1);
    return m_is_initialized =
            drives_table->Initialize(data["info"]);
}

bool CDrivesTab::GetTabName(QString& to_string)
{
    if(m_is_initialized)
    {
        to_string = m_tab_name;
        return true;
    }
    return false;
}
