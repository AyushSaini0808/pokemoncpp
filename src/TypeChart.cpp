#include "TypeChart.h"
#include <array>

namespace {
    constexpr std::size_t kTypeCount{static_cast<std::size_t>(Type::Count)};
    using Table = std::array<std::array<double, kTypeCount>, kTypeCount>;
    constexpr std::size_t index(Type t) { return static_cast<std::size_t>(t); }

    Table buildTable() {
        Table t{};
        for (auto &row: t) {
            row.fill(1.0f);
        }
        auto set = [&t](Type attacking, Type defending, float multiplier) {
            t[index(attacking)][index(defending)] = multiplier;
        };
        set(Type::Fire, Type::Grass, 2.0f);
        set(Type::Fire, Type::Water, 0.5f);
        set(Type::Fire, Type::Fire, 0.5f);
        set(Type::Fire, Type::Electric, 2.0f);

        set(Type::Water, Type::Grass, 0.5f);
        set(Type::Water, Type::Water, 0.5f);
        set(Type::Water, Type::Fire, 2.0f);
        set(Type::Water, Type::Electric, 0.5f);


        set(Type::Grass, Type::Grass, 0.5f);
        set(Type::Grass, Type::Water, 2.0f);
        set(Type::Grass, Type::Fire, 0.5f);
        set(Type::Grass, Type::Electric, 2.0f);


        set(Type::Electric, Type::Grass, 0.5f);
        set(Type::Electric, Type::Water, 2.0f);
        set(Type::Electric, Type::Fire, 0.5f);
        set(Type::Electric, Type::Electric, 0.5f);

        return t;
    }

    const Table& table() {
        static const Table t = buildTable();
        return t;
    }
}


float effectiveness(Type attacking, Type defending) {
    return table()[index(attacking)][index(defending)];
}
