#include <iostream>
#include <string>
#include "legoGPT.h"
#include "module.h"
#include "filter.h"
#include "handler.h"

using namespace std;

void LegoGPT::printHandlers() const
{
    int size = this->handlerMap.size();
    cout << "There is(are) " << size << " handler(s) in the LegoGPT" << endl;
    cout << "They are: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << this->handlerMap.getNames(i) << endl; //refer to the topic of the handler
    }

    return;
}

void LegoGPT::printFilters() const
{
    int size = this->filterArray.size();
    cout << "There is(are) " << size << " filter(s) in the LegoGPT" << endl;
    for (int i = 0; i < size; i++)
    {
        this->filterArray.get(i)->print();
    }
    return;
}

void LegoGPT::printTopics() const
{
    int size = this->topics.size();
    cout << "There is(are) " << size << " topic(s) in the LegoGPT" << endl;
    cout << "They are: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << this->topics.get(i) << endl;
    }
    cout << endl;
    return;
}

void LegoGPT::printLanguages() const
{
    int size = this->languages.size();
    cout << "There is(are) " << size << " additional language(s) in the LegoGPT" << endl;
    cout << "They are: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << this->languages.get(i) << endl;
    }
    cout << endl;
    return;
}

void LegoGPT::chat(string topic, string question) const
{
    if (nullptr == this->handlerMap.find(topic))
    {
        cout << "Sorry, topic not supported. Please look for supported topic." << endl;
        return;
    }
    cout << this->handlerMap.find(topic)->answer(question) << endl;
    return;
}

void LegoGPT::LoadHandlerModule(HandlerModule &input){
    handlerMap.insert(input.getTopic(), &input); // key is the topic.
    topics.insert(input.getTopic());
}

void LegoGPT::LoadFilterModule(FilterModule &input){
    filterArray.insert(&input);
    if (input.getType() == language)
        languages.insert(input.getName());
}

LegoGPT::~LegoGPT() = default;

void LegoGPT::clear(){}