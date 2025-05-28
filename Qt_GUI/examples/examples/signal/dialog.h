#ifndef DIALOG_H
#define DIALOG_H

#include <QDebug>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>

class dialog : public QDialog
{
    QPushButton btn{"Click me"};
    QVBoxLayout layout;

public:
    dialog()
    {
        btn.setFixedWidth(200);

        layout.addWidget(&btn);

        layout.setSizeConstraint(QLayout::SetFixedSize);
        setLayout(&layout);

        setWindowTitle("Signal & Slot");

        connect(&btn, &QPushButton::clicked, this, &dialog::onButtonClicked);
    }

private:
    void onButtonClicked()
    {
        qDebug() << "Button clicked ...";
    }
};

#endif