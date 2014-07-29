###########################################################
# mk for project FaceDetectionApp
###########################################################

include makefile.consts
include opencv.include
SRCDIR = FaceDetectionLib

# Target settings
LANG := c++
TARGET := libFaceDetectionLib.a
TARGETTYPE := staticlib

LIBS := -L$(BINOUTDIR)			                            \
	-L/usr/lib/x86_64-linux-gnu	-lrt -pthread               \
    -lFaceCommonLib                                         \
    $(OPENCV_LIB)                                           \


DEPENDENCIES :=                             \
    $(BINOUTDIR)/libFaceCommonLib.a         \

SRCDIRS :=  ../$(SRCDIR)/

HDRDIRS :=  ../$(SRCDIR)/	\
	../FaceCommonLib/	    \
	$(OPENCV_INCLUDES)

make_dependencies:
	@$(MAKE) --no-print-directory CCFLAG="$(CCFLAG)" LDFLAG="$(LDFLAG)" -f FaceCommonLib.mk build

include makefile.actions
