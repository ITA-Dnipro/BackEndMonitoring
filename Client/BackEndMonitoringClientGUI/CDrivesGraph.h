#ifndef CDRIVESGRAPH_H
#define CDRIVESGRAPH_H

#include <map>

#include <QVector>
#include <QString>

#include "qcustomplot.h"
#include "nlohmann/json.hpp"

class CDrivesGraph
{
public:
    CDrivesGraph(QCustomPlot* graph);

    bool AddEntry(const nlohmann::json& entry);
    bool Clear();
    bool Update();

private:
    QCustomPlot* m_graph;
    std::map<QString,
             QSharedPointer<QCPGraphDataContainer>> m_data;
    time_t m_min_date = LLONG_MAX;
    time_t m_max_date = 0;
    float m_max_val = 0;
};

#endif // CDRIVESGRAPH_H
