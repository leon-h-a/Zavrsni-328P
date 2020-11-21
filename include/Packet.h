#ifndef ZAVRSNI_328P_PACKET_H
#define ZAVRSNI_328P_PACKET_H

#include <map>
using namespace std;

class DataBlock{
public:
    explicit DataBlock(char* rawString);
    map<int, int> mah_st;
};

DataBlock::DataBlock(char* rawString){
    DataBlock::mah_st.in
}

#endif //ZAVRSNI_328P_PACKET_H
