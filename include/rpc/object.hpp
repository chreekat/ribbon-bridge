#ifndef RPC_OBJECT_HPP
#define RPC_OBJECT_HPP

namespace rpc {

/* Metafunction to access the input, output, and error parameter structures of
 * an interface's methods. Specialized in generated code. */
template <template <class> class Interface>
struct Method;

template <class T, template <class> class... Is>
class Object;

/* Break an rpc::Object's encapsulation and return the underlying
 * implementation instance (i.e., the user's object). */
template <class T, template <class> class... Is>
T& getInstance (Object<T, Is...>&);

template <class T, template <class> class... Is>
class Object : public Is<Object<T, Is...>>... {
    /* TODO: static_assert that T implements Is.... */
    friend T& getInstance<> (Object& object);

    T mInstance;
};

template <class T, template <class> class... Is>
T& getInstance (Object<T, Is...>& object) {
    return object.mInstance;
}

} // namespace rpc

#endif