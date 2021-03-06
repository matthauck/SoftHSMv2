/*
 * Copyright (c) 2010 SURFnet bv
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*****************************************************************************
 AESTests.cpp

 Contains test cases to test the AES implementation
 *****************************************************************************/

#include <stdlib.h>
#include <cppunit/extensions/HelperMacros.h>
#include "AESTests.h"
#include "CryptoFactory.h"
#include "AESKey.h"
#include <stdio.h>

CPPUNIT_TEST_SUITE_REGISTRATION(AESTests);

void AESTests::setUp()
{
	aes = NULL;

	aes = CryptoFactory::i()->getSymmetricAlgorithm(SymAlgo::AES);

	// Check the return value
	CPPUNIT_ASSERT(aes != NULL);
}

void AESTests::tearDown()
{
	if (aes != NULL)
	{
		CryptoFactory::i()->recycleSymmetricAlgorithm(aes);
	}

	fflush(stdout);
}

void AESTests::testBlockSize()
{
	CPPUNIT_ASSERT(aes->getBlockSize() == 16);
}

void AESTests::testCBC()
{
	char testKeys128[][33] =
	{
		"00000000000000000000000000000000",
		"0102030405060708090A0B0C0D0E0F10",
		"404142434445464748494A4B4C4D4E4F",
		"89436760984679018453504364534464",
		"49587346983643545706904580436731"
	};

	char testKeys192[][49] =
	{
		"000000000000000000000000000000000000000000000000",
		"0102030405060708090A0B0C0D0E0F101213141516171819",
		"404142434445464748494A4B4C4D4E4F5051525354555657",
		"096874395874290867409857496743857632098479834634",
		"439867439058743095864395348375043296845094854983"
	};

	char testKeys256[][65] =
	{
		"0000000000000000000000000000000000000000000000000000000000000000",
		"0102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F20",
		"404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F",
		"4394398576098257436095746985679043867498572406874967416846341641",
		"4369006859867098670492857409386741095643756930847023587048579014"
	};

	char testData[][256] =
	{
		"4938673409687134684698438657403986439058740935874395813968496846",
		"549813644389670948567490687546098245665626527788",
		"64398769586792586795867965624526",
		"468376458463264536"
	};

	char testResult[5][4][3][256] = {
		{
			{
				"6CAEC72F5E101C66550215ACAB6B874C62E7BD074C0A09A8EE4562EFCB4E560A3E90FA0F50391087824FC27F57618E5C",
				"E20E3123AC64FCA5536E0A2DC48DBEBCECB3F260EFF4A0EB99D72F57EF38DED336EB9DD0B968D24C91E63974E7445A21",
				"C7910B1634DB493998608875A4652B20C64202ED507D9DBA06F62EB20A63C32FB6C9669D42A0AC29D773E6D40A63A2AC"
			},
			{
				"8F48A65BF638FEDB7E6F59BAC8C110FEBA933F106D564119B88569E758B7FB83",
				"125E1D93DC2C43A6FAFC508DB6F9A4A9F390D102C2300F0A3617CE95027BFAA3",
				"FACB8DEF1B476400DE9796D5058E9086ECF04C927F5C160161C7A34D8288EB3C"
			},
			{
				"C810E96482F109C9A05D2B1BEBAC7966BB7784F58A5478C1A07EC0DB39F6D87B",
				"2385391BB8F2DD97280B1FAEFACB6B5C4FE12A2274D6B967509CF18500A640D6",
				"47549520EADA1A5D931EACCC922F88BA2E386089BF97C790FD2CD38553334AE4"
			},
			{
				"A7D9EAE80224624188CAA7012140E946",
				"6ECD5C71ECA4AB9C3B71E91721CA2043",
				"2F77AA438E9259F268985668B00650E5"
			}
		},
		{
			{
				"FCB2FB6BF8ED8910F023A934EB9DA550E4D5B469D75B9390F4A207E54F29412450E52E980862DC80B89F6D1D10B68AA5",
				"7EF0F65513CFE3E0D21305E2ECCBB3554B0DE119720C5A86337E57F74795BC23ED9CB82A951DE3D00D7A0DC8997319DD",
				"5B83BFDB6EF3AEA5191F2EE3366EDE10480E9459C0DE2994DD9C6408A377DFFF8121A38CFD1AA864559B9A435A3BDD6D"
			},
			{
				"81D667193D42BF19C456F4A1F7070C047D94C7EE8136FA315F938162FDDA20C1",
				"2EFBA2B689C0F775097F98B569A1F20004F1A75F0C53473969DBE586ABCAE04D",
				"447326913AA4565951D987F59B48870DD9285EEFCF64B429C2220E4F3E0D9DE2"
			},
			{
				"891DF30BAEA2D24408A9C788D59DBAC7A6F34311813216311E18E9ED7122DB1A",
				"F1629B62ECDF3CDAA3DA0EBB31EE37691AF4EB2B6F9CF04A9861935B2C167D02",
				"C7BD348D5E6696CB8BA813B96EA5C42C5C3C3629D18FC9DAF1B50A0AE4843C5B"
			},
			{
				"91C44D109D46C8E8656793680D43BE94",
				"E68D8E49A19F155B7ED7253120B0D117",
				"FAED8666F695C85283ECF51C96DB41CE"
			}
		},
		{
			{
				"0CCFB49FE2B7E93A556E56B2C616885FBB0515F55A4210FE2F492A4775F078655CB21691CA6A54819C2D885954809D00",
				"2FC6C785D683FC35304DD161A21FA1B256F9FBB2817F1F3BEBCE7C1E292EC6999641AA6953C0FAB6DFC2942CABD32DFB",
				"31FAF4E3DA19D2372666AC635FFE361E33AD7865AEF616273D8F3B471F77A0998C6A41497168A65F621D912C54A4AF28"
			},
			{
				"0B3842152A6365ED14AD952ABBBAF0EED2E8F36250DD25DDA301490FDE05219B",
				"696BF21A887A04E194DCC18719E1BD623D8BD25A0CEF5EC2E21312ACE6C81F40",
				"A2C8E61471EC80FE39AC0D8F720FEA8F2D23D04596A751C755E51CD357BCA5E0"
			},
			{
				"5E0EA3AFBE191A16854C7960F087958F577EA4F80160F521A12D2211FAC25E16",
				"F5475B4FD48F969123C9F7FB08C7E902CCA282F167BBAFF1A7C7EDDB7BCBAC76",
				"380CB860EC6DEF4F9329F4BE826DE1FE61A71629DD978F00BEFB349ACBD0BAD8"
			},
			{
				"BA1452E755E6A43E43B10DD2C1530093",
				"07CA52926D4E8F2F6055E6E0251CB9E5",
				"AB99E5FEE195B4433667AD3074A9322E"
			}
		},
		{
			{
				"D2D46E577723B30E6B5FC96DC18B2C55E0EACCB07CE07C7F30FD113A987E2A2059AB7DF8985C1AE525EFAD9CE111893C",
				"CC5B220688AC0231DBC03C8886C0D0109840B9E58FBB1A6B6C261ED9E7979E951818033A25778FF328786D1777790078",
				"4B4A0B3D6D4E770BECC574BF66CD401942DC4D0DCD0EC65F99B2925B688BB217FCB5C946BE986C440C93279F4670CD43"
			},
			{
				"29C76D62D3C4F7FECCBFD7A73B06E2ECA7AA3B2D4BE79EC945B0B88C813264D8",
				"B898DCE11F3D6BB2182208E0BBBA7F404FE415D4D6D0772960E7CE3549B9899C",
				"11E9552009836B51F241E972D680A9F397260163D9D5369BFC1B136FB4206966"
			},
			{
				"539FC6EDAE21EDDC1CC4650367F527467916A6990E540146238AA9CD6B3B4ADE",
				"2D9DE2BC47DAFCF7867134110C541EBCD72D67B1B23DEF6805DBFF4A4D90EF91",
				"BF484690835FF61C4A7873A996EEB91F553978A40360E192273D3923E04DFE1E"
			},
			{
				"4910EFFFBF571C98D51802F04A42213E",
				"EDD1880FC4D41293BC74B98AF3D8A010",
				"F8BCC258A6CD7FAA4EDF16A3CF5573C4"
			}
		},
		{
			{
				"C2061BD0B4274B5CB4E408B492991F4195FDBFCDED1BC57442151B182BA6E8075AAF858F357C262E0034B9B5F839D823",
				"6EEFEBCC9F8C607D21A158E23980EFA6EC234DC6EA668A446F467F4AE87521F18DC1800D87A5EBC63C444F810557B61D",
				"00C952BA54614A1F11B0D59F3F469A859F62CCE0D35073B91B461302A7F37BD0B23401482DFCEE66ABD12C05615C9862"
			},
			{
				"B36553D93EEF04AE247DBCBDDB8C039FFAC8AC1B0EF14C2E4BA653F089924451",
				"90670C9DE58F95431591FA2BE8EA1B4B3F5BDBFC0B5199F94A41E4FC7B6B1645",
				"A065415413D3A08E4B42A3F2681B8D122167A1E3F92D38C305761D9BF80131F1"
			},
			{
				"12A758F161543F2842138B8C2453C3A05A90BE9F92CB3DD10C40AB9D1D746B49",
				"DF1F4DDFFE1032C812FC6F35AB2B3A7B0E8D26DA49DEC8F5E08D108DB1283BEA",
				"FDCB66159E1B5CF1BE9F7271EF2C35D5E9F7485E32D16C6AC865E64619DB8724"
			},
			{
				"1FC224DCB64848B5E8F9FB91C542991F",
				"1F8C5F65F9205098B47E26894B9154D9",
				"19763CAC206EDFDEBEDAD9C274DEE1C1"
			}
		}
	};

	char testIV[][33] =
	{
		"00000000000000000000000000000000",
		"0102030405060708090A0B0C0D0E0F10",
		"404142434445464748494A4B4C4D4E4F",
		"69836472094875029486750948672066",
		"48670943876904867104398574908554"
	};

	for (int i = 0; i < 5; i++)
	{
		ByteString keyData128(testKeys128[i]);
		ByteString keyData192(testKeys192[i]);
		ByteString keyData256(testKeys256[i]);

		AESKey aesKey128(128);
		CPPUNIT_ASSERT(aesKey128.setKeyBits(keyData128));
		AESKey aesKey192(192);
		CPPUNIT_ASSERT(aesKey192.setKeyBits(keyData192));
		AESKey aesKey256(256);
		CPPUNIT_ASSERT(aesKey256.setKeyBits(keyData256));

		ByteString IV(testIV[i]);

		for (int j = 0; j < 4; j++)
		{
			ByteString plainText(testData[j]), shsmPlainText;
			ByteString cipherText;
			ByteString shsmCipherText, OB;

			// Test 128-bit key
			cipherText = ByteString(testResult[i][j][0]);

			// Now, do the same thing using our AES implementation
			shsmCipherText.wipe();
			CPPUNIT_ASSERT(aes->encryptInit(&aesKey128, SymMode::CBC, IV));

			CPPUNIT_ASSERT(aes->encryptUpdate(plainText, OB));
			shsmCipherText += OB;

			CPPUNIT_ASSERT(aes->encryptFinal(OB));
			shsmCipherText += OB;

			CPPUNIT_ASSERT(shsmCipherText == cipherText);

			// Check that we can get the plain text
			shsmPlainText.wipe();
			CPPUNIT_ASSERT(aes->decryptInit(&aesKey128, SymMode::CBC, IV));

			CPPUNIT_ASSERT(aes->decryptUpdate(shsmCipherText, OB));
			shsmPlainText += OB;

			CPPUNIT_ASSERT(aes->decryptFinal(OB));
			shsmPlainText += OB;

			CPPUNIT_ASSERT(shsmPlainText == plainText);

			// Test 192-bit key
			cipherText = ByteString(testResult[i][j][1]);

			// Now, do the same thing using our AES implementation
			shsmCipherText.wipe();
			CPPUNIT_ASSERT(aes->encryptInit(&aesKey192, SymMode::CBC, IV));

			CPPUNIT_ASSERT(aes->encryptUpdate(plainText, OB));
			shsmCipherText += OB;

			CPPUNIT_ASSERT(aes->encryptFinal(OB));
			shsmCipherText += OB;

			CPPUNIT_ASSERT(shsmCipherText == cipherText);

			// Check that we can get the plain text
			shsmPlainText.wipe();
			CPPUNIT_ASSERT(aes->decryptInit(&aesKey192, SymMode::CBC, IV));

			CPPUNIT_ASSERT(aes->decryptUpdate(shsmCipherText, OB));
			shsmPlainText += OB;

			CPPUNIT_ASSERT(aes->decryptFinal(OB));
			shsmPlainText += OB;

			CPPUNIT_ASSERT(shsmPlainText == plainText);

			// Test 256-bit key
			cipherText = ByteString(testResult[i][j][2]);

			// Now, do the same thing using our AES implementation
			shsmCipherText.wipe();
			CPPUNIT_ASSERT(aes->encryptInit(&aesKey256, SymMode::CBC, IV));

			CPPUNIT_ASSERT(aes->encryptUpdate(plainText, OB));
			shsmCipherText += OB;

			CPPUNIT_ASSERT(aes->encryptFinal(OB));
			shsmCipherText += OB;

			CPPUNIT_ASSERT(shsmCipherText == cipherText);

			// Check that we can get the plain text
			shsmPlainText.wipe();
			CPPUNIT_ASSERT(aes->decryptInit(&aesKey256, SymMode::CBC, IV));

			CPPUNIT_ASSERT(aes->decryptUpdate(shsmCipherText, OB));
			shsmPlainText += OB;

			CPPUNIT_ASSERT(aes->decryptFinal(OB));
			shsmPlainText += OB;

			CPPUNIT_ASSERT(shsmPlainText == plainText);
		}
	}
}

