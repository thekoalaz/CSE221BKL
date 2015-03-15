#! /bin/bash

sudo service rpcbind restart && sudo /etc/init.d/nfs-kernel-server restart && sudo mount -t nfs 76.167.145.48:/remote ./remote_test_files

