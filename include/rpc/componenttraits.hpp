#ifndef RPC_COMPONENTTRAITS_HPP
#define RPC_COMPONENTTRAITS_HPP

#include "rpc/error.hpp"

namespace rpc {

// Access the attribute component messages of an interface by name.
template <class Interface>
struct Attribute;

// Access the method component messages of an interface by name.
template <class Interface>
struct MethodIn;

template <class Interface>
struct MethodOut;

// Access the broadcast component messages of an interface by name.
template <class Interface>
struct Broadcast;

// Identify whether a type is an attribute component message.
template <class Attribute>
struct IsAttribute { constexpr static const bool value = false; };

// Metafunction to identify whether a type is a method component message.
template <class Method>
struct IsMethod { constexpr static const bool value = false; };

// Metafunction to identify whether a type is a broadcast component message.
template <class Broadcast>
struct IsBroadcast { constexpr static const bool value = false; };

template <class Component>
struct IsComponent {
    constexpr static const bool value =
        IsAttribute<Component>::value ||
        IsMethod<Component>::value ||
        IsBroadcast<Component>::value;
};

template <class Interface>
bool isAttribute (uint32_t id);

template <class Interface>
bool isMethod (uint32_t id);

template <class Interface>
bool isBroadcast (uint32_t id);

template <class Interface>
bool isComponent (uint32_t id) {
    return isAttribute<Interface>(id) ||
           isMethod<Interface>(id) ||
           isBroadcast<Interface>(id);
}

// Union containing a data member for every component message of an interface.
template <class Interface>
union ComponentInUnion;

template <class Interface>
union ComponentOutUnion;

template <class Interface>
class Subscriptions;

// Access the component IDs of an interface by name.
template <class Interface>
struct ComponentId;

// Access the component ID of an interface by type.
template <class Payload>
constexpr uint32_t componentId (Payload);

template <class T>
struct ResultOf;

template <class Interface>
struct GetInvoker;

template <class Interface>
struct SetInvoker;

template <class Interface>
struct FireInvoker;

template <class Interface>
struct BroadcastInvoker;

template <class Interface>
struct FulfillWithOutputInvoker;

template <class T, class Interface>
Error invokeGet (T& service,
        ComponentInUnion<Interface>& argument,
        uint32_t componentId,
        com_barobo_rpc_Reply_Output_payload_t& payload) {
    return GetInvoker<Interface>::invoke(service, argument, componentId, payload);
}

template <class T, class Interface>
Error invokeSet (T& service,
        ComponentInUnion<Interface>& argument,
        uint32_t componentId) {
    return SetInvoker<Interface>::invoke(service, argument, componentId);
}

template <class T, class Interface>
Error invokeFire (T& service,
        ComponentInUnion<Interface>& argument,
        uint32_t componentId,
        com_barobo_rpc_Reply_Output_payload_t& payload) {
    return FireInvoker<Interface>::invoke(service, argument, componentId, payload);
}

template <class T, class Interface>
Error invokeBroadcast (T& service,
        ComponentOutUnion<Interface>& argument,
        uint32_t componentId) {
    return BroadcastInvoker<Interface>::invoke(service, argument, componentId);
}

template <class T, class Interface>
Error invokeFulfillWithOutput (T& service,
        ComponentOutUnion<Interface>& argument,
        uint32_t componentId,
        uint32_t requestId) {
    return FulfillWithOutputInvoker<Interface>::invoke(service, argument, componentId, requestId);
}

template <class Interface>
Error decodeSetPayload (ComponentInUnion<Interface>& args,
        uint32_t componentId,
        com_barobo_rpc_Request_Set_payload_t& payload);

template <class Interface>
Error decodeFirePayload (ComponentInUnion<Interface>& args,
        uint32_t componentId,
        com_barobo_rpc_Request_Fire_payload_t& payload);

template <class Interface>
Error decodeBroadcastPayload (ComponentOutUnion<Interface>& args,
        uint32_t componentId,
        com_barobo_rpc_Reply_Broadcast_payload_t& payload);

template <class Interface>
Error decodeOutputPayload (ComponentOutUnion<Interface>& args,
        uint32_t componentId,
        com_barobo_rpc_Reply_Output_payload_t& payload);

} // namespace rpc

#endif
