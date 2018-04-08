# Add project specific ProGuard rules here.
# You can control the set of applied configuration files using the
# proguardFiles setting in build.gradle.
#
# For more details, see
#   http://developer.android.com/guide/developing/tools/proguard.html

# If your project uses WebView with JS, uncomment the following
# and specify the fully qualified class name to the JavaScript interface
# class:
#-keepclassmembers class fqcn.of.javascript.interface.for.webview {
#   public *;
#}

# Uncomment this to preserve the line number information for
# debugging stack traces.
#-keepattributes SourceFile,LineNumberTable

# If you keep the line number information, uncomment this to
# hide the original source file name.
#-renamesourcefileattribute SourceFile

## Android基本混淆配置

-dontusemixedcaseclassnames
-dontskipnonpubliclibraryclasses
-dontskipnonpubliclibraryclassmembers
-dontoptimize
-dontpreverify

-verbose
-dump class_files.txt
-printseeds seeds.txt
-printusage unused.txt
-printmapping mapping.txt

-keepattributes Signature
-keepattributes *Annotation*

-keep public class com.google.vending.licensing.ILicensingService
-keep public class com.android.vending.licensing.ILicensingService

# adding this in to preserve line numbers so that the stack traces can be remapped
-renamesourcefileattribute SourceFile
-keepattributes SourceFile,LineNumberTable

-keepclasseswithmembernames class * {
    native <methods>;
}

-keepclassmembers public class * extends android.view.View {
   void set*(***);
   *** get*();
}

-keepclassmembers class * extends android.app.Activity {
   public void *(android.view.View);
}

-keepclassmembers enum * {
    <fields>;
    public static **[] values();
    public static ** valueOf(java.lang.String);
}

-keep class * implements android.os.Parcelable {
  public static final android.os.Parcelable$Creator *;
}

-keepclassmembers class **.R$* {
    public static <fields>;
}


-dontwarn android.support.**
-keep class android.support.v7.widget.SearchView { *;}


# ButterKnife 混淆配置
-keep class butterknife.** { *; }
-dontwarn butterknife.internal.**
-keep class **$$ViewBinder { *; }

-keepclasseswithmembernames class * {
    @butterknife.* <fields>;
}

-keepclasseswithmembernames class * {
    @butterknife.* <methods>;
}

# Retrofit 混淆配置
-dontwarn retrofit2.**
-keep class retrofit2.** { *; }
# aliyun 混淆配置
-dontwarn com.alibaba.**
-keep class com.alibaba.** { *; }

# Okhttp 混淆配置
-dontwarn com.squareup.okhttp3.**
-keep class com.squareup.okhttp3.** { *;}
-dontwarn okio.*

# ButterKnife 混淆配置
-keep class butterknife.** { *; }
-dontwarn butterknife.internal.**
-keep class **$$ViewBinder { *; }
-keepclasseswithmembernames class * {
    @butterknife.* <fields>;
}
-keepclasseswithmembernames class * {
    @butterknife.* <methods>;
}


# Retrofit 混淆配置
-dontwarn retrofit2.**
-keep class retrofit2.** { *; }
-keep class com.squareup.** { *; }
-keep interface com.squareup.** { *; }
-keepclasseswithmembers class * {
    @retrofit2.http.* <methods>;
}


# rxjava
-keepclassmembers class rx.internal.util.unsafe.*ArrayQueue*Field* {
    long producerIndex;
    long consumerIndex;
}
-keepclassmembers class rx.internal.util.unsafe.BaseLinkedQueueProducerNodeRef {
    rx.internal.util.atomic.LinkedQueueNode producerNode;
}
-keepclassmembers class rx.internal.util.unsafe.BaseLinkedQueueConsumerNodeRef {
    rx.internal.util.atomic.LinkedQueueNode consumerNode;
}


# Okhttp 混淆配置
-dontwarn com.squareup.okhttp3.**
-keep class com.squareup.okhttp3.** { *;}
-dontwarn okio.*

# 其他一些第三方库混淆配置
-dontwarn com.jcraft.jzlib.**
-keep class com.jcraft.jzlib.**  { *;}

