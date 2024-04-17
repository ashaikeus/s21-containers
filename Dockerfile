FROM ubuntu:latest

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install valgrind -y
RUN apt-get install make -y
RUN apt-get install gcc -y
RUN apt-get install g++ -y
RUN apt-get install libgtest-dev -y
RUN apt-get install vim -y

WORKDIR /app

COPY . .

# CMD ["cd", "src"]
# CMD ["make"]

