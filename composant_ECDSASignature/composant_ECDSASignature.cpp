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
#include <bitcoin/bitcoin.hpp>

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
        bc::wallet::hd_private key(bc::config::base16(privateKeyHex));
        return key.to_mnemonic().join(" ");
    }

    std::string mnemonicToPrivateKey(const std::string &mnemonic)
    {
        bc::string_list mnemonicList = bc::split(mnemonic, " ", true); // split by space
        bc::wallet::hd_private key(mnemonicList);
        return bc::encode_base16(key.secret());
    }
};

namespace py = pybind11;


PYBIND11_MODULE(composant_BIP39Converter, module)
{
    module.doc() = "BIP39Converter module";
     module.def("getVersion", &getVersion, "a function returning the version");

    py::class_<ECDSASignature>(module, "ECDSASignature", py::dynamic_attr())
        .def(py::init<>())
        .def("privateKeyToMnemonic", &BIP39Converter::privateKeyToMnemonic)
        .def("mnemonicToPrivateKey", &BIP39Converter::mnemonicToPrivateKey);
}
