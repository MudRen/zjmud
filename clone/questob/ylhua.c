// ylhua.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("���λ�", ({ "yinlou hua", "hua" }));
	set_weight(300);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ����������̵Ļ�������������\n");
		set("value", 4000);
		set("material", "silver");
	}
	setup();
}
