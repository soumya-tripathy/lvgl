export MCU_PLUS_SDK_PATH?=$(abspath ../../../)
include $(MCU_PLUS_SDK_PATH)/imports.mak

LVGL_PATH ?= $(MCU_PLUS_SDK_PATH)/source/drivers/lvgl

# CSRCS += $(shell find src -type f -name '*.c')
# CSRCS += $(shell find demos -type f -name '*.c')
# CSRCS += $(shell find examples -type f -name '*.c')
# CFLAGS += "-I$(LVGL_PATH)"

# include /demos/lv_demos.mk
CSRCS += $(shell find -L demos -name "*.c")

# include /examples/lv_examples.mk
CSRCS += $(shell find -L examples -name "*.c")

# include /src/core/lv_core.mk
CSRCS += $(shell find -L src -name "*.c")

# include /src/draw/lv_draw.mk
# CSRCS += lv_draw_arc.c
# CSRCS += lv_draw.c
# CSRCS += lv_draw_img.c
# CSRCS += lv_draw_label.c
# CSRCS += lv_draw_line.c
# CSRCS += lv_draw_mask.c
# CSRCS += lv_draw_rect.c
# CSRCS += lv_draw_transform.c
# CSRCS += lv_draw_layer.c
# CSRCS += lv_draw_triangle.c
# CSRCS += lv_img_buf.c
# CSRCS += lv_img_cache.c
# CSRCS += lv_img_decoder.c

# include /src/extra/lv_extra.mk
# CSRCS += $(shell find -L src -name "*.c")

# # include /src/font/lv_font.mk
# CSRCS += lv_font.c
# CSRCS += lv_font_fmt_txt.c
# CSRCS += lv_font_loader.c

# CSRCS += lv_font_dejavu_16_persian_hebrew.c
# CSRCS += lv_font_montserrat_8.c
# CSRCS += lv_font_montserrat_10.c
# CSRCS += lv_font_montserrat_12.c
# CSRCS += lv_font_montserrat_12_subpx.c
# CSRCS += lv_font_montserrat_14.c
# CSRCS += lv_font_montserrat_16.c
# CSRCS += lv_font_montserrat_18.c
# CSRCS += lv_font_montserrat_20.c
# CSRCS += lv_font_montserrat_22.c
# CSRCS += lv_font_montserrat_24.c
# CSRCS += lv_font_montserrat_26.c
# CSRCS += lv_font_montserrat_28.c
# CSRCS += lv_font_montserrat_28_compressed.c
# CSRCS += lv_font_montserrat_30.c
# CSRCS += lv_font_montserrat_32.c
# CSRCS += lv_font_montserrat_34.c
# CSRCS += lv_font_montserrat_36.c
# CSRCS += lv_font_montserrat_38.c
# CSRCS += lv_font_montserrat_40.c
# CSRCS += lv_font_montserrat_42.c
# CSRCS += lv_font_montserrat_44.c
# CSRCS += lv_font_montserrat_46.c
# CSRCS += lv_font_montserrat_48.c
# CSRCS += lv_font_simsun_16_cjk.c
# CSRCS += lv_font_unscii_8.c
# CSRCS += lv_font_unscii_16.c
# # include /src/hal/lv_hal.mk
# CSRCS += lv_hal_disp.c
# CSRCS += lv_hal_indev.c
# CSRCS += lv_hal_tick.c


# CSRCS += lv_draw_sw.c
# CSRCS += lv_draw_sw_arc.c
# CSRCS += lv_draw_sw_blend.c
# CSRCS += lv_draw_sw_dither.c
# CSRCS += lv_draw_sw_gradient.c
# CSRCS += lv_draw_sw_img.c
# CSRCS += lv_draw_sw_letter.c
# CSRCS += lv_draw_sw_line.c
# CSRCS += lv_draw_sw_polygon.c
# CSRCS += lv_draw_sw_rect.c
# CSRCS += lv_draw_sw_transform.c
# CSRCS += lv_draw_sw_layer.c


# # include /src/misc/lv_misc.mk
# CSRCS += lv_anim.c
# CSRCS += lv_anim_timeline.c
# CSRCS += lv_area.c
# CSRCS += lv_async.c
# CSRCS += lv_bidi.c
# CSRCS += lv_color.c
# CSRCS += lv_fs.c
# CSRCS += lv_gc.c
# CSRCS += lv_ll.c
# CSRCS += lv_log.c
# CSRCS += lv_lru.c
# CSRCS += lv_math.c
# CSRCS += lv_mem.c
# CSRCS += lv_printf.c
# CSRCS += lv_style.c
# CSRCS += lv_style_gen.c
# CSRCS += lv_timer.c
# CSRCS += lv_tlsf.c
# CSRCS += lv_txt.c
# CSRCS += lv_txt_ap.c
# CSRCS += lv_utils.c



