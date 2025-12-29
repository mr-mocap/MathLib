#pragma once

#include <tuple>


namespace Generic
{

template <class T>
struct Pair
{
    T a;
    T b;

#if 0
    struct Ref
    {
        /** Explicitly force the user to create these
         * 
         */
        constexpr Ref(T &a_in, T &b_in) : a{a_in}, b{b_in} { }

        constexpr Ref operator =(const Ref &input)
        {
            return Ref{ a = input.a, b = input.b };
        }

        constexpr Ref operator =(const Pair<T> &input)
        {
            return Ref{ a = input.a, b = input.b };
        }

        /** Vector2D conversion operator
         * 
         *  This allows Ref objects to automatically be converted to Vector2D objects
         *  for situations like passing to functions or constructors to Vector2D objects.
         */
        constexpr operator Pair<T>() const { return { a, b }; }

        T &a;
        T &b;
    };

    /** @name Swizzle operations
     *  @{
     */
    constexpr const Ref aa() const { return { a, a }; }
    constexpr       Ref aa()       { return { a, a }; }

    constexpr const Ref ab() const { return { a, b }; }
    constexpr       Ref ab()       { return { a, b }; }

    constexpr const Ref ba() const { return { b, a }; }
    constexpr       Ref ba()       { return { b, a }; }

    constexpr const Ref bb() const { return { b, b }; }
    constexpr       Ref bb()       { return { b, b }; }
    /// @}
#endif
    constexpr operator std::tuple<T, T>() const { return std::make_tuple(a, b); }
};

template <class T>
struct Triple
{
    T a;
    T b;
    T c;

#if 0
    struct Ref
    {
        /** Explicitly force the user to create these
         * 
         */
        constexpr Ref(T &a_in, T &b_in, T &c_in) : a{a_in}, b{b_in}, c{c_in} { }

        constexpr Ref operator =(const Ref &input)
        {
            return Ref{ a = input.a, b = input.b, c = input.c };
        }

        constexpr Ref operator =(const Triple<T> &input)
        {
            return Ref{ a = input.a, b = input.b, c = input.c };
        }

        /** Vector2D conversion operator
         * 
         *  This allows Ref objects to automatically be converted to Vector2D objects
         *  for situations like passing to functions or constructors to Vector2D objects.
         */
        constexpr operator Triple<T>() const { return { a, b, c }; }

        T &a;
        T &b;
        T &c;
    };

    /** @name Swizzle operations
     *  @{
     */
    constexpr const Pair<T>::Ref aa() const { return { a, a }; }
    constexpr       Pair<T>::Ref aa()       { return { a, a }; }

    constexpr const Pair<T>::Ref ab() const { return { a, b }; }
    constexpr       Pair<T>::Ref ab()       { return { a, b }; }

    constexpr const Pair<T>::Ref ac() const { return { a, c }; }
    constexpr       Pair<T>::Ref ac()       { return { a, c }; }

    constexpr const Pair<T>::Ref ba() const { return { b, a }; }
    constexpr       Pair<T>::Ref ba()       { return { b, a }; }

    constexpr const Pair<T>::Ref bb() const { return { b, b }; }
    constexpr       Pair<T>::Ref bb()       { return { b, b }; }

    constexpr const Pair<T>::Ref bc() const { return { b, c }; }
    constexpr       Pair<T>::Ref bc()       { return { b, c }; }

    constexpr const Pair<T>::Ref ca() const { return { c, a }; }
    constexpr       Pair<T>::Ref ca()       { return { c, a }; }

    constexpr const Pair<T>::Ref cb() const { return { c, b }; }
    constexpr       Pair<T>::Ref cb()       { return { c, b }; }

    constexpr const Pair<T>::Ref cc() const { return { c, c }; }
    constexpr       Pair<T>::Ref cc()       { return { c, c }; }


    constexpr const Ref abc() const { return { a, b, c }; }
    constexpr       Ref abc()       { return { a, b, c }; }

    constexpr const Ref acb() const { return { a, c, b }; }
    constexpr       Ref acb()       { return { a, c, b }; }

    constexpr const Ref bac() const { return { b, a, c }; }
    constexpr       Ref bac()       { return { b, a, c }; }

    constexpr const Ref bca() const { return { b, c, a }; }
    constexpr       Ref bca()       { return { b, c, a }; }

    constexpr const Ref cab() const { return { c, a, b }; }
    constexpr       Ref cab()       { return { c, a, b }; }

    constexpr const Ref cba() const { return { c, b, a }; }
    constexpr       Ref cba()       { return { c, b, a }; }

    constexpr const Ref aab() const { return { a, a, b }; }
    constexpr       Ref aab()       { return { a, a, b }; }

    constexpr const Ref aac() const { return { a, a, c }; }
    constexpr       Ref aac()       { return { a, a, c }; }

    constexpr const Ref bba() const { return { b, b, a }; }
    constexpr       Ref bba()       { return { b, b, a }; }

