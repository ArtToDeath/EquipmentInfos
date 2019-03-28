#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "xmlutil.h"

#include <QWidget>
#include <QCompleter>
#include "equipmentutil.h"
#include "excelutil.h"

#include "tipsdialog.h"

#include <QDebug>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_pBtn_start_clicked();

    void on_cBox_depart_editTextChanged(const QString &arg1);

private:
    Ui::MainWidget *ui;

    TipsDialog *dialog;

    XmlUtil xmlUtil;

    QString departStr;
    QString classStr;
    QString userStr;
    QStringList departList;

    QList<EquipmentInfo> equipInfos;

    void changedAllUIEnable(bool enabled);
};

#endif // MAINWIDGET_H
