#ifndef CPROCESSESTABLE_H
#define CPROCESSESTABLE_H

#include <QTableWidget>
#include "3rdParty/include/json.hpp"

class CProcessesTable : public QTableWidget
{
public:
    CProcessesTable(QWidget* parent);
    ~CProcessesTable();

    bool Initialize(const nlohmann::json& data);
private:
    bool m_is_initialized;
};

#endif // CPROCESSESTABLE_H