-dontwarn sun.misc.**
-keep class sun.misc.** { *;}

-dontwarn com.alibaba.fastjson.**
-keep class com.alibaba.fastjson.** { *;}


-dontwarn sun.security.**
-keep class sun.security.** { *; }

-dontwarn com.google.**
-keep class com.google.** { *;}

-keep public class android.net.http.SslError
-dontwarn android.net.http.SslError

-keep public class android.webkit.WebViewClient
-dontwarn android.webkit.WebViewClient

-dontwarn android.webkit.WebView
-dontwarn android.support.**

-dontwarn org.apache.**
-keep class org.apache.** { *;}

-dontwarn org.jivesoftware.smack.**
-keep class org.jivesoftware.smack.** { *;}

-dontwarn com.loopj.**
-keep class com.loopj.** { *;}

-dontwarn org.xbill.**
-keep class org.xbill.** { *;}

-dontwarn org.java_websocket.**
-keep class org.java_websocket.** { *;}

# 支付宝
-keep class com.alipay.android.app.IAlixPay{*;}
-keep class com.alipay.android.app.IAlixPay$Stub{*;}
-keep class com.alipay.android.app.IRemoteServiceCallback{*;}
-keep class com.alipay.android.app.IRemoteServiceCallback$Stub{*;}
-keep class com.alipay.sdk.app.PayTask{ public *;}
-keep class com.alipay.sdk.app.AuthTask{ public *;}
-keep class com.alipay.sdk.app.H5PayCallback {
    <fields>;
    <methods>;
}
-keep class com.alipay.android.phone.mrpc.core.** { *; }
-keep class com.alipay.apmobilesecuritysdk.** { *; }
-keep class com.alipay.mobile.framework.service.annotation.** { *; }
-keep class com.alipay.mobilesecuritysdk.face.** { *; }
-keep class com.alipay.tscenter.biz.rpc.** { *; }
-keep class org.json.alipay.** { *; }
-keep class com.alipay.tscenter.** { *; }
-keep class com.ta.utdid2.** { *;}
-keep class com.ut.device.** { *;}

# Gson混淆配置
-keep class sun.misc.Unsafe { *; }
-keep class com.google.renamedgson.stream.** { *; }
-keep class com.google.renamedgson.examples.android.model.** { *; }

# 其他第三方库混淆配置
-keep class com.nineoldandroids.** { *; }
-keep class com.joshdholtz.** { *; }
-keep class org.jsoup.**  { *; }
-keep class org.yaml.snakeyaml.**  { *; }
-keep class net.lingala.zip4j.**  { *; }
-keep class org.markdown4j.**  { *; }
-keep class com.github.rjeschke.txtmark.**  { *; }
-keep public class * implements com.bumptech.glide.module.GlideModule
-keep public enum com.bumptech.glide.load.resource.bitmap.ImageHeaderParser$** {
    **[] $VALUES;
    public *;
}

# EventBus混淆
-keepclassmembers class ** {
    public void onEvent*(**);
}


# 扇贝混淆配置
-dontwarn com.shanbay.ProgressBar.Compat$CompatV16
-keep class com.shanbay.fairies.common.http.** { *; }
-keep @com.shanbay.fairies.common.http.converts.gson.GsonNamingPolicy interface * {
    *;
}

-dontwarn com.shanbay.speechengine.**
-keep class com.shanbay.speechengine.** { *; }

-keepattributes JavascriptInterface

# yasc 混淆配置

-dontwarn com.shanbay.yasc.**
-keep class com.shanbay.yasc.** { *; }

-keep class android.support.** {*;}

#手动启用support keep注解
-dontskipnonpubliclibraryclassmembers
-printconfiguration
-keep,allowobfuscation @interface android.support.annotation.Keep
-keep @android.support.annotation.Keep class *
-keepclassmembers class * {
    @android.support.annotation.Keep *;
}

# bugly
-dontwarn com.tencent.bugly.**
-keep public class com.tencent.bugly.**{*;}
-keep class android.support.**{*;}

-keep class com.tencent.stat.** {*;}
-keep class com.tencent.mid.** {*;}