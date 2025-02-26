/**
 * @file lv_tabview.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_tabview.h"
#if LV_USE_TABVIEW

#include "../../misc/lv_assert.h"
#include "../../indev/lv_indev_private.h"

/*********************
 *      DEFINES
 *********************/
#define MY_CLASS    &lv_tabview_class

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_tabview_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void lv_tabview_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void lv_tabview_event(const lv_obj_class_t * class_p, lv_event_t * e);
static void buttons_value_changed_event_cb(lv_event_t * e);
static void cont_scroll_end_event_cb(lv_event_t * e);

/**********************
 *  STATIC VARIABLES
 **********************/
const lv_obj_class_t lv_tabview_class = {
    .constructor_cb = lv_tabview_constructor,
    .destructor_cb = lv_tabview_destructor,
    .event_cb = lv_tabview_event,
    .width_def = LV_PCT(100),
    .height_def = LV_PCT(100),
    .base_class = &lv_obj_class,
    .instance_size = sizeof(lv_tabview_t)
};

typedef struct {
    lv_dir_t tab_pos;
    lv_coord_t tab_size;
} lv_tabview_create_info_t;

// only used in lv_obj_class_create_obj, no affect multiple instances
static lv_tabview_create_info_t create_info;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * lv_tabview_create(lv_obj_t * parent, lv_dir_t tab_pos, lv_coord_t tab_size)
{
    LV_LOG_INFO("begin");
    create_info.tab_pos = tab_pos;
    create_info.tab_size = tab_size;

    lv_obj_t * obj = lv_obj_class_create_obj(&lv_tabview_class, parent);
    lv_obj_class_init_obj(obj);
    return obj;
}

lv_obj_t * lv_tabview_add_tab(lv_obj_t * obj, const char * name)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_tabview_t * tabview = (lv_tabview_t *)obj;
    lv_obj_t * cont = lv_tabview_get_content(obj);

    lv_obj_t * page = lv_obj_create(cont);
    lv_obj_set_size(page, LV_PCT(100), LV_PCT(100));
    uint32_t tab_id = lv_obj_get_child_cnt(cont);

    lv_obj_t * buttons = lv_tabview_get_tab_buttons(obj);

    char ** old_map = tabview->map;
    char ** new_map;

    /*top or bottom dir*/
    if(tabview->tab_pos & LV_DIR_VER) {
        new_map = lv_malloc((tab_id + 1) * sizeof(const char *));
        lv_memcpy(new_map, old_map, sizeof(const char *) * (tab_id - 1));
        new_map[tab_id - 1] = lv_strdup(name);
        LV_ASSERT_MALLOC(new_map[tab_id - 1]);
        new_map[tab_id] = (char *)"";
    }
    /*left or right dir*/
    else {
        new_map = lv_malloc((tab_id * 2) * sizeof(const char *));
        lv_memcpy(new_map, old_map, sizeof(const char *) * (tab_id - 1) * 2);
        if(tabview->tab_cnt == 0) {
            new_map[0] = lv_strdup(name);
            LV_ASSERT_MALLOC(new_map[0]);
            new_map[1] = (char *)"";
        }
        else {
            new_map[tab_id * 2 - 3] = (char *)"\n";
            new_map[tab_id * 2 - 2] = lv_strdup(name);
            new_map[tab_id * 2 - 1] = (char *)"";
        }
    }
    tabview->map = new_map;
    lv_buttonmatrix_set_map(buttons, (const char **)new_map);
    lv_free(old_map);

    lv_buttonmatrix_set_button_ctrl_all(buttons, LV_BUTTONMATRIX_CTRL_CHECKABLE | LV_BUTTONMATRIX_CTRL_CLICK_TRIG |
                                        LV_BUTTONMATRIX_CTRL_NO_REPEAT);

    tabview->tab_cnt++;
    if(tabview->tab_cnt == 1) {
        lv_tabview_set_act(obj, 0, LV_ANIM_OFF);
    }

    lv_buttonmatrix_set_button_ctrl(buttons, tabview->tab_cur, LV_BUTTONMATRIX_CTRL_CHECKED);

    return page;
}

