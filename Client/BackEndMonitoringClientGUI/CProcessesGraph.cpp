#include "stdafx.h"

#include <QColor>

#include "Utils.h"

#include "CProcessesGraph.h"

CProcessesGraph::CProcessesGraph(QCustomPlot* CPU_graph,
                                 QCustomPlot* RAM_graph,
                                 QCustomPlot* pagefile_graph) :
    m_CPU_graph(CPU_graph),
    m_RAM_graph(RAM_graph),
    m_pagefile_graph(pagefile_graph),
    m_CPU_data(QSharedPointer<QCPGraphDataContainer>::create()),
    m_RAM_data(QSharedPointer<QCPGraphDataContainer>::create()),
    m_pagefile_data(QSharedPointer<QCPGraphDataContainer>::create())
{
    InitializeCPUGraph();
    InitializeRAMGraph();
    InitializePagefileGraph();
}

void CProcessesGraph::InitializeCPUGraph()
{
    m_CPU_graph->xAxis->setLabel("time");
    m_CPU_graph->yAxis->setLabel("utilization %");
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("dd.MM.yyyy\nhh:mm:ss");
    m_CPU_graph->xAxis->setTicker(dateTicker);
}

void CProcessesGraph::InitializeRAMGraph()
{
    m_RAM_graph->xAxis->setLabel("time");
    m_RAM_graph->yAxis->setLabel("load");
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("dd.MM.yyyy\nhh:mm:ss");
    m_RAM_graph->xAxis->setTicker(dateTicker);
}

void CProcessesGraph::InitializePagefileGraph()
{
    m_pagefile_graph->xAxis->setLabel("time");
    m_pagefile_graph->yAxis->setLabel("load");
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("dd.MM.yyyy\nhh:mm:ss");
    m_pagefile_graph->xAxis->setTicker(dateTicker);
}

bool CProcessesGraph::AddEntry(const nlohmann::json& entry)
{
    if(m_CPU_graph == nullptr ||
       m_RAM_graph == nullptr ||
       m_pagefile_graph == nullptr)
    { return false;}

    time_t date;
    if(!Utils::StringToDate(entry["date"].get<std::string>(),
                            "%d.%m.%Y %X", date))
    { return false;}

    if(date > m_max_date)
    { m_max_date = date;}
    if(date < m_min_date)
    { m_min_date = date;}

    if(m_CPU_data.get() == nullptr)
    { m_CPU_data = QSharedPointer<QCPGraphDataContainer>::create();}
    float cpu_val = entry["cpu"].get<float>();
    if(cpu_val > m_CPU_max_val)
    { m_CPU_max_val = cpu_val;}
    m_CPU_data->add({static_cast<double>(date),
                            cpu_val});

    if(m_RAM_data.get() == nullptr)
    { m_RAM_data = QSharedPointer<QCPGraphDataContainer>::create();}
    float ram_val = entry["ram"].get<float>();
    if(ram_val > m_RAM_max_val)
    { m_RAM_max_val = ram_val;}
    m_RAM_data->add({static_cast<double>(date),
                            ram_val});

    if(m_pagefile_data.get() == nullptr)
    { m_pagefile_data = QSharedPointer<QCPGraphDataContainer>::create();}
    float pagefile_val = entry["pagefile"].get<float>();
    if(pagefile_val > m_pagefile_max_val)
    { m_pagefile_max_val = pagefile_val;}
    m_pagefile_data->add({static_cast<double>(date),
                            pagefile_val});
    return true;
}

bool CProcessesGraph::Clear()
{
    if(m_CPU_graph == nullptr ||
       m_RAM_graph == nullptr ||
       m_pagefile_graph == nullptr)
    { return false;}

    m_CPU_graph->clearGraphs();
    m_CPU_data.clear();

    m_RAM_graph->clearGraphs();
    m_RAM_data.clear();

    m_pagefile_graph->clearGraphs();
    m_pagefile_data.clear();

    return true;
}

bool CProcessesGraph::Update()
{
    if(m_CPU_graph == nullptr ||
       m_RAM_graph == nullptr ||
       m_pagefile_graph == nullptr)
    { return false;}

    m_CPU_graph->xAxis->setRange(m_min_date, m_max_date);
    m_RAM_graph->xAxis->setRange(m_min_date, m_max_date);
    m_pagefile_graph->xAxis->setRange(m_min_date, m_max_date);

    m_CPU_graph->yAxis->setRange(0, m_CPU_max_val + (m_CPU_max_val * 0.1));
    m_RAM_graph->yAxis->setRange(0, m_RAM_max_val + (m_RAM_max_val * 0.1));
    m_pagefile_graph->yAxis->setRange(0, m_pagefile_max_val + (m_pagefile_max_val * 0.1));

    QColor color(255, 0, 0);
    QPen pen(color);
    pen.setWidth(3);

    if(m_CPU_graph->graphCount() == 0)
    { m_CPU_graph->addGraph();}
    m_CPU_graph->graph(0)->setData(m_CPU_data);
    m_CPU_graph->graph(0)->setPen(pen);
    m_CPU_graph->replot();


    if(m_RAM_graph->graphCount() == 0)
    { m_RAM_graph->addGraph();}
    m_RAM_graph->graph(0)->setData(m_RAM_data);
    m_RAM_graph->graph(0)->setPen(pen);
    m_RAM_graph->replot();

    if(m_pagefile_graph->graphCount() == 0)
    { m_pagefile_graph->addGraph();}
    m_pagefile_graph->graph(0)->setData(m_pagefile_data);
    m_pagefile_graph->graph(0)->setPen(pen);
    m_pagefile_graph->replot();

    return true;
}
