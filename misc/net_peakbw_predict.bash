#!/bin/bash

time wget http://mirror.internode.on.net/pub/test/100meg.test &> d0.txt 
rm 100meg.test
time wget http://mirror.internode.on.net/pub/test/100meg.test &> d1.txt 
rm 100meg.test
time wget http://mirror.internode.on.net/pub/test/100meg.test &> d2.txt 
rm 100meg.test
time wget http://mirror.internode.on.net/pub/test/100meg.test &> d3.txt 
rm 100meg.test
time wget http://mirror.internode.on.net/pub/test/100meg.test &> d4.txt 
rm 100meg.test
time wget http://mirror.internode.on.net/pub/test/100meg.test &> d5.txt 
rm 100meg.test
time wget http://mirror.internode.on.net/pub/test/100meg.test &> d6.txt 
rm 100meg.test
time wget http://mirror.internode.on.net/pub/test/100meg.test &> d7.txt 
rm 100meg.test
time wget http://mirror.internode.on.net/pub/test/100meg.test &> d8.txt 
rm 100meg.test
time wget http://mirror.internode.on.net/pub/test/100meg.test &> d9.txt 
rm 100meg.test

