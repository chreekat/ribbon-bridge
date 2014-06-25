/* GENERATED CODE */

namespace com {
namespace barobo {

/* Forward declaration of interface */
template <class Derived>
class Robot;

} // namespace barobo
} // namespace com

namespace rpc {

template <>
struct Method<com::barobo::Robot> {
    struct move {
        struct in {
            float desiredAngle1;
            float desiredAngle2;
            float desiredAngle3;
        } in;

        struct out {
            int32_t i;
        } out;

        enum class defaultError {
        } error;

        constexpr static const struct in defaultIn () {
            return {
                float(),
                float(),
                float()
            };
        }

        constexpr static const struct out defaultOut () {
            return {
                int32_t()
            };
        }
    };
};

} // namespace rpc

namespace com {
namespace barobo {

template <class RpcObject>
struct Robot {
    void move (float desiredAngle1, float desiredAngle2, float desiredAngle3) {
        using Method = typename rpc::Method<Robot>::move;
        Method args {
            { desiredAngle1, desiredAngle2, desiredAngle3 },
            Method::defaultOut(),
            Method::defaultError()
        };
        auto& rpcObject = static_cast<RpcObject&>(*this);
        rpc::getInstance(rpcObject).on(args);
    }
};

} // namespace barobo
} // namespace com
