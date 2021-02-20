#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <memory>
#include "CClientController.h"
#include "3rdParty/include/json.hpp"

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
private:
    void UpdateProcessesData();
    void UpdateProcessesTable(const nlohmann::json& data);
    void UpdateProcessesGraph(const nlohmann::json& data);

    void UpdateDrivesData();
    void UpdateDrivesTable(const nlohmann::json& data);
    void UpdateDrivesGraph(const nlohmann::json& data);

    Ui::CMainWindow *ui;
    std::shared_ptr<CClientController> m_controller;
    QTimer timer;
};
#endif // CMAINWINDOW_H
