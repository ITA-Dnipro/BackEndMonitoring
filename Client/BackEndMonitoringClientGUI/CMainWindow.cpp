#include "stdafx.h"

#include <QDebug>

#include "ui_CMainWindow.h"
#include "CRequestDialog.h"
#include "CConnectionDialog.h"
#include "CProcessesTab.h"
#include "CProcessesGraph.h"
#include "CDrivesTab.h"
#include "CDrivesGraph.h"
#include "Utils.h"
#include "CClientController.h"

#include "CMainWindow.h"

CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CMainWindow),
      m_controller(new CClientController),
      m_timer(this)
{
    ui->setupUi(this);

    CConnectionDialog *dialog = new CConnectionDialog(m_controller, this);
    dialog->setWindowModality(Qt::ApplicationModal);
    dialog->exec();
    if(!dialog->IsConnected())
    {
        QTimer::singleShot(0, this, SLOT(close()));
    }

    m_drives_graph = std::make_unique<CDrivesGraph>(ui->drives_graph);
    m_processes_graph = std::make_unique<CProcessesGraph>(ui->CPU_graph, ui->RAM_graph,
                                                          ui->Pagefile_graph);

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(on_update_timer_tick()));
    m_timer.start(10000);
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::on_actionReconnect_triggered()
{
    CConnectionDialog *dialog = new CConnectionDialog(m_controller, this);
    dialog->open();
}

void CMainWindow::on_request_button_clicked()
{
    CRequestDialog *dialog = new CRequestDialog(this);
    dialog->exec();

    if(dialog->HasRequest())
    {
        switch (dialog->GetSelectedRangeType()) {
            case(ERequestRangeSpecification::LAST_DATA):
            {
                HandleAddRequest(dialog->GetRequestType(),
                                 dialog->GetSelectedRangeType());
                break;
            }
            case(ERequestRangeSpecification::RANGE_OF_DATA):
            {
                HandleUpdateRequest(dialog->GetRequestType(),
                                 dialog->GetSelectedRangeType(),
                                 dialog->GetDateFrom(),
                                 dialog->GetDateTo());
                break;
            }
            default:
            {
                HandleUpdateRequest(dialog->GetRequestType(),
                                    dialog->GetSelectedRangeType());
                break;
            }
        }
    }
    delete dialog;
}

void CMainWindow::on_update_timer_tick()
{
    HandleAddRequest(ERequestType::ALL_DATA,
                     ERequestRangeSpecification::LAST_DATA);
}

void CMainWindow::HandleAddRequest(ERequestType request_type,
                                   ERequestRangeSpecification range)
{
    try{
    switch (request_type) {
        case(ERequestType::PROCESSES_DATA) :
        {
            AddProcessesData(request_type,
                             range);
            break;
        }
        case(ERequestType::DISKS_DATA) :
        {
            AddDrivesData(request_type,
                          range);
            break;
        }
        case(ERequestType::ALL_DATA) :
        {
            AddProcessesData(ERequestType::PROCESSES_DATA,
                             range);
            AddDrivesData(ERequestType::DISKS_DATA,
                          range);
            break;
        }
        default :
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Something went wrong!");
            messageBox.setFixedSize(500,200);
        }
    }

    }
    catch(const nlohmann::json::exception&)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Something went wrong!");
        messageBox.setFixedSize(500,200);
    }
}

void CMainWindow::HandleUpdateRequest(ERequestType request_type,
                                      ERequestRangeSpecification range,
                                      const std::string& from,
                                      const std::string& to)
{
    try{
    switch (request_type) {
        case(ERequestType::PROCESSES_DATA) :
        {
            UpdateProcessesData(request_type,
                                range, from, to);
            break;
        }
        case(ERequestType::DISKS_DATA) :
        {
            UpdateDrivesData(request_type,
                             range, from, to);
            break;
        }
        case(ERequestType::ALL_DATA) :
        {
            UpdateProcessesData(ERequestType::PROCESSES_DATA,
                                range, from, to);
            UpdateDrivesData(ERequestType::DISKS_DATA,
                             range, from, to);
            break;
        }
        default :
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Something went wrong!");
            messageBox.setFixedSize(500,200);
        }
    }
    }
    catch(const nlohmann::json::exception&)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Something went wrong!");
        messageBox.setFixedSize(500,200);
    }
}

void CMainWindow::UpdateProcessesData(ERequestType request_type,
                                      ERequestRangeSpecification range,
                                      const std::string& from,
                                      const std::string& to)
{
    std::string last_proc_data;
    if(m_controller->MakeRequest(last_proc_data, request_type, range, from, to))
    {
        nlohmann::json parsed_proc_data = nlohmann::json::parse(last_proc_data);
        nlohmann::json parsed_processes_data
                = nlohmann::json::parse(parsed_proc_data["processes"].get<std::string>());
        nlohmann::json parsed_resources_data
                = nlohmann::json::parse(parsed_proc_data["resources"].get<std::string>());

        UpdateProcessesTable(parsed_processes_data);
        UpdateProcessesGraph(parsed_resources_data);
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Something went wrong!");
        messageBox.setFixedSize(500,200);
    }
}

