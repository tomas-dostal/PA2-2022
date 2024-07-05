# Tests

To compile tests, run the following command:

```bash
cmake .
make 
```

To run tests, run the following command: 

```bash
./tspaint-test
```

Only very basic tests set is included: 
- create each object, assert created
- export empty file, assert not failed 
- export non-empty file, assert created