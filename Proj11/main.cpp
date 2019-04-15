#include <iostream>
using std::cout; using std::endl; using std::boolalpha;

#include <algorithm>
using std::copy;

#include <iterator>
using std::ostream_iterator;

#include <string>
using std::string;

#include "class.h"

int main() {
    cout << boolalpha;
    Element<string, string> element1;
    element1.key_ = "abc";
    element1.values_[0] = "a";
    element1.values_[1] = "b";
    element1.values_[2] = "c";
    element1.count_ = 3;
    cout << element1 << endl;
    Element<string, string> element2("abc", {"a", "b", "c"});
    cout << (element1 == element2) << endl;
    MVM<string, string> mvm{{"abc", {"a", "b", "c"}}, {"xyz", {"x", "y", "z"}}};
    cout << "MVM" << mvm << endl;
    
    auto result = mvm.find_key("abc");
    cout << result.second->key_ << endl;
    MVM<string, string> result_key = mvm.find_value("a");
    cout << "KEY: " << result_key << endl;
    cout << mvm.size() << endl;
    cout << mvm.add("qrs", "q") << endl;
    cout << mvm.add("bcd", "a") << endl;
    cout << mvm.add("qrs", "a") << endl;
    cout << mvm << endl;
    result_key = mvm.find_value("a");
    cout << "KEY: " << result_key << endl;
    cout << mvm.remove_key("bcd") << endl;
    cout << mvm << endl;
    result_key = mvm.remove_value("a");
    cout << "KEY: " << result_key << endl;
    cout << mvm << endl;
}
