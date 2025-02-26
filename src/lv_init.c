/**
 * @file lv_init.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "core/lv_global.h"
#include "core/lv_obj.h"
#include "display/lv_display_private.h"
#include "indev/lv_indev_private.h"
#include "layouts/lv_layout.h"
#include "libs/bmp/lv_bmp.h"
#include "libs/ffmpeg/lv_ffmpeg.h"
#include "libs/freetype/lv_freetype.h"
#include "libs/fsdrv/lv_fsdrv.h"
#include "libs/gif/lv_gif.h"
#include "libs/tjpgd/lv_tjpgd.h"
#include "libs/lodepng/lv_lodepng.h"
#include "draw/lv_draw.h"
#include "misc/lv_cache.h"
#include "misc/lv_cache_builtin.h"
#include "misc/lv_async.h"
#include "misc/lv_fs.h"
#if LV_USE_DRAW_VGLITE
    #include "draw/nxp/vglite/lv_draw_vglite.h"
#endif
#if LV_USE_DRAW_PXP
    #include "draw/nxp/pxp/lv_draw_pxp.h"
#endif

/*********************
 *      DEFINES
 *********************/
#define lv_initialized  LV_GLOBAL_DEFAULT()->inited

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
#if LV_ENABLE_GLOBAL_CUSTOM == 0
    lv_global_t lv_global;
#endif

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
static inline void lv_global_init(lv_global_t * global)
{
    LV_ASSERT_NULL(global);

    if(global == NULL) {
        LV_LOG_ERROR("lv_global cannot be null");
        return;
    }

    lv_memset(global, 0, sizeof(lv_global_t));

    _lv_ll_init(&(global->disp_ll), sizeof(lv_display_t));
    _lv_ll_init(&(global->indev_ll), sizeof(lv_indev_t));

    global->memory_zero = ZERO_MEM_SENTINEL;
    global->style_refresh = true;
    global->layout_count = _LV_LAYOUT_LAST;
    global->style_last_custom_prop_id = (uint16_t)_LV_STYLE_LAST_BUILT_IN_PROP;
    global->area_trans_cache.angle_prev = INT32_MIN;
    global->event_last_register_id = _LV_EVENT_LAST;
    global->math_rand_seed = 0x1234ABCD;

#if defined(LV_DRAW_SW_SHADOW_CACHE_SIZE) && LV_DRAW_SW_SHADOW_CACHE_SIZE > 0
    global->sw_shadow_cache.cache_size = -1;
    global->sw_shadow_cache.cache_r = -1;
#endif
}

bool lv_is_initialized(void)
{
#if LV_ENABLE_GLOBAL_CUSTOM
    if(LV_GLOBAL_DEFAULT()) return lv_initialized;
    else return false;
#else
    return lv_initialized;
#endif
}

