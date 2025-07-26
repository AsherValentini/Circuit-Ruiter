#include <iostream>
#include <vector>
#include <queue>
#include <set>

enum class TileType {
    Empty,
    Wire,
    Splitter,
    Blocker,
    Source,
    Target
};

std::ostream& operator<<(std::ostream& os, TileType t) {
    switch (t) {
        case TileType::Empty: return os << ".";
        case TileType::Wire: return os << "-";
        case TileType::Splitter: return os << "*";
        case TileType::Blocker: return os << "#";
        case TileType::Source: return os << "S";
        case TileType::Target: return os << "T";
        default: return os << "?";
    }
}

using Grid = std::vector<std::vector<TileType>>;
using Coord = std::pair<int, int>;

class CircuitRouter {
public:
    CircuitRouter(Grid board)
        : m_board(std::move(board)),
          m_rows(m_board.size()),
          m_cols(m_board[0].size())
    {}

    bool canRouteSignal() {
        Coord source = findTile(TileType::Source);
        if (source.first == -1) return false;

        std::set<Coord> visited;
        return routeFrom(source, visited);
    }

private:
    Grid m_board;
    int m_rows;
    int m_cols;

    // Returns true if signal reaches the Target from 'from' tile
    bool routeFrom(Coord from, std::set<Coord>& visited) {
        // YOU MUST IMPLEMENT THIS
        int r = from.first;
        int c = from.second;

        if(r<0 || r>=m_rows || c<0 || c>=m_cols) {
            return false;
        }

        if(m_board[r][c] == TileType::Target) {
            return true;
        }

        if(m_board[r][c] == TileType::Empty || m_board[r][c] == TileType::Blocker || visited.count({r, c})) {
            return false;
        }

        // make a decision
        visited.insert({r, c});

        // recurse
        bool found = routeFrom({r+1, c}, visited) ||
                     routeFrom({r, c+1}, visited) ||
                     routeFrom({r-1, c}, visited) ||
                     routeFrom({r, c-1}, visited);

        // undo decion
        visited.erase({r, c});

        return found;

    }


    Coord findTile(TileType target) {
        for (int r = 0; r < m_rows; ++r) {
            for (int c = 0; c < m_cols; ++c) {
                if (m_board[r][c] == target) return {r, c};
            }
        }
        return {-1, -1}; // not found
    }

    bool isValid(int r, int c) const {
        return r >= 0 && c >= 0 && r < m_rows && c < m_cols;
    }
};

int main() {
    Grid board = {
        { TileType::Empty,    TileType::Source,   TileType::Wire,     TileType::Target },
        { TileType::Blocker,  TileType::Blocker,  TileType::Wire,     TileType::Empty  },
        { TileType::Empty,    TileType::Splitter, TileType::Wire,     TileType::Empty  },
        { TileType::Empty,    TileType::Wire,     TileType::Blocker,  TileType::Empty  },
    };

    std::cout << "Circuit Board:\n";
    for (const auto& row : board) {
        for (const auto& tile : row)
            std::cout << tile << " ";
        std::cout << "\n";
    }

    CircuitRouter router(board);
    std::cout << "\nCan route signal to target? "
              << std::boolalpha << router.canRouteSignal() << "\n";
}

