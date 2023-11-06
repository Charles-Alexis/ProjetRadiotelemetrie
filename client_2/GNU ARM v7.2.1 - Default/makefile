################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include version-debug/subdir.mk
-include udp-cli/subdir.mk
-include stack/thread-stack/EFR32/subdir.mk
-include stack/thread-stack/subdir.mk
-include slaac-client/subdir.mk
-include sim-eeprom1/EFR32_1/subdir.mk
-include serial/EFR32/subdir.mk
-include serial/subdir.mk
-include scan-debug/subdir.mk
-include network-management-cli/subdir.mk
-include main/subdir.mk
-include led/EFR32/subdir.mk
-include idle-sleep/subdir.mk
-include icmp-debug/subdir.mk
-include icmp-cli/subdir.mk
-include heartbeat/subdir.mk
-include hal-library/EFR32/subdir.mk
-include global-address-prefix-debug/subdir.mk
-include external-generated-files/subdir.mk
-include emlib/subdir.mk
-include emdrv/subdir.mk
-include dtls-auth-params/subdir.mk
-include diagnostic/EFR32/subdir.mk
-include dhcp-client/subdir.mk
-include debug-print/subdir.mk
-include debug-channel/EFR32/subdir.mk
-include command-interpreter2/subdir.mk
-include coexistence-stub/EFR32/subdir.mk
-include coap-dispatch/subdir.mk
-include coap-cli/subdir.mk
-include cli/subdir.mk
-include buzzer/EFR32/subdir.mk
-include button/EFR32/subdir.mk
-include antenna-stub/subdir.mk
-include address-configuration-debug/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: pre-build main-build

# Main-build Target
main-build: client_2.axf

