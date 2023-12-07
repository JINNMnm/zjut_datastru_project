//
// Created by 31320 on 2023/10/1.
//
# include "../h/BitMap.h"
# include "../h/const.h"
# include <iostream>
# include <string>
using namespace std;

BitMap::BitMap(int size) {
    this->size = size;
    this->bitMap = new bool[size];
    for (int i = 0; i < size; i++) {
        this->bitMap[i] = false;
    }
}

BitMap::BitMap(int size, const std::string& bitMapString) {
    // bitMapString is a string of 0 and 1
    // first check the size and the length of the string
    if (size != bitMapString.length()) {
        std::cout << "The size and the length of the permission string are not equal!" << std::endl;
        system("read");
        return;
    }
    this->size = size;
    this->bitMap = new bool[size];
    for(int i = 0;i < size;i++){
        if(bitMapString[i] == '0'){
            this->bitMap[i] = false;
        }else if(bitMapString[i] == '1'){
            this->bitMap[i] = true;
        }else{
            std::cout << "The string is not a bit map string!" << std::endl;
            system("read");
            return;
        }
    }
}

void BitMap::SetBitAt(int position, bool value) {
        if(position >= this->size){
            std::cout << "The position is out of range!" << std::endl;
            exit(1);
        }
        this->bitMap[position] = value;
}

void BitMap::SetBitMap(const std::string &bitMapString) {
    // bitMapString is a string of 0 and 1
    // first check the size and the length of the string
    if (this->size != bitMapString.length()) {
        std::cout << "The size and the length of the string are not equal!" << std::endl;
        system("read");
        return;
    }
    for(int i = 0;i < this->size;i++){
        if(bitMapString[i] == '0'){
            this->bitMap[i] = false;
        }else if(bitMapString[i] == '1'){
            this->bitMap[i] = true;
        }else{
            std::cout << "The string is not a bit map string!" << std::endl;
            system("read");
            return;
        }
    }
}

bool BitMap::GetBitAt(int position) const{
    if(position >= this->size){
        std::cout << "The position is out of range!" << std::endl;
        exit(1);
    }
    return this->bitMap[position];
}

std::ostream &operator<<(std::ostream &os, const BitMap &bitMap) {
    for(int i = 0;i < bitMap.size;i++){
        if(bitMap.bitMap[i]){
            os << "1";
        }else{
            os << "0";
        }
    }
    return os;
}

BitMap::~BitMap() {
    delete[] this->bitMap;
}

BitMap::BitMap(const BitMap &bitMap) {
    this->size = bitMap.size;
    this->bitMap = new bool[this->size];
    for(int i = 0;i < this->size;i++){
        this->bitMap[i] = bitMap.bitMap[i];
    }
}

bool BitMap::IsRoot() const {
    // if all the permission is true, then it is root
    for(int i = 0;i < this->size;i++){
        if(!this->bitMap[i]){
            return false;
        }
    }
    return true;
}

void BitMap::PrintBitMap() const {
    for(int i = 0;i < this->size;i++){
        cout << PERMISSION_STRING[i] << ":";
        if(this->bitMap[i]){
            cout << "是 ";
        }else{
            cout << "否 ";
        }
    }
    cout << endl;
}

bool BitMap::CanInsertOrChange(const BitMap &bitMap) const {
    // if the bitMap is root, then it can insert or change any other bitMap
    if(bitMap.IsRoot()){
        return true;
    }
    // if the bitMap is not root, then it can only insert or change the bitMap which is smaller than it
    for(int i = 0;i < this->size;i++){
        if(bitMap.GetBitAt(i) && !this->bitMap[i]){
            return false;
        }
    }
    return true;
}

bool BitMap::IsEmpty() const {
    if(bitMap == nullptr){
        return true;
    }
    return false;
}

BitMap &BitMap::operator=(const BitMap &bitMap) {
    this->size = bitMap.size;
    this->bitMap = new bool[this->size];
    for(int i = 0;i < this->size;i++){
        this->bitMap[i] = bitMap.bitMap[i];
    }
    return *this;
}
