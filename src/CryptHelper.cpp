#include "CryptHelper.h"


CryptHelper::CryptHelper()
{
    std::srand(time(NULL));
}

CryptHelper::~CryptHelper()
{
    //dtor
}

std::string CryptHelper::GenRandomString(int length)
{
    std::string sRnd;

	int iMax = 126;
	int iMin = 33;
	int iRange = iMax - iMin + 1;

	for (int i = 0; i < length; i++)
	{
		int iNum = rand() % iRange + iMin;
		sRnd.append(1,(char)iNum);
	}

	return sRnd;
}


std::string CryptHelper::HexHash(std::string sData)
{
    std::string sHashStr;

    byte const* pbData = (byte*)sData.data();

    unsigned int nDataLen = sData.length();
    byte abDigest[CryptoPP::SHA256::DIGESTSIZE];

    CryptoPP::SHA256().CalculateDigest(abDigest, pbData, nDataLen);

    sHashStr = std::string((char*)abDigest, CryptoPP::SHA256::DIGESTSIZE);
    return StringToHex(sHashStr);

}

std::string CryptHelper::StringToHex(const std::string& input)
{
  static const char* const lut = "0123456789ABCDEF";
  size_t len = input.length();

  std::string output;
  output.reserve(2 * len);
  for (size_t i = 0; i < len; ++i)
  {
    const unsigned char c = input[i];
    output.push_back(lut[c >> 4]);
    output.push_back(lut[c & 15]);
  }
  return output;
}

std::string CryptHelper::encrypt(const std::string& str_in, const std::string& password, const std::string& iv)
{
    byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ];
    memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );

    std::string str_out;

    try
    {
        CryptoPP::HKDF<CryptoPP::SHA256> hkdf;
        hkdf.DeriveKey(key, CryptoPP::AES::DEFAULT_KEYLENGTH, (const byte*)password.data(), password.size(), (const byte*)iv.c_str(), CryptoPP::AES::BLOCKSIZE, NULL, 0);


       // CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryption((byte*)key.c_str(), key.length(),(byte*)iv.c_str());
        CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH,(byte*)iv.c_str());

        CryptoPP::StringSource encryptor(str_in, true,
            new CryptoPP::StreamTransformationFilter(encryption,
                new CryptoPP::Base64Encoder(
                    new CryptoPP::StringSink(str_out),
                    false // do not append a newline
                )
            )
        );
    }
    catch(const CryptoPP::Exception& ex)
    {
        wxMessageBox(ex.what());
    }

    return str_out;
}


std::string CryptHelper::decrypt(const std::string& str_in, const std::string& password, const std::string& iv)
{
    byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ];
    memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );

    std::string str_out;

    try
    {
        CryptoPP::HKDF<CryptoPP::SHA256> hkdf;
        hkdf.DeriveKey(key, CryptoPP::AES::DEFAULT_KEYLENGTH, (const byte*)password.data(), password.size(), (const byte*)iv.c_str(), CryptoPP::AES::BLOCKSIZE, NULL, 0);


        //CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decryption((byte*)key.c_str(), key.length(), (byte*)iv.c_str());
        CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH, (byte*)iv.c_str());

        CryptoPP::StringSource decryptor(str_in, true,
            new CryptoPP::Base64Decoder(
                new CryptoPP::StreamTransformationFilter(decryption,
                    new CryptoPP::StringSink(str_out)
                )
            )
        );
    }
    catch(const CryptoPP::Exception& ex)
    {
        wxMessageBox(ex.what());
    }

    return str_out;
}
