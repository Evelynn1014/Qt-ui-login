#include "modpassword.h"
#include "ui_modpassword.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QSqlQuery>
#include <iostream>
#include "login.h"

Modpassword::Modpassword(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Modpassword) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("login.db");     //如果本目录下没有该文件,则会在本目录下生成,否则连接该文件
    if (!db.open()) {
    } else {
        QSqlQuery query(db);
    }
    ui->setupUi(this);
}

Modpassword::~Modpassword() {
    delete ui;
}

void Modpassword::on_pushButton_clicked() {
    QString a = ui->lineEdit->text();
    QString p = ui->lineEdit_2->text();
    QString r = ui->lineEdit_3->text();
    QString o = ui->lineEdit_4->text();
    if (p != r) {
        QMessageBox::warning(this, QString(tr("Waring")),
                             QString(tr("两次输入新密码不一致")));
    } else if (o == p) {
        QMessageBox::warning(this, QString(tr("Waring")),
                             QString(tr("新密码不能和旧密码相同")));
    } else {
        QSqlQuery query;//新建查询实例
        if (query.exec("select * from account")) {
            if (a == "" && p == "" && r == "" && o == "") {
                //如果输入为空
                QMessageBox::warning(this, QString(tr("Waring")),
                                     QString(tr("输入不能为空！请重新输入！")));
            } else {
                //输入不为空时
                int nameno = -1;
                while (query.next())//循环进行查找
                {
                    if (a == query.value(0).toString())
                        nameno = query.at();
                }
                if (nameno == -1) {
                    QMessageBox::warning(this, QString(tr("Waring")),
                                         QString(tr("查无此人！")));
                } else if (query.seek(nameno)) {
                    QString spassword = query.value(1).toString();//读出此行存储的密码
                    if (spassword == o) {
                        QString str = QString("update account set password = %1 where name = '%2'").arg(p).arg(a);
                        query.exec(str);
                        QMessageBox::warning(this, QString(tr("")),
                                             QString(tr("修改成功！")));
                        login *l = new login(this);
                        this->close();
                        l->show();
                    } else {//用户名和密码不对应
                        QMessageBox::warning(this, QString(tr("Waring")),
                                             QString(tr("用户名或旧密码错误！请重新输入！")));
                        ui->lineEdit->clear();
                        ui->lineEdit_2->clear();
                    }
                }
            }
        }
    }
}

void Modpassword::on_pushButton_2_clicked() {
    login *l = new login(this);
    this->close();
    l->show();
}

