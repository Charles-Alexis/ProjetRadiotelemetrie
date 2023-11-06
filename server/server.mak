# Architecture directories
ARCHITECTURE_DIR = efr32
BUILD_DIR = build
OUTPUT_DIR = $(BUILD_DIR)/$(ARCHITECTURE_DIR)
LST_DIR = lst
PROJECTNAME = server

# Stack and submodule directories
GLOBAL_BASE_DIR     = ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/..

SOURCE_FILES = \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emdrv/dmadrv/src/dmadrv.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emdrv/gpiointerrupt/src/gpiointerrupt.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emdrv/rtcdrv/src/rtcdriver.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emdrv/sleep/src/sleep.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emdrv/tempdrv/src/tempdrv.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emdrv/ustimer/src/ustimer.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emlib/src/em_adc.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emlib/src/em_cmu.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emlib/src/em_core.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emlib/src/em_emu.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emlib/src/em_gpio.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emlib/src/em_i2c.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emlib/src/em_ldma.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emlib/src/em_leuart.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emlib/src/em_msc.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emlib/src/em_prs.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emlib/src/em_rmu.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emlib/src/em_rtcc.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emlib/src/em_se.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emlib/src/em_system.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emlib/src/em_timer.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emlib/src/em_usart.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emlib/src/em_wdog.c \
../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../Device/SiliconLabs/EFR32MG13P/Source/system_efr32mg13p.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/assert-crash-handlers.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/bootloader-interface-app.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/bootloader-interface.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/button.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/cstartup-common.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/diagnostic.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/faults-v7m.s79 \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/hal-config-gpio.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/hal-config.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/isr-stubs.s79 \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/led.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/long-token.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/mfg-token.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/micro-common.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/micro.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/mpu.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/sleep-efm32.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/token.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/generic/crc.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/generic/endian.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/generic/mem-util.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/generic/random.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/generic/token-def.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/plugin/adc/adc-efr32.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/plugin/antenna-stub/antenna-stub.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/plugin/buzzer/buzzer-efr32.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/plugin/debug-jtag/debug-jtag-efr32.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/plugin/debug/rtt/SEGGER_RTT.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/plugin/serial/cortexm/efm32/com.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/plugin/serial/ember-printf.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/plugin/serial/serial.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/plugin/sim-eeprom1/sim-eeprom.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/bootloader/api/btl_interface.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/bootloader/api/btl_interface_storage.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/emdrv/uartdrv/src/uartdrv.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/radio/rail_lib/plugin/coexistence/protocol/ieee802154/coexistence-802154.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/radio/rail_lib/plugin/coexistence/protocol/ieee802154/coulomb-counter-802154.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/address-configuration-debug/address-configuration-debug.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/cli/cli.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/coap-cli/coap-cli.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/coap-dispatch/coap-dispatch.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/debug-print/debug-print.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/dhcp-client/dhcp-client.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/dtls-auth-params/dtls-auth-params.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/dtls-auth-params/sample-dotdot-certificates.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/global-address-prefix-debug/global-address-prefix-debug.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/heartbeat/heartbeat.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/icmp-cli/icmp-cli.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/icmp-debug/icmp-debug.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/idle-sleep/idle-sleep.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/main/main.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/network-management-cli/network-management-cli.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/scan-debug/scan-debug.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/slaac-client/slaac-client.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/udp-cli/udp-cli.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/plugin/version-debug/version-debug.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/util/serial/command-interpreter2-error.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/util/serial/command-interpreter2-util.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/util/serial/command-interpreter2.c \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/stack/config/ember-ip-configuration.c \
  thread-bookkeeping.c \
  thread-callback-stubs.c \
  thread-callbacks.c \
  thread-cli.c \
  thread-coap-dispatch.c \
  thread-events.c \
  server-implementation.c \


