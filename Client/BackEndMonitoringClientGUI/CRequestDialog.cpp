#include "CRequestDialog.h"
#include "ui_CRequestDialog.h"

CRequestDialog::CRequestDialog(QWidget *parent) :
    QDialog(parent),
    m_data_type(ERequestDataType::PROCESSES_DATA),
    ui(new Ui::CRequestDialog)
{
    ui->setupUi(this);

    ui->date_from->setEnabled(false);
    ui->date_to->setEnabled(false);
}

CRequestDialog::~CRequestDialog()
{
    delete ui;
}

ERequestDataType CRequestDialog::GetRequestType()
{
    return m_data_type;
}

void CRequestDialog::on_request_combo_box_currentIndexChanged(int index)
{
    if(index == 2)
    {
        ui->date_from->setEnabled(true);
        ui->date_to->setEnabled(true);
    }
    else
    {
        ui->date_from->setEnabled(false);
        ui->date_to->setEnabled(false);
    }
}

void CRequestDialog::on_request_button_clicked()
{
    close();
}

void CRequestDialog::on_cancel_utton_clicked()
{
    close();
}

void CRequestDialog::on_comboBox_currentIndexChanged(int index)
{
    switch(index)
    {
        case(0):
        {
            m_data_type = ERequestDataType::PROCESSES_DATA;
            break;
        }
        case(1):
        {
            m_data_type = ERequestDataType::DRIVES_DATA;
            break;
        }
        case(2):
        {
            m_data_type = ERequestDataType::All_DATA;
            break;
        }
    }
}
