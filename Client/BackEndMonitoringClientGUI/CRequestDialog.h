#ifndef CREQUESTDIALOG_H
#define CREQUESTDIALOG_H

#include <QDialog>
#include <QDateTime>

#include "ERequestType.h"
#include "ERequestRangeSpecification.h"

namespace Ui {
class CRequestDialog;
}

class CRequestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CRequestDialog(QWidget *parent = nullptr);
    ~CRequestDialog();

    ERequestType GetRequestType();
    ERequestRangeSpecification GetSelectedRangeType();
    std::string GetDateFrom();
    std::string GetDateTo();
    bool HasRequest();

private slots:
    void on_request_combo_box_currentIndexChanged(int index);

    void on_request_button_clicked();

    void on_cancel_utton_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    ERequestType m_request_type;
    ERequestRangeSpecification m_selected_range;
    QDateTime m_from_date_time;
    QDateTime m_to_date_time;
    bool m_has_request;
    Ui::CRequestDialog *ui;
};

#endif // CREQUESTDIALOG_H
