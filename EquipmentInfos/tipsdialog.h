#ifndef TIPSDIALOG_H
#define TIPSDIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class TipsDialog;
}

class TipsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TipsDialog(QWidget *parent = nullptr);
    ~TipsDialog();

private:
    Ui::TipsDialog *ui;

    int timeLeft = 4;
    QTimer *timer;
    bool isError;

public:
    void setStatus(bool isError);
    void closeEvent(QCloseEvent* event);

private slots:
    void showTime();
    void on_pBtn_exit_clicked();
};

#endif // TIPSDIALOG_H
