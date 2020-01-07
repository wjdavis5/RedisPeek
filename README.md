# RedisPeek
A redis module to support peeking at a key

Run `make`

Import the module
redis-cli MODULE LOAD RedisPeek.so

Test it out
redis-cli set a a
redis-cli PEEK a
