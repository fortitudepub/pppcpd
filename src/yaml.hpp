#ifndef YAML_HPP
#define YAML_HPP

#include <yaml-cpp/yaml.h>
#include "policy.hpp"
#include "config.hpp"
#include "aaa.hpp"

namespace YAML {
    template <>
    struct convert<PPPOEPolicy>
    {
        static Node encode(const PPPOEPolicy &rhs);
        static bool decode(const Node &node, PPPOEPolicy &rhs);
    };

    template <>
    struct convert<FRAMED_POOL>
    {
        static Node encode(const FRAMED_POOL &rhs);
        static bool decode(const Node &node, FRAMED_POOL &rhs);
    };

    template <>
    struct convert<AAA_METHODS>
    {
        static Node encode(const AAA_METHODS &rhs);
        static bool decode(const Node &node, AAA_METHODS &rhs);
    };

    template <>
    struct convert<PPPOELocalTemplate>
    {
        static Node encode(const PPPOELocalTemplate &rhs);
        static bool decode(const Node &node, PPPOELocalTemplate &rhs);
    };

    template <>
    struct convert<AAARadConf>
    {
        static Node encode(const AAARadConf &rhs);
        static bool decode(const Node &node, AAARadConf &rhs);
    };

    template <>
    struct convert<AAAConf>
    {
        static Node encode(const AAAConf &rhs);
        static bool decode(const Node &node, AAAConf &rhs);
    };

    template <>
    struct convert<InterfaceConf>
    {
        static Node encode(const InterfaceConf &rhs);
        static bool decode(const Node &node, InterfaceConf &rhs);
    };

    template <>
    struct convert<PPPOEGlobalConf>
    {
        static Node encode(const PPPOEGlobalConf &rhs);
        static bool decode(const Node &node, PPPOEGlobalConf &rhs);
    };
}

#endif
