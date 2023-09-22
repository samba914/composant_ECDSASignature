import composant_BIP39Converter as bip39

converter = bip39.BIP39Converter()
print("here")
private_key = "4b8e29b9b0dddd58a709edba7d6df6c07ebdaf5653e325114bc5318c238f87f0"
mnemonic = converter.privateKeyToMnemonic(private_key)
print(mnemonic)

recovered_key = converter.mnemonicToPrivateKey(mnemonic)
print(recovered_key == private_key)  # Devrait afficher True
