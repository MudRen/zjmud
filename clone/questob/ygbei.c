// ygbei.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("ҹ�Ɑ", ({ "ye guangbei", "cup", "bei" }));
	set_weight(400);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "ֻ");
		set("long", "����һֻ����ʵصľƱ���\n");
		set("value", 10000);
		set("material", "jade");
	}
	setup();
}
