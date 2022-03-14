#include <eosio/eosio.hpp>

using namespace std;
using namespace eosio;

CONTRACT did: public contract {
  public:
    using contract::contract;

    ACTION registerid(name from, string did);
    ACTION removeid(name from);
    ACTION clearids(); // for develop

  private:
    TABLE ids {
      name    user;
      string  did;
      auto primary_key() const { return user.value; }
    };
    typedef multi_index<name("ids"), ids> ids_table;
};
