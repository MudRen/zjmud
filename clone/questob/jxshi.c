// jxshi.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("��Ѫʯ", ({ "jixue shi", "shi" }));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�鰵��ɫ�ļ�Ѫʯ��\n");
		set("value", 1500);
		set("material", "stone");
	}
	setup();
}
