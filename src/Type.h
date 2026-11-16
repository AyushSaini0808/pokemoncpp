// The Type.h files is used for enumerating the "type" of pokemon or move,
// along with a function to return the type as a string
#ifndef POKEMON_TYPE_H
#define POKEMON_TYPE_H
#include <iostream>
enum Type {
    Normal,
    Water,
    Grass,
    Fire,
    Electric,
    Count // not a real type; equals the number of types
};

inline std::string toString(Type type) {
    switch (type) {
        case Type::Normal: return "Normal";
        case Type::Fire: return "Fire";
        case Type::Grass: return "Grass";
        case Type::Water: return "Water";
        case Type::Electric: return "Electric";
        case Type::Count: break;
    }
    // not specifying a default so that if we specify a Type that doesn't exist it will just show unknown
    return "unknown";
}
#endif //POKEMON_TYPE_H
