#!/bin/bash 
echo "CS3015 Operating Systems 2023-2"
echo "Building the docker image and creating a container attached to a volume."
name=""
if [ -z "$1" ]
  then
    name="pintos"
    echo "No name provided. Using the default name '$name'"
  else
    name=$1
fi
imageName="${name}_image"
volumeName="${name}_volume"

docker build -t  $imageName .
docker create -it --volume "$(pwd)/src:/pintos/src" --name $volumeName $imageName