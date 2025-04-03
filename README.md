# Zadanie: Świat

| Termin oddania | Punkty     |
|----------------|:-----------|
| 12.06.2025  23:00  |    20  |

--- 
Przekroczenie terminu o **n** zajęć wiąże się z karą:
- punkty uzyskania za realizację zadania są dzielone przez **2<sup>n</sup>**.

--- 
W katalogu [`LivingWorld`](https://github.com/ZeissIQSPL/CppAtAcademia/tree/main/CPP_01_OOP/LivingWorld)
znajduje się szkic programu implementującego dwuwymiarowy świat. 
Poniższe zadania dotyczą refaktoringu kodu tam przedstawionego.

### Zadania
1. **[5 punktów]** 
   Każdy `Organizm` powinien posiadać pole przechowujące historię jego przedków. 
   Historia jest zaimplementowana jako lista numerów tur narodzin i śmierci przodków.
   Wyposażyć `Organizmy` w odpowiedznie konstruktory, także kopiujące, oraz destruktory.
   Obiekty powinny posiadać również odpowiednie mechanizmy aktualizacji nowych danych.
   Jak powinny się zachowywać operatory przypisania?
      
1. **[5 punktów]** Do świata dodać nowe organizmy zgodnie z opisem świata z projektu 
   [`PythonWorld`](https://github.com/tborzyszkowski/PythonWorld/tree/master/Laboratorium), katalogi `World01` - `World04`.
   Wszystkie klasy (także istniejące) wyposażyć w odpowiedni model dziedziczenia oraz odpowiednie metody polimorficzne.
   
1. **[5 punktów]** Po realizacji zadania z poprzedniogo punktu spowodować by klasy `Organizm`, `Animal` i `Plant` 
   były klasami abstrakcyjnymi i nie było możliwe tworznie obiektów tych klas. 
   
1. **[5 punktów]** W klasie `World` mamy naiwny mechanizm serializacji świata. Nie jest on zgodny z SOLID. 
   Przebudować ten mechanizm tak by, każdy obiekt sam zajmował się swoją serializacją / deserializacją. 
   Przetestować nowy mechanizm na wybranych przykładach. 
