# Steganography

## Background

[Steganography](https://en.wikipedia.org/wiki/Steganography) is the process of hiding a "secret message" in another text file, image or even sound file. It differs from cryptography in that the overall file/video/audio looks reasonably normal and still conveys information, making it hard to tell that there is a secret hidden inside. We are going to write a steganographic encoder/decoder for text.

# A Simple Steganography

We are going to take a plaintext message, one that anyone can read, and embed in that message a secret message which someone, who knows the code, can decipher.

The process is this. We are going to take the plaintext message, reduce the plaintext message to all lower case, then encode the secret message in the plaintext based on combinations of UPPER or lower case. Thus it is the **sequence** of upper and lower case letters in the plaintext message that encode our secret message.

We do this as follows. Each individual letter of the secret message is turned into a binary string of 5 0's and 1's. Exactly 5 for each letter. We will only recognize letters and will ignore any other characters in the secret message. For each of these binary strings, we take the next 5 letters of the plaintext and modify them as follows: for every 0 in the secret message binary string we lower case the plaintext letter, for every 1 we upper case the letter. We do this only for letters, ignoring all other characters in the plaintext. Let's consider the following example. The secret message is "help " and the original text is "Mom please send more money!" The index of each letter is its position in the alphabet with 'a' at 0, 'z' at 25.

![](https://raw.githubusercontent.com/liutiantian233/CPP-Project/master/Proj05/proj05-1.png)

-----

## Feedback and suggestions
- E-mail：<liutia20@msu.edu>

---------
Thanks for reading this help document
