#ifndef MODPASSWORD_H
#define MODPASSWORD_H

#include <QDialog>

namespace Ui {
    class Modpassword;
}

class Modpassword : public QDialog {
    Q_OBJECT

public:
    explicit Modpassword(QWidget *parent = nullptr);

    ~Modpassword();

private
    slots:

            void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Modpassword *ui;
};

#endif // MODPASSWORD_H
