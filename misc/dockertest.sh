DOCKERFILES=`ls Dockerfile* | grep -v fable`
for _dockerfile in $DOCKERFILES; do
    /usr/bin/time docker build -t mplapack:${_dockerfile} -f ${_dockerfile} . 2>&1 | tee log.${_dockerfile}
done
