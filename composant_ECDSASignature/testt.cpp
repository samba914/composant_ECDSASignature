#include <bitcoin/bitcoin.hpp>
#include <pybind11/pybind11.h>
#include <iostream>
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

int main()
{
    BIP39Converter converter;

    std::string private_key ="4b8e29b9b0dddd58a709edba7d6df6c07ebdaf5653e325114bc5318c238f87f0";
    std::cout << "Private key: " << private_key << std::endl;

    std::string mnemonic = converter.privateKeyToMnemonic(private_key);
    std::cout << "Mnemonic: " << mnemonic << std::endl;

    std::string recovered_key = converter.mnemonicToPrivateKey(mnemonic);
    std::cout << "Recovered key: " << recovered_key << std::endl;

    std::cout << "Keys match: " << (recovered_key == private_key ? "YES" : "NO") << std::endl;

    return 0;
}
