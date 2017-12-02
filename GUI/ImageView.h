#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>
#include <QLabel>

class ImageView : public QWidget
{
    Q_OBJECT
    QLabel * lblImg;
    QLabel * lblDesc;

public:
    explicit ImageView(QImage image, QString desc, QWidget *parent = nullptr);

    void setImage(QImage image, QString desc = "");

signals:

public slots:

};

class ImageGridView : public QScrolArea
{
    Q_OBJECT
    QLabel * lblImg;
    QLabel * lblDesc;

public:
    explicit ImageView(QImage image, QString desc, QWidget *parent = nullptr);

    void setImage(QImage image, QString desc = "");

signals:

public slots:

};

#endif // IMAGEVIEW_H
