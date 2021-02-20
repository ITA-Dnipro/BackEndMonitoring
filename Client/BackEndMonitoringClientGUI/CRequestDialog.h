#ifndef CREQUESTDIALOG_H
#define CREQUESTDIALOG_H

#include <QDialog>

#include "ERequestDataType.h"

namespace Ui {
class CRequestDialog;
}

class CRequestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CRequestDialog(QWidget *parent = nullptr);
    ~CRequestDialog();

    ERequestDataType GetRequestType();
private slots:
    void on_request_combo_box_currentIndexChanged(int index);

    void on_request_button_clicked();

    void on_cancel_utton_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    ERequestDataType m_data_type;
    Ui::CRequestDialog *ui;
};

#endif // CREQUESTDIALOG_H
