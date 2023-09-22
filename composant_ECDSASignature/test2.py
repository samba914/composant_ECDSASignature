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
