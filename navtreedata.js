/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "FrankEngine", "index.html", [
    [ "Bullet Documentation", "index.html", [
      [ "Introduction", "index.html#intro_sec", null ],
      [ "Installation", "index.html#install_sec", [
        [ "Step 1: Download", "index.html#step1", null ],
        [ "Step 2: Building", "index.html#step2", null ],
        [ "Step 3: Testing demos", "index.html#step3", null ],
        [ "Step 4: Integrating in your application, full Rigid Body and Soft Body simulation", "index.html#step4", null ],
        [ "Step 5 : Integrate the Collision Detection Library (without Dynamics and other Extras)", "index.html#step5", null ],
        [ "Step 6 : Use Snippets like the GJK Closest Point calculation.", "index.html#step6", null ]
      ] ],
      [ "Copyright", "index.html#copyright", null ]
    ] ],
    [ "manual", "md_include_glm_manual.html", [
      [ "GLM 0.9.9 Manual", "md_include_glm_manual.html#autotoc_md0", [
        [ "Table of Contents", "md_include_glm_manual.html#autotoc_md2", null ],
        [ "<a name=\"section0\"></a> Licenses", "md_include_glm_manual.html#autotoc_md4", [
          [ "The Happy Bunny License (Modified MIT License)", "md_include_glm_manual.html#autotoc_md5", null ],
          [ "The MIT License", "md_include_glm_manual.html#autotoc_md6", null ]
        ] ],
        [ "<a name=\"section1\"></a> 1. Getting started", "md_include_glm_manual.html#autotoc_md8", [
          [ "<a name=\"section1_1\"></a> 1.1. Using global headers", "md_include_glm_manual.html#autotoc_md9", null ],
          [ "<a name=\"section1_2\"></a> 1.2. Using separated headers", "md_include_glm_manual.html#autotoc_md10", null ],
          [ "<a name=\"section1_3\"></a> 1.3. Using extension headers", "md_include_glm_manual.html#autotoc_md11", null ],
          [ "<a name=\"section1_4\"></a> 1.4. Dependencies", "md_include_glm_manual.html#autotoc_md12", null ],
          [ "<a name=\"section1_5\"></a> 1.5. Finding GLM with CMake", "md_include_glm_manual.html#autotoc_md13", null ]
        ] ],
        [ "<a name=\"section2\"></a> 2. Preprocessor configurations", "md_include_glm_manual.html#autotoc_md15", [
          [ "<a name=\"section2_1\"></a> 2.1. GLM_FORCE_MESSAGES: Platform auto detection and default configuration", "md_include_glm_manual.html#autotoc_md16", null ],
          [ "<a name=\"section2_2\"></a> 2.2. GLM_FORCE_PLATFORM_UNKNOWN: Force GLM to no detect the build platform", "md_include_glm_manual.html#autotoc_md17", null ],
          [ "<a name=\"section2_3\"></a> 2.3. GLM_FORCE_COMPILER_UNKNOWN: Force GLM to no detect the C++ compiler", "md_include_glm_manual.html#autotoc_md18", null ],
          [ "<a name=\"section2_4\"></a> 2.4. GLM_FORCE_ARCH_UNKNOWN: Force GLM to no detect the build architecture", "md_include_glm_manual.html#autotoc_md19", null ],
          [ "<a name=\"section2_5\"></a> 2.5. GLM_FORCE_CXX_UNKNOWN: Force GLM to no detect the C++ standard", "md_include_glm_manual.html#autotoc_md20", null ],
          [ "<a name=\"section2_6\"></a> 2.6. GLM_FORCE_CXX**: C++ language detection", "md_include_glm_manual.html#autotoc_md21", null ],
          [ "<a name=\"section2_7\"></a> 2.7. GLM_FORCE_EXPLICIT_CTOR: Requiring explicit conversions", "md_include_glm_manual.html#autotoc_md22", null ],
          [ "<a name=\"section2_8\"></a> 2.8. GLM_FORCE_INLINE: Force inline", "md_include_glm_manual.html#autotoc_md23", null ],
          [ "<a name=\"section2_9\"></a> 2.9. GLM_FORCE_ALIGNED_GENTYPES: Force GLM to enable aligned types", "md_include_glm_manual.html#autotoc_md24", null ],
          [ "<a name=\"section2_10\"></a> 2.10. GLM_FORCE_DEFAULT_ALIGNED_GENTYPES: Force GLM to use aligned types by default", "md_include_glm_manual.html#autotoc_md25", null ],
          [ "<a name=\"section2_11\"></a> 2.11. GLM_FORCE_INTRINSICS: Using SIMD optimizations", "md_include_glm_manual.html#autotoc_md26", null ],
          [ "<a name=\"section2_12\"></a> 2.12. GLM_FORCE_PRECISION_**: Default precision", "md_include_glm_manual.html#autotoc_md27", null ],
          [ "<a name=\"section2_13\"></a> 2.13. GLM_FORCE_SINGLE_ONLY: Removed explicit 64-bits floating point types", "md_include_glm_manual.html#autotoc_md28", null ],
          [ "<a name=\"section2_14\"></a> 2.14. GLM_FORCE_SWIZZLE: Enable swizzle operators", "md_include_glm_manual.html#autotoc_md29", [
            [ "2.14.1. Swizzle functions for standard C++ 98", "md_include_glm_manual.html#autotoc_md30", null ],
            [ "2.14.2. Swizzle operations for C++ 98 with language extensions", "md_include_glm_manual.html#autotoc_md31", null ]
          ] ],
          [ "<a name=\"section2_15\"></a> 2.15. GLM_FORCE_XYZW_ONLY: Only exposes x, y, z and w components", "md_include_glm_manual.html#autotoc_md32", null ],
          [ "<a name=\"section2_16\"></a> 2.16. GLM_FORCE_LEFT_HANDED: Force left handed coordinate system", "md_include_glm_manual.html#autotoc_md33", null ],
          [ "<a name=\"section2_17\"></a> 2.17. GLM_FORCE_DEPTH_ZERO_TO_ONE: Force the use of a clip space between 0 to 1", "md_include_glm_manual.html#autotoc_md34", null ],
          [ "<a name=\"section2_18\"></a> 2.18. GLM_FORCE_SIZE_T_LENGTH: Vector and matrix static size", "md_include_glm_manual.html#autotoc_md35", null ],
          [ "<a name=\"section2_19\"></a> 2.19. GLM_FORCE_UNRESTRICTED_GENTYPE: Removing genType restriction", "md_include_glm_manual.html#autotoc_md36", null ],
          [ "<a name=\"section2_20\"></a> 2.20. GLM_FORCE_SILENT_WARNINGS: Silent C++ warnings from language extensions", "md_include_glm_manual.html#autotoc_md37", null ],
          [ "<a name=\"section2_21\"></a> 2.21. GLM_FORCE_QUAT_DATA_WXYZ: Force GLM to store quat data as w,x,y,z instead of x,y,z,w", "md_include_glm_manual.html#autotoc_md38", null ]
        ] ],
        [ "<a name=\"section3\"></a> 3. Stable extensions", "md_include_glm_manual.html#autotoc_md40", [
          [ "<a name=\"section3_1\"></a> 3.1. Scalar types", "md_include_glm_manual.html#autotoc_md41", [
            [ "3.1.1. GLM_EXT_scalar_int_sized", "md_include_glm_manual.html#autotoc_md42", null ],
            [ "3.1.2. GLM_EXT_scalar_uint_sized", "md_include_glm_manual.html#autotoc_md43", null ]
          ] ],
          [ "<a name=\"section3_2\"></a> 3.2. Scalar functions", "md_include_glm_manual.html#autotoc_md44", [
            [ "3.2.1. GLM_EXT_scalar_common", "md_include_glm_manual.html#autotoc_md45", null ],
            [ "3.2.2. GLM_EXT_scalar_relational", "md_include_glm_manual.html#autotoc_md46", null ],
            [ "3.2.3. GLM_EXT_scalar_constants", "md_include_glm_manual.html#autotoc_md47", null ],
            [ "3.2.4. GLM_EXT_scalar_ulp", "md_include_glm_manual.html#autotoc_md48", null ]
          ] ],
          [ "<a name=\"section3_3\"></a> 3.3. Vector types", "md_include_glm_manual.html#autotoc_md49", [
            [ "3.3.1. GLM_EXT_vector_float1", "md_include_glm_manual.html#autotoc_md50", null ],
            [ "3.3.2. GLM_EXT_vector_float2", "md_include_glm_manual.html#autotoc_md51", null ],
            [ "3.3.3. GLM_EXT_vector_float3", "md_include_glm_manual.html#autotoc_md52", null ],
            [ "3.3.4. GLM_EXT_vector_float4", "md_include_glm_manual.html#autotoc_md53", null ],
            [ "3.3.5. GLM_EXT_vector_double1", "md_include_glm_manual.html#autotoc_md54", null ],
            [ "3.3.6. GLM_EXT_vector_double2", "md_include_glm_manual.html#autotoc_md55", null ],
            [ "3.3.7. GLM_EXT_vector_double3", "md_include_glm_manual.html#autotoc_md56", null ],
            [ "3.3.8. GLM_EXT_vector_double4", "md_include_glm_manual.html#autotoc_md57", null ],
            [ "3.3.9. GLM_EXT_vector_int1", "md_include_glm_manual.html#autotoc_md58", null ],
            [ "3.3.10. GLM_EXT_vector_int2", "md_include_glm_manual.html#autotoc_md59", null ],
            [ "3.3.11. GLM_EXT_vector_int3", "md_include_glm_manual.html#autotoc_md60", null ],
            [ "3.3.12. GLM_EXT_vector_int4", "md_include_glm_manual.html#autotoc_md61", null ],
            [ "3.3.13. GLM_EXT_vector_int1", "md_include_glm_manual.html#autotoc_md62", null ],
            [ "3.3.14. GLM_EXT_vector_uint2", "md_include_glm_manual.html#autotoc_md63", null ],
            [ "3.3.15. GLM_EXT_vector_uint3", "md_include_glm_manual.html#autotoc_md64", null ],
            [ "3.3.16. GLM_EXT_vector_uint4", "md_include_glm_manual.html#autotoc_md65", null ],
            [ "3.3.17. GLM_EXT_vector_bool1", "md_include_glm_manual.html#autotoc_md66", null ],
            [ "3.3.18. GLM_EXT_vector_bool2", "md_include_glm_manual.html#autotoc_md67", null ],
            [ "3.3.19. GLM_EXT_vector_bool3", "md_include_glm_manual.html#autotoc_md68", null ],
            [ "3.3.20. GLM_EXT_vector_bool4", "md_include_glm_manual.html#autotoc_md69", null ]
          ] ],
          [ "<a name=\"section3_4\"></a> 3.4. Vector types with precision qualifiers", "md_include_glm_manual.html#autotoc_md70", [
            [ "3.4.1. GLM_EXT_vector_float1_precision", "md_include_glm_manual.html#autotoc_md71", null ],
            [ "3.4.2. GLM_EXT_vector_float2_precision", "md_include_glm_manual.html#autotoc_md72", null ],
            [ "3.4.3. GLM_EXT_vector_float3_precision", "md_include_glm_manual.html#autotoc_md73", null ],
            [ "3.4.4. GLM_EXT_vector_float4_precision", "md_include_glm_manual.html#autotoc_md74", null ],
            [ "3.4.5. GLM_EXT_vector_double1_precision", "md_include_glm_manual.html#autotoc_md75", null ],
            [ "3.4.6. GLM_EXT_vector_double2_precision", "md_include_glm_manual.html#autotoc_md76", null ],
            [ "3.4.7. GLM_EXT_vector_double3_precision", "md_include_glm_manual.html#autotoc_md77", null ],
            [ "3.4.8. GLM_EXT_vector_double4_precision", "md_include_glm_manual.html#autotoc_md78", null ]
          ] ],
          [ "<a name=\"section3_4\"></a> 3.5. Vector functions", "md_include_glm_manual.html#autotoc_md79", [
            [ "3.5.1. GLM_EXT_vector_common", "md_include_glm_manual.html#autotoc_md80", null ],
            [ "3.5.2. GLM_EXT_vector_relational", "md_include_glm_manual.html#autotoc_md81", null ],
            [ "3.5.3. GLM_EXT_vector_ulp", "md_include_glm_manual.html#autotoc_md82", null ]
          ] ],
          [ "<a name=\"section3_6\"></a> 3.6. Matrix types", "md_include_glm_manual.html#autotoc_md83", [
            [ "3.6.1. GLM_EXT_matrix_float2x2", "md_include_glm_manual.html#autotoc_md84", null ],
            [ "3.6.2. GLM_EXT_matrix_float2x3", "md_include_glm_manual.html#autotoc_md85", null ],
            [ "3.6.3. GLM_EXT_matrix_float2x4", "md_include_glm_manual.html#autotoc_md86", null ],
            [ "3.6.4. GLM_EXT_matrix_float3x2", "md_include_glm_manual.html#autotoc_md87", null ],
            [ "3.6.5. GLM_EXT_matrix_float3x3", "md_include_glm_manual.html#autotoc_md88", null ],
            [ "3.6.6. GLM_EXT_matrix_float3x4", "md_include_glm_manual.html#autotoc_md89", null ],
            [ "3.6.7. GLM_EXT_matrix_float4x2", "md_include_glm_manual.html#autotoc_md90", null ],
            [ "3.6.8. GLM_EXT_matrix_float4x3", "md_include_glm_manual.html#autotoc_md91", null ],
            [ "3.6.9. GLM_EXT_matrix_float4x4", "md_include_glm_manual.html#autotoc_md92", null ],
            [ "3.6.10. GLM_EXT_matrix_double2x2", "md_include_glm_manual.html#autotoc_md93", null ],
            [ "3.6.11. GLM_EXT_matrix_double2x3", "md_include_glm_manual.html#autotoc_md94", null ],
            [ "3.6.12. GLM_EXT_matrix_double2x4", "md_include_glm_manual.html#autotoc_md95", null ],
            [ "3.6.13. GLM_EXT_matrix_double3x2", "md_include_glm_manual.html#autotoc_md96", null ],
            [ "3.6.14. GLM_EXT_matrix_double3x3", "md_include_glm_manual.html#autotoc_md97", null ],
            [ "3.6.15. GLM_EXT_matrix_double3x4", "md_include_glm_manual.html#autotoc_md98", null ],
            [ "3.6.16. GLM_EXT_matrix_double4x2", "md_include_glm_manual.html#autotoc_md99", null ],
            [ "3.6.17. GLM_EXT_matrix_double4x3", "md_include_glm_manual.html#autotoc_md100", null ],
            [ "3.6.18. GLM_EXT_matrix_double4x4", "md_include_glm_manual.html#autotoc_md101", null ]
          ] ],
          [ "<a name=\"section3_7\"></a> 3.7. Matrix types with precision qualifiers", "md_include_glm_manual.html#autotoc_md102", [
            [ "3.7.1. GLM_EXT_matrix_float2x2_precision", "md_include_glm_manual.html#autotoc_md103", null ],
            [ "3.7.2. GLM_EXT_matrix_float2x3_precision", "md_include_glm_manual.html#autotoc_md104", null ],
            [ "3.7.3. GLM_EXT_matrix_float2x4_precision", "md_include_glm_manual.html#autotoc_md105", null ],
            [ "3.7.4. GLM_EXT_matrix_float3x2_precision", "md_include_glm_manual.html#autotoc_md106", null ],
            [ "3.7.5. GLM_EXT_matrix_float3x3_precision", "md_include_glm_manual.html#autotoc_md107", null ],
            [ "3.7.6. GLM_EXT_matrix_float3x4_precision", "md_include_glm_manual.html#autotoc_md108", null ],
            [ "3.7.7. GLM_EXT_matrix_float4x2_precision", "md_include_glm_manual.html#autotoc_md109", null ],
            [ "3.7.8. GLM_EXT_matrix_float4x3_precision", "md_include_glm_manual.html#autotoc_md110", null ],
            [ "3.7.9. GLM_EXT_matrix_float4x4_precision", "md_include_glm_manual.html#autotoc_md111", null ],
            [ "3.7.10. GLM_EXT_matrix_double2x2_precision", "md_include_glm_manual.html#autotoc_md112", null ],
            [ "3.7.11. GLM_EXT_matrix_double2x3_precision", "md_include_glm_manual.html#autotoc_md113", null ],
            [ "3.7.12. GLM_EXT_matrix_double2x4_precision", "md_include_glm_manual.html#autotoc_md114", null ],
            [ "3.7.13. GLM_EXT_matrix_double3x2_precision", "md_include_glm_manual.html#autotoc_md115", null ],
            [ "3.7.14. GLM_EXT_matrix_double3x3_precision", "md_include_glm_manual.html#autotoc_md116", null ],
            [ "3.7.15. GLM_EXT_matrix_double3x4_precision", "md_include_glm_manual.html#autotoc_md117", null ],
            [ "3.7.16. GLM_EXT_matrix_double4x2_precision", "md_include_glm_manual.html#autotoc_md118", null ],
            [ "3.7.17. GLM_EXT_matrix_double4x3_precision", "md_include_glm_manual.html#autotoc_md119", null ],
            [ "3.7.18. GLM_EXT_matrix_double4x4_precision", "md_include_glm_manual.html#autotoc_md120", null ]
          ] ],
          [ "<a name=\"section3_8\"></a> 3.8. Matrix functions", "md_include_glm_manual.html#autotoc_md121", [
            [ "3.8.1. GLM_EXT_matrix_relational", "md_include_glm_manual.html#autotoc_md122", null ],
            [ "3.8.2. GLM_EXT_matrix_transform", "md_include_glm_manual.html#autotoc_md123", null ],
            [ "3.8.3. GLM_EXT_matrix_clip_space", "md_include_glm_manual.html#autotoc_md124", null ],
            [ "3.8.4. GLM_EXT_matrix_projection", "md_include_glm_manual.html#autotoc_md125", null ]
          ] ],
          [ "<a name=\"section3_9\"></a> 3.9. Quaternion types", "md_include_glm_manual.html#autotoc_md126", [
            [ "3.9.1. GLM_EXT_quaternion_float", "md_include_glm_manual.html#autotoc_md127", null ],
            [ "3.9.2. GLM_EXT_quaternion_double", "md_include_glm_manual.html#autotoc_md128", null ]
          ] ],
          [ "<a name=\"section3_10\"></a> 3.10. Quaternion types with precision qualifiers", "md_include_glm_manual.html#autotoc_md129", [
            [ "3.10.1. GLM_EXT_quaternion_float_precision", "md_include_glm_manual.html#autotoc_md130", null ],
            [ "3.10.2. GLM_EXT_quaternion_double_precision", "md_include_glm_manual.html#autotoc_md131", null ]
          ] ],
          [ "<a name=\"section3_11\"></a> 3.11. Quaternion functions", "md_include_glm_manual.html#autotoc_md132", [
            [ "3.11.1. GLM_EXT_quaternion_common", "md_include_glm_manual.html#autotoc_md133", null ],
            [ "3.11.2. GLM_EXT_quaternion_geometric", "md_include_glm_manual.html#autotoc_md134", null ],
            [ "3.11.3. GLM_EXT_quaternion_trigonometric", "md_include_glm_manual.html#autotoc_md135", null ],
            [ "3.11.4. GLM_EXT_quaternion_exponential", "md_include_glm_manual.html#autotoc_md136", null ],
            [ "3.11.5. GLM_EXT_quaternion_relational", "md_include_glm_manual.html#autotoc_md137", null ],
            [ "3.11.6. GLM_EXT_quaternion_transform", "md_include_glm_manual.html#autotoc_md138", null ]
          ] ]
        ] ],
        [ "<a name=\"section4\"></a> 4. Recommended extensions", "md_include_glm_manual.html#autotoc_md140", [
          [ "<a name=\"section4_1\"></a> 4.1. GLM_GTC_bitfield", "md_include_glm_manual.html#autotoc_md141", null ],
          [ "<a name=\"section4_2\"></a> 4.2. GLM_GTC_color_space", "md_include_glm_manual.html#autotoc_md142", null ],
          [ "<a name=\"section4_3\"></a> 4.3. GLM_GTC_constants", "md_include_glm_manual.html#autotoc_md143", null ],
          [ "<a name=\"section4_4\"></a> 4.4. GLM_GTC_epsilon", "md_include_glm_manual.html#autotoc_md144", null ],
          [ "<a name=\"section4_5\"></a> 4.5. GLM_GTC_integer", "md_include_glm_manual.html#autotoc_md145", null ],
          [ "<a name=\"section4_6\"></a> 4.6. GLM_GTC_matrix_access", "md_include_glm_manual.html#autotoc_md146", null ],
          [ "<a name=\"section4_7\"></a> 4.7. GLM_GTC_matrix_integer", "md_include_glm_manual.html#autotoc_md147", null ],
          [ "<a name=\"section4_8\"></a> 4.8. GLM_GTC_matrix_inverse", "md_include_glm_manual.html#autotoc_md148", null ],
          [ "<a name=\"section4_9\"></a> 4.9. GLM_GTC_matrix_transform", "md_include_glm_manual.html#autotoc_md149", null ],
          [ "<a name=\"section4_10\"></a> 4.10. GLM_GTC_noise", "md_include_glm_manual.html#autotoc_md150", null ],
          [ "<a name=\"section4_11\"></a> 4.11. GLM_GTC_packing", "md_include_glm_manual.html#autotoc_md151", null ],
          [ "<a name=\"section4_12\"></a> 4.12. GLM_GTC_quaternion", "md_include_glm_manual.html#autotoc_md152", null ],
          [ "<a name=\"section4_13\"></a> 4.13. GLM_GTC_random", "md_include_glm_manual.html#autotoc_md153", null ],
          [ "<a name=\"section4_14\"></a> 4.14. GLM_GTC_reciprocal", "md_include_glm_manual.html#autotoc_md154", null ],
          [ "<a name=\"section4_15\"></a> 4.15. GLM_GTC_round", "md_include_glm_manual.html#autotoc_md155", null ],
          [ "<a name=\"section4_16\"></a> 4.16. GLM_GTC_type_aligned", "md_include_glm_manual.html#autotoc_md156", null ],
          [ "<a name=\"section4_17\"></a> 4.17. GLM_GTC_type_precision", "md_include_glm_manual.html#autotoc_md157", null ],
          [ "<a name=\"section4_18\"></a> 4.18. GLM_GTC_type_ptr", "md_include_glm_manual.html#autotoc_md158", null ],
          [ "<a name=\"section4_19\"></a> 4.19. GLM_GTC_ulp", "md_include_glm_manual.html#autotoc_md159", null ],
          [ "<a name=\"section4_20\"></a> 4.20. GLM_GTC_vec1", "md_include_glm_manual.html#autotoc_md160", null ]
        ] ],
        [ "<a name=\"section5\"></a> 5. OpenGL interoperability", "md_include_glm_manual.html#autotoc_md162", [
          [ "<a name=\"section5_1\"></a> 5.1. GLM replacements for deprecated OpenGL functions", "md_include_glm_manual.html#autotoc_md163", null ],
          [ "<a name=\"section5_2\"></a> 5.2. GLM replacements for GLU functions", "md_include_glm_manual.html#autotoc_md164", null ]
        ] ],
        [ "<a name=\"section6\"></a> 6. Known issues", "md_include_glm_manual.html#autotoc_md166", [
          [ "<a name=\"section6_1\"></a> 6.1. not function", "md_include_glm_manual.html#autotoc_md167", null ],
          [ "<a name=\"section6_2\"></a> 6.2. Precision qualifiers support", "md_include_glm_manual.html#autotoc_md168", null ]
        ] ],
        [ "<a name=\"section7\"></a> 7. FAQ", "md_include_glm_manual.html#autotoc_md170", [
          [ "<a name=\"section7_1\"></a> 7.1 Why GLM follows GLSL specification and conventions?", "md_include_glm_manual.html#autotoc_md171", null ],
          [ "<a name=\"section7_2\"></a> 7.2. Does GLM run GLSL program?", "md_include_glm_manual.html#autotoc_md172", null ],
          [ "<a name=\"section7_3\"></a> 7.3. Does a GLSL compiler build GLM codes?", "md_include_glm_manual.html#autotoc_md173", null ],
          [ "<a name=\"section7_4\"></a> 7.4. Should I use ‘GTX’ extensions?", "md_include_glm_manual.html#autotoc_md174", null ],
          [ "<a name=\"section7_5\"></a> 7.5. Where can I ask my questions?", "md_include_glm_manual.html#autotoc_md175", null ],
          [ "<a name=\"section7_6\"></a> 7.6. Where can I find the documentation of extensions?", "md_include_glm_manual.html#autotoc_md176", null ],
          [ "<a name=\"section7_7\"></a> 7.7. Should I use ‘using namespace glm;’?", "md_include_glm_manual.html#autotoc_md177", null ],
          [ "<a name=\"section7_8\"></a> 7.8. Is GLM fast?", "md_include_glm_manual.html#autotoc_md178", null ],
          [ "<a name=\"section7_9\"></a> 7.9. When I build with Visual C++ with /W4 warning level, I have warnings...", "md_include_glm_manual.html#autotoc_md179", null ],
          [ "<a name=\"section7_10\"></a> 7.10. Why some GLM functions can crash because of division by zero?", "md_include_glm_manual.html#autotoc_md180", null ],
          [ "<a name=\"section7_11\"></a> 7.11. What unit for angles is used in GLM?", "md_include_glm_manual.html#autotoc_md181", null ],
          [ "<a name=\"section7_12\"></a> 7.12. Windows headers cause build errors...", "md_include_glm_manual.html#autotoc_md182", null ],
          [ "<a name=\"section7_13\"></a> 7.13. Constant expressions support", "md_include_glm_manual.html#autotoc_md183", null ]
        ] ],
        [ "<a name=\"section8\"></a> 8. Code samples", "md_include_glm_manual.html#autotoc_md185", [
          [ "<a name=\"section8_1\"></a> 8.1. Compute a triangle normal", "md_include_glm_manual.html#autotoc_md186", null ],
          [ "<a name=\"section8_2\"></a> 8.2. Matrix transform", "md_include_glm_manual.html#autotoc_md187", null ],
          [ "<a name=\"section8_3\"></a> 8.3. Vector types", "md_include_glm_manual.html#autotoc_md188", null ],
          [ "<a name=\"section8_4\"></a> 8.4. Lighting", "md_include_glm_manual.html#autotoc_md189", null ]
        ] ],
        [ "<a name=\"section9\"></a> 9. Contributing to GLM", "md_include_glm_manual.html#autotoc_md191", [
          [ "<a name=\"section9_1\"></a> 9.1. Submitting bug reports", "md_include_glm_manual.html#autotoc_md192", null ],
          [ "<a name=\"section9_2\"></a> 9.2. Contributing to GLM with pull request", "md_include_glm_manual.html#autotoc_md193", [
            [ "Step 1: Setup our GLM Fork", "md_include_glm_manual.html#autotoc_md194", null ],
            [ "Step 2: Synchronizing our fork", "md_include_glm_manual.html#autotoc_md195", null ],
            [ "Step 3: Modifying our GLM Fork", "md_include_glm_manual.html#autotoc_md196", null ],
            [ "Step 4: Submitting a Pull Request", "md_include_glm_manual.html#autotoc_md197", null ]
          ] ],
          [ "<a name=\"section9_3\"></a> 9.3. Coding style", "md_include_glm_manual.html#autotoc_md198", [
            [ "Indentation", "md_include_glm_manual.html#autotoc_md199", null ],
            [ "Spacing", "md_include_glm_manual.html#autotoc_md200", null ],
            [ "Blank lines", "md_include_glm_manual.html#autotoc_md201", null ],
            [ "Comments", "md_include_glm_manual.html#autotoc_md202", null ],
            [ "Cases", "md_include_glm_manual.html#autotoc_md203", null ]
          ] ]
        ] ],
        [ "<a name=\"section10\"></a> 10. References", "md_include_glm_manual.html#autotoc_md205", [
          [ "<a name=\"section10_1\"></a> 10.1. OpenGL specifications", "md_include_glm_manual.html#autotoc_md206", null ],
          [ "<a name=\"section10_2\"></a> 10.2. External links", "md_include_glm_manual.html#autotoc_md207", null ],
          [ "<a name=\"section10_3\"></a> 10.3. Projects using GLM", "md_include_glm_manual.html#autotoc_md208", null ],
          [ "<a name=\"section10_4\"></a> 10.4. Tutorials using GLM", "md_include_glm_manual.html#autotoc_md209", null ],
          [ "<a name=\"section10_5\"></a> 10.5. Equivalent for other languages", "md_include_glm_manual.html#autotoc_md210", null ],
          [ "<a name=\"section10_6\"></a> 10.6. Alternatives to GLM", "md_include_glm_manual.html#autotoc_md211", null ],
          [ "<a name=\"section10_7\"></a> 10.7. Acknowledgements", "md_include_glm_manual.html#autotoc_md212", null ]
        ] ]
      ] ]
    ] ],
    [ "readme", "md_include_glm_readme.html", null ],
    [ "FrankEngine - A Game Engine Project", "md__r_e_a_d_m_e.html", null ],
    [ "Deprecated List", "deprecated.html", null ],
    [ "Todo List", "todo.html", null ],
    [ "Modules", "modules.html", "modules" ],
    [ "Namespaces", "namespaces.html", [
      [ "Namespace List", "namespaces.html", "namespaces_dup" ],
      [ "Namespace Members", "namespacemembers.html", [
        [ "All", "namespacemembers.html", "namespacemembers_dup" ],
        [ "Functions", "namespacemembers_func.html", "namespacemembers_func" ],
        [ "Variables", "namespacemembers_vars.html", null ],
        [ "Typedefs", "namespacemembers_type.html", "namespacemembers_type" ],
        [ "Enumerations", "namespacemembers_enum.html", null ],
        [ "Enumerator", "namespacemembers_eval.html", null ]
      ] ]
    ] ],
    [ "Classes", "annotated.html", [
      [ "Class List", "annotated.html", "annotated_dup" ],
      [ "Class Index", "classes.html", null ],
      [ "Class Hierarchy", "hierarchy.html", "hierarchy" ],
      [ "Class Members", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Functions", "functions_func.html", "functions_func" ],
        [ "Variables", "functions_vars.html", "functions_vars" ],
        [ "Typedefs", "functions_type.html", null ],
        [ "Enumerations", "functions_enum.html", null ],
        [ "Enumerator", "functions_eval.html", null ],
        [ "Related Functions", "functions_rela.html", null ]
      ] ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ],
      [ "File Members", "globals.html", [
        [ "All", "globals.html", "globals_dup" ],
        [ "Functions", "globals_func.html", "globals_func" ],
        [ "Typedefs", "globals_type.html", null ],
        [ "Enumerations", "globals_enum.html", null ],
        [ "Enumerator", "globals_eval.html", "globals_eval" ],
        [ "Macros", "globals_defs.html", "globals_defs" ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"",
"_color_8cpp.html#a7723239a0214e2b70322c9f3b3708772",
"_logger_8hpp.html#a02b8b6684736711bfc07e74805d314bd",
"_s_d_l__audio_8h.html#ae165f64b3f0fecfebe1c97731600ca59",
"_s_d_l__events_8h.html#a3b589e89be6b35c02e0dd34a55f3fccaa31acc5fdafc86ebe2c1f5c3cae48d603",
"_s_d_l__haptic_8h.html#aacee621c474cda53e56f4a2233c65407",
"_s_d_l__keyboard_8h.html#a5d30971127cd386655b891f429b76fe9",
"_s_d_l__keycode_8h.html#a179ce01fa41d35408f06b4b3d1cd9d3dafcaf9f88a67972f265f30f07ea152d88",
"_s_d_l__opengl_8h.html#a0d158c7775e0a361b691f9ca59057636",
"_s_d_l__opengl_8h.html#a4054a5aebcfc3a6e1566802d1ecb161d",
"_s_d_l__opengl_8h.html#a70d4fadcda2e1b4acd59774953001b28",
"_s_d_l__opengl_8h.html#aa17a1911f3029f674843fa13ead17a4b",
"_s_d_l__opengl_8h.html#ad35c09037f6904f3989d4e12d47d8819",
"_s_d_l__pixels_8h.html#a355a9ed42dcc4f61e525ca4a5987fe44a824001fa3058d020c50d9d658d38e409",
"_s_d_l__rwops_8h.html#a054a717fd0b1a2f175e2e822e1ecc67d",
"_s_d_l__scancode_8h.html#a82ab7cff701034fb40a47b5b3a02777bae6a58c2b28e6aa3d473d1a76c75088bc",
"_s_d_l__stdinc_8h.html#aeafdd0f5a8ec4a06405db952e7699028",
"_s_d_l__thread_8h.html#ab519f8d89ea808f32fc139071e6207bb",
"_s_d_l__video_8h.html#ade5fc4847320fb235f17265b683fa013",
"associated__min__max_8hpp_source.html",
"bt_collision_shape_8h_source.html",
"cexport_8h.html#a0998064849f2ef5544f6fd30cda0b964",
"class_assimp_1_1_i_o_system.html#a26a040ad173f498f4ba71df498a61001",
"class_assimp_1_1_stream_writer.html#a64ca1a79ccbf2033a8ad40c738f02670",
"class_collision_manager.html#aa93a9569dd7256a19bb26f40ae70f0e5",
"class_givens_rotation.html#a0c99165120906a70bd81408e0b20af90",
"class_transform.html#ae2359e0cb6cd59e621cd50f0cef37e36",
"classb3_quaternion.html#aaaa48a1fdc56d8cad9e274e0836e0103",
"classbt_collision_algorithm.html#a11004907cdf3028c635486b435302f90",
"classbt_default_serializer.html#a6a6648d2c786c9a45075c3df5f00059b",
"classbt_g_impact_mesh_shape_part_1_1_trimesh_primitive_manager.html#a1408f075f1a6c04fcf80a6c271802640",
"classbt_inverse_dynamics_1_1_multi_body_tree.html#a0d39131a8a047e40a9e42de1a33c46db",
"classbt_matrix2x2.html#a671bec44d7f591788ac3d1fcc8f09687",
"classbt_quaternion.html#abe995d64f60c0cd51278da798518933d",
"classbt_simulation_island_manager_mt.html#ad18572f50e933cbe52c2bdf6ef250ed2",
"classbt_soft_soft_collision_algorithm.html#a30c98dafc3be8e645c48d5d378586a34",
"classluabridge_1_1_lua_ref_base.html#a8de9e2cb013e3157ab09f97438f1d45d",
"classnlohmann_1_1basic__json.html#ac8f3125911eb018ef4ab00d879487baf",
"clew_8h.html#a0559a585efd8c6e400a13633f7e93697",
"clew_8h.html#a71a4baddb5150624fa3d6fe875f8a395",
"clew_8h.html#ad1767a468cdcc7f6231a400f79543e6b",
"compatibility_8hpp.html#ga64a5113afe95db296ff0593232ac772d",
"dir_3a86aadd34177794143c70c6d0463f6b.html",
"ext__matrix__uint4x2__sized_8cpp_source.html",
"functions_func_l.html",
"gim__linear__math_8h.html#abdd6663619451330826ff1e50f7dd30e",
"group__core__func__common.html#ga76b81785045a057989a84d99aeeb1578",
"group__core__func__trigonometric.html#gac61629f3a4aa14057e7a8cae002291db",
"group__core__vector.html#gaa62a8043ef218aaf8df6e2d101950a5d",
"group__ext__matrix__int3x2__sized.html#ga7a98be2ccf6df4a7f629bafc03a565b2",
"group__ext__matrix__uint3x4__sized.html#gaee9f984c70a46beedb63dcef0e09a5de",
"group__ext__vector__bool1__precision.html#ga729f7dc7ae7a852c3eaee94285e865cd",
"group__gtc__bitfield.html#ga46f9295abe3b5c7658f5b13c7f819f0a",
"group__gtc__matrix__integer.html#ga9d46a6aec337080f2190c685991b72b3",
"group__gtc__quaternion.html#ga8da38cdfdc452dafa660c2f46506bad5",
"group__gtc__type__aligned.html#ga2cc2efecf9ef887884ed5d370cf7eabf",
"group__gtc__type__aligned.html#ga88996e3df7350600759c8006ffcb7782",
"group__gtc__type__aligned.html#gae3121f35a569fd14475ff5f4d28bd98e",
"group__gtc__type__precision.html#ga3824f9cf3d20b8e34c8b759c33b416ac",
"group__gtc__type__precision.html#ga7ed0e744529434522a65458439a280cb",
"group__gtc__type__precision.html#gac72b12cf584eb217a8edd2cad0e99792",
"group__gtc__type__ptr.html#ga72565b63af29f056843ecd4956b3c738",
"group__gtx__compatibility.html#ga38235425d2401904456ecbc342d87453",
"group__gtx__easing.html#ga34508d4b204a321ec26d6086aa047997",
"group__gtx__fast__exponential.html#ga7562043539194ccc24649f8475bc5584",
"group__gtx__matrix__operation.html#ga40a38402a30860af6e508fe76211e659",
"group__gtx__rotate__vector.html#ga5a048838a03f6249acbacb4dbacf79c4",
"group__gtx__type__aligned.html#ga65ff0d690a34a4d7f46f9b2eb51525ee",
"group__gtx__vec__swizzle.html",
"gtc_2type__aligned_8hpp.html#ga55529174d4bbcbefc4e7affb80353ebd",
"gtc__bitfield_8cpp.html#a43c198bb3fe1b9fd8285651d42784177",
"gtx_2type__aligned_8hpp.html#gaa0fc531cbaa972ac3a0b86d21ef4a7fa",
"imgui_8h.html#a1b3324308e43eeded5c3599fa0f03e85",
"imgui_8h.html#ac3f45e2aa0b1d591cc8a2cdf8b566a45",
"imgui__internal_8h.html#a9920e3b99972583f7fed0357b64a3fb2",
"io_8inl.html#ac52a8c5f8ea189f5bae2e5b8e382675f",
"matrix__clip__space_8hpp.html#gaaeacc04a2a6f4b18c5899d37e7bb3ef9",
"matrix__int3x3_8hpp.html#gab222d4b3d8005a88b4dd9ce459a44eb8",
"md_include_glm_manual.html#autotoc_md107",
"md_include_glm_readme.html#autotoc_md277",
"namespaceglm.html#a09cb6ae89b52ee4c47e7b708b84e4d13",
"namespaceglm.html#a2d9c5fb05e5e1f0fcd39ccf47241c721",
"namespaceglm.html#a510b2ba4577c88a9cb6b357c8a36b7ab",
"namespaceglm.html#a74d09ef9393d6ee27d922d4e0250b770",
"namespaceglm.html#a9d3c5cb460b250a46e1fe5db49ae04ea",
"namespaceglm.html#ac45b8901aac62b54833f739c099c7d16",
"namespaceglm.html#aeadd5dedb6f8c1cfd4d68a43e8f46e1e",
"namespacenlohmann_1_1detail.html#a1ed8fc6239da25abcaf681d30ace4985adce7cc8ec29055c4158828921f2f265e",
"polar__coordinates_8hpp.html#ga1821d5b3324201e60a9e2823d0b5d0c8",
"scalar__integer_8hpp.html#gada3bdd871ffe31f2d484aa668362f636",
"struct_s_d_l___controller_device_event.html#a62945795fc17f5000fddc80e2cf921b8",
"struct_s_d_l___o_s_event.html#a85a600619ebebc8db007fc757b3895a5",
"structai_file_i_o.html",
"structb3_dynamic_bvh_broadphase.html#a11bdeb80726d66fa78da28be01acbc39",
"structbt_contact_solver_info_double_data.html#ad6e0264dd604a1f1949abadd058e3cdb",
"structbt_mesh_part_data.html#ae0a5d2cf600f993b6feca3a438109aaf",
"structbt_typed_constraint_data.html#a3c9ab2afd6eb427375168828baa3953f",
"type__mat2x2_8hpp.html#a4cf995a375755c1ce8062e09922d9c09",
"type__trait_8inl_source.html",
"ulp_8hpp.html#a7b115fb938d42ebbf8ba8b554326a30a",
"vec__swizzle_8hpp.html#a5b726749e9859458ce93003cf1ffc667",
"vec__swizzle_8hpp.html#ae246d3ab906e25f1e6f118eda368a3d9",
"vector__query_8hpp.html#gac7b95b3f798e3c293262b2bdaad47c57"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';