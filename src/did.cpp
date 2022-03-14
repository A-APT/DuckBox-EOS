#include <did.hpp>

ACTION did::registerid(name from, string did) {
  require_auth(from);
  print("a");

  // Init the _ids table
  ids_table _ids(get_self(), get_self().value);
  print("b");

  // find the record from _ids table
  auto id_itr = _ids.find(from.value);
  if (id_itr == _ids.end()) { // not registered id
    // create the record
    _ids.emplace(from, [&](auto& id) {
      id.user = from;
      id.did = did;
    });
  } // else: do nothing
  print("c");
}

ACTION did::removeid(name from) {
  require_auth(from);

  // Init the _ids table
  ids_table _ids(get_self(), get_self().value);

  // find the record from _ids table
  auto id_itr = _ids.find(from.value);
  if (id_itr == _ids.end()) { // not registered id
    // do nothing // TODO throw error
  } else {
    // remove id from table
    _ids.erase(id_itr);
  }
}

ACTION did::clearids() {
  require_auth(get_self());

  ids_table _ids(get_self(), get_self().value);

  // Delete all records in _messages table
  auto id_itr = _ids.begin();
  while (id_itr != _ids.end()) {
    id_itr = _ids.erase(id_itr);
  }
}

EOSIO_DISPATCH(did, (registerid)(removeid)(clearids))
