#include "Damage.h"
// DAMAGE FORMULA :
// Damage = ((((2 × Level / 5) + 2) × Power × Attack / Defense) / 50 + 2) × Modifiers

#include "TypeChart.h"

int calculateDamage(const Pokemon &attacker, const Pokemon &defender, const Move &move, std::mt19937 &rng) {
    if (move.power() == 0)return 0; // for stat moves that dont inflict damage
    const int level = attacker.level();
    const double levelFactor = (2.0 * level / 5.0) + 2.0;
    const double ratio = static_cast<double>(attacker.attack()) / (std::max(1, defender.defence()));

    const double base = (move.power() * ratio * levelFactor) / 50.0 + 2.0;
    double multiplier = effectiveness(attacker.type(), defender.type());
    if (move.type() == attacker.type()) multiplier *= 1.5;

    std::uniform_real_distribution<double> roll(0.85, 1);

    const double damage = base * multiplier * roll(rng);

    return std::max(1, static_cast<int>(damage));
    // an attack always does atleast 1HP worth of damage, provided it isnt a status move, which is already covered in the base condition.
}
