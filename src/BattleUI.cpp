#include "BattleUI.h"

namespace {
    std::vector<std::size_t> usableMoves(const Pokemon& p) {
        std::vector<std::size_t> result;
        for (std::size_t i=0;i<p.moveCount();i++) {
            if (p.move(i).hasPP()) result.push_back(i);
        }
        return result;
    }

    std::optional<int> parseInt(const std::string& text) {
        try {
            std::size_t used=0;
            int value=std::stoi(text,&used);
            if (used!=text.size())return std::nullopt;
            return value;
        }catch ( const std::exception&) {
            return std::nullopt;
        }
    }

    void printStatus(const Pokemon& player, const Pokemon& enemy){
        std::cout<<enemy.name()<<" HP: "<<enemy.currentHP()<<"/ "<<enemy.maxHP()<<'\n';
        std::cout<<player.name()<<" HP: "<<player.currentHP()<<"/ "<<player.maxHP()<<'\n';

    }
}


std::optional<std::size_t> promptPlayerMove(const Pokemon& player, const Pokemon& enemy) {
    printStatus(player,enemy);

    if (usableMoves(player).empty()) {
        std::cout<<player.name()<<" has no moves left!\n";
        return std::size_t{0};
    }

    while (true) {
        std::cout<<"Choose a move: \n";
        for (std::size_t i =0;i<player.moveCount();i++) {
            const Move& move = player.move(i);
            std::cout<<" "<<i+1<<". "<<move.name()
            <<" ("<< toString(move.type()) << ", pow " << move.power()
                      << ", PP " << move.currentPP() << "/" << move.maxPP() << ")"
                      << (move.hasPP() ? "" : "  [no PP]") << '\n';
        }
        std::cout<<"> ";

        std::string line;
        if (!std::getline(std::cin,line)) return std::nullopt;

        auto choice=parseInt(line);
        if (!choice|| *choice<1 || *choice>static_cast<int>(player.moveCount())) {
            std::cout<<"Please enter a number form 1 to "<<player.moveCount()<<"\n";
            continue;
        }

        auto index = static_cast<std::size_t>(*choice -1);
        if (!player.move(index).hasPP()) {
            std::cout<<"No PP left for that move, pick another.\n";
            continue;
        }

        return index;
    }
}

std::size_t chooseEnemyMove(const Pokemon &enemy, std::mt19937& rng) {
    std::vector<std::size_t> usable= usableMoves(enemy);
    if (usable.empty()) return 0;

    std::uniform_int_distribution<std::size_t>pick(0,usable.size()-1);
    return usable[pick(rng)];
}
