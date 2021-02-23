#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "nlohmann/json.hpp"
#include "ERequestType.h"
#include "ERequestRangeSpecification.h"

class CDrivesGraph;
class CClientController;

QT_BEGIN_NAMESPACE
namespace Ui { class CMainWindow; }
QT_END_NAMESPACE

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

private slots:

    void on_actionReconnect_triggered();

    void on_request_button_clicked();

    void on_update_timer_tick();
private:
    void HandleAddRequest(ERequestType request_type,
                          ERequestRangeSpecification range);
    void HandleUpdateRequest(ERequestType request_type,
                             ERequestRangeSpecification range,
                             const std::string& from = "",
                             const std::string& to = "");

    void UpdateProcessesData(ERequestType request_type,
                             ERequestRangeSpecification range,
                             const std::string& from = "",
                             const std::string& to = "");
    void AddProcessesData(ERequestType request_type,
                          ERequestRangeSpecification range);

    void UpdateProcessesTable(const nlohmann::json& data);
    void UpdateProcessesGraph(const nlohmann::json& data);
    void AddToProcessesGraph(const nlohmann::json& data);

    void UpdateDrivesData(ERequestType request_type,
                          ERequestRangeSpecification range,
                          const std::string& from = "",
                          const std::string& to = "");
    void AddDrivesData(ERequestType request_type,
                       ERequestRangeSpecification range);

    void UpdateDrives(const nlohmann::json& data);
    void AddToDrives(const nlohmann::json& data);


    QTimer m_timer;
    std::shared_ptr<CClientController> m_controller;
    std::unique_ptr<CDrivesGraph> m_drives_graph;
    Ui::CMainWindow *ui;
};
#endif // CMAINWINDOW_H