void AESTests::testECB()
{
	char testKeys128[][33] =
	{
		"00000000000000000000000000000000",
		"0102030405060708090A0B0C0D0E0F10",
		"404142434445464748494A4B4C4D4E4F",
		"89436760984679018453504364534464",
		"49587346983643545706904580436731"
	};

	char testKeys192[][49] =
	{
		"000000000000000000000000000000000000000000000000",
		"0102030405060708090A0B0C0D0E0F101213141516171819",
		"404142434445464748494A4B4C4D4E4F5051525354555657",
		"096874395874290867409857496743857632098479834634",
		"439867439058743095864395348375043296845094854983"
	};

	char testKeys256[][65] =
	{
		"0000000000000000000000000000000000000000000000000000000000000000",
		"0102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F20",
		"404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F",
		"4394398576098257436095746985679043867498572406874967416846341641",
		"4369006859867098670492857409386741095643756930847023587048579014"
	};

	char testData[][256] =
	{
		"4938673409687134684698438657403986439058740935874395813968496846",
		"549813644389670948567490687546098245665626527788",
		"64398769586792586795867965624526",
		"468376458463264536"
	};

	char testResult[5][4][3][256] = {
		{
			{
				"6CAEC72F5E101C66550215ACAB6B874CD26479922B98D9839D7DA729B557ABA00143DB63EE66B0CDFF9F69917680151E",
				"E20E3123AC64FCA5536E0A2DC48DBEBC0E4E53BDA45FFC97C677951A891A6B7502BB292527E726FD51EB29894D6F0AAD",
				"C7910B1634DB493998608875A4652B205750B3B761DA7718E120C23A575F7D821F788FE6D86C317549697FBF0C07FA43"
			},
			{
				"8F48A65BF638FEDB7E6F59BAC8C110FE0E5E6370CBEFACFA0D7A5744030A481B",
				"125E1D93DC2C43A6FAFC508DB6F9A4A933738D14C219340D5F4D7203DEDCA7E1",
				"FACB8DEF1B476400DE9796D5058E90863A9A8C8BB2420B9A85BA3E8F87BB48F2"
			},
			{
				"C810E96482F109C9A05D2B1BEBAC79660143DB63EE66B0CDFF9F69917680151E",
				"2385391BB8F2DD97280B1FAEFACB6B5C02BB292527E726FD51EB29894D6F0AAD",
				"47549520EADA1A5D931EACCC922F88BA1F788FE6D86C317549697FBF0C07FA43"
			},
			{
				"A7D9EAE80224624188CAA7012140E946",
				"6ECD5C71ECA4AB9C3B71E91721CA2043",
				"2F77AA438E9259F268985668B00650E5"
			}
		},
		{
			{
				"8947CE273536C8A4D1E878F38371B9A8D2B3B45496779386CBA32CA70001D6AA6CC00A66D2AD83FFD76E9A2BCAD89A01",
				"B151340CFECADA3AE176637D0A78686E2063E1A602C85D03AE648BDF4FA57C36F7F1878D088644BD5FB43D3C0FE1C30C",
				"C19AE024C8F6B8E3383F675DF463512E273AAD7D0B88F22D5225EF09D2E37118D45D7C5AA26BCA9D6B1D5DDBF68F9EF6"
			},
			{
				"16C30BBAE7CDB2EE1E02275B79A064F6EE69FB37C8E039400435782F550CF86A",
				"F6C869D28D2D167C50BEE8F605D33021CB9173567B8B4AB3EEC68F0298324B78",
				"07DB563F7E31F1E670A02F97E8D120C7EE3FCEBBF2FDC2D37FC17D93ED1A778B"
			},
			{
				"52902B599686234833C4D420A9BF17FF6CC00A66D2AD83FFD76E9A2BCAD89A01",
				"B17FA9EA89D5578A844B3D82891330B1F7F1878D088644BD5FB43D3C0FE1C30C",
				"74BC55BE85291E0D1FA4A4444051CF65D45D7C5AA26BCA9D6B1D5DDBF68F9EF6"
			},
			{
				"3F00CAAC6FA432A7C1826CA4DA7C55D6",
				"9C2DBF449FF2C4AC1CFD7C43D200D33A",
				"E2183AB600A986806D86ADA4EE38E562"
			}
		},
		{
			{
				"23741EF993CBA04E5C67B42A16CA4D100BA6DF745E6D90818500DEC1CFC9811DBD3ACBFC853ED5DE825266C3B1883EC4",
				"F14D0EB7DFDB9B8960B0E47D7F4828E8756C38BA83655AAC466986ECB229A66FA390265A4BF5F50A8DFFAD253701E418",
				"0AAE579A796C94AF4FFB9D7C71381CB5E68E15465F30D7085A72D0CCEC7030BBC9CB7B3859E1A550BCBF11B624022C56"
			},
			{
				"AFCD6801459845C88548CC337BDD4D8B87E81D9D6AC945E14E3C4E0AC976A4B9",
				"117129A4775FC84E703F2F2C54B1B55DC4A79241F6CB0A37A8D551D71983D944",
				"1128250DA7C9A1BBE6A61AC01F28D4D9E3027C3625BD5514AE5DFE4B9132DAFA"
			},
			{
				"B275BDAF14AE286643C533258343F822BD3ACBFC853ED5DE825266C3B1883EC4",
				"93ACFCCFE2C4736B6492A673A59DACE2A390265A4BF5F50A8DFFAD253701E418",
				"2C2165E6491662A855FD7A20CDFF23BDC9CB7B3859E1A550BCBF11B624022C56"
			},
			{
				"30BBF52D760BAEA653FD03E5E84E583A",
				"F5F55DF3FC4D9CF2A2829BACA774A51A",
				"7EE196D148C11FA4998A90C6C7932395"
			}
		},
		{
			{
				"44C2B3344B002BB7A6994E1C74CC7BA70CE55BF44FD96506B553F0EFD3FE02B28329D59D480B0C1714A0DC60EB9FA8CE",
				"568C7627FD2519BE6031F052DE8F680860F7680460E92A524EA912174BE17B1337D593DEF15FB5BA64F03D1AAE276775",
				"99E36C0097BCFE41945C064EFA476FF4AA6048F909BEDE32A649F1035A2FB83CD601D09C3FDB36BC61B8CDE5BDD73804"
			},
			{
				"D748E8E93D29775BD8831E3BC1E1ABF75F484C7CC693521A66A5AB1637822E40",
				"010103778E123E5140F8D0356DA831E1587DB7E416AE9FAD14C6E2F78DC83148",
				"A8B8926E8FB762A1AB8CD9FA08507D77872C8EAAAFF3527572F49497B8B366C9"
			},
			{
				"CFF3212C7E94C2DD65EC1CDC998D6C4B8329D59D480B0C1714A0DC60EB9FA8CE",
				"324D16FEEC9DCA75A80F4B80175F8A7537D593DEF15FB5BA64F03D1AAE276775",
				"850567F4F0200CFBF88F1A6D35CAF6D9D601D09C3FDB36BC61B8CDE5BDD73804"
			},
			{
				"417F142D7609AE701B3D263FFECE4502",
				"E0DC994D8DC01C4EB2ECD19AD120C3D1",
				"FB26CC4E48B40EAB755FF65164EFB406"
			}
		},
		{
			{
				"048AEE75741BC60D01B512A53FEE97238F294743E7A351FAF589DD9E040BB8AF0F59D8F60E9C700F10025B5E69828819",
				"67FB10E52640B1E060F3D7868524721AC375DC76628B0D79C5F40ADC653FC001B50C33356548289D3E70EB7FBC0E2B56",
				"31953FF249D7519D3C39FB21D70A41033286A320193CC938C5ACBBCA2B25340829799212E3CABACE0BFD4424427705AB"
			},
			{
				"8D8D50FA4619F0E1B821DCA4ACBDFD46AE92D76A0B95A0331D61C4A7032D9705",
				"10685E8F632AC41D92E3A0403BB20C79868BD6F94691226EC54D7220C45E7233",
				"C5FF99FD1BC2BFDBEA62894B279DE6CBF51CCD00362A557DB9D9102DAF623A50"
			},
			{
				"0330B8FF58E4E6E956B4F81F7A4770200F59D8F60E9C700F10025B5E69828819",
				"C79BABE5B34B305B05E38013DC5568F7B50C33356548289D3E70EB7FBC0E2B56",
				"98BEE460FF803288C898A900DD08CE2529799212E3CABACE0BFD4424427705AB"
			},
			{
				"9A4FD3A26DD0D3A12F224E5E7A06EB76",
				"B86FE6F088C3A6497F21BCB29DB703D1",
				"313CC604B301DACA48CDB6F405AA7938"
			}
		}
	};

	char testIV[][33] =
	{
		"00000000000000000000000000000000",
		"0102030405060708090A0B0C0D0E0F10",
		"404142434445464748494A4B4C4D4E4F",
		"69836472094875029486750948672066",
		"48670943876904867104398574908554"
	};

	for (int i = 0; i < 5; i++)
	{
		ByteString keyData128(testKeys128[i]);
		ByteString keyData192(testKeys192[i]);
		ByteString keyData256(testKeys256[i]);

		AESKey aesKey128(128);
		CPPUNIT_ASSERT(aesKey128.setKeyBits(keyData128));
		AESKey aesKey192(192);
		CPPUNIT_ASSERT(aesKey192.setKeyBits(keyData192));
		AESKey aesKey256(256);
		CPPUNIT_ASSERT(aesKey256.setKeyBits(keyData256));

		ByteString IV(testIV[i]);

		for (int j = 0; j < 4; j++)
		{
			ByteString plainText(testData[j]), shsmPlainText;
			ByteString cipherText;
			ByteString shsmCipherText, OB;

			// Test 128-bit key

			// Get the reference for the encrypted data
			cipherText = ByteString(testResult[i][j][0]);

			// Now, do the same thing using our AES implementation
			shsmCipherText.wipe();
			CPPUNIT_ASSERT(aes->encryptInit(&aesKey128, SymMode::ECB, IV));

			CPPUNIT_ASSERT(aes->encryptUpdate(plainText, OB));
			shsmCipherText += OB;

			CPPUNIT_ASSERT(aes->encryptFinal(OB));
			shsmCipherText += OB;

			CPPUNIT_ASSERT(shsmCipherText == cipherText);

			// Check that we can get the plain text
			shsmPlainText.wipe();
			CPPUNIT_ASSERT(aes->decryptInit(&aesKey128, SymMode::ECB, IV));

			CPPUNIT_ASSERT(aes->decryptUpdate(shsmCipherText, OB));
			shsmPlainText += OB;

			CPPUNIT_ASSERT(aes->decryptFinal(OB));
			shsmPlainText += OB;

			CPPUNIT_ASSERT(shsmPlainText == plainText);

			// Test 192-bit key
			cipherText = ByteString(testResult[i][j][1]);

			// Now, do the same thing using our AES implementation
			shsmCipherText.wipe();
			CPPUNIT_ASSERT(aes->encryptInit(&aesKey192, SymMode::ECB, IV));

			CPPUNIT_ASSERT(aes->encryptUpdate(plainText, OB));
			shsmCipherText += OB;

			CPPUNIT_ASSERT(aes->encryptFinal(OB));
			shsmCipherText += OB;

			CPPUNIT_ASSERT(shsmCipherText == cipherText);

			// Check that we can get the plain text
			shsmPlainText.wipe();
			CPPUNIT_ASSERT(aes->decryptInit(&aesKey192, SymMode::ECB, IV));

			CPPUNIT_ASSERT(aes->decryptUpdate(shsmCipherText, OB));
			shsmPlainText += OB;

			CPPUNIT_ASSERT(aes->decryptFinal(OB));
			shsmPlainText += OB;

			CPPUNIT_ASSERT(shsmPlainText == plainText);

			// Test 256-bit key
			cipherText = ByteString(testResult[i][j][2]);

			// Now, do the same thing using our AES implementation
			shsmCipherText.wipe();
			CPPUNIT_ASSERT(aes->encryptInit(&aesKey256, SymMode::ECB, IV));

			CPPUNIT_ASSERT(aes->encryptUpdate(plainText, OB));
			shsmCipherText += OB;

			CPPUNIT_ASSERT(aes->encryptFinal(OB));
			shsmCipherText += OB;

			CPPUNIT_ASSERT(shsmCipherText == cipherText);

			// Check that we can get the plain text
			shsmPlainText.wipe();
			CPPUNIT_ASSERT(aes->decryptInit(&aesKey256, SymMode::ECB, IV));

			CPPUNIT_ASSERT(aes->decryptUpdate(shsmCipherText, OB));
			shsmPlainText += OB;

			CPPUNIT_ASSERT(aes->decryptFinal(OB));
			shsmPlainText += OB;

			CPPUNIT_ASSERT(shsmPlainText == plainText);
		}
	}
}

