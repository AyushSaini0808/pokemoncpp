#include "TypeChart.h"
#include <array>

namespace {
    constexpr std::size_t kTypeCount{static_cast<std::size_t>(Type::Count)};
    using Table = std::array<std::array<double, kTypeCount>, kTypeCount>;
    constexpr std::size_t index(Type t) { return static_cast<std::size_t>(t); }

    Table buildTable() {
        Table t{};
        // Initialising the table with 1.0 multipliers
        for (auto &row: t) {
            row.fill(1.0f);
        }
        // Lambda function that takes attacker and defender types, along with the multiplier associated for that combination
        auto set = [&t](Type attacking, Type defending, float multiplier) {
            t[index(attacking)][index(defending)] = multiplier;
        };
        set(Type::Fire, Type::Grass, 2.0f);
        set(Type::Fire, Type::Water, 0.5f);
        set(Type::Fire, Type::Fire, 0.5f);

        set(Type::Water, Type::Grass, 0.5f);
        set(Type::Water, Type::Water, 0.5f);
        set(Type::Water, Type::Fire, 2.0f);

        set(Type::Grass, Type::Grass, 0.5f);
        set(Type::Grass, Type::Water, 2.0f);
        set(Type::Grass, Type::Fire, 0.5f);


        set(Type::Electric, Type::Grass, 0.5f);
        set(Type::Electric, Type::Water, 2.0f);
        set(Type::Electric, Type::Electric, 0.5f);

        return t;
    }

    const Table& table() {
        static const Table t = buildTable(); // Table would be created once at the start
        return t;
    }
}


float effectiveness(Type attacking, Type defending) {
    return table()[index(attacking)][index(defending)];
}
