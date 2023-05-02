#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <utility>
#include <tuple>

using namespace std;

template <typename... Payload>
class Train
{
public:

    explicit Train(tuple<Payload...> InPayload) : mPayload(InPayload) {}

    void DeliverPayload() const
    {
        cout << "Delivering Payload" << endl;

        PrintTuple(mPayload);
    }
protected:

    template <size_t I = 0>
    void PrintTuple(tuple<Payload...> arg) const
    {
        if constexpr (I == sizeof...(Payload))
        {
            return;
        }
        else
        {
            cout << get<I>(arg) << endl;

            PrintTuple<I+1>(arg);
        }
    }

    tuple<Payload...> mPayload;
};

class CargoTrain : public Train<int>
{
public:
    explicit CargoTrain(int Cargo) : Train<int>(make_tuple(Cargo)) {}
};


// first method, define a concept that restricts the types to be strings
//template <typename T>
//concept StringType = is_same_v<T, string>;

template <typename... Ts>
// second method, use the requires clause and a fold expression to ensure that all members are names of passengers
requires ((is_same_v<Ts, string>,...))
class PassengerTrain : public Train<Ts...>
{
public:

    explicit PassengerTrain(Ts... Cargo) : Train<Ts...>(make_tuple(Cargo...)) {}
};


int main() {
    PassengerTrain<string, string, string> PT {"alex", "rengar", "ezekiel"};
    //PassengerTrain<string, string, int> PT {"alex", "rengar", 32}; this wouldn't compile due to not being all strings
    CargoTrain CT{31};

    PT.DeliverPayload();
    CT.DeliverPayload();

    cout << "Hello World\n";
    cout << "Input: ";
    string data;
    getline(cin, data);
    cout << "Output: " << data << "\n\n";
    return 0;
}