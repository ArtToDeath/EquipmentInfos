#include "tipsdialog.h"
#include "ui_tipsdialog.h"

TipsDialog::TipsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TipsDialog)
{
    ui->setupUi(this);
    isError = false;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
}

TipsDialog::~TipsDialog()
{
    delete ui;
}

void TipsDialog::setStatus(bool isError)
{
    if(isError){
        QPixmap pixmap(":/status/images/error.png");
        ui->label_status->setPixmap(pixmap);
        this->isError = true;
        ui->label_time->setText("程序错误\n 5 秒后返回");
    }else{
        QPixmap pixmap(":/status/images/finish.png");
        ui->label_status->setPixmap(pixmap);
        this->isError = false;
        ui->label_time->setText("5 秒后自动关闭程序");
    }
    timer->start(1000);
}

void TipsDialog::closeEvent(QCloseEvent *event)
{
    timer->stop();
    if(isError){
        //不关闭父窗口
        this->accept();
    }else{//close
        qApp->quit();
    }
}

void TipsDialog::showTime()
{
    if(timeLeft > 0){
        if(isError){
            ui->label_time->setText(QString("程序错误\n %1 秒后返回").arg(timeLeft));
        }else{
            ui->label_time->setText(QString("%1 秒后自动关闭程序").arg(timeLeft));
        }
        timeLeft --;
    }else{
        timer->stop();
        if(isError){
            //不关闭父窗口
            this->accept();
        }else{//close
            qApp->quit();
        }
    }
}

void TipsDialog::on_pBtn_exit_clicked()
{
    timer->stop();
    if(isError){
        //不关闭父窗口
        this->accept();
    }else{//close
        qApp->quit();
    }
}
