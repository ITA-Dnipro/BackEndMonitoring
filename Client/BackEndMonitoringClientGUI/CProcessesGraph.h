#ifndef CPROCESSESGRAPH_H
#define CPROCESSESGRAPH_H

#include <QVector>
#include <QString>

#include "qcustomplot.h"
#include "nlohmann/json.hpp"

class CProcessesGraph
{
public:
    CProcessesGraph(QCustomPlot* CPU_graph,
                    QCustomPlot* RAM_graph,
                    QCustomPlot* pagefile_graph);

    bool AddEntry(const nlohmann::json& entry);
    bool Clear();
    bool Update();

private:
    void InitializeCPUGraph();
    void InitializeRAMGraph();
    void InitializePagefileGraph();

    time_t m_min_date = LLONG_MAX;
    time_t m_max_date = 0;

    float m_CPU_max_val = 0;
    float m_RAM_max_val = 0;
    float m_pagefile_max_val = 0;

    QSharedPointer<QCPGraphDataContainer> m_CPU_data;
    QSharedPointer<QCPGraphDataContainer> m_RAM_data;
    QSharedPointer<QCPGraphDataContainer> m_pagefile_data;

    QCustomPlot* m_CPU_graph;
    QCustomPlot* m_RAM_graph;
    QCustomPlot* m_pagefile_graph;
};

#endif // CPROCESSESGRAPH_H
