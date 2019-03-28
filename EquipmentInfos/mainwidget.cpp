#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    xmlUtil()
{
    setWindowFlag(Qt::WindowMaximizeButtonHint);
    setFixedSize(353, 442);
    ui->setupUi(this);

    dialog = new TipsDialog (this);
    //部门列表
    xmlUtil.getDepartList(departList);
    if(!departList.isEmpty())
        ui->cBox_depart->addItems(departList);

    //下拉框自动补充
    QCompleter *departCompleter = new QCompleter(ui->cBox_depart->model(), this);
    ui->cBox_depart->setCompleter(departCompleter);
    departCompleter->setFilterMode(Qt::MatchContains);
    departCompleter->setModelSorting(QCompleter::CaseInsensitivelySortedModel);

    QCompleter *classCompleter = new QCompleter(ui->cBox_class->model(), this);
    ui->cBox_class->setCompleter(classCompleter);
    classCompleter->setFilterMode(Qt::MatchContains);
    classCompleter->setModelSorting(QCompleter::CaseInsensitivelySortedModel);

    equipInfos = EquipmentUtil::getSoftwareInfos();
    EquipmentInfo info = EquipmentUtil::getOSInfo();
    equipInfos.push_back(info);
}

MainWidget::~MainWidget()
{
    delete ui;
    delete dialog;
}

void MainWidget::on_pBtn_start_clicked()
{
    //禁止所有输入
    changedAllUIEnable(false);
    this->setCursor(Qt::WaitCursor);
    //获取部门、课别、姓名
    departStr = ui->cBox_depart->currentText();
    classStr = ui->cBox_class->currentText();
    userStr = ui->lineEdit_user->text();
    //检查信息输入
    if(departStr.isEmpty() || classStr.isEmpty() || userStr.isEmpty()){
        changedAllUIEnable(true);
        this->setCursor(Qt::ArrowCursor);
        QMessageBox::question(this, tr("温馨提示"), tr("请检查内容是否填写完整"),
                              QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    //存储部门、课别至xml文件，存在则放弃操作
    //执行失败不存储
    //Excel生成
    //成功0倒计时退出or回车退出
    //-1失败，关闭Excel再来一次
    xmlUtil.writeXml(departStr, classStr);
    ExcelUtil excelUtil(userStr, departStr, classStr);

    if(!equipInfos.isEmpty()){
        QString displayerDate = ui->lineEdit_displayer_date->text();
        QString displayerNumber = ui->lineEdit_displayer->text();
        EquipmentInfo displayerInfo("显示器", displayerNumber + "(固资编号)", displayerDate + "(购买时间)");

        QString engineDate = ui->lineEdit_engine_date->text();
        QString engineNumber = ui->lineEdit_main_engine->text();
        EquipmentInfo engineInfo("主机", engineNumber + "(固资编号)", engineDate + "(购买时间)");

        for(int i = 0; i < equipInfos.length(); i ++){
            if(equipInfos.at(i).getEquipmentName() == displayerInfo.getEquipmentName()){
                equipInfos.removeAt(i);
                break;
            }
        }
        for(int i = 0; i < equipInfos.length(); i ++){
            if(equipInfos.at(i).getEquipmentName() == engineInfo.getEquipmentName()){
                equipInfos.removeAt(i);
                break;
            }
        }
        equipInfos.push_front(displayerInfo);
        equipInfos.push_front(engineInfo);


        if(excelUtil.toExcelFile(equipInfos)){
            dialog->setStatus(false);
            dialog->show();
        }else{
            dialog->setStatus(true);
            dialog->show();
        }
    }else{
        QMessageBox::question(this, tr("温馨提示"), tr("没有读写到系统内容\n请邮箱联系资讯室"),
                              QMessageBox::Ok, QMessageBox::Ok);
    }

    this->setCursor(Qt::ArrowCursor);
    changedAllUIEnable(true);
}

void MainWidget::changedAllUIEnable(bool enabled)
{
    ui->pBtn_start->setEnabled(enabled);
    ui->cBox_depart->setEnabled(enabled);
    ui->cBox_class->setEnabled(enabled);
    ui->lineEdit_user->setEnabled(enabled);
    ui->lineEdit_main_engine->setEnabled(enabled);
    ui->lineEdit_engine_date->setEnabled(enabled);
    ui->lineEdit_displayer->setEnabled(enabled);
    ui->lineEdit_displayer_date->setEnabled(enabled);
}



void MainWidget::on_cBox_depart_editTextChanged(const QString &arg1)
{
    int currentIndex = ui->cBox_depart->currentIndex();
    if(currentIndex != -1){
        if(currentIndex < departList.length()){
            if(arg1 == departList.at(currentIndex)){//确实是选择下拉框的
                QStringList classList;
                xmlUtil.getClassList(arg1, classList);
                ui->cBox_class->clear();
                if(!classList.isEmpty()){
                    ui->cBox_class->addItems(classList);
                }
            }else{
                ui->cBox_class->clear();
            }
        }
    }
}
