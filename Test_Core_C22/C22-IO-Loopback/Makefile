# The TARGET variable determines what target system the application is
# compiled for. It either refers to an XN file in the source directories
# or a valid argument for the --target option when compiling

TARGET = C22_Workaround

# The APP_NAME variable determines the name of the final .xe file. It should
# not include the .xe postfix. If left blank the name will default to
# the project name
APP_NAME = C22-IO-Loopback

# The USED_MODULES variable lists other module used by the application.
USED_MODULES = module_c_xcore_resources

# The flags passed to xcc when building the application
# You can also set the following to override flags for a particular language:
# XCC_XC_FLAGS, XCC_C_FLAGS, XCC_ASM_FLAGS, XCC_CPP_FLAGS
# If the variable XCC_MAP_FLAGS is set it overrides the flags passed to
# xcc for the final link (mapping) stage.
XCC_FLAGS_Debug = -O0 -g -lxscope
XCC_FLAGS_Release = -O2 -g -lxscope

# The VERBOSE variable, if set to 1, enables verbose output from the make system.
VERBOSE = 0

XMOS_MAKE_PATH ?= ../..
-include $(XMOS_MAKE_PATH)/xcommon/module_xcommon/build/Makefile.common



showdevices:
	xrun -l

sim: all
	xsim --vcd-tracing "-core stdcore[3] -ports" $(BIN_DIR)/$(APP_NAME).xe > trace.vcd

run: all showdevices
	xrun --io $(BIN_DIR)/$(APP_NAME).xe

rundbg: all showdevices
	xgdb $(BIN_DIR)/$(APP_NAME).xe -ex connect -ex run

runxscope: all showdevices
	xrun --verbose --io --xscope-file xscope.xmt $(BIN_DIR)/$(APP_NAME).xe

flash: all showdevices
	xflash --verbose $(BIN_DIR)/$(APP_NAME).xe

flash_erase: showdevices
	xflash --verbose --target $(TARGET) --erase-all

flashtest: flash flash_erase
