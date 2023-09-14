#include "handler.h"

HandlerModule::~HandlerModule() = default; // clear()

void HandlerModule::print() const
{
    std::cout << "Module name = " << m_name << ", this is a Handler, can handle topic = " << topic << std::endl;
}

void HandlerModule::trainData(const string &question, const string &answer)
{
    data.insert(question, answer);
}
string HandlerModule::answer(const string &question) const
{
    string data = question;
    string datacopy = data;
    if (languageFilter)
    {
        data = languageFilter->translatePreData(question); // translated question
        if (data == "")
            data = datacopy; // if the question doesn't exists in the preData, restore the question.
    }
    datacopy = data;
    if (toneFilter)
    {
        data = toneFilter->translatePreData(data);
        if (data == "")
            data = datacopy;
    }
    // std::cout << "data: " << data << endl;
    string ans = inneranswer(data);
    // std::cout << "ans: " << ans << endl;
    string anscopy = ans;
    if (ans == "")
        return "Sorry, I don't know";
    if (toneFilter)
    {
        ans = toneFilter->translatePostData(ans);
        if (ans == "")
            ans = anscopy;
    }
    anscopy = ans;
    if (languageFilter)
    {
        ans = languageFilter->translatePostData(ans);
        if (ans == "")
            ans = anscopy;
    }
    return ans;
}

string HandlerModule::inneranswer(const string &question) const
{
    if (data.size())
        return data.find(question);
    return "";
}

// handlermap
HandlerMap::HandlerMap() : arraySize(0), names(nullptr), handlerModules(nullptr) {}
HandlerMap::~HandlerMap()
{
    clear();
}

void HandlerMap::insert(string key, HandlerModule *value)
{ // key is the topic
    if (arraySize == 0)
    {
        handlerModules = new HandlerModule *[++arraySize]
        { value };
        names = new string[arraySize]{key};
        return;
    }
    HandlerModule **temph = new HandlerModule *[++arraySize];
    string *tempn = new string[arraySize];
    for (int i = 0; i < arraySize - 1; ++i)
    {
        temph[i] = handlerModules[i];
        tempn[i] = names[i];
    }
    temph[arraySize - 1] = value;
    tempn[arraySize - 1] = key;
    delete[] handlerModules;
    delete[] names;
    handlerModules = temph;
    names = tempn;
}
HandlerModule *HandlerMap::find(const string &key) const // key is topic
{
    for (int i = 0; i < arraySize; ++i)
        if (key == handlerModules[i]->getTopic())
            return handlerModules[i];
    return nullptr;
}
string HandlerMap::getNames(int index) const
{
    if (index <= arraySize - 1 && index >= 0)
        return names[index];
    return nullptr; // additional remarks
}
void HandlerMap::clear()
{
    if (arraySize != 0)
    {
        delete[] names;
        names = nullptr;
        delete[] handlerModules;
        handlerModules = nullptr;
        arraySize = 0;
    }
    return;
}