void AESTests::testWrap(const char testKeK[][128], const char testKey[][128], const char testCt[][128], const int testCnt, SymWrap::Type mode)
{
	for (int i = 0; i < testCnt; i++)
	{
		ByteString kekData(testKeK[i]);
		ByteString keyData(testKey[i]);

		AESKey aesKeK(kekData.size() * 8);
		CPPUNIT_ASSERT(aesKeK.setKeyBits(kekData));

		ByteString wrapped;
		ByteString expectedCt(testCt[i]);
		CPPUNIT_ASSERT(aes->wrapKey(&aesKeK, mode, keyData, wrapped));
		CPPUNIT_ASSERT(wrapped.size() == expectedCt.size());
		CPPUNIT_ASSERT(wrapped == expectedCt);

		ByteString unwrapped;
		CPPUNIT_ASSERT(aes->unwrapKey(&aesKeK, mode, wrapped, unwrapped));
		CPPUNIT_ASSERT(unwrapped.size() == keyData.size());
		CPPUNIT_ASSERT(unwrapped == keyData);
/*
	#ifdef HAVE_AES_KEY_WRAP_PAD
		keyData.resize(20);
		ByteString padwrapped;
		CPPUNIT_ASSERT(aes->wrapKey(&aesKeK, SymWrap::AES_KEYWRAP_PAD, keyData, padwrapped));
		CPPUNIT_ASSERT(padwrapped.size() == 32);

		ByteString padunwrapped;
		CPPUNIT_ASSERT(aes->unwrapKey(&aesKeK, SymWrap::AES_KEYWRAP_PAD, padwrapped, padunwrapped));
		CPPUNIT_ASSERT(padunwrapped == keyData);
	#endif
*/
	}
}

