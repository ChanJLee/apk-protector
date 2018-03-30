package com.shanbay.yasc;

import android.content.Context;

import java.lang.reflect.Method;

/**
 * Common functions used for detection of system fingerprints.
 * 
 * @author tstrazzere
 */
public class Utilities {

    /**
     * Method to reflectively invoke the SystemProperties.get command - which is the equivalent to the adb shell getProp
     * command.
     * 
     * @param context
     *            A {@link Context} object used to get the proper ClassLoader (just needs to be Application Context
     *            object)
     * @param property
     *            A {@code String} object for the property to retrieve.
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
}
