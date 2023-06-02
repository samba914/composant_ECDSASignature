#include "./cryptopp/eccrypto.h"
#include "./cryptopp/osrng.h"
#include "./cryptopp/oids.h"
#include "./cryptopp/hex.h"
#include <pybind11/pybind11.h>

char version[]="1.0";

const char* getVersion() {
	return version;
}

class ECDSASignature
{
private:
    CryptoPP::SecByteBlock privateKey;
    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey ecdsaPrivateKey;

public:
    ECDSASignature() {}
    ~ECDSASignature() {}

    void Initialize(const std::string& hexPrivateKey)
    {
        CryptoPP::StringSource ss(hexPrivateKey, true, new CryptoPP::HexDecoder(new CryptoPP::StringSink(privateKey)));
        ecdsaPrivateKey.Load(CryptoPP::StringStore(privateKey).Ref());
    }

    std::string Sign(const std::string& message)
    {
        CryptoPP::AutoSeededRandomPool prng;
        CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Signer signer(ecdsaPrivateKey);

        std::string signature;
        CryptoPP::StringSource ss(message, true, new CryptoPP::SignerFilter(prng, signer, new CryptoPP::HexEncoder(new CryptoPP::StringSink(signature))));
        
        return signature;
    }
};

namespace py = pybind11;

PYBIND11_MODULE(composant_ECDSASignature, module)
{
    module.doc() = "composant_ECDSASignature 1.0";
    module.def("getVersion", &getVersion, "a function returning the version");
  
    py::class_<ECDSASignature>(module, "ECDSASignature", py::dynamic_attr())
            .def(py::init<>())
            .def("Initialize", &ECDSASignature::Initialize)
            .def("Sign", &ECDSASignature::Sign);
}
