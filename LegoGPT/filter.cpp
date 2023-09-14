#include "filter.h"

void FilterModule::print() const{
    std::cout << "Module name = " << m_name << ", this is a filter, filter type = " << getFilterType(type) << std::endl;
}

void FilterModule::trainPreData(const string &source, const string &target){
    preData.insert(source, target);
}
void FilterModule::trainPostData(const string &source, const string &target){
    postData.insert(source, target);
}
string FilterModule::translatePreData(string question) const{
    return preData.find(question);
}
string FilterModule::translatePostData(string question) const{
    return postData.find(question);
}



// filterarray
void FilterArray::insert(FilterModule *input){
    if (arraySize == 0){
        array = new FilterModule*[++arraySize]{input};
        return;
    }
    FilterModule **tempa = new FilterModule *[++arraySize];
    for (int i = 0; i < arraySize - 1; ++i){
        tempa[i] = array[i];
    }
    tempa[arraySize - 1] = input;
    delete[] array;
    array = tempa;
}
FilterModule* FilterArray::get(int index) const{
    if (index < arraySize && index >= 0)
        return array[index];
    return nullptr;
}
//:)