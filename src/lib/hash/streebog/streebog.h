/*
* Streebog
* (C) 2017 Ribose Inc.
*
* Botan is released under the Simplified BSD License (see license.txt)
*/

#ifndef BOTAN_STREEBOG_H_
#define BOTAN_STREEBOG_H_

#include <botan/hash.h>

namespace Botan {

/**
* Streebog (GOST R 34.11-2012)
* RFC 6986
*/
class Streebog final : public HashFunction {
   public:
      size_t output_length() const override { return m_output_bits / 8; }

      std::unique_ptr<HashFunction> new_object() const override { return std::make_unique<Streebog>(m_output_bits); }

      void clear() override;
      std::string name() const override;

      size_t hash_block_size() const override { return 64; }

      std::unique_ptr<HashFunction> copy_state() const override;

      explicit Streebog(size_t output_bits);

   protected:
      void add_data(const uint8_t input[], size_t length) override;
      void final_result(uint8_t out[]) override;

      void compress(const uint8_t input[], bool lastblock = false);

      void compress_64(const uint64_t input[], bool lastblock = false);

   private:
      const size_t m_output_bits;
      uint64_t m_count;
      size_t m_position;
      secure_vector<uint8_t> m_buffer;
      secure_vector<uint64_t> m_h;
      secure_vector<uint64_t> m_S;
};

}  // namespace Botan

#endif
