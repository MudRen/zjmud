// sjping.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("�ļ�ƿ", ({ "sijian ping", "ping" }));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ����ʯƿ�ӣ�����ȥͦ�����۵ġ�\n");
		set("value", 1000);
		set("material", "stone");
	}
	setup();
}
