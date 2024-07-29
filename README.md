[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/6TmJW73q)
CS3015 Operating systems 
=======================

This repository contains an skeleton for the PintOS Project 3 - Virtual Memory.

## Author

- name lastname ([email](email))

## Project Setup

**Requirements:**
- [Docker](https://docs.docker.com/get-docker/)

### Quick setup

Just execute the `build.sh pintos-vm` bash script to create your docker image, your container and attach it to a volume. In this way every change you did inside the containers will be replicated to your local folder.

```
foo@bar:~$bash build.sh pintos-vm
```

###  Step by step

If you want to execute the bash scripts commands by yourself, you can execute the following commands:

> Don't forget to run the following commands in the same folder as the Dockerfile

- Create the PintOS image

```console
foo@bar:~$ docker build -t pintos-vm-image .
```

- Create a docker volume to made your changes persistent

```console
foo@bar:~$ docker create -it --volume $(pwd)/src:/pintos/src --name <my-volume-name> pintos-vm-image
```

## Run the container

To start working on your container, you need to run just the `exec.sh` bash script or the following commands:

> Don't forget to replace <my-volume-name> with your volume name

```console
foo@bar:~$ docker start <my-volume-name>
foo@bar:~$ docker exec -it <my-volume-name> bash
```

Inside your container, locate the project **vm** and then execute `make`. 

```console
container:/pintos/src$ cd vm/
container:/pintos/src/vm$ make
```

You will see that all test fails. You need to figure out what is missing to get it to work.

## References

- [For the dockerfile](https://github.com/JohnStarich/docker-pintos)
- [For the .gitignore](https://github.com/Berkeley-CS162/group0/blob/master/.gitignore)

