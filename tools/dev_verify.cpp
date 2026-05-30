// Dev-environment smoke test: exercises CatchFish save-data encoding (GMAccessData).
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

#include "DataBase64Himi.h"

int main() {
    const char* payload = "CatchFish|score=1200|coins=50|checkpoint=3";
    const unsigned int len = static_cast<unsigned int>(strlen(payload));

    const std::string encoded = himiSaveData(
        reinterpret_cast<const unsigned char*>(payload), len);
    const std::string decoded = himiParseData(encoded);

    if (decoded != payload) {
        std::cerr << "round-trip failed\n  in:  " << payload << "\n  out: " << decoded
                  << "\n";
        return 1;
    }

    std::cout << "CatchFish dev verify OK\n";
    std::cout << "  payload: " << payload << "\n";
    std::cout << "  encoded: " << encoded << "\n";
    return 0;
}
