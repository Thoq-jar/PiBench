**PIBENCH**

To download the source run this command
```bash
git clone https://github.com/Thoq-jar/PiBench.git
```

**[Purriler](https://github.com/Thoq-jar/Purriler) is required to compile this project.**
**Purriler is a build system for C++ that I made. It is not ready for production. Please use clang to compile this project for the time being.**

```bash
clang++ -std=c++17 -pthread -o pibench src/main.cpp
```

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.