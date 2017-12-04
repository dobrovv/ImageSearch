#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QGridLayout>

class ImageView : public QWidget
{
    Q_OBJECT
    QLabel * lblImg;
    QLabel * lblDesc;

public:
    explicit ImageView(QImage image = QImage(), QString desc = "", bool descInLine = false, QWidget *parent = nullptr);

    void setImage(QImage image, QString desc = "");
};


class ImageGridView : public QWidget
{
    Q_OBJECT
    QGridLayout * grid;
    int imgCount;

public:
    explicit ImageGridView(QWidget *parent = nullptr);

    void addImage(QImage image, QString desc = "");
    void clearImages();
};


class ImageScrollView : public QScrollArea
{
    Q_OBJECT
    ImageGridView * grid;

public:
    explicit ImageScrollView(QWidget *parent = nullptr);

    void addImage(QImage image, QString desc = "");
    void clearImages();
};

#endif // IMAGEVIEW_H
