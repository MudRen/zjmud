// zhuxiao.c

#include <ansi.h>
#include <music.h>

inherit ITEM;
inherit MI_XIAO;

void create()
{
	set_name("����", ({ "zhuxiao" }));
	set_weight(300);

	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ������ͨͨ������������Ҳ�ܴ������˵����ӡ�\n");
		set("value", 10);
		set("material", "bamboo");
	}
	setup();
}

void init()
{
	add_action("play_xiao", "play");
}

int query_autoload() { return 1; }