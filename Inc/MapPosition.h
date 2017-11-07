#ifndef MAPPOSITION_H_
#define MAPPOSITION_H_

#include <utility>
#include "Variable.h"

namespace Maze {
    using MapPosition = std::pair<char, char>;
    static constexpr auto mapPos =
        std::make_pair<MapPosition::first_type, MapPosition::second_type>;
    namespace Position {
        // Get Positons
        static constexpr MapPosition GetLeft(const MapPosition& pos) {
            return mapPos((char)pos.first - 1, (char)pos.second);
        }
        static constexpr MapPosition GetRight(const MapPosition& pos) {
            return mapPos((char)pos.first + 1, (char)pos.second);
        }
        static constexpr MapPosition GetFront(const MapPosition& pos) {
            return mapPos((char)pos.first, (char)pos.second + 1);
        }
        static constexpr MapPosition GetBack(const MapPosition& pos) {
            return mapPos((char)pos.first, (char)pos.second - 1);
        }
        // Is
        static constexpr bool IsLeftEnd(const MapPosition& pos) { return pos.first == 0; }
        static constexpr bool IsRightEnd(const MapPosition& pos) {
            return pos.first == mazeSize - 1;
        }
        static constexpr bool IsTop(const MapPosition& pos) { return pos.second == mazeSize - 1; }
        static constexpr bool IsBottom(const MapPosition& pos) { return pos.second == 0; }
    }
}

#endif