#ifndef MAINDLG_H
#define MAINDLG_H

#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedLayout>

#include "boxdlg.h"
#include "griddlg.h"
#include "vboxdlg.h"
#include "hboxdlg.h"

class maindlg : public QDialog
{
    QPushButton prevBtn{"Prev"};
    QPushButton nextBtn{"Next"};
    QPushButton closeBtn{"Close"};

    QVBoxLayout mainLayout;
    QStackedLayout stackLayout;
    QBoxLayout navigationLayout{QBoxLayout::Direction::RightToLeft};

    boxdlg bxdlg;
    griddlg grddlg;
    vboxdlg vbxdlg;
    hboxdlg hbxdlg;

public:
    maindlg()
    {
        stackLayout.addWidget(&bxdlg);
        stackLayout.addWidget(&grddlg);
        stackLayout.addWidget(&vbxdlg);
        stackLayout.addWidget(&hbxdlg);

        navigationLayout.addWidget(&closeBtn);
        navigationLayout.addWidget(&nextBtn);
        navigationLayout.addWidget(&prevBtn);
        navigationLayout.addStretch();

        mainLayout.addLayout(&stackLayout);
        mainLayout.addLayout(&navigationLayout);

        mainLayout.setSizeConstraint(QLayout::SetFixedSize);
        setLayout(&mainLayout);

        setWindowTitle("Stacked Layout");

        connect(&closeBtn, &QPushButton::clicked, this, &maindlg::onAppExit);

        connect(&nextBtn, &QPushButton::clicked, this, &maindlg::onNextPage);

        connect(&prevBtn, &QPushButton::clicked, this, &maindlg::onPrevPage);
    }

private:
    void onAppExit()
    {
        close();
    }

    void onNextPage()
    {
        int index = stackLayout.currentIndex();

        if (index < 3)
        {
            stackLayout.setCurrentIndex(index + 1);
        }
    }

    void onPrevPage()
    {
        int index = stackLayout.currentIndex();

        if (index > 0)
        {
            stackLayout.setCurrentIndex(index - 1);
        }
    }
};

#endif