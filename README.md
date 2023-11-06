# ProjetRadiotelemetrie

Vieux projet réalisé durant mes deux derniers stages aux GRAMs. Programme en C permettant de transmettre des données efficacement entre deux microcontrôleurs.

Le code client s'implémente sur un dev board de silicons labs (Gecko EFM32) et a pour but de capter les différents signes vitaux d'un agneau. Il transmet ensuite ces données à l'aide d'un encodage delta et de paquet "tweaker" spécifiquement pour améliorer la quantité de données utiles envoyées au serveur. 

Le serveur décode les différents paquets des différents clients et le retransmet directement à un ADC pour que le système d'acquisition déjà en place puisse le capter et l'insérer dans la base de données du groupe de recherche.

