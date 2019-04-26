<img src="logo.png">

Wedit - Real-Time Collaborative Text Editor
&middot;
[![GitLab license](https://img.shields.io/github/license/Day8/re-frame.svg)](LICENSE)
=====
> Wedit is an open-source, real-time, collaborative text editor for the browser built from scratch in C++ using Peer-to-Peer connection and CRDT.

## Table Of Contents
- [Introduction](#introduction)
- [Requirements](#requirements)
- [Run Wedit](#run-wedit)
- [How It Works](#how-it-works)
- [Author](#author)

## Introduction
Recently, there are many assignments those were givens by our professors. Unfortunately, we couldn't meet each other because we have our own activities. We decided to work remotely from our own places. That's why we use Google Docs, an online collaborative editors created by Google, in order to finish all our assignments reports. We were amazed with the Google Docs because of its live-editing features. Intrigued by Google Docs, we try to challenge ourselves and set out to build one from scratch using CPP.

## Requirements
* GCC
* Cmake

## Run Wedit
- Built Wedit
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

- Run the server (only need once)
```
$ ./wedit_server
```

- Run the client (can be more than once)
```
$ ./wedit <PEER_PORT> <SERVER_IP> <SERVER_PORT>
```

## How It Works
- [**System Design and How It Works**](#system-design-and-how-it-works)
- [**More Details About Wedit**](#more-details-about-wedit)
- [**Self-Analysis Of Wedit**](#self-analysis-of-wedit)
- [**Wedit Testing**](#wedit-testing)

### System Design and How It Works
Wedit is a peer-to-peer, real-time collaborative text editing applicaion. The two most important aspects of the app that we want to discuss here are the use of peer-to-peer connections and the use of CRDT to provide a conflic-free distributed representations of the text editor.

We designed Wedit to be distributed via peer-to-peer connections from the start. We consider this an advantage since a peer-to-peer connection guarantees a shortest-path distance between each users hence a more real-time experience. But, this design poses another challenge. Since our database is distributed, how do we ensure that each user's database are synced with the other users'. This is where Conflict-free Replicated Data Type (CRDT) comes in. This data type provides us with the two properties that we need to ensure a consistent database which are commutativity and idempotency.

### More Details About Wedit
To develop Wedit, we decided to use C++. That is because we think that implementing a CRDT will be quite complex and running and maintaining a CRDT will be quite computationally expensive (if not done correctly). So, we decided that C++, with it's flexibility, rich STLs, and speed, is the right choice. To develop the GUI, we use Qt since it provides the most complete feature set and have a comprehensive documentation. This comes at a cost, however, since we ultimately need to implement the peer-to-peer connection by ourselves from scratch using TCP sockets but we think it is a fair tradeoff.

### Self-Analysis Of Wedit
From the beginning we take performance-related considerations very seriously. That is why we implemented every aspect of the CRDT as efficient as possible and we also utilize C++'s many STLs to achieve high performance on many of the CRDT's operations. On the networking side, we use TCP sockets to ensure a lossless transfer of information. Although TCP can cause some delays on real-time systems, we think it is OK since any consistency-hampering scenarios caused by delays are largely solved by the use of CRDT. Hence we decided to prioritize achieving a lossless information transfer here.

### Wedit Testing
During our tests, Wedit performed well as intended. Here is a snapshot of Wedit in action:

![](demo.gif)

## Author
### Nicholas Rianto Putra
```
Email: nicholasmagbanua@gmail.com
Github: https://github.com/nicholaz99
```

### Faza Fahleraz
```
Email: ffahleraz@gmail.com
Github: https://github.com/ffahleraz
```

### Abram Perdanaputra
```
Email: abram.perdanaputra@gmail.com
Github: https://github.com/abrampers
```
