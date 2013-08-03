# Puddle

I'm not sure how this is gonna go. It's very much a work in progress now.

To clone and hack:

    git clone https://github.com/jonspeicher/Puddle.git
    cd Puddle && git submodule init && git submodule update
    <pebble-sdk-root>/Pebble/tools/create_pebble_project.py --symlink-only <pebble-sdk-root>/Pebble/sdk .
    ./waf configure
    ./waf build
