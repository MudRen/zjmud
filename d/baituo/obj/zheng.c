// zheng.c

#include <ansi.h>
#include <music.h>

inherit ITEM;
inherit MI_ZHENG;

void create()
{
	set_name("����", ({ "guzheng" }));
	set_weight(300);
	
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "̨");
		set("long", "һ̨����ȥ��Щ�¾ɵĹ��ݡ�\n");
		set("value", 50);
		set("material", "wood");
	      set("icon","01028");
	}
	setup();
}

void init()
{
	add_action("play_zheng", "play");
}
