#include "CRequestDialog.h"
#include "ui_CRequestDialog.h"

CRequestDialog::CRequestDialog(QWidget *parent) :
    QDialog(parent),
    m_data_type(ERequestDataType::PROCESSES_DATA),
    m_select_type(ERequestSelectType::LAST_INFO),
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

ERequestSelectType CRequestDialog::GetSelectType()
{
    return m_select_type;
}

void CRequestDialog::on_request_combo_box_currentIndexChanged(int index)
{
    switch(index)
    {
        case(0):
        {
            m_select_type = ERequestSelectType::LAST_INFO;
            ui->date_from->setEnabled(false);
            ui->date_to->setEnabled(false);
            break;
        }
        case(1):
        {
            m_select_type = ERequestSelectType::ALL_INFO;
            ui->date_from->setEnabled(false);
            ui->date_to->setEnabled(false);
            break;
        }
        case(2):
        {
            m_select_type = ERequestSelectType::SELECTED_INFO;
            ui->date_from->setEnabled(true);
            ui->date_to->setEnabled(true);
            break;
        }
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
