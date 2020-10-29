/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = CollisionSystem
 *
 * File creation = 11/06/2020
 * Last modification = 11/06/2020
 */

#include "Engine/CollisionSystem.hpp"

indie::engine::CollisionSystem::CollisionSystem()
{
    _isEmpty = true;
    _metaTriangle = nullptr;
}

indie::engine::CollisionSystem::CollisionSystem(
    std::list<indie::object3D::StaticObject> &walls,
    indie::object3D::Player &player,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager)
{
    CollisionSystem::create(walls, player, sceneManager);
    _isEmpty = false;
}

void indie::engine::CollisionSystem::create(std::list<indie::object3D::StaticObject> &walls,
    indie::object3D::Player &player,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager)
{
    _metaTriangle = sceneManager->createMetaTriangleSelector();
    for (auto &wall : walls) {
        const irr::core::aabbox3d<irr::f32>& box = wall.getScene()->getBoundingBox();
        irr::core::vector3df radius = box.MaxEdge - box.getCenter();
        wall.setSelector(sceneManager->createOctreeTriangleSelector(wall.getMesh(), wall.getScene(), 128));
        _metaTriangle->addTriangleSelector(wall.getSelector());
        wall.setAnimator(sceneManager->createCollisionResponseAnimator(wall.getSelector(), player.getScene(), {radius.X, radius.Y, radius.Z}, {0, 0, 0}, {0, 0, 0}, 0));
        player.addAnimator(wall.getAnimator());
    }
    _isEmpty = false;
}

void indie::engine::CollisionSystem::drop(indie::object3D::Player &player)
{
    if (_metaTriangle)
        _metaTriangle->removeAllTriangleSelectors();
    player.getScene()->removeAnimators();
    _isEmpty = true;
}

void indie::engine::CollisionSystem::createBorder(std::list<indie::object3D::StaticObject> &walls,
    indie::object3D::Player &player,
    const std::shared_ptr<irr::scene::ISceneManager> &sceneManager)
{
    _metaTriangle = sceneManager->createMetaTriangleSelector();
    for (auto &wall : walls) {
        if (wall.getPosition().X == 0 || wall.getPosition().Z == 0 || wall.getPosition().X == 14 || wall.getPosition().Z == -14) {
            const irr::core::aabbox3d<irr::f32> &box = wall.getScene()->getBoundingBox();
            irr::core::vector3df radius = box.MaxEdge - box.getCenter();
            wall.setSelector(
                sceneManager->createOctreeTriangleSelector(wall.getMesh(),
                                                           wall.getScene(),
                                                           128));
            _metaTriangle->addTriangleSelector(wall.getSelector());
            wall.setAnimator(sceneManager->createCollisionResponseAnimator(
                wall.getSelector(), player.getScene(),
                {radius.X, radius.Y, radius.Z}, {0, 0, 0}, {0, 0, 0}, 0));
            player.addAnimator(wall.getAnimator());
        }
    }
    _isEmpty = false;
}