#pragma once

#include <ion/ion.hpp>

using namespace ion;

CONTRACT talk : public ion::contract
{
public:
  using contract::contract;

  ACTION post(uint64_t id, uint64_t reply_to, ion::name user, const std::string& content);

private:
  static constexpr ion::name nameByReplyTo = ion::name("by.reply.to");

  TABLE message {
    uint64_t    id       = {}; // Non-0
    uint64_t    reply_to = {}; // Non-0 if this is a reply
    ion::name   user     = {};
    std::string content  = {};

    uint64_t primary_key() const { return id; }
    uint64_t get_reply_to() const { return reply_to; }
  };

  using fnByReplyTo = ion::const_mem_fun<message, uint64_t, &message::get_reply_to>;
  using TableMessage = ion::multi_index<"message"_n, message, ion::indexed_by<nameByReplyTo, fnByReplyTo>>;

};
