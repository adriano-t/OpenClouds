### Changelog

######24-05-2015
Andrea Luzzati, Adriano Tumminelli

- Installato MySQL Connector + Workbench
- Linkate librerie (entrambe: sia statica che dinamica) e aggiunti include del Connector
- Aggiunte DLL MSVCP100D.dll e MSVCR100D.dll per la compilazione in Debug (reperibili da internet)
- Problema: Connector richiede librerie BOOST per due variabili di tipo shared_pointer
- Soluzione: convertire entrambe le variabili al tipo std::shared_ptr (modificando il sorgente del Connector)