    constexpr const Ref bbc() const { return { b, b, c }; }
    constexpr       Ref bbc()       { return { b, b, c }; }

    constexpr const Ref cca() const { return { c, c, a }; }
    constexpr       Ref cca()       { return { c, c, a }; }

    constexpr const Ref ccb() const { return { c, c, b }; }
    constexpr       Ref ccb()       { return { c, c, b }; }
    /// @}
#endif
    constexpr operator std::tuple<T, T, T>() const { return std::make_tuple(a, b, c); }
};

template <class T>
struct Quadruple
{
    T a;
    T b;
    T c;
    T d;

#if 0
    struct Ref
    {
        /** Explicitly force the user to create these
         * 
         */
        constexpr Ref(T &a_in, T &b_in, T &c_in, T &d_in) : a{a_in}, b{b_in}, c{c_in}, d{d_in} { }

        constexpr Ref operator =(const Ref &input)
        {
            return Ref{ a = input.a, b = input.b, c = input.c, d = input.d };
        }

        constexpr Ref operator =(const Quadruple<T> &input)
        {
            return Ref{ a = input.a, b = input.b, c = input.c, d = input.d };
        }

        /** Vector2D conversion operator
         * 
         *  This allows Ref objects to automatically be converted to Vector2D objects
         *  for situations like passing to functions or constructors to Vector2D objects.
         */
        operator Quadruple<T>() const { return { a, b, c, d }; }

        T &a;
        T &b;
        T &c;
        T &d;
    };

    /** @name Swizzle operations
     *  @{
     */
    constexpr const Pair<T>::Ref aa() const { return { a, a }; }
    constexpr       Pair<T>::Ref aa()       { return { a, a }; }

    constexpr const Pair<T>::Ref ab() const { return { a, b }; }
    constexpr       Pair<T>::Ref ab()       { return { a, b }; }

    constexpr const Pair<T>::Ref ac() const { return { a, c }; }
    constexpr       Pair<T>::Ref ac()       { return { a, c }; }

    constexpr const Pair<T>::Ref ad() const { return { a, d }; }
    constexpr       Pair<T>::Ref ad()       { return { a, d }; }

    constexpr const Pair<T>::Ref ba() const { return { b, a }; }
    constexpr       Pair<T>::Ref ba()       { return { b, a }; }

    constexpr const Pair<T>::Ref bb() const { return { b, b }; }
    constexpr       Pair<T>::Ref bb()       { return { b, b }; }

    constexpr const Pair<T>::Ref bc() const { return { b, c }; }
    constexpr       Pair<T>::Ref bc()       { return { b, c }; }

    constexpr const Pair<T>::Ref bd() const { return { b, d }; }
    constexpr       Pair<T>::Ref bd()       { return { b, d }; }

    constexpr const Pair<T>::Ref ca() const { return { c, a }; }
    constexpr       Pair<T>::Ref ca()       { return { c, a }; }

    constexpr const Pair<T>::Ref cb() const { return { c, b }; }
    constexpr       Pair<T>::Ref cb()       { return { c, b }; }

    constexpr const Pair<T>::Ref cc() const { return { c, c }; }
    constexpr       Pair<T>::Ref cc()       { return { c, c }; }

    constexpr const Pair<T>::Ref cd() const { return { c, d }; }
    constexpr       Pair<T>::Ref cd()       { return { c, d }; }


    constexpr const Ref abc() const { return { a, b, c }; }
    constexpr       Ref abc()       { return { a, b, c }; }

    constexpr const Ref acb() const { return { a, c, b }; }
    constexpr       Ref acb()       { return { a, c, b }; }

    constexpr const Ref bac() const { return { b, a, c }; }
    constexpr       Ref bac()       { return { b, a, c }; }

    constexpr const Ref bca() const { return { b, c, a }; }
    constexpr       Ref bca()       { return { b, c, a }; }

    constexpr const Ref cab() const { return { c, a, b }; }
    constexpr       Ref cab()       { return { c, a, b }; }

    constexpr const Ref cba() const { return { c, b, a }; }
    constexpr       Ref cba()       { return { c, b, a }; }

    constexpr const Ref aab() const { return { a, a, b }; }
    constexpr       Ref aab()       { return { a, a, b }; }

    constexpr const Ref aac() const { return { a, a, c }; }
    constexpr       Ref aac()       { return { a, a, c }; }

    constexpr const Ref bba() const { return { b, b, a }; }
    constexpr       Ref bba()       { return { b, b, a }; }

    constexpr const Ref bbc() const { return { b, b, c }; }
    constexpr       Ref bbc()       { return { b, b, c }; }

    constexpr const Ref cca() const { return { c, c, a }; }
    constexpr       Ref cca()       { return { c, c, a }; }

    constexpr const Ref ccb() const { return { c, c, b }; }
    constexpr       Ref ccb()       { return { c, c, b }; }
    /// @}
#endif
    constexpr operator std::tuple<T, T, T, T>() const { return std::make_tuple(a, b, c, d); }
};

}