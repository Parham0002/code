#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMainWindow>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    QPushButton button{"Click me"};

    QVBoxLayout VBLayout;

    QStatusBar statusBar;
    QMenuBar menuBar;

    QMenu fileMenu{"File"};
    QAction exitAction{"Exit"};

    QMenu helpMenu{"Help"};
    QAction aboutAction{"About"};

public:
    MainWindow()
    {
        QWidget *centerWidget = new QWidget(this);

        button.setFixedWidth(200);

        VBLayout.setAlignment(Qt::AlignCenter);
        VBLayout.addWidget(&button);

        centerWidget->setLayout(&VBLayout);
        setCentralWidget(centerWidget);

        setWindowTitle("Qt6 MainWindow Example");

        connect(&button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

        connect(&exitAction, &QAction::triggered, this, &MainWindow::close);
        fileMenu.addAction(&exitAction);

        connect(&aboutAction, &QAction::triggered, [this]()
                { QMessageBox::about(this, "About", "Qt6 MainWindow Example"); });
        helpMenu.addAction(&aboutAction);

        menuBar.addMenu(&fileMenu);
        menuBar.addMenu(&helpMenu);
        setMenuBar(&menuBar);

        statusBar.showMessage("Ready");
        setStatusBar(&statusBar);
    }

private:
    void onButtonClicked()
    {
        qDebug() << "Button clicked ...";
    }
};

#endif