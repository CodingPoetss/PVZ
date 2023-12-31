#ifndef PLANT_H
#define PLANT_H

#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>

class Plant : public QGraphicsItem
{
public:
    int hp;
    int state;
    bool hasSoundPlayed=false;
    QMediaPlayer* sound = new QMediaPlayer();
    QAudioOutput* audioOutput = new QAudioOutput();
    enum { Type = UserType + 1};
    Plant();
    ~Plant() override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    int type() const override;
    void setMovie(QString path);

protected:
    QMovie *movie;
    int atk;
    int counter;
    int time;
};

#endif // PLANT_H
