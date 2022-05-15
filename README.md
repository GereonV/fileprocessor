# C-Utils

Small C-Programs written for convenient Usage in other Projects.

<details>
    <summary>Table of Contents</summary>
    <ol>
        <li><a href="#getting-started">Getting Started</a></li>
        <ul>
            <li><a href="#prerequisites">Prerequisites</a></li>
            <li><a href="#installation">Installation</a></li>
        </ul>
        <li><a href="#contributing">Contributing</a></li>
    </ol>
</details>

## Getting Started

To use any of these Programs locally you will need to clone this Repository and follow these instructions.

### Prerequisites

In order to use the Makefiles provided in this Repository need to have the following installed:

- **gcc**
- **make**

Check by running:
```sh
gcc --version
make --version
```

### Installation

1. Enter the Directory of the Repo!
    ```sh
    git clone git@github.com:GereonV/C-Utils.git
    cd C-Utils
    ```
1. Build everything even if you just want one Utility to make sure all dependencies are met!
    ```sh
    make
    ```
1. **Congratulations!** All executables should now be in the Projects root-directory.

    Alternatively on Linux you can use `make install` to directly put them into */usr/local/bin/*

## Contributing

Any contributions are appreciated.

[Open an issue](https://github.com/GereonV/C-Utils/issues) with the "enhancement"-tag. Your suggestion will be considered for implementation.

If you want to work on the Code yourself let me know in the Issue! After getting the "go-ahead" follow these steps:

(You will need to fork the Project to do these commands)

1. Create a Branch named after your issue's number (`git checkout -b i#<num>`)
1. Implement your proposed Changes/Additions and commit them
1. After the Feature is finished and you pushed your changes open a Pull Request
