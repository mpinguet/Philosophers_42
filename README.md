# 🧠 Philosophers — I never thought philosophy would be so deadly

## 📌 Description
Le projet **Philosophers** est une implémentation classique du problème des **dîneurs philosophes** 
L’objectif est d’apprendre à gérer **le multi-threading**, la synchronisation et l’utilisation des **mutex**, tout en respectant des contraintes strictes de mémoire et de timing.  

Chaque philosophe :
- **mange** quand il possède deux fourchettes,
- **dort** après avoir mangé,
- **pense** lorsqu’il n’est pas en train de dormir ou de manger.  

Le but est de simuler correctement ce cycle en évitant :
- les **conditions de concurrence** (data races),
- la **famine** (un philosophe qui ne peut jamais manger),
- et bien sûr, que les philosophes meurent trop tôt.

---

## 📂 Structure du projet

- `philo/` → version **threads + mutexes** (partie obligatoire).  
- `philo_bonus/` → version **processus + sémaphores** (bonus).  
- `Makefile` → compilation avec les règles standardes (`all`, `clean`, `fclean`, `re`, `bonus`).  
- `*.c / *.h` → sources du projet.  

---

## ⚙️ Compilation

Pour compiler le projet :  

```bash
make
```
Puis vous pouvez lancer le programme avec ce prototype:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
Ici, aucun philosophe ne devraient mourrir.
```bash
./philo 5 800 200 200
```
Par contre ici, un philosophe doit mourrir
```bash
./philo 4 310 200 100
```
Et nous pouvons rajouter un sixième argument qui est le nombre de repas que les philosophes doivent manger avant que le programme s'arrête proprement.
```bash
./philo 5 800 200 200 7
```
---

## 🧹Pour nettoyer
executable + fichiers obj:
```bash
make fclean
```

fichier obj:
```bash
make clean
```
---

## ✒️ Auteur
Projet réalisé par Macéo Pinguet dans le cadre de l’école 42.
