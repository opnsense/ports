--- src/3rdParty/salomesmesh/src/DriverSTL/DriverSTL_R_SMDS_Mesh.cpp.orig	2026-07-01 15:13:02 UTC
+++ src/3rdParty/salomesmesh/src/DriverSTL/DriverSTL_R_SMDS_Mesh.cpp
@@ -44,17 +44,17 @@ namespace
     {
       union
       {
-        Standard_Real    R[3];
-        Standard_Integer I[6];
+        double    R[3];
+        int I[6];
       } U;
 
       point.Coord( U.R[0], U.R[1], U.R[2] );
-      return std::hash<Standard_Integer>{}(U.I[0]/23+U.I[1]/19+U.I[2]/17+U.I[3]/13+U.I[4]/11+U.I[5]/7);
+      return std::hash<int>{}(U.I[0]/23+U.I[1]/19+U.I[2]/17+U.I[3]/13+U.I[4]/11+U.I[5]/7);
     }
 
     size_t operator()(const gp_Pnt& point1, const gp_Pnt& point2) const noexcept
     {
-      static Standard_Real tab1[3], tab2[3];
+      static double tab1[3], tab2[3];
       point1.Coord(tab1[0],tab1[1],tab1[2]);
       point2.Coord(tab2[0],tab2[1],tab2[2]);
       return (memcmp(tab1,tab2,sizeof(tab1)) == 0);
@@ -64,27 +64,27 @@ namespace
     //function : HashCode
     //purpose  :
     //=======================================================================
-    inline static Standard_Integer HashCode
-    (const gp_Pnt& point,  Standard_Integer Upper)
+    inline static int HashCode
+    (const gp_Pnt& point,  int Upper)
     {
       union
       {
-        Standard_Real    R[3];
-        Standard_Integer I[6];
+        double    R[3];
+        int I[6];
       } U;
 
       point.Coord( U.R[0], U.R[1], U.R[2] );
-      return std::hash<Standard_Integer>{}(U.I[0]/23+U.I[1]/19+U.I[2]/17+U.I[3]/13+U.I[4]/11+U.I[5]/7);
+      return std::hash<int>{}(U.I[0]/23+U.I[1]/19+U.I[2]/17+U.I[3]/13+U.I[4]/11+U.I[5]/7);
     }
  
     //=======================================================================
     //function : IsEqual
     //purpose  :
     //=======================================================================
-    inline static Standard_Boolean IsEqual
+    inline static bool IsEqual
     (const gp_Pnt& point1, const gp_Pnt& point2)
     {
-      static Standard_Real tab1[3], tab2[3];
+      static double tab1[3], tab2[3];
       point1.Coord(tab1[0],tab1[1],tab1[2]);
       point2.Coord(tab2[0],tab2[1],tab2[2]);
       return (memcmp(tab1,tab2,sizeof(tab1)) == 0);
@@ -109,7 +109,7 @@ DriverSTL_R_SMDS_Mesh::DriverSTL_R_SMDS_Mesh()
 DriverSTL_R_SMDS_Mesh::DriverSTL_R_SMDS_Mesh()
 {
   myIsCreateFaces = true;
-  myIsAscii = Standard_True;
+  myIsAscii = true;
 }
 
 //=======================================================================
@@ -149,10 +149,10 @@ Driver_Mesh::Status DriverSTL_R_SMDS_Mesh::Perform()
   data += HEADER_SIZE;
 
   // we check 128 characters to detect if we have a non-ascii char
-  myIsAscii = Standard_True;
+  myIsAscii = true;
   for (int i = 0; i < 128; ++i, ++data) {
     if ( !isascii( *data ) && data < file.end() ) {
-      myIsAscii = Standard_False;
+      myIsAscii = false;
       break;
     }
   }
@@ -172,11 +172,11 @@ Driver_Mesh::Status DriverSTL_R_SMDS_Mesh::Perform()
 
 // static methods
 
-static Standard_Real readFloat(SMESH_File& theFile)
+static double readFloat(SMESH_File& theFile)
 {
   union {
-    Standard_Boolean i;
-    Standard_ShortReal f;
+    bool i;
+    float f;
   } u;
 
   const char* c = theFile;
@@ -208,7 +208,7 @@ static SMDS_MeshNode* readNode(FILE* file,
                                TDataMapOfPntNodePtr& uniqnodes,
                                SMDS_Mesh* theMesh)
 {
-  Standard_ShortReal coord[3];
+  float coord[3];
   // reading vertex
   fscanf(file,"%*s %f %f %f\n",&coord[0],&coord[1],&coord[2]);
 
@@ -245,7 +245,7 @@ Driver_Mesh::Status DriverSTL_R_SMDS_Mesh::readAscii(S
   FILE* file = fopen( myFile.c_str(),"r");
 
   // count the number of lines
-  Standard_Integer nbLines = 0;
+  int nbLines = 0;
   for (long ipos = 0; ipos < filesize; ++ipos) {
     if (getc(file) == '\n')
       nbLines++;
@@ -254,17 +254,17 @@ Driver_Mesh::Status DriverSTL_R_SMDS_Mesh::readAscii(S
   // go back to the beginning of the file
   rewind(file);
   
-  Standard_Integer nbTri = (nbLines / ASCII_LINES_PER_FACET);
+  int nbTri = (nbLines / ASCII_LINES_PER_FACET);
 
   TDataMapOfPntNodePtr uniqnodes;
   // skip header
   while (getc(file) != '\n');
 
   // main reading
-  for (Standard_Integer iTri = 0; iTri < nbTri; ++iTri) {
+  for (int iTri = 0; iTri < nbTri; ++iTri) {
 
     // skipping the facet normal
-    Standard_ShortReal normal[3];
+    float normal[3];
     fscanf(file,"%*s %*s %f %f %f\n",&normal[0],&normal[1],&normal[2]);
 
     // skip the keywords "outer loop"
@@ -306,19 +306,19 @@ Driver_Mesh::Status DriverSTL_R_SMDS_Mesh::readBinary(
   if ( (filesize - HEADER_SIZE) % SIZEOF_STL_FACET !=0 
       // Commented to allow reading small files (ex: 1 face)
       /*|| (filesize < STL_MIN_FILE_SIZE)*/) {
-    Standard_NoMoreObject::Raise("DriverSTL_R_SMDS_MESH::readBinary (wrong file size)");
+      throw Standard_NoMoreObject("DriverSTL_R_SMDS_MESH::readBinary (wrong file size)");
   }
 
   // don't trust the number of triangles which is coded in the file
   // sometimes it is wrong, and with this technique we don't need to swap endians for integer
-  Standard_Integer nbTri = ((filesize - HEADER_SIZE) / SIZEOF_STL_FACET);
+  int nbTri = ((filesize - HEADER_SIZE) / SIZEOF_STL_FACET);
 
   // skip the header
   file += HEADER_SIZE;
 
   TDataMapOfPntNodePtr uniqnodes;
   
-  for (Standard_Integer iTri = 0; iTri < nbTri; ++iTri) {
+  for (int iTri = 0; iTri < nbTri; ++iTri) {
 
     // ignore normals
     file += 3 * SIZE_OF_FLOAT;
