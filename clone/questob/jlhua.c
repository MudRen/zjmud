// jlhua.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("���λ�", ({ "jinlou hua", "hua" }));
	set_weight(400);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ���ý𲭵�̵Ļ�������������\n");
		set("value", 12000);
		set("material", "gold");
	}
	setup();
}
