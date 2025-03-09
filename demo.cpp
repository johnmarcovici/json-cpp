#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

namespace ns {
struct person {
    std::string name;
    std::string address;
    int age;
    double weight;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(person, name, address, age, weight);
}

int main(void)
{
    json data = json::parse(std::ifstream("example.json"));
    std::cout
        << data.dump(4)
        << std::endl;

    const auto pi_plus_1 = data["pi"].template get<double>() + 1.0;
    double pi_plus_1_by_ref;
    data["pi"].get_to(pi_plus_1_by_ref);
    pi_plus_1_by_ref += 1.0;

    std::cout
        << "name = " << data["name"] << std::endl
        << "pi = " << data["pi"] << std::endl
        << "pi + 1 = " << pi_plus_1 << std::endl
        << "pi + 1 (by ref) = " << pi_plus_1_by_ref << std::endl
        << std::endl;

    // struct --> json --> file
    ns::person p { "Ned Flanders", "744 Evergreen Terrace", 60, 166.88 };
    std::cout << json(p).dump(4) << std::endl;
    const auto filename = "struct-serialized.json";
    std::ofstream(filename) << json(p).dump(4) << std::endl;

    // file --> json --> struct
    const auto p2 = json::parse(std::ifstream(filename)).template get<ns::person>();
    std::cout
        << "name = " << p2.name << std::endl
        << "address = " << p2.address << std::endl
        << "age = " << p2.age << std::endl
        << "weight = " << p2.weight << std::endl
        << std::endl;

    return 0;
}
