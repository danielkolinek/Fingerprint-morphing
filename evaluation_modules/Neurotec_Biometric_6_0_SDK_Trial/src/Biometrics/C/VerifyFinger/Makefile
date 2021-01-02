include ../../../Common/Build/config.mk

### target ###

TARGET_NAME   = VerifyFinger

### Objects, sources ###

# C source files

CSRCS = \
	VerifyFinger.c

ifeq ($(N_MAC_OSX_FRAMEWORKS),yes)
  LDLIBS ?= -framework NBiometricClient -framework NBiometrics -framework NMedia -framework NCore -framework NLicensing
else
  LDLIBS ?= -lNBiometricClient -lNBiometrics -lNMedia -lNCore -lNLicensing
endif

include ../../../Common/Build/rules.mk

