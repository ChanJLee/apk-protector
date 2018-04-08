package com.shanbay.yasc;

import android.content.Context;
import android.support.annotation.Keep;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Method;

/**
 * Common functions used for detection of system fingerprints.
 *
 * @author tstrazzere
 */
@Keep
public class Utilities {

	/**
	 * Method to reflectively invoke the SystemProperties.get command - which is the equivalent to the adb shell getProp
	 * command.
	 *
	 * @param context  A {@link Context} object used to get the proper ClassLoader (just needs to be Application Context
	 *                 object)
	 * @param property A {@code String} object for the property to retrieve.
	 * @return {@code String} value of the property requested.
	 */
	public static String getProp(Context context, String property) {
		try {
			ClassLoader classLoader = context.getClassLoader();
			Class<?> systemProperties = classLoader.loadClass("android.os.SystemProperties");

			Method get = systemProperties.getMethod("get", String.class);

			Object[] params = new Object[1];
			params[0] = new String(property);

			return (String) get.invoke(systemProperties, params);
		} catch (IllegalArgumentException iAE) {
			throw iAE;
		} catch (Exception exception) {
			throw null;
		}
	}

	public static void writeAll(Context context, String src, String dest) {
		InputStream inputStream = null;
		FileOutputStream outputStream = null;
		try {
			inputStream = context.getAssets().open(src);
			outputStream = new FileOutputStream(dest);
			byte[] bytes = new byte[128];
			int len = -1;
			while ((len = inputStream.read(bytes)) != -1) {
				outputStream.write(bytes, 0, len);
			}
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (inputStream != null) {
				try {
					inputStream.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}

			if (outputStream != null) {
				try {
					outputStream.flush();
					outputStream.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
	}
}
