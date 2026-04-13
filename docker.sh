# docker.sh used from m1 mac to launch docker 
#!/bin/bash
docker run -it --rm \
    -v $(pwd):/code \
    -v "/Users/kushikasenera/god mode":/vault \
    c-practice