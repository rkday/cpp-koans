FROM ubuntu:20.04

RUN apt-get update && apt-get install -y clang cmake
RUN mkdir /koans
ADD src/ /koans/src
ADD include/ /koans/include
ADD koan_runner.py /koans/

WORKDIR /koans
CMD /koans/koan_runner.py
