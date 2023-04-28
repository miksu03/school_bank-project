const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds = 10;

const card = {
    getAll: function (callback) {
        return db.query('select * from card', callback);
    },
    getById: function (user, callback) {
        return db.query('select * from card where idCard=?', [user], callback);
    },
    add: function (card, callback) {
	  bcrypt.hash(card.password, saltRounds, function (err, hashed_password) {
		bcrypt.hash(card.pinCode, saltRounds, function (err, hashed_pinCode) {
		  return db.query('INSERT INTO card (cardNumber, password, pinCode, Account_idCard, Customer_idCustomer, idCard) VALUES (?, ?, ?, ?, ?, ?)',
			[card.cardNumber, hashed_password, hashed_pinCode, card.Account_idCard, card.Customer_idCustomer, card.idCard],
			callback);
		});
	  });
	},
    delete: function (id, callback) {
        return db.query('delete from card where idCard=?', [id], callback);
    },
    update: function (id, card, callback) {
		bcrypt.hash(card.password, saltRounds, function (err, hashed_password) {
			bcrypt.hash(card.pinCode, saltRounds, function (err, hashed_pinCode) {
				return db.query('update card set cardNumber=?, password=?, pinCode=?, Account_idCard=?, Customer_idCustomer=? where idCard=?',
					[card.cardNumber, hashed_password, hashed_pinCode, card.Account_idCard, card.Customer_idCustomer, id],
					callback);
			});
		});
    },
};
module.exports = card;