# # include /src/widgets/lv_widgets.mk
# CSRCS += lv_arc.c
# CSRCS += lv_bar.c
# CSRCS += lv_btn.c
# CSRCS += lv_btnmatrix.c
# CSRCS += lv_canvas.c
# CSRCS += lv_checkbox.c
# CSRCS += lv_dropdown.c
# CSRCS += lv_img.c
# CSRCS += lv_label.c
# CSRCS += lv_line.c
# CSRCS += lv_roller.c
# CSRCS += lv_slider.c
# CSRCS += lv_switch.c
# CSRCS += lv_table.c
# CSRCS += lv_textarea.c



FILES_PATH_common = \
	src/widgets \
	src/misc	\
	src/hal		\
	src/font	\
	src/draw	\
	src/draw/sw	\
	src/core	\
	src/dev		\
	src/disp	\
	src/indev	\
	src/layouts	\
	src/libs	\
	src/osal	\
	src/others	\
	src/stdlib	\
	src/themes	\
	src/tick	\
	demos		\
	examples	\


CG_TOOL_ROOT=$(CGT_TI_ARM_CLANG_PATH)

CC=$(CGT_TI_ARM_CLANG_PATH)/bin/tiarmclang
AR=$(CGT_TI_ARM_CLANG_PATH)/bin/tiarmar

PROFILE?=release
ConfigName:=$(PROFILE)

LIBNAME:=lvgl.am62px.wkup-r5f.ti-arm-clang.$(PROFILE).lib

INCLUDES_common := \
    -I${CG_TOOL_ROOT}/include/c \
    -I${MCU_PLUS_SDK_PATH}/source \

DEFINES_common := \
    -DSOC_AM62PX \
    -DENABLE_SCICLIENT_DIRECT \
    -DFVID2_CFG_TRACE_ENABLE \
    -DFVID2_CFG_ASSERT_ENABLE \

CFLAGS_common := \
    -mcpu=cortex-r5 \
    -mfloat-abi=hard \
    -mfpu=vfpv3-d16 \
    -mthumb \
    -Wall \
    -Werror \
    -g \
    -Wno-gnu-variable-sized-type-not-at-end \
    -Wno-unused-function \

CFLAGS_cpp_common := \
    -Wno-c99-designator \
    -Wno-extern-c-compat \
    -Wno-c++11-narrowing \
    -Wno-reorder-init-list \
    -Wno-deprecated-register \
    -Wno-writable-strings \
    -Wno-enum-compare \
    -Wno-reserved-user-defined-literal \
    -Wno-unused-const-variable \
    -x c++ \

CFLAGS_debug := \
    -D_DEBUG_=1 \

CFLAGS_release := \
    -Os \

ARFLAGS_common := \
    rc \

FILES := $(CSRCS) $(FILES_$(PROFILE))
ASMFILES := $(ASMFILES_common) $(ASMFILES_$(PROFILE))
FILES_PATH := $(FILES_PATH_common) $(FILES_PATH_$(PROFILE))
CFLAGS := $(CFLAGS_common) $(CFLAGS_$(PROFILE))
ASMFLAGS := $(CFLAGS_common) $(CFLAGS_$(PROFILE))
ifeq ($(CPLUSPLUS_BUILD), yes)
CFLAGS += $(CFLAGS_cpp_common)
endif
DEFINES := $(DEFINES_common) $(DEFINES_$(PROFILE))
INCLUDES := $(INCLUDES_common) $(INCLUDE_$(PROFILE))
ARFLAGS := $(ARFLAGS_common) $(ARFLAGS_$(PROFILE))

LIBDIR := lib
OBJDIR := $(LVGL_PATH)/obj/am62px/$(PROFILE)/wkup-r5f/
OBJS := $(FILES:%.c=%.obj)
OBJS += $(ASMFILES:%.S=%.obj)
DEPS := $(FILES:%.c=%.d)

vpath %.obj $(OBJDIR)
vpath %.c $(FILES_PATH)
vpath %.S $(FILES_PATH)

$(OBJDIR)/%.obj %.obj: %.c
	@echo  Compiling: $(LIBNAME): $<
	$(CC) -c $(CFLAGS) $(INCLUDES) $(DEFINES) -MMD -o $(OBJDIR)/$@ $<

$(OBJDIR)/%.obj %.obj: %.S
	@echo  Compiling: $(LIBNAME): $<
	$(CC) -c $(ASMFLAGS) -o $(OBJDIR)/$@ $<

all: $(LIBDIR)/$(LIBNAME)

