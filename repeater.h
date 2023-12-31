#ifndef REAPTER_H
#define REAPTER_H

#include "plant.h"
#include "zombie.h"
#include "blastpea.h"

class Cherryshooter : public Plant
{
public:
    Cherryshooter();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
};

#endif // REAPTER_H
