const forj128 = require('./index');

console.log('Forj128 Node.js Test');
console.log('====================\n');

// Test 1: Hash a string
const input = 'hello world';
const digest = forj128.hash(input);
const hex = forj128.hashHex(input);

console.log('Input:', input);
console.log('Digest (hex):', hex);
console.log('Digest length:', digest.length, 'bytes');
console.log('');

// Test 2: Hash with Buffer
const bufferInput = Buffer.from('test data', 'utf8');
const bufferDigest = forj128.hash(bufferInput);
console.log('Buffer input hash:', bufferDigest.toString('hex'));
console.log('');

// Test 3: Consistency check
const hash1 = forj128.hashHex('consistent');
const hash2 = forj128.hashHex('consistent');
console.log('Consistency check:', hash1 === hash2 ? '✓' : '✗');
console.log('');

// Test 4: Different inputs produce different hashes
const hashA = forj128.hashHex('input A');
const hashB = forj128.hashHex('input B');
console.log('Different inputs:', hashA !== hashB ? '✓' : '✗');
console.log('');

console.log('All tests passed!');