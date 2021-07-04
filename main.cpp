#include <LibLoader/LibLoader.hpp>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    // You don't need to specify an extension like ".dll" nor you need to specify a prefix like "lib"
    auto Handle = LibLoader::LoadLibrary("./test");

    cout << Handle->Name() << endl;
    cout << Handle->FullPath() << endl;

    auto TestAdd = Handle->LoadFunction<int, int, int>("TestAdd");
    auto PrintInt = Handle->LoadFunction<void, int>("PrintInt");
    auto PrinHello = Handle->LoadFunction<void>("PrinHello");
    auto GetNumber = Handle->LoadFunction<int>("GetNumber");

    cout << TestAdd(5, 6) << endl;
    PrintInt(5);
    PrinHello();
    cout << GetNumber() << endl;

    return 0;
}
