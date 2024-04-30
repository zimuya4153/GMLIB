#include "Global.h"
#include <GMLIB/Server/ActorAPI.h>
#include <GMLIB/Server/LevelAPI.h>
#include <GMLIB/Server/SpawnerAPI.h>
#include <mc/server/commands/CommandUtils.h>
#include <mc/world/actor/ActorDefinitionIdentifier.h>

GMLIB_Actor*
GMLIB_Spawner::spawnEntity(Vec3 const& pos, DimensionType dimId, std::string const& id, GMLIB_Actor* owner) {
    auto name = id;
    try {
        ll::utils::string_utils::replaceAll(name, "minecraft:", "");
        ActorDefinitionIdentifier identifier(name);

        auto bs     = GMLIB_Level::getInstance()->getBlockSource(dimId);
        auto result = (GMLIB_Actor*)ll::service::getLevel()
                          ->getSpawner()
                          .spawnProjectile(*bs, identifier, owner, pos, Vec3::ZERO);
        return result;
    } catch (...) {
        return nullptr;
    }
}

Mob* GMLIB_Spawner::spawnMob(
    Vec3 const&        pos,
    DimensionType      dimId,
    std::string const& id,
    GMLIB_Actor*       owner,
    bool               naturalSpawn,
    bool               surface,
    bool               fromSpawner
) {
    auto name = id;
    try {
        ll::utils::string_utils::replaceAll(name, "minecraft:", "");
        ActorDefinitionIdentifier identifier(name);
        auto                      bs = GMLIB_Level::getInstance()->getBlockSource(dimId);

        Mob* mob = ll::service::getLevel()
                       ->getSpawner()
                       .spawnMob(*bs, identifier, owner, pos, naturalSpawn, surface, fromSpawner);
        return mob;
    } catch (...) {
        return nullptr;
    }
}

ItemActor* GMLIB_Spawner::spawnItem(Vec3 const& pos, DimensionType dimId, ItemStack& item, GMLIB_Actor* owner) {
    try {
        auto       bs        = GMLIB_Level::getInstance()->getBlockSource(dimId);
        ItemActor* itemActor = ll::service::getLevel()->getSpawner().spawnItem(*bs, item, owner, pos, 0);
        return itemActor;
    } catch (...) {
        return nullptr;
    }
}

ItemActor*
GMLIB_Spawner::spawnItem(Vec3 const& pos, int dimid, std::string const& name, int count, int aux, GMLIB_Actor* owner) {
    try {
        auto       bs        = GMLIB_Level::getInstance()->getBlockSource(dimid);
        auto       item      = ItemStack{name, count, aux};
        ItemActor* itemActor = ll::service::getLevel()->getSpawner().spawnItem(*bs, item, owner, pos, 0);
        return itemActor;
    } catch (...) {
        return nullptr;
    }
}

GMLIB_Actor* GMLIB_Spawner::spawnProjectile(GMLIB_Actor* owner, std::string const& name, float speed, float offset) {
    if (owner) {
        auto proj = spawnEntity(owner->getPosition(), owner->getDimensionId(), name, owner);
        if (proj) {
            owner->setProjectile(proj, speed, offset);
            return proj;
        }
    }
    return nullptr;
}

GMLIB_Actor* GMLIB_Spawner::summonEntity(Vec3 const& pos, int dimId, std::string const& name, GMLIB_Actor* summoner) {
    ll::utils::string_utils::replaceAll(name, "minecraft:", "");
    auto identifider = ActorDefinitionIdentifier(name);
    auto uniqueId    = ActorUniqueID(GMLIB_Actor::getNextActorUniqueID());
    return (GMLIB_Actor*)CommandUtils::spawnEntityAt(
        *GMLIB_Level::getInstance()->getBlockSource(dimId),
        pos,
        identifider,
        uniqueId,
        summoner
    );
}