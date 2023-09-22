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
#include "../trezor-crypto/bip39.h"


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
        // Convert hex string to bytes
        uint8_t data[32];
        for (int i = 0; i < 32; i++)
            sscanf(privateKeyHex.c_str() + 2*i, "%02hhx", &data[i]);
            
        // Convert to mnemonic
        const char *mnemonic = mnemonic_from_data(data, sizeof(data));
        return std::string(mnemonic);
    }

    std::string mnemonicToPrivateKey(const std::string &mnemonic)
    {
        uint8_t seed[512 / 8];
        const int seed_size = mnemonicToPrivateKey(mnemonic.c_str(), "", seed, NULL);
        
        char hexseed[2 * seed_size + 1];
        for(int i = 0; i < seed_size; i++)
            sprintf(hexseed + 2*i, "%02x", seed[i]);
        hexseed[2 * seed_size] = '\0';
        
        return std::string(hexseed);
    }
};
namespace py = pybind11;
PYBIND11_MODULE(composant_BIP39Converter, module)
{
    module.doc() = "BIP39ConverterTrezor module";

    py::class_<BIP39Converter>(module, "BIP39ConverterTrezor")
        .def(py::init<>())
        .def("privateKeyToMnemonic", &BIP39Converter::privateKeyToMnemonic)
        .def("mnemonicToSeed", &BIP39Converter::mnemonicToPrivateKey);
}



