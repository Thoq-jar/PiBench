**PIBENCH**

To download the source run this command
```bash
git clone https://github.com/Thoq-jar/PiBench.git
```

To compile on Windows do this:
Open Visual Studio .sln file and run the project. Im too lazy to make a writeup for windows.

To compile on Unix run this command:
```bash
cd PiBench && cd zoom && g++ -std=c++11 -pthread -o zoom zoom.cpp && ./zoom
```

Super Command:
```bash
rm -rf PiBench && git clone https://github.com/Thoq-jar/PiBench.git && cd PiBench && cd zoom && g++ -std=c++11 -pthread -o zoom zoom.cpp && clear && ./zoom && cd ~
```
