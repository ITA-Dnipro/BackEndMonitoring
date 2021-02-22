#ifndef CPROCESSESTAB_H
#define CPROCESSESTAB_H

#include <QTabWidget>
#include <QString>

#include "nlohmann/json.hpp"
#include "CProcessesTable.h"

class CProcessesTab : public QWidget
{
public:
    CProcessesTab(QWidget* parent);
    ~CProcessesTab();

    bool Initialize(const nlohmann::json& data);
    bool GetTabName(QString& to_string);
private:
    QString m_tab_name;
    bool m_is_initialized;
};

#endif // CPROCESSESTAB_H
