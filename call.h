#pragma once
#include <any>
#include <list>
#include <functional>
#include <type_traits>
template <typename T>
auto fetch_back(T& t) -> typename std::remove_reference<decltype(t.back())>::type
{
    typename std::remove_reference<decltype(t.back())>::type ret = t.back();
    t.pop_back();
    return ret;
}

template <typename X>
struct any_ref_cast
{
    X do_cast(std::any y)
    {
        return std::any_cast<X>(y);
    }
};

template <typename X>
struct any_ref_cast<X&>
{
    X& do_cast(std::any y)
    {
        std::reference_wrapper<X> ref = std::any_cast<std::reference_wrapper<X>>(y);
        return ref.get();
    }
};

template <typename X>
struct any_ref_cast<const X&>
{
    const X& do_cast(std::any y)
    {
        std::reference_wrapper<const X> ref = std::any_cast<std::reference_wrapper<const X>>(y);
        return ref.get();
    }
};

template <typename Ret, typename...Arg>
Ret call (Ret (*func)(Arg...), std::list<std::any> args)
{
    if (sizeof...(Arg) != args.size())
        throw "Argument number mismatch!";
    return func(any_ref_cast<Arg>().do_cast(fetch_back(args))...);
}

template <typename Ret, typename...Arg,typename ... realArg>
Ret call (Ret (*func)(Arg...), realArg... args)
{
    if (sizeof...(Arg) != sizeof...(realArg))
        throw "Argument number mismatch!";
    std::any datas [sizeof...(Arg)] = {args...};
    size_t index = sizeof...(Arg);
    return func(any_ref_cast<Arg>().do_cast([&index,&datas]() -> decltype(datas[index]) {
        return datas [--index];
    }())...);
}
class functionPack {
    virtual std::any Call(std::list<std::any> arguments) = 0;
};
template<typename f>
class FunctionPack:public functionPack {
private:
    f function;
public:
    FunctionPack(f data) {
        static_assert(!std::is_function<f>::value,"it must be a function!");
        this->function = data;
    }
    std::any Call(std::list<std::any> arguments) {
        return call(function,arguments);
    }
};