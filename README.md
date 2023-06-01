# Spécification du composant ECDSASignature


**Titre :** Spécification de la Classe ECDSASignature pour la signature ECDSA

**Auteurs :** Diouf_Samba & Alassaf_Mohamed

**Historique des versions :**

- 1.0 (31 Mai 2023) - Première version

---

**Description :**

**Contexte :**

La classe ECDSASignature est une implémentation en C++ de l'algorithme de signature numérique ECDSA (Elliptic Curve Digital Signature Algorithm). Elle utilise la bibliothèque Crypto++, une bibliothèque open-source C++ pour le chiffrement, le déchiffrement, les codes d'authentification de message, les codes d'authentification de message à clé secrète etc.

**Schéma bloc incluant les composants connexes**

```
[Application] --> [ECDSASignature Class] --> [Crypto++ Library]
```

**Interface et interaction avec chaque autre composant :**

La classe ECDSASignature fournit une interface vers la bibliothèque Crypto++. Elle utilise les classes et fonctions fournies par Crypto++ pour générer des signatures ECDSA.

**Résumé :**

```cpp
class ECDSASignature {
public:
    ECDSASignature();
    void Initialize(const std::string& hexPrivateKey);
    std::string Sign(const std::string& message);
};
```

Le constructeur par défaut de la classe `ECDSASignature` crée une instance de la classe.

La méthode `Initialize` prend une clé privée sous forme de chaîne hexadécimale comme paramètre et initialise l'instance avec cette clé privée. La clé privée doit être générée à l'aide de l'algorithme ECDSA et doit être codée en hexadécimal.

La méthode `Sign` prend un message à signer comme paramètre et renvoie la signature ECDSA du message. La signature est renvoyée sous forme de chaîne hexadécimale.

---

**Utilisation du composant**

---

Pour utiliser le composant ECDSASignature, vous devez d'abord cloner le dépôt et récupérer les sous-modules nécessaires.

**Clonage du dépôt et récupération des sous-modules :**

```bash
cd composant_ECDSASignature 
git submodule add -b master https://github.com/weidai11/cryptopp composant_ECDSASignature/cryptopp
git submodule init
git submodule update
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
signer.Initialize("YOUR_PRIVATE_KEY")

# Signez un message
signature = signer.Sign("YOUR_MESSAGE")

# Affichez la signature
print(signature)
```
Ainsi, vous pouvez utiliser le composant ECDSASignature pour signer des messages à l'aide de l'algorithme ECDSA.



**Cas d’erreurs :**

Si une clé privée invalide est fournie à la méthode `Initialize`, Crypto++ lancera une exception lors du chargement de la clé. De plus, si un message vide est passé à la méthode `Sign`, une exception sera également levée.

---

**Test :**

**Plan de test :**

Nous testerons la méthode `Sign` de la classe `ECDSASignature` en utilisant des messages et des clés privées connus, et nous vérifierons si la signature générée correspond à ce qui est attendu.

**Programme de test :**

```python
import composant_ECDSASignature

# Remplacez ceci par une clé privée valide et la signature attendue
known_private_key = "4b8e29b9b0dddd58a709edba7d6df6c07ebdaf5653e325114bc5318c238f87f0"
known_message = "Hello, World!"
expected_signature = "EXPECTED_SIGNATURE"  # Remplacez par la signature attendue

signer = composant_ECDSASignature.ECDSASignature()
signer.Initialize(known_private_key)
signature = signer.Sign(known_message)

assert signature == expected_signature, "Signature does not match the expected

 value."

# Test avec une clé privée invalide
try:
    signer = composant_ECDSASignature.ECDSASignature()
    signer.Initialize("INVALID_PRIVATE_KEY")
except Exception:
    pass
else:
    assert False, "Expected an Exception for invalid private key."

# Test avec un message vide
try:
    signer = composant_ECDSASignature.ECDSASignature()
    signer.Initialize(known_private_key)
    signature = signer.Sign("")
except Exception:
    pass
else:
    assert False, "Expected an Exception for empty message."
```

Cela vérifie que la signature générée correspond à ce qui est attendu, et que des exceptions sont levées lorsqu'une clé privée invalide ou un message vide sont utilisés.

---

**Fin de la spécification de la Classe ECDSASignature.**
