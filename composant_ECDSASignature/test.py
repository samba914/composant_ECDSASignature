import composant_ECDSASignature

# Remplacez ceci par une clé privée valide et la signature attendue
known_private_key = "4b8e29b9b0dddd58a709edba7d6df6c07ebdaf5653e325114bc5318c238f87f0"
known_message = "Hello, World!"
expected_signature = "EXPECTED_SIGNATURE"  # Remplacez par la signature attendue

signer = composant_ECDSASignature.ECDSASignature()
signer.Initialize(known_private_key)
signature = signer.Sign(known_message)

assert signature == expected_signature, "Signature does not match the expected value."

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