const db = require('../database');

const customer = {
  getAll: function(callback) {
    return db.query('select * from customer', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from customer where idCustomer=?', [id], callback);
  },
  /*getByUsername:function(user,callback){
    return db.query('select from course inner join customer on course.idcourse=customer.idcourse inner join student on student.idstudent=customer.idstudent where username=?',[user],callback);
  },*/
  add: function(customer, callback) {
    return db.query(
      'insert into customer (name,surName,idCustomer) values(?,?,?)',
      [ customer.name, customer.surName, customer.idCustomer],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from customer where idCustomer=?', [id], callback);
  },
  update: function(id, customer, callback) {
    return db.query(
      'update customer set name=?, surName=? where idCustomer=?',
      [customer.name, customer.surName, id],
      callback
    );
  }
};
module.exports = customer;