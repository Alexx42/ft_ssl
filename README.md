# ft_ssl
Hashing algorithms. Rewrite MD5 and SHA-256 hash functions. 🔐

## Installation
```bash
git clone [project]
```

```bash
make && make clean
```

## Usage
Two hashing algorithms are avalaible: MD5 and SHA-256. <br />
These are the options: <br />
• -p, echo STDIN to STDOUT and append the checksum to STDOUT <br />
• -q, quiet mode <br />
• -r, reverse the format of the output. <br />
• -s, print the sum of the given string <br />
```bash
./ft_ssl [command] [command_options] [command_arguments]
```

## Example of use
An example with MD5
```bash
./ft_ssl md5 -s "example"
```

Gives the following output
```bash
MD5 ("example") = 1a79a4d60de6718e8e5b326e338ae533
```
Another one with SHA-256
```bash
./ft_ssl sha256 -s "example"
```
Gives
```bash
SHA256 ("example") = 50d858e0985ecc7f60418aaf0cc5ab587f42c2570a884095a9e8ccacd0f6545c
```
