#!/bin/sh

curl -X POST -d @request.json http://latrice.local:9000 --header "Content-Type:application/json"
