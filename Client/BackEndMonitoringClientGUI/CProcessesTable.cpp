#include "CProcessesTable.h"
#include <QHeaderView>

CProcessesTable::CProcessesTable(QWidget* parent)
    : QTableWidget(parent),
      m_is_initialized(false)
{
    if (columnCount() < 4)
        setColumnCount(4);

    QTableWidgetItem * table_item1 = new QTableWidgetItem();
    table_item1->setText("PID");
    setHorizontalHeaderItem(0, table_item1);
    QTableWidgetItem *table_item2 = new QTableWidgetItem();
    table_item2->setText("CPU");
    setHorizontalHeaderItem(1, table_item2);
    QTableWidgetItem *table_item3 = new QTableWidgetItem();
    table_item3->setText("Pagefile");
    setHorizontalHeaderItem(2, table_item3);
    QTableWidgetItem *table_item4 = new QTableWidgetItem();
    table_item4->setText("RAM");
    setHorizontalHeaderItem(3, table_item4);

    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setVisible(false);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSortingEnabled(true);
}

CProcessesTable::~CProcessesTable()
{
    qDebug("__TABLE_DELETED__");
}

bool CProcessesTable::Initialize(const nlohmann::json& data)
{
    if(m_is_initialized)
    {  return false;}

    unsigned row = 0;
    for(auto process : data)
    {
        insertRow(row);

        QTableWidgetItem* pid_item = new QTableWidgetItem(QString::number(process["PID"].get<unsigned>()));
        setItem(row, 0, pid_item);

        QTableWidgetItem* cpu_item = new QTableWidgetItem(QString::number(process["CPU_usage"].get<float>()));
        setItem(row, 1, cpu_item);

        QTableWidgetItem* pagefile_item = new QTableWidgetItem(QString::number(process["Pagefile_usage"].get<float>()));
        setItem(row, 2, pagefile_item);

        QTableWidgetItem* ram_item = new QTableWidgetItem(QString::number(process["RAM_usage"].get<float>()));
        setItem(row, 3, ram_item);

        ++row;
    }
    return m_is_initialized = true;
}
