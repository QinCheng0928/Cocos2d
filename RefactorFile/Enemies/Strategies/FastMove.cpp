#include "FastMove.h"

void FastMove::move(Enemy* enemy, float speed, float dt) {
    // Implement fast movement logic here
    auto parent = dynamic_cast<baseLevel*>(enemy->getParent());
    if (parent) {
        if (fabs(enemy->getPosition().x - nextPosition->getPosition().x) < 10 && fabs(enemy->getPosition().y - nextPosition->getPosition().y) < 10) {
            auto pathIter = parent->path.begin();
            while (*pathIter != nextPosition && pathIter != parent->path.end()) {
                pathIter++;
            }
            if (nextPosition != parent->path.back()) {
                nextPosition = *(pathIter + 1);
            }
        }

        auto length = Vec2(nextPosition->getPosition().x - enemy->getPosition().x, nextPosition->getPosition().y - enemy->getPosition().y).length();
        auto dmove = MoveBy::create(1 / 60.0, Vec2(speed* (nextPosition->getPosition().x - enemy->getPosition().x) / length, speed * (nextPosition->getPosition().y - enemy->getPosition().y) / length));
        enemy->runAction(dmove);
    }
    else {
        CCLog("enemy : move error!");
    }
}
