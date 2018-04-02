package com.shanbay.fairy.yasc;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.TextUtils;
import android.util.Log;
import android.widget.TextView;

import com.shanbay.yasc.DebugChecker;
import com.shanbay.yasc.EmulatorChecker;
import com.shanbay.yasc.SecurityToken;
import com.shanbay.yasc.Yasc;

import java.security.MessageDigest;

public class MainActivity extends AppCompatActivity {

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);


		Context context = getApplicationContext();

		TextView result = (TextView) findViewById(R.id.result);
		String TAG = "YARC";

		// 1. Debugger and Emulator Check
		Boolean isDebugged = DebugChecker.isDebugged();
		Boolean isEmulator = EmulatorChecker.isQEmuEnvDetected(context);
		String strDebugged = "Is Debugged ==> " + isDebugged.toString();
		String strEmultor = "Is Emulator ==> " + isEmulator.toString();
		result.setText(strDebugged + "\n" + strEmultor);


		// 3. Robot Check
		String token1 = "xP9cAXdvlmVnTtWDtCyXyjv8EZQhS/XccZQQ"; // token1 in document
		try {
			String packageName = Yasc.getP(context);
			Log.d(TAG, packageName);
			String packageMd5 = Yasc.getMd5(packageName);
			Log.d(TAG, packageMd5);
			SecurityToken encode = new SecurityToken(packageMd5);
			String token2 = encode.encrypt(token1);
			Log.d(TAG, token2);
			String iv = encode.getIv();
			Log.d(TAG, iv);
			String apiStr = "a:" + packageName + ":" + iv + ":" + token2;
			Log.d(TAG, apiStr);
			String decryptedStr = encode.decrypt(token2, iv);
			Log.d(TAG, decryptedStr);

		} catch (Exception e) {
			e.printStackTrace();
		}

		Intent intent = new Intent(this, MyService.class);
		startService(intent);
	}

	public static String encryptionMD5(byte[] byteStr) {
		MessageDigest messageDigest = null;
		StringBuffer md5StrBuff = new StringBuffer();
		try {
			messageDigest = MessageDigest.getInstance("MD5");
			messageDigest.reset();
			messageDigest.update(byteStr);
			byte[] byteArray = messageDigest.digest();
			for (int i = 0; i < byteArray.length; i++) {
				if (Integer.toHexString(0xFF & byteArray[i]).length() == 1) {
					md5StrBuff.append("0").append(Integer.toHexString(0xFF & byteArray[i]));
				} else {
					md5StrBuff.append(Integer.toHexString(0xFF & byteArray[i]));
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return md5StrBuff.toString();
	}

	public static String getMD5(String input) {
		if (TextUtils.isEmpty(input)) {
			return null;
		}

		try {
			MessageDigest messageDigest = MessageDigest.getInstance("MD5");
			messageDigest.reset();
			messageDigest.update(input.getBytes());
			byte[] digest = messageDigest.digest();
			StringBuilder hexString = new StringBuilder();
			for (byte bit : digest) {
				String hex = Integer.toHexString(0xff & bit);
				if (hex.length() == 1) {
					hexString.append('0');
				}
				hexString.append(hex);
			}

			return hexString.toString();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}
}
