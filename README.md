# Spécification du composant ECDSASignature

**Titre :** Spécification de la Classe ECDSASignature pour la signature ECDSA

**Auteurs :** Diouf_Samba & Alassaf_Mohamed

**Historique des versions :**

- 1.0 (31 Mai 2023) - Première version

---

**Description :**

**Contexte :**

La classe ECDSASignature est une implémentation en C++ de l'algorithme de signature numérique ECDSA (Elliptic Curve Digital Signature Algorithm). Elle utilise la bibliothèque OpenSSL, une bibliothèque open-source C pour la cryptographie, qui implémente divers algorithmes de chiffrement, de déchiffrement, et de signature numérique.

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

**Utilisation :**

Pour utiliser le composant ECDSASignature, vous devez importer le module dans votre script Python.

```python
import composant_ECDSASignature

# Créez une instance de la classe ECDSASignature
signer = composant_ECDSASignature.ECDSASignature()

# Initialisez l'instance avec votre clé privée
signer.Initialize("4b8e29b9b0dddd58a709edba7d6df6c07ebdaf5653e325114bc5318c238f87f0")

# Signez un message
signature = signer.Sign("YOUR_MESSAGE")

# Affichez la signature
print(signature)
```
Ainsi, vous pouvez utiliser le composant ECDSASignature pour signer des messages à l'aide de l'algorithme ECDSA.



**Cas d’erreurs :**

Si une clé privée invalide est fournie à la méthode `Initialize`, Le composant lancera une exception lors du chargement de la clé. De plus, si un message vide est passé à la méthode `Sign`, une exception sera également levée.

---

**Test :**

**Plan de test :**

Nous testerons les méthodes `Initialize` et `Sign` de la classe `ECDSASignature` en utilisant des messages et des clés privées connus, et nous vérifierons si la signature générée est correcte.
Nous allons testé aussi les cas où la clé privée est incorrecte ou le message est vide. Ces deux cas de figure devront lancer une exception.

**Programme de test :**

```python
import composant_ECDSASignature

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
    print("Signature test passed.")
else:
    print("Signature test failed: Signature does not have the expected length.")

# Test avec une clé privée invalide
try:
    signer = composant_ECDSASignature.ECDSASignature()
    signer.Initialize("INVALID_PRIVATE_KEY")
except Exception:
    print("Private key test passed: Exception correctly thrown for invalid private key.")
else:
    print("Private key test failed: No exception thrown for invalid private key.")

# Test avec un message vide
try:
    signer = composant_ECDSASignature.ECDSASignature()
    signer.Initialize(known_private_key)
    signature = signer.Sign("")
except Exception:
    print("Empty message test passed: Exception correctly thrown for empty message.")
else:
    print("Empty message test failed: No exception thrown for empty message.")

```

Cela vérifie que la signature générée a la bonne longueur et que des exceptions sont levées lorsqu'une clé privée invalide ou un message vide sont utilisés.

---

**Fin de la spécification de la Classe ECDSASignature.**
