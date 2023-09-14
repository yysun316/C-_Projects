#include "array.h"

DataMap::DataMap():arraySize(0), keys(nullptr), values(nullptr){}

DataMap::~DataMap(){
    clear();
}

void DataMap::insert(const string &key, const string &value){
    if (0 == arraySize)
    {
        arraySize = 1;
        keys = new string[1]{key};
        values = new string[1]{value};
        return;
    }
    string *tempkey = new string[++arraySize];
    string *tempvalue = new string[arraySize];
    for (int i = 0; i < arraySize - 1; ++i){
        tempkey[i] = keys[i];
        tempvalue[i] = values[i];
    }
    tempkey[arraySize - 1] = key;
    tempvalue[arraySize - 1] = value;
    delete[] keys;
    delete[] values;
    keys = tempkey;
    values = tempvalue;
    return;
}
string DataMap::find(const string &key) const {
    for (int i = 0; i < arraySize; ++i)
        if (keys[i] == key)
            return values[i];
    return ""; //not sure is empty string or nullptr ""
}
void DataMap::clear(){
    if (arraySize > 0){
        arraySize = 0;
        delete[] values;
        delete[] keys;
        values = nullptr;
        keys = nullptr;
    }
    return;
}