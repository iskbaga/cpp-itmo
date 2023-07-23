#pragma once

#include <array>
#include <cstddef>
#include <string>
#include <vector>

#define PUSH_BYTE(x) message.push_back(x)
#define PUSH_UINT32(x)                                                                                                                                          \
    {                                                                                                                                                           \
        uint32_t temp_le = static_cast<uint32_t>(x);                                                                                                            \
        uint32_t temp_be = __builtin_bswap32(temp_le);                                                                                                          \
        message.insert(message.end(), reinterpret_cast<const unsigned char *>(&temp_be), reinterpret_cast<const unsigned char *>(&temp_be) + sizeof(uint32_t)); \
    }
#define PUSH_PRICE(x)                                                                                                                                          \
    {                                                                                                                                                          \
        uint32_t temp_le = (ord_type == OrdType::Limit) ? static_cast<uint32_t>(x * 10000) : 0x7FFFFFFF;                                                       \
        uint32_t temp_be;                                                                                                                                      \
        std::memcpy(&temp_be, &temp_le, sizeof(temp_le));                                                                                                      \
        std::reverse(reinterpret_cast<unsigned char *>(&temp_be), reinterpret_cast<unsigned char *>(&temp_be) + sizeof(temp_be));                              \
        message.insert(message.end(), reinterpret_cast<const unsigned char *>(&temp_be), reinterpret_cast<const unsigned char *>(&temp_be) + sizeof(temp_be)); \
    }
#define PUSH_STRING(str, len)                              \
    message.insert(message.end(), str.begin(), str.end()); \
    message.resize(message.size() + len - str.size(), 0x20);

#define PUSH_REPLACE_PRICE(value)                                 \
    {                                                             \
        uint32_t value_le = static_cast<uint32_t>(value * 10000); \
        uint8_t bytes[4];                                         \
        std::memcpy(bytes, &value_le, sizeof(bytes));             \
        std::reverse(bytes, bytes + sizeof(bytes));               \
        message.insert(message.end(), bytes, bytes + 4);          \
    }

enum class RequestType
{
    EnterOrder
};

enum class Side
{
    Buy,
    Sell
};

enum class OrdType
{
    Market,
    Limit
};

enum class TimeInForce
{
    Day,
    IOC
};

enum class Capacity
{
    Agency,
    Principal,
    RisklessPrincipal
};

std::vector<unsigned char> create_enter_order_request(
        const std::string & cl_ord_id,
        Side side,
        double volume,
        double price,
        const std::string & symbol,
        OrdType ord_type,
        TimeInForce time_in_force,
        Capacity capacity,
        const std::string & firm,
        const std::string & user);

std::vector<unsigned char> create_replace_order_request(
        const std::string & old_cl_ord_id,
        const std::string & new_cl_ord_id,
        double total_volume,
        double price,
        TimeInForce time_in_force,
        const std::string & user);
