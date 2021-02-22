#include "stdafx.h"

#include "ui_CRequestDialog.h"

#include "CRequestDialog.h"

CRequestDialog::CRequestDialog(QWidget *parent) :
    QDialog(parent),
    m_request_type(ERequestType::PROCESSES_DATA),
    m_selected_range(ERequestRangeSpecification::LAST_DATA),
    m_has_request(false),
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

ERequestType CRequestDialog::GetRequestType()
{
    return m_request_type;
}

ERequestRangeSpecification CRequestDialog::GetSelectedRangeType()
{
    return m_selected_range;
}

bool CRequestDialog::HasRequest()
{
    return m_has_request;
}


std::string CRequestDialog::GetDateFrom()
{
    return m_from_date_time.toString("dd.MM.yyyy hh:mm:ss").toStdString();
}

std::string CRequestDialog::GetDateTo()
{
    return m_to_date_time.toString("dd.MM.yyyy hh:mm:ss").toStdString();
}

void CRequestDialog::on_request_combo_box_currentIndexChanged(int index)
{
    switch(index)
    {
        case(0):
        {
            m_selected_range = ERequestRangeSpecification::LAST_DATA;
            ui->date_from->setEnabled(false);
            ui->date_to->setEnabled(false);
            break;
        }
        case(1):
        {
            m_selected_range = ERequestRangeSpecification::ALL_DATA;
            ui->date_from->setEnabled(false);
            ui->date_to->setEnabled(false);
            break;
        }
        case(2):
        {
            m_selected_range = ERequestRangeSpecification::RANGE_OF_DATA;
            ui->date_from->setEnabled(true);
            ui->date_to->setEnabled(true);
            break;
        }
    }
}

void CRequestDialog::on_request_button_clicked()
{
    m_has_request = true;
    if(m_selected_range == ERequestRangeSpecification::RANGE_OF_DATA)
    {
        m_from_date_time = ui->date_from->dateTime();
        m_to_date_time = ui->date_to->dateTime();
    }
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
            m_request_type = ERequestType::PROCESSES_DATA;
            break;
        }
        case(1):
        {
            m_request_type = ERequestType::DISKS_DATA;
            break;
        }
        case(2):
        {
            m_request_type = ERequestType::ALL_DATA;
            break;
        }
    }
}
