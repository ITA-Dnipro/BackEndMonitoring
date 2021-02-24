#ifndef CONNECTIONERRORDIALOG_H
#define CONNECTIONERRORDIALOG_H

#include <QDialog>

namespace Ui {
class CConnectionErrorDialog;
}

class CConnectionErrorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CConnectionErrorDialog(QWidget *parent = nullptr);
    ~CConnectionErrorDialog();

    bool IsNeedToOpenReconnectMenu();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::CConnectionErrorDialog *ui;
    bool m_open_reconnect_menu;
};

#endif // CONNECTIONERRORDIALOG_H