LIB_FILES = \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/radio/rail_lib/autogen/librail_release/librail_efr32xg13_gcc_release.a \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/build/dhcp-library-cortexm3-gcc-efr32mg13p-rail/dhcp-library.a \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/build/hal-library-cortexm3-gcc-efr32mg13p-rail/hal-library.a \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/build/mbedtls-library-cortexm3-gcc-efr32mg13p-rail/mbedtls-library.a \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/build/mfglib-library-cortexm3-gcc-efr32mg13p-rail/mfglib-library.a \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/build/sim-eeprom1-library-cortexm3-gcc-efr32mg13p-rail/sim-eeprom1-library.a \
  ../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/build/thread-stack-cortexm3-gcc-efr32mg13p-rail/thread-stack.a \


CDEFS = -DAPP_GECKO_INFO_PAGE_BTL \
-DEFR32MG13P632F512GM48 \
-DEFR32MG13P \
-DCORTEXM3 \
-DCORTEXM3_EFR32 \
-DCORTEXM3_EFR32_MICRO \
-DCORTEXM3_EFM32_MICRO \
-DEFR32_SERIES1_CONFIG3_MICRO \
-DCONFIGURATION_HEADER=\"thread-configuration.h\" \
-DPLATFORM_HEADER=\"../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/compiler/gcc.h\" \
-DPSSTORE_SIZE=0 \
-DLONGTOKEN_SIZE=0 \
-DLOCKBITS_IN_MAINFLASH_SIZE=0 \
  -DHAL_CONFIG=1 \
  -DEMBER_AF_USE_HWCONF \
  -DEMBER_HEAP_SIZE=16000 \
  -DEMBER_AF_API_EMBER_TYPES=\"stack/include/ember-types.h\" \
  -DEMBER_STACK_IP \
  -DMFGLIB \
  -DHAVE_TLS_JPAKE \
  -DHAVE_TLS_PSK \
  -DHAVE_TLS_ECDHE_ECDSA \
  -DDEBUG_LEVEL=FULL_DEBUG \
  -DEMLIB_USER_CONFIG \
  -DAPPLICATION_TOKEN_HEADER=\"thread-token.h\" \
  -DAPPLICATION_MFG_TOKEN_HEADER=\"thread-mfg-token.h\" \
  -DPHY_RAIL=1 \


ASMDEFS = -DAPP_GECKO_INFO_PAGE_BTL \
-DEFR32MG13P632F512GM48 \
-DEFR32MG13P \
-DCORTEXM3 \
-DCORTEXM3_EFR32 \
-DCORTEXM3_EFR32_MICRO \
-DCORTEXM3_EFM32_MICRO \
-DEFR32_SERIES1_CONFIG3_MICRO \
-DCONFIGURATION_HEADER=\"thread-configuration.h\" \
-DPLATFORM_HEADER=\"../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/compiler/gcc.h\" \
-DPSSTORE_SIZE=0 \
-DLONGTOKEN_SIZE=0 \
-DLOCKBITS_IN_MAINFLASH_SIZE=0 \
  -DHAL_CONFIG=1 \
  -DEMBER_AF_USE_HWCONF \
  -DEMBER_HEAP_SIZE=16000 \
  -DEMBER_AF_API_EMBER_TYPES=\"stack/include/ember-types.h\" \
  -DEMBER_STACK_IP \
  -DMFGLIB \
  -DHAVE_TLS_JPAKE \
  -DHAVE_TLS_PSK \
  -DHAVE_TLS_ECDHE_ECDSA \
  -DDEBUG_LEVEL=FULL_DEBUG \
  -DEMLIB_USER_CONFIG \
  -DAPPLICATION_TOKEN_HEADER=\"thread-token.h\" \
  -DAPPLICATION_MFG_TOKEN_HEADER=\"thread-mfg-token.h\" \
  -DPHY_RAIL=1 \


