#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ImageDB.h"
#include "GUI/ImageView.h"

#include <QWidget>
#include <QPushButton>
#include <QSpinBox>

class MainWindow : public QWidget
{
    Q_OBJECT

    ImageDB * db;
    QImage queryImg;

    ImageView * imageView;
    ImageScrollView * resultView;

    QLabel * lblImageFilePath;

    QPushButton * btnOpenImage;
    QPushButton * btnQueryDB;
    QSpinBox    * spbTolerance;

public:
    explicit MainWindow(ImageDB *db, QWidget *parent = nullptr);

public slots:
    void btnOpenImageClicked();
    void btnQueryDBClicked();

};

#endif // MAINWINDOW_H
