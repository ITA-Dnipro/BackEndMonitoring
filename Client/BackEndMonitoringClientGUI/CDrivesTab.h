#ifndef CDRIVESTAB_H
#define CDRIVESTAB_H

#include <QTabWidget>
#include <QString>

#include "nlohmann/json.hpp"
#include "CDrivesTable.h"

class CDrivesTab : public QWidget
{
public:
    CDrivesTab(QWidget* parent);
    ~CDrivesTab();

    bool Initialize(const nlohmann::json& data);
    bool GetTabName(QString& to_string);
private:
    QString m_tab_name;
    bool m_is_initialized;
};

#endif // CDRIVESTAB_H