// RFC 3394 tests
void AESTests::testWrapWoPad()
{
	char testKeK[][128] = {
		"000102030405060708090A0B0C0D0E0F", // section 4.1
		"000102030405060708090A0B0C0D0E0F1011121314151617", // section 4.2
		"000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F", // section 4.3
		"000102030405060708090A0B0C0D0E0F1011121314151617", // section 4.4
		"000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F", // section 4.5
		"000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F", // section 4.6
	};
	char testKey[][128] = {
		"00112233445566778899AABBCCDDEEFF",
		"00112233445566778899AABBCCDDEEFF",
		"00112233445566778899AABBCCDDEEFF",
		"00112233445566778899AABBCCDDEEFF0001020304050607",
		"00112233445566778899AABBCCDDEEFF0001020304050607",
		"00112233445566778899AABBCCDDEEFF000102030405060708090A0B0C0D0E0F"
	};
	char testCt[][128] = {
		"1FA68B0A8112B447AEF34BD8FB5A7B829D3E862371D2CFE5",
		"96778B25AE6CA435F92B5B97C050AED2468AB8A17AD84E5D",
		"64E8C3F9CE0F5BA263E9777905818A2A93C8191E7D6E8AE7",
		"031D33264E15D33268F24EC260743EDCE1C6C7DDEE725A936BA814915C6762D2",
		"A8F9BC1612C68B3FF6E6F4FBE30E71E4769C8B80A32CB8958CD5D17D6B254DA1",
		"28C9F404C4B810F4CBCCB35CFB87F8263F5786E2D80ED326CBC7F0E71A99F43BFB988B9B7A02DD21"
	};

	testWrap(testKeK, testKey, testCt, sizeof(testKeK) / 128, SymWrap::AES_KEYWRAP);
}

// RFC 5649 tests
void AESTests::testWrapPad()
{
	char testKeK[][128] = {
		"5840DF6E29B02AF1AB493B705BF16EA1AE8338F4DCC176A8", // section 6 example 1
		"5840DF6E29B02AF1AB493B705BF16EA1AE8338F4DCC176A8", // section 6 example 2
	};
	char testKey[][128] = {
		"C37B7E6492584340BED12207808941155068F738",
		"466F7250617369"
	};
	char testCt[][128] = {
		"138BDEAA9B8FA7FC61F97742E72248EE5AE6AE5360D1AE6A5F54F373FA543B6A",
		"AFBEB0F07DFBF5419200F2CCB50BB24F"
	};

	testWrap(testKeK, testKey, testCt, sizeof(testKeK) / 128, SymWrap::AES_KEYWRAP_PAD);
}
