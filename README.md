# LDCF
The Logarithmicl Dynamic Cuckoo Filter (LDCF) is an efficient approximate membership test data strucutre for dynamic big data sets. LDCF uses a novel multi-level tree structure and reduces the worst insertion and membership testing time from O(N) to O(1), where N is the size of the set. At the same time, LDCF reduces the memory cost of [DCF](https://github.com/CGCL-codes/DCF) as the cardinality of the set increases.

## Environment
We implement DCF with an Intel(R) Core(TM) i5-2430M CPU @2.4GHz and OpenSSL library environment.

Install OpenSSL (Please refer to https://www.openssl.org to learn more).

```txt
sudo apt-get install openssl
sudo apt-get install libssl-dev
```

Build and run the example

```txt
cd src/
make test
./test
```

## Configurations
Configurations including false pisitive, item number can be costomized in "configuration/config.txt".

```txt
false positive = 0.01
item number = 100000000
```

## Publications

If you want to know more detailed information, please refer to the following papers:

Fan Zhang, Hanhua Chen, Hai Jin, Pedro Reviriego. "The Logarithmic Dynamic Cuckoo Filter." in Proceedings of 37th IEEE International Conference on Data Engineering (ICDE 2021), Chania, Crete, Greece, April 19-22, 2021.

Hanhua Chen, Liangyi Liao, Hai Jin, Jie Wu. ["The Dynamic Cuckoo Filter."](https://ieeexplore.ieee.org/document/8117563) in Proceedings of the 25th IEEE International Conference on Network Protocols (ICNP 2017), Toronto, Canada, Oct. 10-13, 2017. ([https://github.com/CGCL-codes/DCF](https://github.com/CGCL-codes/DCF))

Feiyue Wang, Hanhua Chen, Liangyi Liao, Fan Zhang, Hai Jin. ["The Power of Better Choice: Reducing Relocations in Cuckoo Filter."](https://ieeexplore.ieee.org/document/8885169) in Proceedings of 39th IEEE International Conference on Distributed Computing Systems (ICDCS 2019), Dallas, Texas, USA, July 7-10, 2019. ([https://github.com/CGCL-codes/BCF](https://github.com/CGCL-codes/BCF))

## Author and Copyright

LDCF is developed in National Engineering Research Center for Big Data Technology and System, Cluster and Grid Computing Lab, Services Computing Technology and System Lab, School of Computer Science and Technology, Huazhong University of Science and Technology, Wuhan, China by Fan Zhang(zhangf@hust.edu.cn), Hanhua Chen (chen@hust.edu.cn), and Hai Jin (hjin@hust.edu.cn).

Copyright (C) 2021, [STCS & CGCL](http://grid.hust.edu.cn/) and [Huazhong University of Science and Technology](http://www.hust.edu.cn).
