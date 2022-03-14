#include <eosio/eosio.hpp>

using namespace std;
using namespace eosio;

CONTRACT did: public contract {
  public:
    using contract::contract;

    ACTION registerid(name from);
    ACTION removeid(name from);
    ACTION clearids();

  private:
    TABLE ids {
      name  user;
      auto primary_key() const { return user.value; }
    };
    typedef multi_index<name("ids"), ids> ids_table;
};
