const db = require('../database');

const account = {
  getAll: function(callback) {
    return db.query('select * from events', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from events where idEvent=?', [id], callback);
  },
  add: function(events, callback) {
    return db.query(
      'insert into events (value, idEvent, idAccount, date) values(?,?,?)',
      [events.value, events.idEvent, events.idAccount, events.date],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from events where idEvent=?', [id], callback);
  },
  update: function(id, account, callback) {
    return db.query(
      'update account set value=?, idAccount=?, date=? where idEvent=?',
      [events.value, events.idAccount, events.date, id],
      callback
    );
  }
};
module.exports = account;