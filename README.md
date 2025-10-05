# CS50x - Week 4: Memory

This repo contains my solutions for **Week 4** of Harvard's [CS50x](https://pll.harvard.edu/course/cs50-introduction-computer-science) course. The focus this week was on learning the basics of the **memory**, including:

- Hexadecimal
- Pointers
- Defining Custom Types
- Dynamic Memory Allocation
- Call Stacks
- File Pointers

---

## ✅ Projects

### `volume`

In `volume/volume.c`, I wrote a program to modify the volume of a WAV audio file. WAV files store sound as 16-bit samples following a 44-byte header. The program reads each sample, scales it by a user-provided factor, and writes the adjusted samples to a new file, effectively increasing or decreasing the audio volume.

### `filter`

In `filter-less/helpers.c`, I implemented several image filters for 24-bit BMP files. Each pixel’s red, green, and blue (RGB) components are modified to produce effects such as grayscale, reflection, blur, and edge detection. The program manipulates pixel data directly to transform the image at the byte level.

### `recover`

In `recover/recover.c`, I created a program to recover JPEG images from a raw memory card image. The program scans the card’s binary data for JPEG headers, extracts each image, and writes them to separate output files — effectively restoring deleted photos.
