package com.shanbay.yasc;

import android.content.Context;

/**
 * Created by caspar on 6/23/16.
 * YASC = Yet Another Security Checker
 */
public class Yasc {
	static {
		System.loadLibrary("yasc");
	}

	public static native String getP(Context context);

	public static native String getMd5(String mStr);
}
