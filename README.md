# Simulator

Simulateur d'écosystème IoT C++17 pour le monitoring de la qualité de l'air (Projet AP4A).

## Structure du Projet

```text
.
├── CMakeLists.txt
├── headers/          # Fichiers d'en-tête (.h / .hpp)
├── src/              # Fichiers sources (.cpp)
└── bin/              # Dossier où est généré l'exécutable
```

## Préréquis

* Compilateur C++ supportant le standard **C++17** (`g++`, `clang++`, ou MSVC)
* **CMake** (version >= 3.16)

---

## Guide Rapide (Quick Start)

### 1. Configuration du projet

```bash
cmake -B build -S .
```

### 2. Compilation

```bash
cmake --build build
```

### 3. Exécution

* **Linux / macOS :**
```bash
./bin/simulator
```


* **Windows (PowerShell) :**
```powershell
.\bin\simulator.exe
```



---

## Commandes Utiles

| Action | Commande | Description |
| --- | --- | --- |
| **Configuration** | `cmake -B build -S .` | Génère les fichiers de build dans le dossier `build/` |
| **Compilation standard** | `cmake --build build` | Compile les fichiers modifiés |
| **Recompilation complète** | `cmake --build build --target cleanbuild` | Nettoie la compilation précédente et recompile tout |
| **Nettoyage** | `cmake --build build --target clean` | Supprime les fichiers objet et binationales générés |

---

## Résolution des problèmes courants

Si vous rencontrez une erreur lors du build ou du lancement :

1. **Effacer le cache CMake et reconfigurer :**
```bash
rm -rf build bin
cmake -B build -S .
cmake --build build
```


*(Sur Windows PowerShell : `Remove-Item -Recurse -Force build, bin`)*
2. **Dossier `bin/` manquant :**
Le dossier `bin/` est créé automatiquement lors de la première compilation par CMake. Si vous tentez d'exécuter l'application avant la première compilation, le binaire n'existera pas.
