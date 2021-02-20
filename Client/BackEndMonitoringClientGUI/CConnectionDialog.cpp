#include <string>

#include <QMessageBox>
#include "CConnectionDialog.h"
#include "ui_CConnectionDialog.h"

CConnectionDialog::CConnectionDialog(std::shared_ptr<CClientController> controller,
                                     QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CConnectionDialog),
    m_controller(controller),
    m_is_connected(false)
{
    ui->setupUi(this);
}

CConnectionDialog::~CConnectionDialog()
{
    delete ui;
}

bool CConnectionDialog::IsConnected()
{
    return m_is_connected;
}

void CConnectionDialog::on_connect_button_clicked()
{
    m_controller->InitHost(ui->PORT_line->text().toInt(),
                           ui->IP_line->text().toStdString());
    m_is_connected = m_controller->Connect();
    if(m_is_connected)
    {
        close();
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Can't connect to server!");
        messageBox.setFixedSize(500,200);
    }
}