void lv_tabview_rename_tab(lv_obj_t * obj, uint32_t id, const char * new_name)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_tabview_t * tabview = (lv_tabview_t *)obj;

    if(id >= tabview->tab_cnt) return;
    if(tabview->tab_pos & LV_DIR_HOR) id *= 2;

    lv_free(tabview->map[id]);
    tabview->map[id] = lv_strdup(new_name);
    LV_ASSERT_MALLOC(tabview->map[id]);
    lv_obj_invalidate(obj);
}

void lv_tabview_set_act(lv_obj_t * obj, uint32_t id, lv_anim_enable_t anim_en)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_tabview_t * tabview = (lv_tabview_t *)obj;

    if(id >= tabview->tab_cnt) {
        id = tabview->tab_cnt - 1;
    }

    /*To be sure lv_obj_get_content_width will return valid value*/
    lv_obj_update_layout(obj);

    lv_obj_t * cont = lv_tabview_get_content(obj);
    if(cont == NULL) return;

    if((tabview->tab_pos & LV_DIR_VER) != 0) {
        lv_coord_t gap = lv_obj_get_style_pad_column(cont, LV_PART_MAIN);
        lv_coord_t w = lv_obj_get_content_width(cont);
        if(lv_obj_get_style_base_dir(obj, LV_PART_MAIN) != LV_BASE_DIR_RTL) {
            lv_obj_scroll_to_x(cont, id * (gap + w), anim_en);
        }
        else {
            int32_t id_rtl = -(int32_t)id;
            lv_obj_scroll_to_x(cont, (gap + w) * id_rtl, anim_en);
        }
    }
    else {
        lv_coord_t gap = lv_obj_get_style_pad_row(cont, LV_PART_MAIN);
        lv_coord_t h = lv_obj_get_content_height(cont);
        lv_obj_scroll_to_y(cont, id * (gap + h), anim_en);
    }

    lv_obj_t * buttons = lv_tabview_get_tab_buttons(obj);
    lv_buttonmatrix_set_button_ctrl(buttons, id, LV_BUTTONMATRIX_CTRL_CHECKED);
    tabview->tab_cur = id;
}

uint16_t lv_tabview_get_tab_act(lv_obj_t * obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_tabview_t * tabview = (lv_tabview_t *)obj;
    return tabview->tab_cur;
}

lv_obj_t * lv_tabview_get_content(lv_obj_t * tv)
{
    return lv_obj_get_child(tv, 1);
}

lv_obj_t * lv_tabview_get_tab_buttons(lv_obj_t * tv)
{
    return lv_obj_get_child(tv, 0);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void lv_tabview_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);
    lv_tabview_t * tabview = (lv_tabview_t *)obj;

    tabview->tab_pos = create_info.tab_pos;

    switch(tabview->tab_pos) {
        case LV_DIR_TOP:
            lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_COLUMN);
            break;
        case LV_DIR_BOTTOM:
            lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_COLUMN_REVERSE);
            break;
        case LV_DIR_LEFT:
            lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW);
            break;
        case LV_DIR_RIGHT:
            lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW_REVERSE);
            break;
    }

    lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));

    lv_obj_t * btnm;
    lv_obj_t * cont;

    btnm = lv_buttonmatrix_create(obj);
    cont = lv_obj_create(obj);

    lv_buttonmatrix_set_one_checked(btnm, true);
    tabview->map = lv_malloc(sizeof(const char *));
    tabview->map[0] = (char *)"";
    lv_buttonmatrix_set_map(btnm, (const char **)tabview->map);
    lv_obj_add_event(btnm, buttons_value_changed_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_flag(btnm, LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_add_event(cont, cont_scroll_end_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);

    switch(tabview->tab_pos) {
        case LV_DIR_TOP:
        case LV_DIR_BOTTOM:
            lv_obj_set_size(btnm, LV_PCT(100), create_info.tab_size);
            lv_obj_set_width(cont, LV_PCT(100));
            lv_obj_set_flex_grow(cont, 1);
            break;
        case LV_DIR_LEFT:
        case LV_DIR_RIGHT:
            lv_obj_set_size(btnm, create_info.tab_size, LV_PCT(100));
            lv_obj_set_height(cont, LV_PCT(100));
            lv_obj_set_flex_grow(cont, 1);
            break;
    }

    lv_group_t * g = lv_group_get_default();
    if(g) lv_group_add_obj(g, btnm);

    if((tabview->tab_pos & LV_DIR_VER) != 0) {
        lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);
        lv_obj_set_scroll_snap_x(cont, LV_SCROLL_SNAP_CENTER);
    }
    else {
        lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_scroll_snap_y(cont, LV_SCROLL_SNAP_CENTER);
    }
    lv_obj_add_flag(cont, LV_OBJ_FLAG_SCROLL_ONE);
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
}

