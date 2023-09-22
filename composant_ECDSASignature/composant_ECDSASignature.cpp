#include <openssl/ec.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/sha.h>
#include <openssl/err.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <pybind11/pybind11.h>
extern "C" {
#include <TrezorCrypto/bip39.h>
}

char version[] = "1.0";

const char *getVersion()
{
    return version;
}

class BIP39Converter
{
public:
    std::string privateKeyToMnemonic(const std::string &privateKeyHex)
    {
        const char* mnemonic = mnemonic_from_data(privateKeyHex.data(), privateKeyHex.size());
        return std::string(mnemonic);
    }

    std::string mnemonicToPrivateKey(const std::string &mnemonic)
    {
        uint8_t seed[64];
        mnemonic_to_seed(mnemonic.c_str(), "", seed, NULL); // Assuming no passphrase
        return std::string(reinterpret_cast<char*>(seed), 64);
    }
};

namespace py = pybind11;


PYBIND11_MODULE(composant_BIP39Converter, module)
{
    module.doc() = "BIP39Converter module using TrezorCrypto";

    py::class_<BIP39Converter>(module, "BIP39Converter")
        .def(py::init<>())
        .def("privateKeyToMnemonic", &BIP39Converter::privateKeyToMnemonic)
        .def("mnemonicToPrivateKey", &BIP39Converter::mnemonicToPrivateKey);
}



