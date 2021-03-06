#pragma once

#include <vector>
#include <QPainter>

class Coordinate;
class RectCollider;
class ObstacleVelocityUpdateVisitor;

class Entity {
    friend class StageMemento;
    friend class Stage3Tester;
public:
    Entity();
    Entity(Coordinate* position, std::string name);
    virtual ~Entity();

    Coordinate* getPosition();
    void setPosition(Coordinate* position);

    std::string getName() {return name;}
    std::vector<Entity*>& getChildren() { return children; }

    // Override this if your entity has a collider.
    virtual RectCollider* getCollider() { return nullptr; }
    virtual void onCollision(Entity* /*other */) {}

    virtual void update(bool paused, double time_since_last_frame) = 0;
    virtual void render(QPainter &painter) = 0;

    void accept(ObstacleVelocityUpdateVisitor *visitor, double velocity);

    std::vector<Entity *> makeChildrenMemento() { return children; }
    void restoreChildrenState(std::vector<double> childrenMemento);

protected:
    std::vector<Entity*> children;

private:
    Coordinate* position;
    std::string name;
};

