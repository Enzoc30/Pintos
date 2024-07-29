#!/bin/bash 
echo "CS3015 Operating Systems 2023-2"
echo "Staring the docker container."
name=""
if [ -z "$1" ]
  then
    name="pintos"
    echo "No name provided. Using the default name '$name'"
  else
    name=$1
fi
volumeName="${name}_volume"
docker start $volumeName
docker exec -it $volumeName bash