CINC = -I./ \
-I$(ARM_IAR7_DIR)/ARM/INC \
-I..\..\..\..\..\..\..\SiliconLabs\SimplicityStudio\v4\developer\sdks\gecko_sdk_suite\v2.6 \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/../.. \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/../../stack \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/protocol/thread/app/thread/../util \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/plugin \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/.. \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32 \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/config \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/micro/cortexm3/efm32/efr32 \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../CMSIS/Include \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../Device/SiliconLabs-Restricted/efr32mg13p/Include \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../Device/SiliconLabs/efr32mg13p/Include \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emdrv/common/inc \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emdrv/config \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emdrv/dmadrv/inc \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emdrv/gpiointerrupt/inc \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emdrv/rtcdrv/inc \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emdrv/sleep/inc \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emdrv/spidrv/inc \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emdrv/tempdrv/inc \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emdrv/uartdrv/inc \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emdrv/ustimer/inc \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../emlib/inc \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../middleware/glib \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../middleware/glib/glib \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../radio/rail_lib/plugin \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/base/hal/../../halconfig/inc/hal-config \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6 \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/halconfig/inc/hal-config \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/hardware/module/config \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/hardware/kit/common/halconfig \
-I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/hardware/kit/common/bsp \
  -I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/bootloader \
  -I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/radio/rail_lib/chip/efr32/efr32xg1x \
  -I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/radio/rail_lib/common \
  -I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/radio/rail_lib/plugin/coexistence/common \
  -I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/radio/rail_lib/plugin/coexistence/hal/efr32 \
  -I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/radio/rail_lib/plugin/coexistence/protocol/ieee802154 \
  -I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/radio/rail_lib/protocol/ble \
  -I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/radio/rail_lib/protocol/ieee802154 \
  -I../../../../../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6/platform/radio/rail_lib/protocol/zwave \
  -Ihal-config \


TARGET = server

CSOURCES = $(filter %.c, $(SOURCE_FILES))
ASMSOURCES = $(filter %.s79, $(SOURCE_FILES))
ASMSOURCES2 = $(filter %.s, $(SOURCE_FILES))
ASMSOURCES3 = $(filter %.S, $(SOURCE_FILES))

COBJS = $(addprefix $(OUTPUT_DIR)/,$(CSOURCES:.c=.o))
ASMOBJS = $(addprefix $(OUTPUT_DIR)/,$(ASMSOURCES:.s79=.o))
ASMOBJS2 = $(addprefix $(OUTPUT_DIR)/,$(ASMSOURCES2:.s=.o))
ASMOBJS3 = $(addprefix $(OUTPUT_DIR)/,$(ASMSOURCES3:.S=.o))

OUTPUT_DIRS = $(sort $(dir $(COBJS)) $(dir $(ASMOBJS)) $(dir $(ASMOBJS2)) $(dir $(ASMOBJS3)))

ARCHITECTUREID = efr32~family[m]~series[1]~device_configuration[3]~performance[p]~radio[632]~flash[512k]~temp[g]~package[m]~pins[48]~!module+brd4159a+gcc

