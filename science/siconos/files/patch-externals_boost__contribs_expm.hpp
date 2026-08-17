-- fix compilation on 16

--- externals/boost_contribs/expm.hpp.orig	2026-07-18 15:56:44 UTC
+++ externals/boost_contribs/expm.hpp
@@ -68,7 +68,7 @@ template<typename MATRIX> MATRIX expm_pad(const MATRIX
 	{
 		real_value_type temp = 0.0;
 		for(size_type j=0;j<n;j++)
-			temp += std::abs<real_value_type>(H(i,j)); // Correct me, if H is complex, can I use that abs?
+			temp += std::abs(H(i,j)); // Correct me, if H is complex, can I use that abs?
 		norm = std::max<real_value_type>(norm, temp);
 	}
 	if (norm == 0.0) 
