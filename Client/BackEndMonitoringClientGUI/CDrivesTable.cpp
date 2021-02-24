#include "stdafx.h"

#include <QHeaderView>

#include "CDrivesTable.h"

CDrivesTable::CDrivesTable(QWidget* parent)
    : QTableWidget(parent),
      m_is_initialized(false)
{
    if (columnCount() < 4)
        setColumnCount(4);

    QTableWidgetItem * table_item1 = new QTableWidgetItem();
    table_item1->setText("Name");
    setHorizontalHeaderItem(0, table_item1);
    QTableWidgetItem *table_item2 = new QTableWidgetItem();
    table_item2->setText("Capacity");
    setHorizontalHeaderItem(1, table_item2);
    QTableWidgetItem *table_item3 = new QTableWidgetItem();
    table_item3->setText("Free");
    setHorizontalHeaderItem(2, table_item3);
    QTableWidgetItem *table_item4 = new QTableWidgetItem();
    table_item4->setText("Available");
    setHorizontalHeaderItem(3, table_item4);

    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setVisible(false);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSortingEnabled(true);
}

CDrivesTable::~CDrivesTable()
{
    qDebug("__DRIVES_TABLE_DELETED__");
}

bool CDrivesTable::Initialize(const nlohmann::json& data)
{
    if(m_is_initialized)
    {  return false;}

    unsigned row = 0;
    for(auto drive : data)
    {
        insertRow(row);

        QTableWidgetItem* name_item = new QTableWidgetItem(QString::fromStdString(drive["name"].get<std::string>()));
        setItem(row, 0, name_item);

        QTableWidgetItem* capacity_item = new QTableWidgetItem();
        capacity_item->setData(Qt::EditRole, drive["capacity"].get<unsigned>());
        setItem(row, 1, capacity_item);

        QTableWidgetItem* free_item = new QTableWidgetItem();
        free_item->setData(Qt::EditRole, drive["free"].get<unsigned>());
        setItem(row, 2, free_item);

        QTableWidgetItem* avaliable_item = new QTableWidgetItem();
        avaliable_item->setData(Qt::EditRole, drive["available"].get<unsigned>());
        setItem(row, 3, avaliable_item);

        ++row;
    }
    return m_is_initialized = true;
}