# GNU ARM compiler
ifeq ($(findstring +gcc,$(ARCHITECTUREID)), +gcc)
$(info GCC Build)
	# Add linker circular reference as the order of objects may matter for any libraries used
	GROUP_START =-Wl,--start-group
	GROUP_END =-Wl,--end-group

	CCFLAGS = -g3 \
    -gdwarf-2 \
    -mcpu=cortex-m4 \
    -mthumb \
    -std=gnu99 \
    -Os  \
    -Wall  \
    -c  \
    -fmessage-length=0  \
    -ffunction-sections  \
    -fdata-sections  \
    -mfpu=fpv4-sp-d16  \
    -mfloat-abi=softfp \
	$(CDEFS) \
	$(CINC) \

	ASMFLAGS = -c \
	-g3 \
	-gdwarf-2 \
	-mcpu=cortex-m4 \
	-mthumb \
	-c \
	-x assembler-with-cpp \
	$(CINC) \
	$(ASMDEFS)

	LDFLAGS = -g3 \
	-gdwarf-2 \
	-mcpu=cortex-m4 \
	-mthumb -T "C:\SiliconLabs\SimplicityStudio\v4\developer\sdks\gecko_sdk_suite\v2.6\platform\base\hal/micro/cortexm3/efm32/gcc-cfg.ld" \
	-L"$(GLOBAL_BASE_DIR)/hal/micro/cortexm3/" \
	-Xlinker --defsym="SIMEEPROM_SIZE=8192" \
	-Xlinker --defsym="PSSTORE_SIZE=0" \
	-Xlinker --defsym="LONGTOKEN_SIZE=0" \
	-Xlinker --defsym="LOCKBITS_IN_MAINFLASH_SIZE=0" \
	-Xlinker --defsym="FLASH_SIZE=524288" \
	-Xlinker --defsym="RAM_SIZE=65536" \
	-Xlinker --defsym="FLASH_PAGE_SIZE=2048" \
	-Xlinker --defsym="APP_GECKO_INFO_PAGE_BTL=1" \
	-Xlinker --defsym="EMBER_MALLOC_HEAP_SIZE=0" \
	-Xlinker --defsym="HEADER_SIZE=256" \
	-Xlinker --gc-sections \
	-Xlinker -Map="$(PROJECTNAME).map" \
	-mfpu=fpv4-sp-d16 \
	-mfloat-abi=softfp --specs=nano.specs -u _printf_float \
	-Wl,--start-group -lgcc -lc -lnosys   -Wl,--end-group

	ARCHFLAGS = r

	ELFTOOLFLAGS_BIN = -O binary
	ELFTOOLFLAGS_HEX = -O ihex
	ELFTOOLFLAGS_S37 = -O srec

	ifeq ($(OS),Windows_NT)
		ARCH = $(ARM_GNU_DIR)/bin/arm-none-eabi-gcc-ar.exe
		AS = $(ARM_GNU_DIR)/bin/arm-none-eabi-gcc.exe
		CC = $(ARM_GNU_DIR)/bin/arm-none-eabi-gcc.exe
		ELFTOOL = $(ARM_GNU_DIR)/bin/arm-none-eabi-objcopy.exe
		LD = $(ARM_GNU_DIR)/bin/arm-none-eabi-gcc.exe
	else
		ARCH = $(ARM_GNU_DIR)/bin/arm-none-eabi-gcc-ar
		AS = $(ARM_GNU_DIR)/bin/arm-none-eabi-gcc
		CC = $(ARM_GNU_DIR)/bin/arm-none-eabi-gcc
		ELFTOOL = $(ARM_GNU_DIR)/bin/arm-none-eabi-objcopy
		LD = $(ARM_GNU_DIR)/bin/arm-none-eabi-gcc
	endif

endif

# IAR 7.xx toolchain
ifeq ($(findstring +iar,$(ARCHITECTUREID)), +iar)
$(info IAR Build)

	# IAR is not sensitive to linker lib order thus no groups needed.
	GROUP_START =
	GROUP_END =
	CINC += -I$(ARM_IAR6_DIR)/ARM/INC

	ifndef ARM_IAR7_DIR
	$(error ARM_IAR7_DIR is not set. Please define ARM_IAR7_DIR pointing to your IAR 7.xx installation folder.)
	endif

	CCFLAGS = --cpu=cortex-m3 \
	--cpu_mode=thumb \
	--diag_suppress=Pa050 \
	-e \
	--endian=little \
	--fpu=none \
	--no_path_in_file_macros \
	--separate_cluster_for_initialized_variables \
	--dlib_config=$(ARM_IAR7_DIR)/ARM/inc/c/DLib_Config_Normal.h \
	--debug \
	--dependencies=m $*.d \
	-Ohz \
	$(CDEFS) \
	$(CINC)

	ASMFLAGS = --cpu cortex-M3 \
	--fpu None \
	-s+ \
	"-M<>" \
	-w+ \
	-t2 \
	-r \
	$(CINC) \
	$(ASMDEFS)

	LDFLAGS = --entry __iar_program_start \
	--diag_suppress=Lp012 \
	--config C:\SiliconLabs\SimplicityStudio\v4\developer\sdks\gecko_sdk_suite\v2.6\platform\base\hal/micro/cortexm3/efm32/iar-cfg.icf \
	--config_def APP_GECKO_INFO_PAGE_BTL=1 \
	--config_def EMBER_MALLOC_HEAP_SIZE=0

	ARCH = $(JAMEXE_PREFIX) $(ARM_IAR7_DIR)/arm/bin/iarchive.exe
	AS = $(JAMEXE_PREFIX) $(ARM_IAR7_DIR)/arm/bin/iasmarm.exe
	CC = $(JAMEXE_PREFIX) $(ARM_IAR7_DIR)/arm/bin/iccarm.exe
	ELFTOOL = $(JAMEXE_PREFIX) $(ARM_IAR7_DIR)/arm/bin/ielftool.exe
	LD = $(JAMEXE_PREFIX) $(ARM_IAR7_DIR)/arm/bin/ilinkarm.exe

	# No archiver arguments needed for IAR.
	ARCHFLAGS =

	ELFTOOLFLAGS_BIN = --bin
	ELFTOOLFLAGS_HEX = --ihex
	ELFTOOLFLAGS_S37 = --srec --srec-s3only

