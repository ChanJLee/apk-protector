package com.shanbay.yasc;

import android.util.Base64;

import java.io.UnsupportedEncodingException;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

public class SecurityToken {
    private static byte[] iv;
    private SecretKeySpec secretKeySpec;
    private Cipher cipher;

    public SecurityToken(String secretKey) throws UnsupportedEncodingException, NoSuchPaddingException,
			NoSuchAlgorithmException, InvalidKeyException, InvalidAlgorithmParameterException {
        secretKeySpec = new SecretKeySpec(secretKey.getBytes("UTF-8"), "AES");
        cipher = Cipher.getInstance("AES/CBC/PKCS7PADDING");
    }

    public String encrypt(String toBeEncrypt) throws NoSuchPaddingException, NoSuchAlgorithmException,
			InvalidAlgorithmParameterException, InvalidKeyException, BadPaddingException, IllegalBlockSizeException {
        cipher.init(Cipher.ENCRYPT_MODE, secretKeySpec);
        byte[] encrypted = cipher.doFinal(toBeEncrypt.getBytes());
        return Base64.encodeToString(encrypted, Base64.NO_WRAP);
    }

    public String decrypt(String encrypted, String ivStr) throws InvalidAlgorithmParameterException, InvalidKeyException,
			BadPaddingException, IllegalBlockSizeException {
        iv = Base64.decode(ivStr, Base64.DEFAULT);
        IvParameterSpec ivParameterSpec = new IvParameterSpec(iv);
        cipher.init(Cipher.DECRYPT_MODE, secretKeySpec, ivParameterSpec);
        byte[] decryptedBytes = cipher.doFinal(Base64.decode(encrypted, Base64.DEFAULT));
        return new String(decryptedBytes);
    }

    public String getIv() throws UnsupportedEncodingException {
        iv = cipher.getIV();
        return Base64.encodeToString(iv, Base64.NO_WRAP); // Base64.No_WRAP will not add new line
    }
}