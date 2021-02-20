#ifndef CDRIVESTABLE_H
#define CDRIVESTABLE_H

#include <QTableWidget>
#include "3rdParty/include/json.hpp"

class CDrivesTable : public QTableWidget
{
public:
    CDrivesTable(QWidget* parent);
    ~CDrivesTable();

    bool Initialize(const nlohmann::json& data);
private:
    bool m_is_initialized;
};

#endif // CDRIVESTABLE_H
