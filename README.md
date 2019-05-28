# Algoritmi e Strutture Dati

## Project

Bloom filters operations (except hashing function) implementation in C.

### Steps

1. Completare il progetto implementando il file mancante, `bloom.c`
2. Verificare che il programma, quando eseguito, produca in output la seguente dicitura:
"Verifica dei risultati eseguita con successo."
In caso contrario, l'elaborato non può essere consegnato.
3. Quando la verifica dell'output è eseguita con successo, procedere alla consegna sul sito
web del corso (Unibo e-learning), seguendo le istruzioni riportate.

### Run

```
cd project/
make clean
make
./main && echo -n "\n" && cat OUTPUT1.txt && echo "\n" && cat output.txt
/bin/diff --strip-trailing-cr output.txt OUTPUT1.txt
```

### Deliver

```
zip matricola.zip bloom.c
```
