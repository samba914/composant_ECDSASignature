# Spécification du composant ECDSASignature

**Titre :** Spécification de la Classe ECDSASignature pour la signature ECDSA

**Auteurs :** Diouf_Samba & Alassaf_Mohamed

**Historique des versions :**

- 1.0 (31 Mai 2023) - Première version

---

**Description :**

**Contexte :**

Dans le cadre d'une application de transfert d'argent peer-to-peer, chaque transaction doit être sécurisée pour prévenir la fraude et garantir l'intégrité des transactions. À cette fin, la spécification de la signature ECDSA (Elliptic Curve Digital Signature Algorithm) est appliquée.

Lorsqu'un utilisateur souhaite effectuer une transaction, il entre les détails de celle-ci dans l'application. Avant que la transaction ne soit soumise au réseau, l'application génère une clé privée ECDSA pour l'utilisateur (si celle-ci n'existe pas déjà). Cette clé est utilisée pour signer numériquement les détails de la transaction.

Une fois la transaction signée, elle est soumise au réseau. Les autres utilisateurs, ou nœuds du réseau, utilisent alors la clé publique ECDSA associée à l'utilisateur pour vérifier la signature. Si la vérification réussit, cela signifie que la transaction a bien été initiée par l'utilisateur prétendu, assurant ainsi l'intégrité et la non-répudiation de la transaction.

Cette utilisation de la signature ECDSA assure non seulement la sécurité des transactions au sein de l'application, mais contribue également à renforcer la confiance des utilisateurs dans le système, car ils savent que leurs transactions sont protégées contre les fraudes et les manipulations.

**Schéma bloc incluant les composants connexes**

```
[Interface utilisateur] --> [ECDSASignature Class] --> [Envoi du message]
```

**Résumé :**
La classe ECDSASignature fournit une interface vers la bibliothèque OpenSSL. Elle utilise les classes et fonctions fournies par OpenSSL pour générer des signatures ECDSA.

```cpp
class ECDSASignature {
public:
    ECDSASignature();
    ~ECDSASignature();
    void Initialize(const std::string& hexPrivateKey);
    std::string Sign(const std::string& message);
};
```

Le constructeur par défaut de la classe `ECDSASignature` crée une instance de la classe. Le destructeur libère les ressources allouées lors de l'utilisation de la classe.

La méthode `Initialize` prend une clé privée sous forme de chaîne hexadécimale comme paramètre et initialise l'instance avec cette clé privée. La clé privée doit être générée à l'aide de l'algorithme ECDSA et doit être codée en hexadécimal.

La méthode `Sign` prend un message à signer comme paramètre et renvoie la signature ECDSA du message. La signature est renvoyée sous forme de chaîne hexadécimale.

---

**Utilisation du composant**

---



**Utilisation :**

Pour utiliser le composant ECDSASignature dans votre script Python, vous devez d'abord importer le module avec la commande : `import composant_ECDSASignature`.

Ensuite, vous créez une instance de la classe ECDSASignature et vous utilisez la méthode `Initialize` pour la configurer avec une clé privée. Cette clé sera par la suite utilisée pour créer la signature.

Prenons comme exemple l'utilisation de la clé privée `4b8e29b9b0dddd58a709edba7d6df6c07ebdaf5653e325114bc5318c238f87f0`. Pour obtenir cette clé privée, nous avons d'abord créé un fichier `private_key.pem` contenant une clé privée générée avec OpenSSL. Cela a été fait en utilisant la commande suivante : `openssl ecparam -name secp256k1 -genkey -noout -out private_key.pem`.

Ensuite, nous avons utilisé la commande `openssl ec -in private_key.pem -noout -text` pour décoder le fichier pem et afficher la clé privée en format texte. C'est de cette manière que nous avons récupéré la clé privée à utiliser avec notre composant ECDSASignature.

Maintenant reste plus qu'à appeler la méthode `Sign` avec un message en paramètre pour obtenir la signature de ce message.

```python
import composant_ECDSASignature

# Créez une instance de la classe ECDSASignature
signer = composant_ECDSASignature.ECDSASignature()

# Initialisez l'instance avec votre clé privée
signer.Initialize("4b8e29b9b0dddd58a709edba7d6df6c07ebdaf5653e325114bc5318c238f87f0")

# Signez un message
signature = signer.Sign("Hello word!")

# Affichez la signature
print(signature)
```
Ainsi, vous pouvez utiliser le composant ECDSASignature pour signer des messages à l'aide de l'algorithme ECDSA.



**Cas d’erreurs :**

Si une clé privée invalide est fournie à la méthode `Initialize`, Le composant lancera une exception lors du chargement de la clé.

---

**Test :**

**Plan de test :**

Dans notre programme de test, nous allons examiner les méthodes `Initialize` et `Sign` de la classe `ECDSASignature`. Pour ce faire, nous allons utiliser un message et une clé privée connus afin de générer une signature. Ensuite, nous allons vérifier si la signature générée est correcte en utilisant notre fichier `verify_sig.cpp` qui utilise bibliothèque C de `ECDSA`.

Dans le cadre de ce test, nous allons prendre comme entrée une clé privée, obtenue selon la méthode précédemment indiquée, un message spécifique, et la clé publique associée à la clé privée utilisée pour signer le message.

Notre programme commence par signer le message avec une clé privée valide. Ensuite, il vérifie la validité de la signature obtenue. Cette vérification se fera en deux temps : premièrement, nous nous assurerons que la signature a bien une longueur valide(qu'elle comporte bien 124 caractères) et ensuite nous vérifierons qu'elle est bien au format hexadécimal.

Pour effectuer une deuxième vérification et confirmer que la signature générée est bien une signature ECDSA valide, il suffit d'intégrer la signature obtenue dans la fonction principale `main` du fichier `verify_sig.cpp`. Plus précisément, cette signature devra être assignée à la variable `signature`.

Ce programme invoquera ensuite la méthode `Verify` qui utilisera la fonction `ECDSA_do_verify` fournie par la bibliothèque OpenSSL en C pour confirmer la validité de la signature. 

Pour compiler et exécuter ce programme, les commandes suivantes doivent être saisies dans le terminal :

```bash
g++ verify_sig.cpp -o verify_sig -lcrypto
./verify_sig
```
En suivant ces étapes, vous pourrez ainsi vérifier efficacement la validité de la signature ECDSA.

Enfin, nous testerons un cas d'erreur : nous tenterons de générer une signature en utilisant une clé privée qui ne respecte pas les normes valides. Nous vérifierons alors que notre programme se comporte correctement en levant une exception.

Cela nous permettra de valider que notre programme gère correctement les erreurs et que les méthodes `Initialize` et `Sign` fonctionnent comme prévu.

**Programme de test :**

```python
import composant_ECDSASignature
import re

# Remplacez ceci par une clé privée valide
known_private_key = "4b8e29b9b0dddd58a709edba7d6df6c07ebdaf5653e325114bc5318c238f87f0"
known_message = "Hello, World!"

# Test de signature
signer = composant_ECDSASignature.ECDSASignature()
signer.Initialize(known_private_key)
signature = signer.Sign(known_message)

print("Signature :")
print(signature)

# Vérification de la longueur de la signature
if len(signature) == 128:
    print("Signature length test passed.")
else:
    print("Signature length test failed: Signature does not have the expected length.")

# Vérification que la signature est en format hexadécimal
if re.fullmatch(r'[0-9a-fA-F]*', signature):
    print("Signature format test passed.")
else:
    print("Signature format test failed: Signature is not hexadecimal.")

# Test avec une clé privée invalide
try:
    signer = composant_ECDSASignature.ECDSASignature()
    signer.Initialize("INVALID_PRIVATE_KEY")
except Exception:
    print("Private key test passed: Exception correctly thrown for invalid private key.")
else:
    print("Private key test failed: No exception thrown for invalid private key.")


```


---


---
ANNEXE
---
Pour utiliser le composant ECDSASignature, vous devez d'abord cloner le dépôt et récupérer les sous-modules nécessaires.

**Clonage du dépôt et récupération des sous-modules :**

```bash
cd composant_ECDSASignature 
git submodule init
git submodule update
```
Vous devez aussi installer les fichiers d'en-tête nécessaires pour utiliser OpenSSL en utilisant la commande suivante :

```bash
sudo apt-get install libssl-dev
```

**Compilation :**

Naviguez jusqu'au sous-répertoire `composant_ECDSASignature ` et compilez le code.

```bash
cd composant_ECDSASignature 
make
```

**Fin de la spécification de la Classe ECDSASignature.**
