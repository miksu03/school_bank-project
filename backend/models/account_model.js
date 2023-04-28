const db = require('../database');

const account = {
  getAll: function(callback) {
    return db.query('select * from account', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from account where id=?', [id], callback);
  },
  add: function(account, callback) {
    return db.query(
      'insert into account (value, MaxCredit, idCustomer, idCard, id) values(?,?,?,?,?)',
      [account.value, account.MaxCredit, account.idCustomer, account.idCard, account.id],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from account where id=?', [id], callback);
  },
  update: function(id, account, callback) {
    return db.query(
      'update account set value=?, maxCredit=? idCustomer=?, idCard=? where id=?',
      [account.value, account.maxCredit, account.idCustomer, account.idCard, id],
      callback
    );
  }
};
module.exports = account;