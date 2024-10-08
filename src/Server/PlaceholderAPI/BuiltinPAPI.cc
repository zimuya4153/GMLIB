#include "Global.h"
#include "Server/PlaceholderAPI/Helper.h"
#include <GMLIB/GMLIB.h>
#include <GMLIB/Server/LevelAPI.h>
#include <GMLIB/Server/PlaceholderAPI.h>
#include <GMLIB/Server/PlayerAPI.h>
#include <mc/server/common/PropertiesSettings.h>
#include <mc/world/attribute/Attribute.h>
#include <mc/world/attribute/AttributeInstance.h>
#include <mc/world/level/LayeredAbilities.h>

namespace GMLIB {

using namespace Server;

std::time_t startTime = 0;

std::string double2String(double num, int fixnum) {
    std::stringstream sn;
    sn << std::setiosflags(std::ios::fixed) << std::setprecision(fixnum) << num;
    return sn.str();
}

void regPlayerPAPI() {

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_realname",
        [](Player* sp) { return sp->getRealName(); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_name",
        [](Player* sp) { return sp->getName(); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_uuid",
        [](Player* sp) { return sp->getUuid().asString(); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_ping",
        [](Player* sp) {
            auto pl = (GMLIB_Player*)sp;
            return S(pl->getAvgPing());
        },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_health",
        [](Player* sp) { return S(sp->getHealth()); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_max_health",
        [](Player* sp) { return S(sp->getMaxHealth()); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_gamemode",
        [](Player* sp) {
            auto type = magic_enum::enum_name(sp->getPlayerGameType());
            return std::string(type);
        },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_x",
        [](Player* sp) { return S(sp->getPosition().x); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_y",
        [](Player* sp) { return S(sp->getPosition().y); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_z",
        [](Player* sp) { return S(sp->getPosition().z); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_pos",
        [](Player* sp) { return sp->getPosition().toString(); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_dimid",
        [](Player* sp) { return S(sp->getDimensionId()); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_direction",
        [](Player* sp) { return S(sp->getDirection()); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_exp_to_next",
        [](Player* sp) { return S(sp->getXpNeededForNextLevel()); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_exp_level",
        [](Player* sp) { return S(sp->getPlayerLevel()); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_speed",
        [](Player* sp) { return S(sp->getSpeed()); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_flying",
        [](Player* sp) {
            auto abi = sp->getAbilities();
            return S(abi.getBool(AbilitiesIndex::Flying));
        },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_can_fly",
        [](Player* sp) { return S(sp->canFly()); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_displayname",
        [](Player* sp) { return sp->getNameTag(); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_is_op",
        [](Player* sp) { return S(sp->isOperator()); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_item_in_hand",
        [](Player* sp) {
            auto item = sp->getCarriedItem();
            return item.getName();
        },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_ip",
        [](Player* sp) { return sp->getIPAndPort(); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_device",
        [](Player* sp) {
            auto device = magic_enum::enum_name(sp->getPlatform());
            return std::string(device);
        },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_language",
        [](Player* sp) {
            auto pl = (GMLIB_Player*)sp;
            return std::string(pl->getLanguageCode());
        },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_xuid",
        [](Player* sp) { return sp->getXuid(); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_bed_x",
        [](Player* sp) {
            if (sp->hasRespawnPosition()) {
                return S(sp->getSpawnPosition().x);
            }
            return std::string();
        },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_bed_y",
        [](Player* sp) {
            if (sp->hasRespawnPosition()) {
                return S(sp->getSpawnPosition().y);
            }
            return std::string();
        },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_bed_z",
        [](Player* sp) {
            if (sp->hasRespawnPosition()) {
                return S(sp->getSpawnPosition().z);
            }
            return std::string();
        },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_bed_pos",
        [](Player* sp) {
            if (sp->hasRespawnPosition()) {
                return sp->getSpawnPosition().toString();
            }
            return std::string();
        },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_hunger",
        [](Player* sp) { return S((int)sp->getAttribute(Player::HUNGER).getCurrentValue()); },
        "GMLIB"
    );

    PlaceholderAPI::registerPlayerPlaceholder(
        "player_max_hunger",
        [](Player* sp) { return S((int)sp->getAttribute(Player::HUNGER).getMaxValue()); },
        "GMLIB"
    );

    GMLIB::Server::PlaceholderAPI::registerPlayerPlaceholder(
        "player_score_<objective>",
        [](Player* sp, std::unordered_map<std::string, std::string> map) {
            auto pl = (GMLIB_Player*)sp;
            if (map.contains("<objective>")) {
                auto score = pl->getScore(map["<objective>"]);
                if (score) {
                    return std::to_string(score.value());
                }
            }
            return std::string();
        },
        "GMLIB"
    );
}

void regServerPAPI() {
    PlaceholderAPI::registerServerPlaceholder(
        "server_time_<format>_s",
        [](std::unordered_map<std::string, std::string> map) {
            if (map.contains("<format>")) {
                if ("<format>" != map["<format>"]) return Helper::getTime(map["<format>"]);
            }

            return Helper::getTime("H:M:S");
        },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_time_<format>",
        [](std::unordered_map<std::string, std::string> map) {
            if (map.contains("<format>")) {
                if ("<format>" != map["<format>"]) return Helper::getTime(map["<format>"]);
            }
            return Helper::getTime("H:M:S");
        },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_online",
        []() { return S(ll::service::getLevel()->getActivePlayerCount()); },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_max_players",
        []() { return S(GMLIB_Level::getInstance()->getMaxPlayerCount()); },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_version",
        []() { return GMLIB::Version::getGameVersionString(); },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_protocol_version",
        []() { return S(GMLIB::Version::getProtocolVersion()); },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_total_entities",
        []() { return S(ll::service::getLevel()->getRuntimeActorList().size()); },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_world_name",
        []() { return ll::service::getLevel()->getLevelData().getLevelName(); },
        "GMLIB"
    );
    PlaceholderAPI::registerServerPlaceholder(
        "server_difficulty",
        []() {
            auto res = magic_enum::enum_name(ll::service::getPropertiesSettings()->getDifficulty());
            return std::string(res);
        },
        "GMLIB"
    );
    PlaceholderAPI::registerServerPlaceholder(
        "server_on_allowlist",
        []() { return S(ll::service::getPropertiesSettings()->useAllowList()); },
        "GMLIB"
    );
    PlaceholderAPI::registerServerPlaceholder(
        "server_port",
        []() { return S(ll::service::getPropertiesSettings()->getServerPort()); },
        "GMLIB"
    );
    PlaceholderAPI::registerServerPlaceholder(
        "server_port_v6",
        []() { return S(ll::service::getPropertiesSettings()->getServerPortv6()); },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_uptime",
        []() { return S(std::time(0) - startTime); },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_start_time_<format>_s",
        [](std::unordered_map<std::string, std::string> map) {
            if (map.contains("<format>")) {
                if ("<format>" != map["<format>"]) {
                    return Helper::getTime(map["<format>"], startTime);
                }
            }
            return Helper::getTime("H:M:S", startTime);
        },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_start_time_<format>",
        [](std::unordered_map<std::string, std::string> map) {
            if (map.contains("<format>")) {
                if ("<format>" != map["<format>"]) {
                    return Helper::getTime(map["<format>"], startTime);
                }
            }
            return Helper::getTime("H:M:S", startTime);
        },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_name",
        []() { return ll::service::getPropertiesSettings()->getMotd(); },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_has_whitelist",
        []() { return S(ll::service::getPropertiesSettings()->useAllowList()); },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_ram_bds_used",
        []() {
            auto ram = Helper::getRam();
            return ram["bdsused"];
        },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_ram_free",
        []() {
            auto ram = Helper::getRam();
            return ram["canuse"];
        },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_ram_used",
        []() {
            auto ram = Helper::getRam();
            return ram["used"];
        },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_ram_max",
        []() {
            auto ram = Helper::getRam();
            return ram["all"];
        },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_tps",
        []() {
            if (auto level = GMLIB_Level::getInstance()) {
                return S(level->getServerCurrentTps());
            }
            return S(0.0f);
        },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_tps_fix_<fixed>",
        [](std::unordered_map<std::string, std::string> map) {
            if (map.contains("<fixed>")) {
                try {
                    auto num = std::stoi(map["<fixed>"]);
                    if (auto level = GMLIB_Level::getInstance()) {
                        return double2String(level->getServerCurrentTps(), num);
                    }
                    return std::string();
                } catch (...) {}
            }
            return std::string("%server_tps_fix_<fixed>%");
        },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_tps_colored_<fixed>",
        [](std::unordered_map<std::string, std::string> map) {
            if (map.contains("<fixed>")) {
                try {
                    auto num = std::stoi(map["<fixed>"]);
                    if (auto level = GMLIB_Level::getInstance()) {
                        auto tps    = level->getServerCurrentTps();
                        auto result = double2String(tps, num);
                        if (tps >= 20) return "§a" + result;
                        else if (tps > 15) return "§6" + result;
                        else return "§c" + result;
                    }
                    return std::string();
                } catch (...) {}
            }
            return std::string("%server_mspt_colored_<fixed>%");
        },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_mspt",
        []() {
            if (auto level = GMLIB_Level::getInstance()) {
                return S(level->getServerMspt());
            }
            return S(0.0f);
        },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_mspt_fix_<fixed>",
        [](std::unordered_map<std::string, std::string> map) {
            if (map.contains("<fixed>")) {
                try {
                    auto num = std::stoi(map["<fixed>"]);
                    if (auto level = GMLIB_Level::getInstance()) {
                        return double2String(level->getServerMspt(), num);
                    }
                    return double2String(0.0f, num);
                } catch (...) {}
            }
            return std::string("%server_mspt_fix_<fixed>%");
        },
        "GMLIB"
    );

    PlaceholderAPI::registerServerPlaceholder(
        "server_mspt_colored_<fixed>",
        [](std::unordered_map<std::string, std::string> map) {
            if (map.contains("<fixed>")) {
                try {
                    auto num = std::stoi(map["<fixed>"]);
                    if (auto level = GMLIB_Level::getInstance()) {
                        auto mspt   = level->getServerMspt();
                        auto result = double2String(mspt, num);
                        if (mspt < 50) return "§a" + result;
                        else if (mspt < 100) return "§6" + result;
                        else return "§c" + result;
                    }
                    return std::string();
                } catch (...) {}
            }
            return std::string("%server_mspt_colored_<fixed>%");
        },
        "GMLIB"
    );
}

} // namespace GMLIB
