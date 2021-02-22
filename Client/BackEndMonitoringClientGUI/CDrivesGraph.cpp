#include <QColor>

#include "Utils/include/Utils.h"

#include "CDrivesGraph.h"

CDrivesGraph::CDrivesGraph(QCustomPlot* graph)
    : m_graph(graph)
{
    m_graph->xAxis->setLabel("time");
    m_graph->yAxis->setLabel("free space");
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("dd.MM.yyyy\nhh:mm:ss");
    m_graph->xAxis->setTicker(dateTicker);
    m_graph->legend->setVisible(true);
}

bool CDrivesGraph::AddEntry(const nlohmann::json& entry)
{
    if(m_graph == nullptr)
    { return false;}

    time_t date;
    if(!Utils::StringToDate(entry["date"].get<std::string>(),
                            "%d.%m.%Y %X", date))
    { return false;}

    if(date > m_max_date)
    { m_max_date = date;}
    if(date < m_min_date)
    { m_min_date = date;}

    for(auto drive : entry["info"])
    {
        qDebug("Entered graph cycle");
        QString drive_name = QString::fromStdString(
                    drive["name"].get<std::string>());
        float val = drive["free"].get<float>();
        if(val > m_max_val)
        { m_max_val = val;}

        if(m_data[drive_name].get() == nullptr)
        { m_data[drive_name] = QSharedPointer<QCPGraphDataContainer>::create();}

        m_data[drive_name]->add({static_cast<double>(date),
                                val});
    }
    return true;
}

bool CDrivesGraph::Clear()
{
    if(m_graph == nullptr)
    { return false;}

    m_graph->clearGraphs();
    m_data.clear();
    return true;
}

bool CDrivesGraph::Update()
{
    if(m_graph == nullptr)
    { return false;}

    m_graph->xAxis->setRange(m_min_date, m_max_date);
    m_graph->yAxis->setRange(0, m_max_val + (m_max_val * 0.1));

    unsigned i = 0;
    for(auto& graph : m_data)
    {
        QColor color(20+200/4.0*i,70*(1.6-i/4.0), 150, 150);
        m_graph->addGraph();
        m_graph->graph(i)->setData(graph.second);
        m_graph->graph(i)->setName(graph.first);
        m_graph->graph(i)->setPen(QPen(color.lighter(200)));
        m_graph->graph(i)->setBrush(QBrush(color));
        ++i;
    }

    m_graph->replot();
    return true;
}
