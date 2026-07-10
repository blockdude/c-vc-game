#ifndef VCP_TRAITS_H
#define VCP_TRAITS_H

#include <variant>
#include <utility>

namespace vcp
{

template<typename Lambda, int = (Lambda{}(), 0)>
constexpr bool is_constexpr(Lambda) { return true; }
constexpr bool is_constexpr(...) { return false; }

template<typename... Ts> struct Overload : Ts... { using Ts::operator()...; };
template<typename... Ts> Overload(Ts...) -> Overload<Ts...>;

template<typename V, typename... Ts>
void match(V &&variant, Ts &&... visitors)
{
    std::visit(Overload{ std::forward<Ts>(visitors)... }, std::forward<V>(variant));
}

} // namespace vcp

#endif // VCP_TRAITS_H
