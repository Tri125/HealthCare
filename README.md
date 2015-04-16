Projet Utopia
Système de consultation de dossiers santé
=======
*Écrit en C++*

*OS: Windows 7 supporté*

*Permet de consulter le dossier médicale de patients et de suivre*

  * Consulter des professionnels de la santé à partir d'un code PS
  * Consulter la liste des patients et des interventions des professionnels.
  * Consulter des patients à partir de leur NAS
  * Consulter la liste des problèmes et des ressources utilisées par un patients.
  
Les données sont initialement séparé dans trois fichiers textes: 

  * population.txt* pour les Citoyen/Professionnel
  * problèmes.txt* pour les Blessure/Maladie
  * utilisations.txt* pour les Hospitalisation/RendezVous
  

Indexation

Lors de la lecture, les données seront indexées. L'index est invalidé et supprimé si les fichiers de données (les fichiers textes) sont plus récents que l'index.

Le système d'indexation s'inspire du même système utilisé par Git, un HASH, à partir de l'algorithme SHA1, est calculé par le code unique identifiant chaque données (CodePS ou le NAS). Les deux bytes les plus significatifs forment un dossier, le reste le nom d'un fichier sous ce dossier. Le contenu de ce fichier sont les données.

Limitation actuelles

* L'index est supprimé au complet peut importe si le fichier de population, de problèmes ou d'utilisations est plus récent.
* Recherche dans l'index à l'aveugle: il est possible de faire planter le logiciel en cherchant un Professionnel avec un NAS indexé.
* Utilise Windows.h


Avant utilisation

* Modifier *constants.h* pour changer l'emplacement de l'index et le nom des dossiers. 
* Dans le fichier indexation.ccp dans la méthode DestroyIndex, modifier "index" pour réflèter le path de l'index.
Cette valeur est hardcodé, car je ne connais pas de moyen de convertir un string en PCZZSTR.

Disclaimer

Le code des fichiers sha1.h et sha1.cpp provient de https://code.google.com/p/smallsha1/ et ont la notice suivante:

 Copyright (c) 2011, Micael Hildenborg
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Micael Hildenborg nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY Micael Hildenborg ''AS IS'' AND ANY
 EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL Micael Hildenborg BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