endif

.PHONY: all clean PROLOGUE

all: PROLOGUE $(OUTPUT_DIRS) $(COBJS) $(ASMOBJS) $(ASMOBJS2) $(ASMOBJS3) $(LIB_FILES)
	@echo 'Linking...'
	@$(LD) $(GROUP_START) $(LDFLAGS) $(COBJS) $(ASMOBJS) $(ASMOBJS2) $(ASMOBJS3) $(LIB_FILES) $(GROUP_END) -o $(OUTPUT_DIR)/$(TARGET).out
	@$(ELFTOOL) $(OUTPUT_DIR)/$(TARGET).out $(ELFTOOLFLAGS_BIN) $(OUTPUT_DIR)/$(TARGET).bin
	@$(ELFTOOL) $(OUTPUT_DIR)/$(TARGET).out $(ELFTOOLFLAGS_HEX) $(OUTPUT_DIR)/$(TARGET).hex
	@$(ELFTOOL) $(OUTPUT_DIR)/$(TARGET).out $(ELFTOOLFLAGS_S37) $(OUTPUT_DIR)/$(TARGET).s37
	@echo 'Done.'

PROLOGUE:
#	@echo $(COBJS)
#	@echo $(ASMOBJS)
#	@echo $(ASMOBJS2)

$(OUTPUT_DIRS):
	@mkdir -p $@

$(COBJS): %.o:
	@echo 'Building $(notdir $(@:%.o=%.c))...'
	@$(CC) $(CCFLAGS) -o $@ $(filter %$(@:$(OUTPUT_DIR)/%.o=%.c),$(CSOURCES)) > /dev/null \

$(ASMOBJS): %.o:
	@echo 'Building $(notdir $(@:%.o=%.s79))...'
	@$(AS) $(ASMFLAGS) -o $@ $(filter %$(@:$(OUTPUT_DIR)/%.o=%.s79),$(ASMSOURCES)) > /dev/null

$(ASMOBJS2): %.o:
	@echo 'Building $(notdir $(@:%.o=%.s))...'
	@$(AS) $(ASMFLAGS) -o $@ $(filter %$(@:$(OUTPUT_DIR)/%.o=%.s),$(ASMSOURCES2)) > /dev/null

$(ASMOBJS3): %.o:
	@echo 'Building $(notdir $(@:%.o=%.S))...'
	@$(AS) $(ASMFLAGS) -o $@ $(filter %$(@:$(OUTPUT_DIR)/%.o=%.S),$(ASMSOURCES3)) > /dev/null

clean:
	$(RM) -r $(COBJS)
	$(RM) -r $(ASMOBJS)
	$(RM) -r $(ASMOBJS2)
	$(RM) -r $(OUTPUT_DIR)
