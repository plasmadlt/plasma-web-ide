#!/bin/bash

yarn
nginx -c $PWD/nginx.conf
npx webpack-dev-server