void CMainWindow::AddProcessesData(ERequestType request_type,
                                   ERequestRangeSpecification range)
{
    std::string last_proc_data;
    if(m_controller->MakeRequest(last_proc_data, request_type, range))
    {
        nlohmann::json parsed_proc_data = nlohmann::json::parse(last_proc_data);
        nlohmann::json parsed_processes_data
                = nlohmann::json::parse(parsed_proc_data["processes"].get<std::string>());
        nlohmann::json parsed_resources_data
                = nlohmann::json::parse(parsed_proc_data["resources"].get<std::string>());

        AddProcessesTable(parsed_processes_data);
        AddToProcessesGraph(parsed_resources_data);
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Something went wrong!");
        messageBox.setFixedSize(500,200);
    }
}

void CMainWindow::UpdateProcessesTable(const nlohmann::json& data)
{
    while(ui->proc_tab_widget->count())
    {
        ui->proc_tab_widget->widget(ui->proc_tab_widget->currentIndex())->deleteLater();
        ui->proc_tab_widget->removeTab(ui->proc_tab_widget->currentIndex());
    }

    AddProcessesTable(data);
}

void CMainWindow::AddProcessesTable(const nlohmann::json& data)
{
    for(auto entry : data)
    {
        QString date_str = QString::fromStdString(
                    entry["date"].get<std::string>());


        int found_index = -1;
        if(ui->proc_tab_widget->count() != 0)
        {
            for(int i = ui->proc_tab_widget->count(); i >= 0; --i)
            {
                  if (ui->proc_tab_widget->tabText(i) == date_str)
                  {
                    found_index = i;
                    break;
                  }
            }
        }
        if(found_index == -1)
        {
            CProcessesTab* proc_tab = new CProcessesTab(ui->proc_tab_widget);
            if(proc_tab->Initialize(entry))
            {
                QString date;
                if(proc_tab->GetTabName(date))
                {
                        ui->proc_tab_widget->addTab(proc_tab, date);
                }
            }
        }
    }
}

void CMainWindow::UpdateProcessesGraph(const nlohmann::json& data)
{
     m_processes_graph->Clear();
     AddToProcessesGraph(data);

}

void CMainWindow::AddToProcessesGraph(const nlohmann::json& data)
{
    bool success = false;
    for(auto entry : data)
    {
        success = m_processes_graph->AddEntry(entry);
    }
    success = m_processes_graph->Update();

    if(!success)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Something went wrong!");
        messageBox.setFixedSize(500,200);
    }

}


void CMainWindow::UpdateDrivesData(ERequestType request_type,
                                   ERequestRangeSpecification range,
                                   const std::string& from,
                                   const std::string& to)
{
    std::string last_drives_data;
    if(m_controller->MakeRequest(last_drives_data, request_type, range, from, to))
    {
        nlohmann::json parsed_drives_data = nlohmann::json::parse(last_drives_data);
        UpdateDrives(parsed_drives_data);
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Something went wrong!");
        messageBox.setFixedSize(500,200);
    }
}

void CMainWindow::AddDrivesData(ERequestType request_type,
                                ERequestRangeSpecification range)
{
    std::string last_drives_data;
    if(m_controller->MakeRequest(last_drives_data, request_type, range))
    {
        nlohmann::json parsed_drives_data = nlohmann::json::parse(last_drives_data);
        AddToDrives(parsed_drives_data);
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Something went wrong!");
        messageBox.setFixedSize(500,200);
    }
}

void CMainWindow::UpdateDrives(const nlohmann::json& data)
{
    while(ui->drives_tab_widget->count())
    {
        ui->drives_tab_widget->widget(ui->drives_tab_widget->currentIndex())->deleteLater();
        ui->drives_tab_widget->removeTab(ui->drives_tab_widget->currentIndex());
    }
    m_drives_graph->Clear();

    AddToDrives(data);
}

void CMainWindow::AddToDrives(const nlohmann::json& data)
{
    bool changes_presented = false;
    for(auto entry : data)
    {
        QString date_str = QString::fromStdString(
                    entry["date"].get<std::string>());

        int found_index = -1;
        if(ui->drives_tab_widget->count() != 0)
        {
            for(int i = ui->drives_tab_widget->count(); i >= 0; --i)
            {
                  if (ui->drives_tab_widget->tabText(i) == date_str)
                  {
                    found_index = i;
                    break;
                  }
            }
        }
        if(found_index == -1)
        {
            CDrivesTab* drives_tab = new CDrivesTab(ui->drives_tab_widget);
            if(drives_tab->Initialize(entry))
            {
                QString date;
                if(drives_tab->GetTabName(date))
                {
                        ui->drives_tab_widget->addTab(drives_tab, date);
                        m_drives_graph->AddEntry(entry);
                        changes_presented = true;
                }
            }
        }
    }
    if(changes_presented)
    { m_drives_graph->Update();}
}
