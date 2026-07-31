const binding = require('./build/Release/forj128');

/**
 * Compute Forj128 hash of input string or buffer.
 * 
 * @param {string|Buffer} input - Data to hash
 * @returns {Buffer} 16-byte digest
 */
function hash(input) {
    if (typeof input === 'string') {
        input = Buffer.from(input, 'utf8');
    }
    return binding.hash(input);
}

/**
 * Compute Forj128 hash and return as lowercase hex string.
 * 
 * @param {string|Buffer} input - Data to hash
 * @returns {string} 32-character lowercase hex string
 */
function hashHex(input) {
    return hash(input).toString('hex');
}

module.exports = {
    hash,
    hashHex
};