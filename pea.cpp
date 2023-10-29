#include "pea.h"
#include "zombie.h"

Pea::Pea(int attack, bool flag)
{
    snow = flag;
    atk = attack;
    speed = 360.0 * 33 / 1000;
}

QRectF Pea::boundingRect() const
{
    return QRectF(-12, -28, 24, 24);
}

void Pea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-12, -28, 24, 24), QPixmap(snow ? ":/images/BasketBallSnow.png" : ":/images/BasketBall .png"));
}

bool Pea::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 15;
}

void Pea::advance(int phase)
{
    if (!phase)
        return;
    update();
    QList<QGraphicsItem *> items = collidingItems();
    if (!items.isEmpty())
    {
        Zombie *zombie = qgraphicsitem_cast<Zombie *>(items[rand() % items.size()]);
        zombie->hp -= atk;

        // 创建一个颜色效果
        QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect;
        QColor hit(255,0,0,100);
        effect->setColor(hit);
        zombie->setGraphicsEffect(effect);

        // 设置一个定时器，在一段时间后停止颜色效果
        QTimer *timer = new QTimer;
        timer->setSingleShot(true);
        timer->setInterval(500); // 500毫秒（0.5秒）后停止效果
        QObject::connect(timer, &QTimer::timeout, [=]() {
            effect->setEnabled(false); // 停止颜色效果
            delete timer; // 删除定时器
        });
        timer->start();

        sound->setAudioOutput(audioOutput);
        sound->setSource(QUrl::fromLocalFile("qrc:/music/splat1.mp3"));
        sound->play();

        if (snow && zombie->speed > 0.55)
            zombie->speed /= 2;
        delete this;
        return;
    }
    setX(x() + speed);
    if (x() > 1069)
        delete this;
}

Pea::~Pea(){
    delete sound;
    delete audioOutput;
}
