#!/bin/sh

curl -X POST -d @request.json http://`hostname`:9000/response.json --header "Content-Type:application/json"