static void lv_tabview_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);
    lv_tabview_t * tabview = (lv_tabview_t *)obj;

    uint32_t i;
    if(tabview->tab_pos & LV_DIR_VER) {
        for(i = 0; i < tabview->tab_cnt; i++) {
            lv_free(tabview->map[i]);
            tabview->map[i] = NULL;
        }
    }
    if(tabview->tab_pos & LV_DIR_HOR) {
        for(i = 0; i < tabview->tab_cnt; i++) {
            lv_free(tabview->map[i * 2]);
            tabview->map[i * 2] = NULL;
        }
    }


    lv_free(tabview->map);
    tabview->map = NULL;
}

static void lv_tabview_event(const lv_obj_class_t * class_p, lv_event_t * e)
{
    LV_UNUSED(class_p);
    lv_result_t res = lv_obj_event_base(&lv_tabview_class, e);
    if(res != LV_RESULT_OK) return;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);

    if(code == LV_EVENT_SIZE_CHANGED) {
        lv_tabview_set_act(target, lv_tabview_get_tab_act(target), LV_ANIM_OFF);
    }
}


static void buttons_value_changed_event_cb(lv_event_t * e)
{
    lv_obj_t * buttons = lv_event_get_target(e);

    lv_obj_t * tv = lv_obj_get_parent(buttons);
    uint32_t id = lv_buttonmatrix_get_selected_button(buttons);
    lv_tabview_set_act(tv, id, LV_ANIM_OFF);
}

static void cont_scroll_end_event_cb(lv_event_t * e)
{
    lv_obj_t * cont = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);

    lv_obj_t * tv = lv_obj_get_parent(cont);
    lv_tabview_t * tv_obj = (lv_tabview_t *)tv;
    if(code == LV_EVENT_LAYOUT_CHANGED) {
        lv_tabview_set_act(tv, lv_tabview_get_tab_act(tv), LV_ANIM_OFF);
    }
    else if(code == LV_EVENT_SCROLL_END) {
        lv_indev_t * indev = lv_indev_get_act();
        if(indev && indev->state == LV_INDEV_STATE_PRESSED) {
            return;
        }

        lv_point_t p;
        lv_obj_get_scroll_end(cont, &p);

        lv_coord_t t;
        if((tv_obj->tab_pos & LV_DIR_VER) != 0) {
            lv_coord_t w = lv_obj_get_content_width(cont);
            if(lv_obj_get_style_base_dir(tv, LV_PART_MAIN) == LV_BASE_DIR_RTL)  t = -(p.x - w / 2) / w;
            else t = (p.x + w / 2) / w;
        }
        else {
            lv_coord_t h = lv_obj_get_content_height(cont);
            t = (p.y + h / 2) / h;
        }

        if(t < 0) t = 0;
        bool new_tab = false;
        if(t != lv_tabview_get_tab_act(tv)) new_tab = true;


        /*If not scrolled by an indev set the tab immediately*/
        if(lv_indev_get_act()) {
            lv_tabview_set_act(tv, t, LV_ANIM_ON);
        }
        else {
            lv_tabview_set_act(tv, t, LV_ANIM_OFF);
        }

        if(new_tab) lv_obj_send_event(tv, LV_EVENT_VALUE_CHANGED, NULL);
    }
}
#endif /*LV_USE_TABVIEW*/
