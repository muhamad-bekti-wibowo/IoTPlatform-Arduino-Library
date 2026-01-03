# IoTPlatform Arduino Library

Folder ini berisi Arduino library untuk IoT Platform yang siap di-upload ke GitHub.

## Struktur Folder

```
IoTPlatform-Arduino-Library/
├── src/                          # Library source files
│   ├── IoTPlatform.h            # Main library (dengan callback)
│   ├── IoTPlatformSimple.h      # Simplified version
│   └── config.h                 # Configuration file
├── examples/                     # Example sketches
│   ├── simple_example.ino       # Basic example
│   ├── mbektiw_example.ino      # Full example
│   └── direct_websocket_example.ino
├── README.md                     # Documentation
└── library.properties            # Arduino library metadata
```

## Cara Upload ke GitHub

1. Buat repository baru di GitHub dengan nama `IoTPlatform-Arduino-Library`
2. Di folder ini, jalankan:

```bash
git init
git add .
git commit -m "Initial commit: IoTPlatform Arduino Library v1.0.0"
git branch -M main
git remote add origin https://github.com/YOUR_USERNAME/IoTPlatform-Arduino-Library.git
git push -u origin main
```

3. Update link di Dashboard frontend dengan URL repository Anda

## Instalasi untuk User

User bisa install dengan cara:

### Via Arduino IDE
1. Download ZIP dari GitHub (Code → Download ZIP)
2. Arduino IDE → Sketch → Include Library → Add .ZIP Library

### Via Git
```bash
cd ~/Documents/Arduino/libraries
git clone https://github.com/YOUR_USERNAME/IoTPlatform-Arduino-Library.git
```

## Update library.properties

Jangan lupa update file `library.properties`:
- Ganti `YOUR_USERNAME` dengan username GitHub Anda
- Ganti author dan maintainer dengan nama dan email Anda