$(LIBDIR)/$(LIBNAME): $(OBJS) | $(LIBDIR)
	@echo  .
	@echo  Archiving: $(LIBNAME) to $@ ...
	$(AR) $(ARFLAGS) $@ $(addprefix $(OBJDIR), $(OBJS))
	@echo  Archiving: $(LIBNAME) Done !!!
	@echo  .

clean:
	@echo  Cleaning: $(LIBNAME) ...
	$(RMDIR) $(OBJDIR)
	$(RM) $(LIBDIR)/$(LIBNAME)

scrub:
	@echo  Scrubing: $(LIBNAME) ...
	-$(RMDIR) obj/
	-$(RMDIR) lib/

$(OBJS): | $(OBJDIR)

$(LIBDIR) $(OBJDIR):
	$(MKDIR) $@
	$(MKDIR) $@/demos/keypad_encoder
	$(MKDIR) $@/demos/benchmark/assets
	$(MKDIR) $@/demos/benchmark/assets
	$(MKDIR) $@/demos/music/assets
	$(MKDIR) $@/demos/stress
	$(MKDIR) $@/demos/widgets/assets
	$(MKDIR) $@/examples/anim
	$(MKDIR) $@/examples/arduino
	$(MKDIR) $@/examples/assets/font
	$(MKDIR) $@/examples/assets/emoji
	$(MKDIR) $@/examples/event
	$(MKDIR) $@/examples/get_started
	$(MKDIR) $@/examples/layouts/flex
	$(MKDIR) $@/examples/layouts/grid
	$(MKDIR) $@/examples/libs/bmp
	$(MKDIR) $@/examples/libs/ffmpeg
	$(MKDIR) $@/examples/libs/freetype
	$(MKDIR) $@/examples/libs/gif
	$(MKDIR) $@/examples/libs/png
	$(MKDIR) $@/examples/libs/qrcode
	$(MKDIR) $@/examples/libs/rlottie
	$(MKDIR) $@/examples/libs/sjpg
	$(MKDIR) $@/examples/others/fragment
	$(MKDIR) $@/examples/others/gridnav
	$(MKDIR) $@/examples/others/ime
	$(MKDIR) $@/examples/others/imgfont
	$(MKDIR) $@/examples/others/monkey
	$(MKDIR) $@/examples/others/msg
	$(MKDIR) $@/examples/others/snapshot
	$(MKDIR) $@/examples/porting
	$(MKDIR) $@/examples/scroll
	$(MKDIR) $@/examples/styles
	$(MKDIR) $@/examples/widgets
	$(MKDIR) $@/examples/widgets/win
	$(MKDIR) $@/examples/widgets/animimg
	$(MKDIR) $@/examples/widgets/arc
	$(MKDIR) $@/examples/widgets/bar
	$(MKDIR) $@/examples/widgets/btn
	$(MKDIR) $@/examples/widgets/btnmatrix
	$(MKDIR) $@/examples/widgets/calendar
	$(MKDIR) $@/examples/widgets/canvas
	$(MKDIR) $@/examples/widgets/chart
	$(MKDIR) $@/examples/widgets/checkbox
	$(MKDIR) $@/examples/widgets/colorwheel
	$(MKDIR) $@/examples/widgets/dropdown
	$(MKDIR) $@/examples/widgets/img
	$(MKDIR) $@/examples/widgets/imgbtn
	$(MKDIR) $@/examples/widgets/keyboard
	$(MKDIR) $@/examples/widgets/label
	$(MKDIR) $@/examples/widgets/led
	$(MKDIR) $@/examples/widgets/line
	$(MKDIR) $@/examples/widgets/list
	$(MKDIR) $@/examples/widgets/menu
	$(MKDIR) $@/examples/widgets/meter
	$(MKDIR) $@/examples/widgets/msgbox
	$(MKDIR) $@/examples/widgets/obj
	$(MKDIR) $@/examples/widgets/roller
	$(MKDIR) $@/examples/widgets/slider
	$(MKDIR) $@/examples/widgets/span
	$(MKDIR) $@/examples/widgets/spinbox
	$(MKDIR) $@/examples/widgets/spinner
	$(MKDIR) $@/examples/widgets/switch
	$(MKDIR) $@/examples/widgets/table
	$(MKDIR) $@/examples/widgets/tabview
	$(MKDIR) $@/examples/widgets/textarea
	$(MKDIR) $@/examples/widgets/tileview
	$(MKDIR) $@/src/core
	$(MKDIR) $@/src/dev
	$(MKDIR) $@/src/dev/disp
	$(MKDIR) $@/src/dev/disp/drm
	$(MKDIR) $@/src/dev/disp/fb
	$(MKDIR) $@/src/dev/disp/lcd
	$(MKDIR) $@/src/dev/disp/tft_espi
	$(MKDIR) $@/src/dev/input/touchscreen
	$(MKDIR) $@/src/dev/sdl
	$(MKDIR) $@/src/disp
	$(MKDIR) $@/src/font
	$(MKDIR) $@/src/indev
	$(MKDIR) $@/src/layouts/flex
	$(MKDIR) $@/src/layouts/grid
	$(MKDIR) $@/src/libs
	$(MKDIR) $@/src/libs/barcode
	$(MKDIR) $@/src/libs/bmp
	$(MKDIR) $@/src/libs/ffmpeg
	$(MKDIR) $@/src/libs/freetype
	$(MKDIR) $@/src/libs/fsdrv
	$(MKDIR) $@/src/libs/gif
	$(MKDIR) $@/src/libs/png
	$(MKDIR) $@/src/libs/qrcode
	$(MKDIR) $@/src/libs/rlottie
	$(MKDIR) $@/src/libs/sjpg
	$(MKDIR) $@/src/libs/tiny_ttf
	$(MKDIR) $@/src/misc
	$(MKDIR) $@/src/osal
	$(MKDIR) $@/src/others
	$(MKDIR) $@/src/others/file_explorer
	$(MKDIR) $@/src/others/fragment
	$(MKDIR) $@/src/others/gridnav
	$(MKDIR) $@/src/others/ime
	$(MKDIR) $@/src/others/imgfont
	$(MKDIR) $@/src/others/msg
	$(MKDIR) $@/src/others/monkey
	$(MKDIR) $@/src/others/msg
	$(MKDIR) $@/src/others/snapshot
	$(MKDIR) $@/src/others/sysmon
	$(MKDIR) $@/src/stdlib
	$(MKDIR) $@/src/stdlib/builtin
	$(MKDIR) $@/src/stdlib/clib
	$(MKDIR) $@/src/stdlib/micropython
	$(MKDIR) $@/src/themes
	$(MKDIR) $@/src/themes/basic
	$(MKDIR) $@/src/themes/default
	$(MKDIR) $@/src/themes/mono
	$(MKDIR) $@/src/tick
	$(MKDIR) $@/src/widgets
	$(MKDIR) $@/src/widgets/animimage
	$(MKDIR) $@/src/widgets/arc
	$(MKDIR) $@/src/widgets/bar
	$(MKDIR) $@/src/widgets/button
	$(MKDIR) $@/src/widgets/buttonmatrix
	$(MKDIR) $@/src/widgets/calendar
	$(MKDIR) $@/src/widgets/canvas
	$(MKDIR) $@/src/widgets/chart
	$(MKDIR) $@/src/widgets/checkbox
	$(MKDIR) $@/src/widgets/dropdown
	$(MKDIR) $@/src/widgets/image
	$(MKDIR) $@/src/widgets/imgbtn
	$(MKDIR) $@/src/widgets/keyboard
	$(MKDIR) $@/src/widgets/label
	$(MKDIR) $@/src/widgets/led
	$(MKDIR) $@/src/widgets/line
	$(MKDIR) $@/src/widgets/list
	$(MKDIR) $@/src/widgets/menu
	$(MKDIR) $@/src/widgets/meter
	$(MKDIR) $@/src/widgets/msgbox
	$(MKDIR) $@/src/widgets/objx_templ
	$(MKDIR) $@/src/widgets/roller
	$(MKDIR) $@/src/widgets/scale
	$(MKDIR) $@/src/widgets/slider
	$(MKDIR) $@/src/widgets/span
	$(MKDIR) $@/src/widgets/spinbox
	$(MKDIR) $@/src/widgets/spinner
	$(MKDIR) $@/src/widgets/switch
	$(MKDIR) $@/src/widgets/table
	$(MKDIR) $@/src/widgets/tabview
	$(MKDIR) $@/src/widgets/textarea
	$(MKDIR) $@/src/widgets/tileview
	$(MKDIR) $@/src/widgets/win
	$(MKDIR) $@/examples/widgets/tileview
	$(MKDIR) $@/src/draw/sw
	$(MKDIR) $@/src/draw/sw/blend
	$(MKDIR) $@/demos/multilang/assets/avatars
	$(MKDIR) $@/demos/multilang/assets/emojis
	$(MKDIR) $@/demos/multilang/assets/fonts
	$(MKDIR) $@/demos/flex_layout
	$(MKDIR) $@/demos/transform/assets
	$(MKDIR) $@/demos/scroll
	$(MKDIR) $@/examples/libs/barcode
	$(MKDIR) $@/examples/libs/tiny_ttf
	$(MKDIR) $@/examples/others/file_explorer
	$(MKDIR) $@/examples/widgets/scale




-include $(addprefix $(OBJDIR)/, $(DEPS))
