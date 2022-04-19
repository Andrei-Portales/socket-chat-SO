#include "./chat_structs.cpp"
#include <list>

std::list<std::string> splitjsons(std::string jsonString)
{
    int left = 0;
    int right = 0;

    std::list<std::string> jsonList;

    std::string temp;


    for (int i = 0; i < jsonString.size(); i++)
    {
        if (jsonString[i] == '{')
        {
            left++;
        }

        if (jsonString[i] == '}')
        {
            right++;
        }

        temp += jsonString[i];

        if (left == right)
        {
            jsonList.push_back(temp);
            temp = "";
        }
    }

    return jsonList;
}