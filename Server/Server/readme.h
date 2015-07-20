/**
enum NameEnum
{
VALUE_ONE,
VALUE_TWO
};


class Example
{
private:
	auto param;
	int paramSecondary;
public:
	// Comment example.
	Example();
	void DoSomething();
}


DECISIONS:
1) Server: thread principale con receive, riempie una queue, thread secondario serve i pacchetti 
nell'ordine di ricezione.
Gestione pacchetti e files in swap con HD secondo limiti fissati.

2) Client: Ci sarà una cartella root contenente due cartelle: MyFiles, SharedFiles.
Esempio: Supponiamo che l'utente 'Adriano' fa click destro su un suo file o una sua cartella (dentro MyFiles)
-> condividi con -> Andrea.
Andrea riceve la richiesta di condivisione (notifica), accetta, e si crea la cartella "Adriano" dentro "SharedFiles"
nello storage locale di Andrea. Adriano può scegliere quali diritti conferire ad Andrea se ha condiviso una cartella
intera invece di un file. Così Andrea può leggere oppure anche scrivere (aggiungere files o eliminarne), e tali modifiche
si ripercuotono nella cartella locale di Adriano.

*/