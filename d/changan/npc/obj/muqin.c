// muqin.c

#include <ansi.h>
#include <music.h>

inherit ITEM;
inherit MI_QIN;

void create()
{
	set_name("ľ��", ({ "muqin" }));
	set_weight(600);

	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "̨");
		set("long", "һ��ƽ����ľ�٣�û��ʲô����֮����\n");
		set("value", 50);
		set("material", "wood");
	}
	setup();
}

void init()
{
	add_action("play_qin", "play");
}
