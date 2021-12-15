#include "login.h"
#include "ui_login.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include "mainwindow.h"
#include <QMessageBox>
#include "modpassword.h"

login::login(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::login) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("login.db");     //如果本目录下没有该文件,则会在本目录下生成,否则连接该文件
    if (!db.open()) {
    } else {
        QSqlQuery query(db);
//        query.exec("CREATE TABLE account("
//                  "name string  ,"
//                  "password string"
//                  " );");

//            query.exec("INSERT INTO account (name, password) "
//                          "VALUES ('admin', '123456')");
    }
//    query.exec("INSERT INTO aaa (name, X,Y,time,message) "
//                  "VALUES ('0西操', 100, 50,100, '一个大操场')");

    ui->setupUi(this);
}

login::~login() {
    delete ui;
}

void login::on_pushButton_clicked() {
    QSqlQuery query;//新建查询实例
    QString a, p;
    a = ui->lineEdit->text();
    p = ui->lineEdit_2->text();
    int ju = 0;
    if (query.exec("select * from account")) {
        if (a == "" && p == "") {
            //如果输入为空
            QMessageBox::warning(this, QString(tr("Waring")),
                                 QString(tr("输入不能为空！请重新输入！")));
        } else {
            //输入不为空时
            while (query.next())//循环进行查找
            {
                if (a == query.value(0).toString()) {
                    ju++;
                } else {
                    qDebug() << "none";
                }
            }
            if (ju != 0) {
                QMessageBox::warning(this, QString(tr("Waring")),
                                     QString(tr("此用户名已存在！")));
                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
            } else {
                QString l = "";
                l.append("INSERT INTO account (name, password) VALUES ('" + a + "'," + p + ")");
                query.exec(l);
                QMessageBox::warning(this, QString(tr("")),
                                     QString(tr("注册成功！")));
                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
            }
        }
    }
}

void login::on_pushButton_2_clicked() {
    QSqlQuery query;//新建查询实例
    QString a, p;
    a = ui->lineEdit->text();
    p = ui->lineEdit_2->text();
    if (query.exec("select * from account")) {
        if (a == "" && p == "") {
            //如果输入为空
            QMessageBox::warning(this, QString(tr("Waring")),
                                 QString(tr("输入不能为空！请重新输入！")));
        } else {
            //输入不为空时
            int nameno = 0;
            while (query.next())//循环进行查找
            {
                if (a == query.value(0).toString()) {
                    nameno = query.at();
                } else {
                    qDebug() << "none";
                }
            }
            if (query.seek(nameno)) {
                QString spassword = query.value(1).toString();//读出此行存储的密码
                if (spassword == p) {
                    QMessageBox::information(NULL, QString(tr(" ")),
                                             QString(tr("登录成功")));
                    //accept();
                    MainWindow *w = new MainWindow(this);
                    this->close();
                    w->show();
                } else {//用户名和密码不对应
                    QMessageBox::warning(this, QString(tr("Waring")),
                                         QString(tr("用户名或密码错误！请重新输入！")));
                    ui->lineEdit->clear();
                    ui->lineEdit_2->clear();
                }
            }
        }
    }
}


void login::on_pushButton_3_clicked() {
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
}


void login::on_pushButton_4_clicked() {
    exit(0);
}


void login::on_pushButton_6_clicked() {
    QMessageBox::warning(this, QString(tr("")),
                         QString(tr("这都要帮助吗？你真笨!")));
}


void login::on_pushButton_5_clicked() {
    Modpassword *m = new Modpassword(this);
    this->close();
    m->show();
}

