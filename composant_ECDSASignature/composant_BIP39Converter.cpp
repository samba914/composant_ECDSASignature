#include <bitcoin/bitcoin.hpp>
#include <pybind11/pybind11.h>
#include <string>

namespace py = pybind11;

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

PYBIND11_MODULE(composant_BIP39Converter, module)
{
    module.doc() = "BIP39Converter module";

    py::class_<BIP39Converter>(module, "BIP39Converter")
        .def(py::init<>())
        .def("privateKeyToMnemonic", &BIP39Converter::privateKeyToMnemonic)
        .def("mnemonicToPrivateKey", &BIP39Converter::mnemonicToPrivateKey);
}
