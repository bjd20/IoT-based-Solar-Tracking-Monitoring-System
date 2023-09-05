# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Espressif/frameworks/esp-idf-v5.0.2/components/bootloader/subproject"
  "E:/EmbeddedSystem/esp-idf_vsCode_projects/IoT-based-Solar-Tracking-Monitoring-System/build/bootloader"
  "E:/EmbeddedSystem/esp-idf_vsCode_projects/IoT-based-Solar-Tracking-Monitoring-System/build/bootloader-prefix"
  "E:/EmbeddedSystem/esp-idf_vsCode_projects/IoT-based-Solar-Tracking-Monitoring-System/build/bootloader-prefix/tmp"
  "E:/EmbeddedSystem/esp-idf_vsCode_projects/IoT-based-Solar-Tracking-Monitoring-System/build/bootloader-prefix/src/bootloader-stamp"
  "E:/EmbeddedSystem/esp-idf_vsCode_projects/IoT-based-Solar-Tracking-Monitoring-System/build/bootloader-prefix/src"
  "E:/EmbeddedSystem/esp-idf_vsCode_projects/IoT-based-Solar-Tracking-Monitoring-System/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/EmbeddedSystem/esp-idf_vsCode_projects/IoT-based-Solar-Tracking-Monitoring-System/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/EmbeddedSystem/esp-idf_vsCode_projects/IoT-based-Solar-Tracking-Monitoring-System/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
