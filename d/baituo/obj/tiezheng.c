// tiezheng.c

#include <ansi.h>
#include <music.h>

inherit ITEM;
inherit MI_ZHENG;

void create()
{
	set_name("����", ({ "tiezheng" }));
	set_weight(300);

	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "̨");
		set("long", "һ̨����������ݡ�\n");
		set("value", 5000);
		set("material", "steel");
	}
	setup();
}

void init()
{
	add_action("play_zheng", "play");
}