# Tool invocations
client_2.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -T "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//platform/base/hal/micro/cortexm3/efm32/gcc-cfg.ld" -L"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//platform/base/hal/micro/cortexm3/" -Xlinker --defsym=FLASH_SIZE=524288 -Xlinker --defsym=RAM_SIZE=65536 -Xlinker --defsym=FLASH_PAGE_SIZE=2048 -Xlinker --defsym=SIMEEPROM_SIZE=8192 -Xlinker --defsym=PSSTORE_SIZE=0 -Xlinker --defsym=LONGTOKEN_SIZE=0 -Xlinker --defsym=HEADER_SIZE=256 -Xlinker --defsym=LOCKBITS_IN_MAINFLASH_SIZE=0 -Xlinker --defsym=APP_GECKO_INFO_PAGE_BTL=1 -Xlinker --defsym=EMBER_MALLOC_HEAP_SIZE=0 -Xlinker --gc-sections -Xlinker -Map="client_2.map" -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -o client_2.axf -Wl,--start-group "./address-configuration-debug/address-configuration-debug.o" "./antenna-stub/antenna-stub.o" "./button/EFR32/button.o" "./buzzer/EFR32/buzzer-efr32.o" "./cli/cli.o" "./client-implementation.o" "./delta-encoding.o" "./em_letimer.o" "./thread-bookkeeping.o" "./thread-callback-stubs.o" "./thread-callbacks.o" "./thread-cli.o" "./thread-coap-dispatch.o" "./thread-events.o" "./coap-cli/coap-cli.o" "./coap-dispatch/coap-dispatch.o" "./coexistence-stub/EFR32/coexistence-802154.o" "./coexistence-stub/EFR32/coulomb-counter-802154.o" "./command-interpreter2/command-interpreter2-error.o" "./command-interpreter2/command-interpreter2-util.o" "./command-interpreter2/command-interpreter2.o" "./debug-channel/EFR32/debug-jtag-efr32.o" "./debug-print/debug-print.o" "./dhcp-client/dhcp-client.o" "./diagnostic/EFR32/diagnostic.o" "./dtls-auth-params/dtls-auth-params.o" "./emdrv/dmadrv.o" "./emdrv/gpiointerrupt.o" "./emdrv/rtcdriver.o" "./emdrv/sleep.o" "./emdrv/tempdrv.o" "./emdrv/uartdrv.o" "./emdrv/ustimer.o" "./emlib/em_adc.o" "./emlib/em_cmu.o" "./emlib/em_core.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_i2c.o" "./emlib/em_ldma.o" "./emlib/em_leuart.o" "./emlib/em_msc.o" "./emlib/em_prs.o" "./emlib/em_rmu.o" "./emlib/em_rtcc.o" "./emlib/em_se.o" "./emlib/em_system.o" "./emlib/em_timer.o" "./emlib/em_usart.o" "./emlib/em_wdog.o" "./emlib/system_efr32mg13p.o" "./external-generated-files/bootloader-interface-app.o" "./external-generated-files/bootloader-interface.o" "./external-generated-files/btl_interface.o" "./external-generated-files/btl_interface_storage.o" "./external-generated-files/sample-dotdot-certificates.o" "./global-address-prefix-debug/global-address-prefix-debug.o" "./hal-library/EFR32/assert-crash-handlers.o" "./hal-library/EFR32/crc.o" "./hal-library/EFR32/cstartup-common.o" "./hal-library/EFR32/endian.o" "./hal-library/EFR32/faults-v7m.o" "./hal-library/EFR32/hal-config-gpio.o" "./hal-library/EFR32/hal-config.o" "./hal-library/EFR32/isr-stubs.o" "./hal-library/EFR32/long-token.o" "./hal-library/EFR32/mem-util.o" "./hal-library/EFR32/mfg-token.o" "./hal-library/EFR32/micro-common.o" "./hal-library/EFR32/micro.o" "./hal-library/EFR32/mpu.o" "./hal-library/EFR32/random.o" "./hal-library/EFR32/sleep-efm32.o" "./hal-library/EFR32/token-def.o" "./hal-library/EFR32/token.o" "./heartbeat/heartbeat.o" "./icmp-cli/icmp-cli.o" "./icmp-debug/icmp-debug.o" "./idle-sleep/idle-sleep.o" "./led/EFR32/led.o" "./main/main.o" "./network-management-cli/network-management-cli.o" "./scan-debug/scan-debug.o" "./serial/EFR32/ember-printf.o" "./serial/EFR32/serial.o" "./serial/com.o" "./sim-eeprom1/EFR32_1/sim-eeprom.o" "./slaac-client/slaac-client.o" "./stack/thread-stack/EFR32/SEGGER_RTT.o" "./stack/thread-stack/ember-ip-configuration.o" "./udp-cli/udp-cli.o" "./version-debug/version-debug.o" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/thread/build/hal-library-cortexm3-gcc-efr32mg13p-rail/hal-library.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/thread/build/thread-stack-cortexm3-gcc-efr32mg13p-rail/thread-stack.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/thread/build/dhcp-library-cortexm3-gcc-efr32mg13p-rail/dhcp-library.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/thread/build/mbedtls-library-cortexm3-gcc-efr32mg13p-rail/mbedtls-library.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//platform/radio/rail_lib/autogen/librail_release/librail_efr32xg13_gcc_release.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/thread/build/sim-eeprom1-library-cortexm3-gcc-efr32mg13p-rail/sim-eeprom1-library.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/thread/build/mfglib-library-cortexm3-gcc-efr32mg13p-rail/mfglib-library.a" -lm -Wl,--end-group -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: client_2.hex'
	arm-none-eabi-objcopy -O ihex "client_2.axf" "client_2.hex"
	@echo ' '

	@echo 'Building bin file: client_2.bin'
	arm-none-eabi-objcopy -O binary "client_2.axf" "client_2.bin"
	@echo ' '

	@echo 'Building s37 file: client_2.s37'
	arm-none-eabi-objcopy -O srec "client_2.axf" "client_2.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "client_2.axf" -A
	@echo ' '

	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) client_2.axf
	-@echo ' '

pre-build:
	-cmd //c 'C:\Users\CHARLE~1\Desktop\UNIVER~1\T5\NEWWRO~1\client_2/client_2-prebuild.bat' 'client_2' 'C:/Users/Charles-Alexis/Desktop/Université/T5/NEWWROKSPACE/client_2' '' 'C:\SiliconLabs\SimplicityStudio\v4'
	-@echo ' '

post-build:
	-cmd //c 'C:\Users\CHARLE~1\Desktop\UNIVER~1\T5\NEWWRO~1\client_2/client_2-postbuild.bat' 'client_2' 'C:/Users/Charles-Alexis/Desktop/Université/T5/NEWWROKSPACE/client_2' '' 'C:\SiliconLabs\SimplicityStudio\v4'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: main-build pre-build post-build

-include ../makefile.targets
