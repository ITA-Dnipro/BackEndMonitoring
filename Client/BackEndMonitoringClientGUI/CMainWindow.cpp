#include "CMainWindow.h"
#include "CConnectionDialog.h"
#include "CRequestDialog.h"
#include "ui_CMainWindow.h"
#include "ERequestType.h"
#include "CProcessesTab.h"
#include "CDrivesTab.h"
#include "3rdParty/include/json.hpp"
#include "Utils/include/Utils.h"
#include <QDebug>

CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CMainWindow),
      m_controller(new CClientController),
      timer(this)
{
    ui->setupUi(this);

    CConnectionDialog *dialog = new CConnectionDialog(m_controller, this);
    dialog->setWindowModality(Qt::ApplicationModal);
    dialog->exec();
    if(!dialog->IsConnected())
    {
        QTimer::singleShot(0, this, SLOT(close()));
    }
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
    switch (dialog->GetRequestType()) {
        case(ERequestDataType::PROCESSES_DATA) :
        {
            UpdateProcessesData();
            break;
        }
        case(ERequestDataType::DRIVES_DATA) :
        {
            UpdateDrivesData();
            break;
        }
        case(ERequestDataType::All_DATA) :
        {
            UpdateProcessesData();
            UpdateDrivesData();
            break;
        }
    }
    delete dialog;
}

void CMainWindow::UpdateProcessesData()
{
    std::string last_proc_data;
    if(m_controller->MakeRequest(ERequestType::PROCESSES_DATA,
                                 last_proc_data))
    {
        nlohmann::json parsed_proc_data = nlohmann::json::parse(last_proc_data);
        UpdateProcessesTable(parsed_proc_data);
        UpdateProcessesGraph(parsed_proc_data);
    }
}

void CMainWindow::UpdateProcessesTable(const nlohmann::json& data)
{
    while(ui->proc_tab_widget->count())
    {
        ui->proc_tab_widget->widget(ui->proc_tab_widget->currentIndex())->deleteLater();
        ui->proc_tab_widget->removeTab(ui->proc_tab_widget->currentIndex());
    }

    for(auto entry : data)
    {
        qDebug("Entered cycle");
        CProcessesTab* proc_tab = new CProcessesTab(ui->proc_tab_widget);
        qDebug("Proc tab created");
        if(proc_tab->Initialize(entry))
        {
            qDebug("ProcTab initialized");
            QString date;
            if(proc_tab->GetTabName(date))
            {
                qDebug("Date readed");
                qDebug(date.toStdString().c_str());

                ui->proc_tab_widget->addTab(proc_tab, date);
            }
        }
    }
}

void CMainWindow::UpdateProcessesGraph(const nlohmann::json& data)
{

}


void CMainWindow::UpdateDrivesData()
{
    std::string last_drives_data;
    if(m_controller->MakeRequest(ERequestType::DISKS_DATA,
                                 last_drives_data))
    {
        nlohmann::json parsed_drives_data = nlohmann::json::parse(last_drives_data);
        UpdateDrivesTable(parsed_drives_data);
        UpdateDrivesGraph(parsed_drives_data);
    }
}


void CMainWindow::UpdateDrivesTable(const nlohmann::json& data)
{
    while(ui->drives_tab_widget->count())
    {
        ui->drives_tab_widget->widget(ui->drives_tab_widget->currentIndex())->deleteLater();
        ui->drives_tab_widget->removeTab(ui->drives_tab_widget->currentIndex());
    }
    for(auto entry : data)
    {
        qDebug("Entered cycle");
        CDrivesTab* drives_tab = new CDrivesTab(ui->drives_tab_widget);
        qDebug("Drives tab created");
        if(drives_tab->Initialize(entry))
        {
            qDebug("Drives tab initialized");
            QString date;
            if(drives_tab->GetTabName(date))
            {
                qDebug("Date readed");
                qDebug(date.toStdString().c_str());

                ui->drives_tab_widget->addTab(drives_tab, date);
            }
        }
    }
}

void CMainWindow::UpdateDrivesGraph(const nlohmann::json& data)
{
    time_t date;
    Utils::StringToDate(data.begin()->at("date"), "%d.%m.%Y %X", date);
    S
    for(auto entry : data)
    {

    }
}
