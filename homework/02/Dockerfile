FROM gcc:latest

RUN mkdir -p /src
COPY main.cpp /src/main.cpp
COPY mat.h /src/mat.h
COPY mat.cpp /src/mat.cpp
COPY matmul.h /src/matmul.h
COPY matmul.cpp /src/matmul.cpp
COPY Makefile /src/Makefile

RUN cd /src && make clean-all && make

CMD ["/src/demo"]