void lv_init(void)
{
    /*First initialize Garbage Collection if needed*/
#ifdef LV_GC_INIT
    LV_GC_INIT();
#endif

    /*Do nothing if already initialized*/
    if(lv_initialized) {
        LV_LOG_WARN("lv_init: already initialized");
        return;
    }

    LV_LOG_INFO("begin");

    /*Initialize members of static variable lv_global */
    lv_global_init(LV_GLOBAL_DEFAULT());

    lv_mem_init();

    _lv_draw_buf_init_handlers();

#if LV_USE_SPAN != 0
    lv_span_stack_init();
#endif

#if LV_USE_PROFILER && LV_USE_PROFILER_BUILTIN
    lv_profiler_builtin_config_t profiler_config;
    lv_profiler_builtin_config_init(&profiler_config);
    lv_profiler_builtin_init(&profiler_config);
#endif

    _lv_timer_core_init();

    _lv_fs_init();

    _lv_layout_init();

    _lv_anim_core_init();

    _lv_group_init();

    lv_draw_init();

#if LV_USE_DRAW_SW
    lv_draw_sw_init();
#endif

#if LV_USE_DRAW_VGLITE
    lv_draw_vglite_init();
#endif

#if LV_USE_DRAW_PXP
    lv_draw_pxp_init();
#endif

    _lv_obj_style_init();

    /*Initialize the screen refresh system*/
    _lv_refr_init();

#if LV_USE_SYSMON
    _lv_sysmon_builtin_init();
#endif

    _lv_image_decoder_init();

    _lv_cache_init();
    _lv_cache_builtin_init();
    lv_cache_lock();
    lv_cache_set_max_size(LV_CACHE_DEF_SIZE);
    lv_cache_unlock();

    /*Test if the IDE has UTF-8 encoding*/
    const char * txt = "Á";

    uint8_t * txt_u8 = (uint8_t *)txt;
    if(txt_u8[0] != 0xc3 || txt_u8[1] != 0x81 || txt_u8[2] != 0x00) {
        LV_LOG_WARN("The strings have no UTF-8 encoding. Non-ASCII characters won't be displayed.");
    }

    uint32_t endianess_test = 0x11223344;
    uint8_t * endianess_test_p = (uint8_t *) &endianess_test;
    bool big_endian = endianess_test_p[0] == 0x11;

    if(big_endian) {
        LV_ASSERT_MSG(LV_BIG_ENDIAN_SYSTEM == 1,
                      "It's a big endian system but LV_BIG_ENDIAN_SYSTEM is not enabled in lv_conf.h");
    }
    else {
        LV_ASSERT_MSG(LV_BIG_ENDIAN_SYSTEM == 0,
                      "It's a little endian system but LV_BIG_ENDIAN_SYSTEM is enabled in lv_conf.h");
    }

#if LV_USE_ASSERT_MEM_INTEGRITY
    LV_LOG_WARN("Memory integrity checks are enabled via LV_USE_ASSERT_MEM_INTEGRITY which makes LVGL much slower");
#endif

#if LV_USE_ASSERT_OBJ
    LV_LOG_WARN("Object sanity checks are enabled via LV_USE_ASSERT_OBJ which makes LVGL much slower");
#endif

#if LV_USE_ASSERT_STYLE
    LV_LOG_WARN("Style sanity checks are enabled that uses more RAM");
#endif

#if LV_LOG_LEVEL == LV_LOG_LEVEL_TRACE
    LV_LOG_WARN("Log level is set to 'Trace' which makes LVGL much slower");
#endif

#if LV_USE_MSG
    lv_msg_init();
#endif

#if LV_USE_FS_FATFS != '\0'
    lv_fs_fatfs_init();
#endif

#if LV_USE_FS_STDIO != '\0'
    lv_fs_stdio_init();
#endif

#if LV_USE_FS_POSIX != '\0'
    lv_fs_posix_init();
#endif

#if LV_USE_FS_WIN32 != '\0'
    lv_fs_win32_init();
#endif

#if LV_USE_FS_MEMFS
    lv_fs_memfs_init();
#endif

#if LV_USE_LODEPNG
    lv_lodepng_init();
#endif

#if LV_USE_TJPGD
    lv_tjpgd_init();
#endif

#if LV_USE_BMP
    lv_bmp_init();
#endif

    /*Make FFMPEG last because the last converter will be checked first and
     *it's superior to any other */
#if LV_USE_FFMPEG
    lv_ffmpeg_init();
#endif

#if LV_USE_FREETYPE
    /*Init freetype library*/
#  if LV_FREETYPE_CACHE_SIZE >= 0
    lv_freetype_init(LV_FREETYPE_CACHE_FT_FACES, LV_FREETYPE_CACHE_FT_SIZES, LV_FREETYPE_CACHE_SIZE);
#  else
    lv_freetype_init(0, 0, 0);
#  endif
#endif

    lv_initialized = true;

    LV_LOG_TRACE("finished");
}

#if LV_ENABLE_GLOBAL_CUSTOM || LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN

void lv_deinit(void)
{
#if LV_USE_SYSMON
    _lv_sysmon_builtin_deinit();
#endif

    lv_display_set_default(NULL);

#if LV_USE_SPAN != 0
    lv_span_stack_deinit();
#endif

#if LV_USE_FREETYPE
    lv_freetype_uninit();
#endif

#if LV_USE_THEME_DEFAULT
    lv_theme_default_deinit();
#endif

#if LV_USE_THEME_BASIC
    lv_theme_basic_deinit();
#endif

#if LV_USE_THEME_MONO
    lv_theme_mono_deinit();
#endif

    lv_mem_deinit();

    lv_initialized = false;

    LV_LOG_INFO("lv_deinit done");

#if LV_USE_LOG
    lv_log_register_print_cb(NULL);
#endif
}
#endif

/**********************
 *   STATIC FUNCTIONS
 **********************/
