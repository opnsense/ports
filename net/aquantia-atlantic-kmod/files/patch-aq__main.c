--- aq_main.c.orig	2019-09-24 14:45:34 UTC
+++ aq_main.c
@@ -193,8 +193,12 @@ static driver_t aq_driver = {
 	"aq", aq_methods, sizeof(struct aq_dev),
 };
 
+#if __FreeBSD_version >= 1400058
+DRIVER_MODULE(atlantic, pci, aq_driver, 0, 0);
+#else
 static devclass_t aq_devclass;
 DRIVER_MODULE(atlantic, pci, aq_driver, aq_devclass, 0, 0);
+#endif
 
 MODULE_DEPEND(atlantic, pci, 1, 1, 1);
 MODULE_DEPEND(atlantic, ether, 1, 1, 1);
--- aq_main.orig	2025-10-04 07:50:15.419816000 +0200
+++ aq_main.c	2025-10-04 08:37:40.357656000 +0200
@@ -101,7 +101,12 @@
 #define AQ_DEVICE_ID_AQC109	0x09B1
 #define AQ_DEVICE_ID_AQC111	0x11B1
 #define AQ_DEVICE_ID_AQC112	0x12B1
+#define AQ_DEVICE_ID_AQC113	0x04c0
 
+#define AQ_DEVICE_ID_AQC113C	0x14c0
+#define AQ_DEVICE_ID_AQC113CA	0x34c0
+#define AQ_DEVICE_ID_AQC113CS	0x94c0
+
 #define AQ_DEVICE_ID_AQC100S	0x80B1
 #define AQ_DEVICE_ID_AQC107S	0x87B1
 #define AQ_DEVICE_ID_AQC108S	0x88B1
@@ -130,6 +135,11 @@
 	PVID(AQUANTIA_VENDOR_ID, AQ_DEVICE_ID_AQC111S, "Aquantia AQtion 5Gbit Network Adapter"),
 	PVID(AQUANTIA_VENDOR_ID, AQ_DEVICE_ID_AQC112S, "Aquantia AQtion 2.5Gbit Network Adapter"),
 
+	PVID(AQUANTIA_VENDOR_ID, AQ_DEVICE_ID_AQC113, "Aquantia AQtion 10Gbit Network Adapter"),
+	PVID(AQUANTIA_VENDOR_ID, AQ_DEVICE_ID_AQC113C, "Aquantia AQtion 10Gbit Network Adapter"),
+	PVID(AQUANTIA_VENDOR_ID, AQ_DEVICE_ID_AQC113CA, "Aquantia AQtion 10Gbit Network Adapter"),
+	PVID(AQUANTIA_VENDOR_ID, AQ_DEVICE_ID_AQC113CS, "Aquantia AQtion 10Gbit Network Adapter"),
+
 	PVID_END
 };
 
@@ -1097,6 +1107,14 @@
 	case AQ_DEVICE_ID_AQC112S:
 		softc->media_type = AQ_MEDIA_TYPE_TP;
 		softc->link_speeds = AQ_LINK_ALL & ~(AQ_LINK_10G | AQ_LINK_5G);
+		break;
+
+	case AQ_DEVICE_ID_AQC113:
+	case AQ_DEVICE_ID_AQC113C:
+	case AQ_DEVICE_ID_AQC113CA:
+	case AQ_DEVICE_ID_AQC113CS:
+		softc->media_type = AQ_MEDIA_TYPE_TP;
+		softc->link_speeds = AQ_LINK_ALL;
 		break;
 
 	default:
