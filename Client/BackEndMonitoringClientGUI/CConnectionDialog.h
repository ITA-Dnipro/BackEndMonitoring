#ifndef CCONNECTIONDIALOG_H
#define CCONNECTIONDIALOG_H

#include <memory>
#include <QDialog>

class CClientController;

namespace Ui {
class CConnectionDialog;
}

class CConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CConnectionDialog(std::shared_ptr<CClientController> controller,
                               QWidget *parent = nullptr);
    ~CConnectionDialog();

    bool IsConnected();
private slots:
    void on_connect_button_clicked();

private:
    Ui::CConnectionDialog *ui;
    std::shared_ptr<CClientController> m_controller;
    bool m_is_connected;
};

#endif // CCONNECTIONDIALOG_H
