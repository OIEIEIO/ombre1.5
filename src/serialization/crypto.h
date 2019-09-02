// Copyright (c) 2018, Ryo Currency Project
// Portions copyright (c) 2014-2018, The Monero Project
//
// Portions of this file are available under BSD-3 license. Please see ORIGINAL-LICENSE for details
// All rights reserved.
//
// ombre changes to this code are in public domain. Please note, other licences may apply to the file.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Parts of this file are originally copyright (c) 2012-2013 The Cryptonote developers

#pragma once

#include <vector>

#include "crypto/chacha.h"
#include "crypto/crypto.h"
#include "crypto/hash.h"
#include "debug_archive.h"
#include "serialization.h"

// read
template <template <bool> class Archive>
bool do_serialize(Archive<false> &ar, std::vector<crypto::signature> &v)
{
	size_t cnt = v.size();
	v.clear();

	// very basic sanity check
	if(ar.remaining_bytes() < cnt * sizeof(crypto::signature))
	{
		ar.stream().setstate(std::ios::failbit);
		return false;
	}

	v.reserve(cnt);
	for(size_t i = 0; i < cnt; i++)
	{
		v.resize(i + 1);
		ar.serialize_blob(&(v[i]), sizeof(crypto::signature), "");
		if(!ar.stream().good())
			return false;
	}
	return true;
}

// write
template <template <bool> class Archive>
bool do_serialize(Archive<true> &ar, std::vector<crypto::signature> &v)
{
	if(0 == v.size())
		return true;
	ar.begin_string();
	size_t cnt = v.size();
	for(size_t i = 0; i < cnt; i++)
	{
		ar.serialize_blob(&(v[i]), sizeof(crypto::signature), "");
		if(!ar.stream().good())
			return false;
	}
	ar.end_string();
	return true;
}

BLOB_SERIALIZER(crypto::chacha_iv);
BLOB_SERIALIZER(crypto::hash);
BLOB_SERIALIZER(crypto::hash8);
BLOB_SERIALIZER(crypto::public_key);
BLOB_SERIALIZER(crypto::secret_key);
BLOB_SERIALIZER(crypto::key_derivation);
BLOB_SERIALIZER(crypto::key_image);
BLOB_SERIALIZER(crypto::signature);
BLOB_SERIALIZER(crypto::uniform_payment_id);
VARIANT_TAG(debug_archive, crypto::hash, "hash");
VARIANT_TAG(debug_archive, crypto::hash8, "hash8");
VARIANT_TAG(debug_archive, crypto::public_key, "public_key");
VARIANT_TAG(debug_archive, crypto::secret_key, "secret_key");
VARIANT_TAG(debug_archive, crypto::key_derivation, "key_derivation");
VARIANT_TAG(debug_archive, crypto::key_image, "key_image");
VARIANT_TAG(debug_archive, crypto::signature, "signature");
