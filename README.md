# cpp-koans

These are programming koans - short pieces of code which you can fix errors in and improve your knowledge of C++.

## Running them

If you have Clang and Python3 installed, you can run these with:

```
./koan_runner.py
```

If not, you can run them in a Docker container:

```
docker build -t cpp-koans .
docker run -it --rm cpp-koans
```