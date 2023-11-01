#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QPainter>
#include <QMovie>

class Zombie : public QGraphicsItem
{
public:
    int hp;
    int atk;
    // state{Eating: 0, Walking: 1, Dead: 2, Freezed: 3}
    int state;
    qreal speed;
    enum { Type = UserType + 2};
    QMediaPlayer* sound = new QMediaPlayer();
    QAudioOutput* audioOutput = new QAudioOutput();
    Zombie();
    ~Zombie() override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    int type() const override;
    void setMovie(QString path);
    void setHead(QString path);
protected:
    QMovie *movie;
    QMovie *head;
};

#endif // ZOOMBIE_H
