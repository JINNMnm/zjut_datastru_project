//
// Created by 31320 on 2023/10/1.
//

#ifndef CODE_BITMAP_H
#define CODE_BITMAP_H
#include <string>


class BitMap {
public:
    // constructor
    BitMap(int size);
    BitMap(int size, const std::string& bitMapString);
    BitMap(const BitMap& bitMap);

    // setBit at position
    void SetBitAt(int position, bool value);
    void SetBitMap(const std::string& bitMapString);
    // getBit at position
    bool GetBitAt(int position) const;
    // overload operator <<
    friend std::ostream& operator<<(std::ostream& os, const BitMap& bitMap);
    void PrintBitMap() const;

    // check if this bitMap can Insert or change Another bitMap
    bool CanInsertOrChange(const BitMap& bitMap) const;

    // is root?
    bool IsRoot() const;

    // isEmpty?
    bool IsEmpty() const;

    // overload operator =
    BitMap& operator=(const BitMap& bitMap);

    // destructor
    ~BitMap();
private:
    int size;
    bool* bitMap;
};

#endif //CODE_BITMAP_H
