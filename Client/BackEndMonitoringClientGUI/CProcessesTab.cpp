#include "CProcessesTab.h"
#include "CProcessesTable.h"
#include <QGridLayout>
#include <QDebug>

CProcessesTab::CProcessesTab(QWidget* parent)
    : QWidget(parent),
      m_is_initialized(false)
{ }

CProcessesTab::~CProcessesTab()
{
    qDebug("TAB DELETED");
}

bool CProcessesTab::Initialize(const nlohmann::json& data)
{
    if(m_is_initialized)
    { return false;}

    m_tab_name = QString::fromStdString(
                data["date"].get<std::string>());

    QGridLayout* tab_layout = new QGridLayout(this);
    CProcessesTable* proc_table = new CProcessesTable(this);
    tab_layout->addWidget(proc_table, 0, 0, 1, 1);
    return m_is_initialized =
            proc_table->Initialize(data["info"]);
}

bool CProcessesTab::GetTabName(QString& to_string)
{
    if(m_is_initialized)
    {
        to_string = m_tab_name;
        return true;
    }
    return false;
}

