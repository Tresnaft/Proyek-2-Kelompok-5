# Instalasi
Dev-C++: 
1. Buka cipherlinkedlist.dev.
2. Klik tombol compile & run atau F11.

Compile manual:
```sh
g++ -o main main.cpp bmpio.cpp cip.cpp display.cpp linkedlist.cpp lsbbmp.cpp lsbjpeg.cpp lsbpng.cpp
```

# Struktur Program
Program ini akan menampilkan menu, yang dapat dinavigasi sesuai dengan input pengguna.
Jika pengguna memilih untuk melakukan enkripsi, maka program akan meminta input dari pengguna tentang enkripsi apa yang akan dilakukan, kemudian akan diminta nama file sumber, file tujuan, pesan yang akan dienkripsi, dan key enkripsi.
Jika pengguna memilih untuk melakukan dekripsi, maka program akan meminta input dari pengguna tentang dekripsi apa yang akan dilakukan, kemudian akan dimintan nama file sumber dan key dekripsi.

# Daftar Fitur Aplikasi
1. Enkripsi dan dekripsi teks menggunakan Hill Cipher.
2. Embedding teks menggunakan metode LSB (Least Significant Bit) ke dalam gambar (BMP, JPEG, PNG).
3. Ekstrak embedded teks.

# About Us
Aplikasi ini dibuat oleh Kelompok 5 kelas 1B-D3 Jurusan Teknik Komputer dan Informatika
Politeknik Negeri Bandung 

| No. | Nama                        | NIM        | Github Username |
| --- | --------------------------- | ---------- | --------------- |
| 1.  | Firgianathyas Siti Fadillah | 231511047  | fnathyas        |
| 2.  | Hanif Ahmad Naufal          | 231511048  | ramenyeon       |
| 3.  | Muhammad Azzam Izzudin      | 231511054  | mazzazzu        |
| 4.  | Nur Akmal                   | 231511059  | AkmallNr        |
| 5.  | Tresnardi Fathu Rhamdan     | 231511062  | Tresnaft        |
| 6.  | Zidan Tri Satria Mukti      | 231511064  | ZidanTSM22      |

Manajer : Sofy Fitriani, S.S.T., M.Kom NIP:199106142019032022

# Referensi
https://engineering.purdue.edu/ece264/17au/hw/HW15
https://abhijitnathwani.github.io/blog/2017/12/19/Introduction-to-Image-Processing-using-C
https://www.codeproject.com/Questions/1209078/How-do-i-impement-image-steganography-in-C-using-L
https://github.com/nothings/stb.git
