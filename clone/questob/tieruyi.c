// tieruyi.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("������", ({ "tie ruyi", "ruyi" }));
	set_weight(300);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�������⣬�ڲ�����ģ��������ۡ�\n");
		set("value", 1000);
		set("material", "iron");
	}
	setup();
}
