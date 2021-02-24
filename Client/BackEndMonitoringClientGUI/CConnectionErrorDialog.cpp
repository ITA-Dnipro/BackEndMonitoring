#include "CConnectionErrorDialog.h"
#include "ui_CConnectionErrorDialog.h"

CConnectionErrorDialog::CConnectionErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CConnectionErrorDialog),
    m_open_reconnect_menu(false)
{
    ui->setupUi(this);
}

CConnectionErrorDialog::~CConnectionErrorDialog()
{
    delete ui;
}

bool CConnectionErrorDialog::IsNeedToOpenReconnectMenu()
{
    return m_open_reconnect_menu;
}

void CConnectionErrorDialog::on_pushButton_2_clicked()
{
    m_open_reconnect_menu = true;
    close();
}

void CConnectionErrorDialog::on_pushButton_clicked()
{
    close();
}
